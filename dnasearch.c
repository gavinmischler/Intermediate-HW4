#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
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
