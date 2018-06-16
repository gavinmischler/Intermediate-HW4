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
    return 0;
  }
  return num_bases;//function succeeded and at least one valid char was read in
}

// Checks a user-input pattern to make sure it is valid
/*
  Returns
    int 1 if valid
    int 0 if not valid
*/
int CheckValidPattern(char pattern[], unsigned int filelength) {
  if (strlen(pattern) > filelength) {
    printf("String too long\n");
    return 0;
  }
  int sz = strlen(pattern);
  printf("pattern: %s has size: %d\n", pattern, sz);
  for (int i = 0; i < sz; i++) {
    if (CheckValidChar(pattern[i]) != 1) {
      printf("%d Invalid char: %c\n", i, pattern[i]);
      return 0;
    }
  }
  return 1;
}

// Read in each user input (space delimited) into the patterns array of strings
// which holds up to 50 strings that are each at most 100 chars long
/*
  Returns
    int: the number of input patterns read in
    0 if invalid pattern
*/
int ReadInputs(char patterns[][SMALL_MAX_PATTERN_SIZE], int num_patterns, unsigned int filelength) {
  char buffer[500];
  if (fgets(buffer, 500, stdin) != NULL) { //read in the line
    printf("length is: %lu\n", strlen(buffer));
    char * token;
    char delim[2] = " ";
    token = strtok(buffer, delim);
    while (token != NULL) {
      strcpy(patterns[num_patterns], token);
      num_patterns += 1;
      token = strtok(NULL, delim);
    }
    // NEED TO BE ABLE TO COPY MORE THAN JUST ONE PATTERN FROM THE LINE
  }
  printf("num_patterns: %d\n", num_patterns);
  if (num_patterns > 0) {
    // Remove newline character from last input
    strtok(patterns[num_patterns-1], "\n");
  }
  // Check that each pattern is valid
  for (int i = 0; i < num_patterns; i++) {
    printf("checking pattern: %s\n", patterns[i]);
    if (!CheckValidPattern(patterns[i], filelength)) {
      printf("Invalid pattern\n");
      return 0;
    }
  }

  return num_patterns;
}

// Search for the pattern within the sequence array
/*
  Returns
    the number of indeces found
*/
int FindPattern(char pattern[], char *sequence, int* indeces, unsigned int filelength) {
  int num_indeces_found = 0;
  int j;
  int k;
  for (unsigned int i = 0; i < filelength; i++) {
    printf("checking %c against %c\n", pattern[0], *(sequence+i));
    if ((char)toupper(pattern[0]) == *(sequence+i)) { //first char matches
      printf("first char matched at %u\n", i);
      int pattern_len = strlen(pattern);
      for (j = 0, k = 0; j < pattern_len; j++, k++) { //compare the rest of the chars in the pattern
        printf("j = %d, k = %d\n", j, k);
        if ((char)toupper(pattern[j]) != *(sequence+i+k)) {
          printf("%c was not equal to %c\n", pattern[j], *(sequence+i+k));
          break;
        }
      }
      printf("j is now: %d\n", j);
      if (j == pattern_len) { //found
        printf("original value in indeces array %d\n", *(indeces+num_indeces_found));
        *(indeces+num_indeces_found) = i;
        printf("just saved the index of %d\n", *(indeces+num_indeces_found));
        num_indeces_found += 1;
      }
    }
  }

  printf("first index: %d\n", *indeces);

  return num_indeces_found;
}
