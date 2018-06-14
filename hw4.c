#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "dnasearch.h"



int main(int argc, char const *argv[]) {

  // Store the filepath that the user input from the command line
  char *filepath;
  if (argc == 2) {
    filepath = malloc(strlen(argv[1]+1));
    strcpy(filepath, argv[1]);
  } else {
    printf("Error: Not the right number of input arguments. Specify the path to the DNA test sequence text file.\n");
    return -1;
  }

  char *sequence = malloc(MAX_PATTERN_SIZE*sizeof(char));
  FILE *fp = fopen(filepath, "r");
  if (fp == NULL) {
    printf("Error: failed to open input file\n");
    return -1;
  }
  // } else {
  //   if (!ReadFile(fp, ))
  // }
  int num_found = ReadFile(fp, sequence, 0);
  printf("Scanned in: %d\n", num_found);


  // Linked list testing
  User_Input *head = NULL, *u;
  printf("Testing\n");
  char s1[6] = "hello";
  char s2[3] = "hi";
  char s3[15] = "howdy partner";
  head = Create(s1);
  InsertAfter(head, s2);
  InsertAfter(head->next, s3);
  printf("head pattern: %s\n",head->user_pattern);
  printf("s2 pattern: %s\n",head->next->user_pattern);
  printf("s3 pattern: %s\n",head->next->next->user_pattern);

  free(sequence);
  return 0;
}
