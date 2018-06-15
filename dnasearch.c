#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "dnasearch.h"

/* The functions for working with the dnasearch program,
    including the creation of a linked list for dynamic
    entry of patterns by the user
*/

// Create an input element of the pattern the user wants to search for
User_Input * Create(char c[]) {
  User_Input * u = malloc(sizeof(User_Input));
  assert(u);
  u->next = NULL;
  u->user_pattern = malloc(strlen(c)*sizeof(char));
  strcpy((u->user_pattern), c);
  return u;
}

// void MakeHead(User_Input ** head, char c[]) {
//   User_Input * new_head = Create(c);
//
// }

// Insert another input element in the list after the last one
void InsertAfter(User_Input * u, char * c) {
  User_Input * new_u = Create(c);
  new_u->next = u->next;
  strcpy((new_u->user_pattern), c);
  u->next = new_u;
}

// Check that the char trying to be read in is valid
/*  Returns
    1: char is either C, A, T, of G, of upper or lower case
    0: char is a whitespace or newline character
    -1: char is invalid
*/
int CheckValidChar(char c) {
  char big_c = (char)toupper(c);
  if (big_c == 'C' || big_c == 'A' || big_c == 'T' || big_c == 'G') {
    return 1;
  } else if (big_c == ' ' || big_c == '\n') {
    return 0;
  } else {
    return -1;
  }
}

// Read in the characters in the file into the sequence array
/*
  Inputs:
    fp: pointer to text file with dna sequence
    sequence: pointer to char array for sequence
    num_bases: the number of valid bases found
  Returns
    num_bases>1: success at reading entire file
    0: failed to read in file, or the file had not bases in it
*/
int ReadFile(FILE *fp, char *sequence, int num_bases) {
  char c = fgetc(fp);
  while(!feof(fp)) {
    int validity = CheckValidChar(c);
    switch (validity) {
      case 1:
        *(sequence+num_bases) = (char)toupper(c);
        num_bases += 1;
        printf("Just read in: %c\n", c);
        break;
      case 0:
        //printf("Just read in a space or newline\n");
        break;
      case -1:
        return 0;
    }
    c = fgetc(fp);
  }
  if (num_bases == 0) {
    printf("Error: failed to read in file\n");
    return 0;
  }
  return num_bases;//function succeeded and at least one valid char was read in
}

// Read in each user input (space delimited) into the patterns array of strings
// which holds up to 50 strings that are each at most 100 chars long
/*
  Returns
    int: the number of input patterns read in
*/
int ReadInputs(char patterns[][SMALL_MAX_PATTERN_SIZE], int num_patterns) {
  char buffer[500];
  while (fgets(buffer, 500, stdin) != NULL) { //read in the line
    char temp_pattern[SMALL_MAX_PATTERN_SIZE];
    if (scanf("%s\n", temp_pattern) == 0) {
      printf("Failed to read in line of pattern inputs\n");
      return -1;
    }
    strcpy(patterns[num_patterns], temp_pattern);
    num_patterns += 1;
    // NEED TO BE ABLE TO COPY MORE THAN JUST ONE PATTERN FROM THE LINE
  }
  return num_patterns
}
