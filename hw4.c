#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "dnasearch.h"



int main(int argc, char const *argv[]) {
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
  return 0;
}
