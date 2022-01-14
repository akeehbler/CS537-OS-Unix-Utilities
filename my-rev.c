// Copyright 2021 Alec Keehbler
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 128

static void exit_with_error() {
  printf("my-rev: invalid command line\n");
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
        printf("my-rev from CS537 Spring 2021\n");
        exit(0);
        break;
     // Prints help information about this utility
      case 'h':
        printf("./my-rev [-V] [-h] [-f filename] \n");
        exit(0);
        break;
      // Deals with file input and will reverse all lines in the file
      case 'f':
        filename = optarg;
        fp = fopen(filename, "r");
        if (fp == NULL) {
          printf("my-rev: cannot open file\n");
          exit(1);
        }
      break;
      // Deals with incorrect command line
      default:
        exit_with_error();
        break;
    }
  }
  // Deals with incorrect number of command line arguments
  if (optind != argc) {
    exit_with_error();
  }
  // Read from stdin if there is no file given
  if (fp == NULL) {
    fp = stdin;
  }
  char buffer[BUFFER_SIZE];
  int i, l;
  char *begin, *end, ch;
  int removed;
  while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
    removed = 0;
    // Remove new line and add it back in later
    if (buffer[strlen(buffer) - 1] == '\n') {
      buffer[strlen(buffer) - 1] = '\0';
      removed = 1;
    }
    l = strlen(buffer);
    begin = buffer;
    end = buffer;
    // Move end pointer to the end of the string
    for (i = 0; i < l -1; i++) {
      end++;
    }
    // Reverses the string
    for (i = 0; i < l/2; i++) {
      ch = *end;
      *end = *begin;
      *begin = ch;
      begin++;
      end--;
    }
    // Print reversed string and print new line if it was removed
    printf("%s", buffer);
    if (removed ==1) {
      printf("\n");
    }
  }
  fclose(fp);
  exit(0);
}

