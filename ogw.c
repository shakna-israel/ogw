#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <libtcc.h>

#include <libgen.h>

#include <evil_build.h>
/*
  Supplies:
  unsigned char evil_h[]
  unsigned int evil_h_len
*/

#include <MT19937.h>
/*
  Supplies our random functions...
*/

TCCState *s;
int run_mode;

int main(int argc, char* argv[]) {

  if(argc < 2) {
    fprintf(stderr, "OGW ERROR: No input file supplied.\n");
    return 1;
  }

  if(argc < 3) {
    fprintf(stderr, "OGW ERROR: No output file supplied.\n");
    return 1;
  }

  // Choose to eval or compile
  if(strncmp(argv[1], "-run", FILENAME_MAX) == 0) {
    run_mode = TCC_OUTPUT_MEMORY;
  } else {
    run_mode = TCC_OUTPUT_EXE;
  }

  FILE* openFile;
  if(run_mode == TCC_OUTPUT_MEMORY) {
    openFile = fopen(argv[2], "r");
  } else {
    openFile = fopen(argv[1], "r");
  }

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
  tcc_set_output_type(s, run_mode);

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
  if(!program) {
    fprintf(stderr, "OGW ERROR: Unable to allocate space for the program\n");
    return 1;
  }

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

  // This accepts a ; seperated string.
  char* units = getenv("UNITS");
  if(units != NULL) {
    char* chunk;
    chunk = strtok(units, ";");
    while(chunk != NULL) {
      tcc_add_file(s, chunk);
      chunk = strtok(NULL, ";");
    }
  }

  // Check for a libraries.txt file relative to
  // the file being executed, not the current working directory.

  char* dir = dirname(argv[1]);
  size_t dir_len = strnlen(dir, FILENAME_MAX);

  size_t path_size = dir_len + 15;

  char* libraries_txt_path = calloc(path_size, sizeof(char));

  if(!libraries_txt_path) {
    fprintf(stderr, "OGW ERROR: Unable to allocate space for libraries.txt path.");
    return 1;
  }

  for(size_t i = 0; i < dir_len; i++) {
    libraries_txt_path[i] = dir[i];
  }
  strcat(libraries_txt_path, "/libraries.txt");

  // This is a line-deliminated series of libraries
  FILE* req_file = fopen(libraries_txt_path, "r");
  if(req_file != NULL) {
    char* buffer = calloc(FILENAME_MAX, sizeof(char));
    if(!buffer) {
      fprintf(stderr, "OGW ERROR: Unable to allocate space for library name.\n");
      return 1;
    }

    if (fgets(buffer, FILENAME_MAX, req_file) != NULL) {
      // Remove trailing new line if it exists
      buffer[strcspn(buffer, "\n")] = 0;
      tcc_add_library(s, buffer);
    }
    fclose(req_file);
    free(buffer);
  }
  free(libraries_txt_path);

  // Check for a units.txt file relative to
  // the file being executed, not the current working directory.

  path_size = dir_len + 11;

  char* units_txt_path = calloc(path_size, sizeof(char));

  if(!units_txt_path) {
    fprintf(stderr, "OGW ERROR: Unable to allocate space for units.txt path.");
    return 1;
  }

  for(size_t i = 0; i < dir_len; i++) {
    units_txt_path[i] = dir[i];
  }
  strcat(units_txt_path, "/units.txt");

  // This is a line-deliminated series of libraries
  req_file = fopen(units_txt_path, "r");
  if(req_file != NULL) {
    char* buffer = calloc(FILENAME_MAX, sizeof(char));
    if(!buffer) {
      fprintf(stderr, "OGW ERROR: Unable to allocate space for unit filename.\n");
      return 1;
    }

    if (fgets(buffer, FILENAME_MAX, req_file) != NULL) {
      // Remove trailing new line if it exists
      buffer[strcspn(buffer, "\n")] = 0;
      tcc_add_file(s, buffer);
    }
    fclose(req_file);
    free(buffer);
  }
  free(units_txt_path);

  // TODO: We should be able to set INCLUDE_PATHS, LIBRARY_PATHS
  // somehow else. Maybe we could add a mandatory header to the file or something?

  /* Compile the program */
  if (tcc_compile_string(s, program) == -1) {
    fprintf(stderr, "OGW ERROR: Failed to compile program.\n");
    return 1;
  }

  /* TODO: Expose any helpers */
  //tcc_add_symbol(s, "name", function);
  tcc_add_symbol(s, "randomseed", init_genrand);
  tcc_add_symbol(s, "randomint", genrand_int32);
  tcc_add_symbol(s, "randomint_31", genrand_int31);
  tcc_add_symbol(s, "randomreal", genrand_real1);
  tcc_add_symbol(s, "randomreal_2", genrand_real2);
  tcc_add_symbol(s, "randomreal_3", genrand_real2);
  tcc_add_symbol(s, "randomreal_53", genrand_res53);

  // If we're compiling, create an executable and exit.
  if(run_mode == TCC_OUTPUT_EXE) {
    if(tcc_output_file(s, argv[2]) < 0) {
      fprintf(stderr, "OGW ERROR: Failed to output executable file.\n");
      return 1;
    }

    // Cleanup
    tcc_delete(s);
    free(program);

    return 0;
  }

  // relocate the code
  if (tcc_relocate(s, TCC_RELOCATE_AUTO) < 0) {
    fprintf(stderr, "OGW ERROR: Unable to initialise executable memory.\n");
    return 1;
  }

  // This should have the same signature as main(argc, argv)
  int (*func)(int, char**);

  // Get the entry point
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
  return 0;
}
