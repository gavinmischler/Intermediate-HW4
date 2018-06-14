#ifndef DNASEARCH_H
#define DNASEARCH_H

#define MAX_PATTERN_SIZE 15000

// Linked List structures
typedef struct _UserInput
{
  struct _UserInput * next;
  char * user_pattern;

} User_Input;

User_Input * Create(char c[]);
void InsertAfter(User_Input * u, char c[]);

int CheckValidChar(char c);
int ReadFile(FILE *fp, char *sequence, int num_bases);

#endif //DNASEARCh_H included
