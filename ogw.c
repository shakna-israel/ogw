#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <libtcc.h>

#include <evil_build.h>
/*
  Supplies:
  unsigned char evil_h[]
  unsigned int evil_h_len
*/

TCCState *s;

int main(int argc, char* argv[]) {

  if(argc < 2) {
    fprintf(stderr, "OGW ERROR: No file supplied.\n");
    return 1;
  }

  FILE* openFile = fopen(argv[1], "r");
  if(!openFile) {
    fprintf(stderr, "OGW ERROR: Unable to read file.\n");
    return 1;
  }

  s = tcc_new();
  if (!s) {
    fprintf(stderr, "OGW ERROR: Could not initialise compiler.\n");
    return 1;
  }

  /* MUST BE CALLED before any compilation */
  tcc_set_output_type(s, TCC_OUTPUT_MEMORY);

  // Add some handy include paths...
  tcc_add_include_path(s, "."); // Current folder
  tcc_add_include_path(s, "include"); // ./include folder

  // Build our program...

  // Length of our header, and to newlines for the base size...
  size_t size = evil_h_len + 2;

  // Get the file size...
  fseek(openFile, 0L, SEEK_END);
  size += (size_t)ftell(openFile);
  fseek(openFile, 0L, SEEK_SET);

  char* program = calloc(size + 1, sizeof(char));

  // Copy in our header...
  for(size_t i = 0; i < evil_h_len; i++) {
    program[i] = (char)evil_h[i];
  }
  program[evil_h_len] = '\n';
  program[evil_h_len + 1] = '\n';

  // Copy in the user's file...
  size_t cur = evil_h_len + 2;
  int c = 0;
  do {
    c = fgetc(openFile);
    if(c != EOF) {
      program[cur] = (char)c;
      cur++;
    }
  } while(c != EOF);

  // This accepts a ; seperated string.
  char* include_path = getenv("INCLUDE_PATHS");
  if(include_path != NULL) {
    tcc_add_include_path(s, include_path);
  }

  // This accepts a ; seperated string.
  char* library_path = getenv("LIBRARY_PATHS");
  if(library_path != NULL) {
    tcc_add_library_path(s, library_path);
  }

  // This accepts a ; seperated string.
  char* libraries = getenv("LIBRARIES");
  if(libraries != NULL) {
    char* chunk;
    chunk = strtok(libraries, ";");
    while(chunk != NULL) {
      tcc_add_library(s, chunk);
      chunk = strtok(NULL, ";");
    }
  }

  // TODO: Library name length limit?
  #define LIBRARY_NAME_LENGTH_LIMIT 200

  // This is a line-deliminated series of libraries
  FILE* req_file = fopen("libraries.txt", "r");
  if(req_file != NULL) {
    char buffer[LIBRARY_NAME_LENGTH_LIMIT];
    if (fgets(buffer, LIBRARY_NAME_LENGTH_LIMIT, req_file) != NULL) {
      // Remove trailing new line if it exists
      buffer[strcspn(buffer, "\n")] = 0;
      tcc_add_library(s, buffer);
    }
    fclose(req_file);
  }

  // TODO: We should be able to set INCLUDE_PATHS, LIBRARY_PATHS and LIBRARIES
  // somehow else. Maybe we could add a mandatory header to the file or something?

  /* Compile the program */
  if (tcc_compile_string(s, program) == -1) {
    fprintf(stderr, "OGW ERROR: Failed to compile program.\n");
    return 1;
  }

  /* TODO: Expose any helpers */
  //tcc_add_symbol(s, "name", function);

  /* relocate the code */
  if (tcc_relocate(s, TCC_RELOCATE_AUTO) < 0) {
    fprintf(stderr, "OGW ERROR: Unable to initialise executable memory.\n");
    return 1;
  }

  // This should have the same signature as main(argc, argv)
  int (*func)(int, char**);

  /* Get the entry point */
  func = tcc_get_symbol(s, "main");
  if (!func) {
    fprintf(stderr, "OGW ERROR: Unable to find `Main`.\n");
    return 1;
  }

  // Execute the user's code...
  int r = func(argc, argv);

  // Cleanup...
  tcc_delete(s);
  free(program);

  // Return the exit status of the program.
  return r;
}
