// Copyright 2021 Alec Keehbler

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 128

static void exit_with_error() {
  printf("my-look: invalid command line\n");
  exit(1);
}

int main(int argc, char* argv[]) {
  int opt;
  char *filename;
  FILE *fp;
  while ((opt = getopt(argc, argv, "Vhf:")) != -1) {
    switch (opt) {
      // Prints information about this utility
      case 'V':
        printf("my-look from CS537 Spring 2021\n");
        exit(0);
        break;
      // Prints help information about this utility
      case 'h':
        printf("./my-look [-V] [-h] [-f filename] word\n");
        exit(0);
        break;
      // Read a file full of words to check
      case 'f':
        filename = optarg;
        fp = fopen(filename, "r");
        if (fp == NULL) {
          printf("my-look: cannot open file\n");
          exit(1);
        }
        break;
      default:
        exit_with_error();
    }
  }
  // Checks for wrong number of command line arguments
  if (optind != argc - 1) {
    exit_with_error();
  }
  // If the -f tag was not specified then read from stdin
  if (fp == NULL) {
    fp = stdin;
  }
  char buffer[BUFFER_SIZE];
  int result;
  // Goes word by word checking if there is a match
  while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
    result = strncasecmp(argv[argc - 1], buffer, strlen(argv[argc - 1]));
    if (result == 0) {
      printf("%s", buffer);
    }
  }
  fclose(fp);
  exit(0);
}

