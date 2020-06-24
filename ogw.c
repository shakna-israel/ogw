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

  TCCState *s;
  s = tcc_new();
  if (!s) {
    fprintf(stderr, "OGW ERROR: Could not initialise compiler.\n");
    return 1;
  }

  /* MUST BE CALLED before any compilation */
  tcc_set_output_type(s, TCC_OUTPUT_MEMORY);

  // TODO:
  // Prepend evil_h[] to a string.
  // Append the user's supplied program to the same string.

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

  if (tcc_compile_string(s, program) == -1) {
    fprintf(stderr, "OGW ERROR: Failed to compile program.\n");
    return 1;
  }

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
