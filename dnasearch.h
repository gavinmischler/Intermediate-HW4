#ifndef DNASEARCH_H
#define DNASEARCH_H

#define MAX_PATTERN_SIZE 15000
#define SMALL_MAX_PATTERN_SIZE 100

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
int ReadInputs(char patterns[][SMALL_MAX_PATTERN_SIZE], int num_patterns, unsigned int filelength);
int CheckValidPattern(char pattern[], unsigned int filelength);
int FindPattern(char pattern[], char *sequence, int* indeces, unsigned int filelength);
#endif //DNASEARCh_H included
