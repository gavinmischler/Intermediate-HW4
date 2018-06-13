#ifndef DNASEARCH_H
#define DNASEARCH_H

#define MAX_PATTERN_SIZE

typedef struct _UserInput
{
  struct _UserInput * next;
  char * user_pattern;

} User_Input;

User_Input * Create(char c[]);
void InsertAfter(User_Input * u, char c[]);

#endif //DNASEARCh_H included
