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
    printf("Invalid text file\n");
    return -1;
  }

  char *sequence = malloc(MAX_PATTERN_SIZE*sizeof(char));
  FILE *fp = fopen(filepath, "r");
  if (fp == NULL) {
    printf("Error: failed to open input file\n");
    return -1;
  }
  unsigned int num_found = ReadFile(fp, sequence, 0);
  if (num_found == 0) {
    printf("Invalid text file\n");
    return -1;
  }
  // printf("Scanned in: %d\n", num_found);
  // printf("G should be: %c\n", *(sequence+2));


  // Read in the user's list of patterns they want to search for into the patterns array
  int num_patterns = 0;
  char patterns[50][SMALL_MAX_PATTERN_SIZE];
  num_patterns = ReadInputs(patterns, num_patterns, num_found);
  if (num_patterns == 0) {
    return -1;
  }
  printf("num patterns found: %d\n", num_patterns);
  for (int i = 0; i < num_patterns; i++) {
    printf("%s\n", patterns[i]);
  }

  for (int i = 0; i < num_patterns; i++) {

    int* indeces = malloc(num_found*sizeof(int));
    int num_indeces_found = FindPattern(patterns[0], sequence, indeces, num_found);
    printf("found %s at %d\n", patterns[0], *indeces);
    free(indeces);
  }

  // Linked list testing
  // User_Input *head = NULL, *u;
  // printf("Testing\n");
  // char s1[6] = "hello";
  // char s2[3] = "hi";
  // char s3[15] = "howdy partner";
  // head = Create(s1);
  // InsertAfter(head, s2);
  // InsertAfter(head->next, s3);
  // printf("head pattern: %s\n",head->user_pattern);
  // printf("s2 pattern: %s\n",head->next->user_pattern);
  // printf("s3 pattern: %s\n",head->next->next->user_pattern);

  free(sequence);
  return 0;
}
