# Intermediate-HW4
  From Gabe's Intermediate Programming Homeworks Spring 2017

  This program loads a DNA sequence from a text file and searches for shorter
  patterns of DNA sequences specified by the user at stdin.

  To run:
  make
  ./hw4 "dnasequence.txt"
  "DNA sequences, separated by any amount of whitespace"
    For example: GCA GGATA  GCaa aat
    Note: inputs can be lower- or uppercase

  Outputs:
  The program will output each pattern input by the user, followed by each index location within the dnasequence.txt file where the pattern matches the larger sequence.
    For example:
    GCA 2 8 50
    GGATA 15
    GCaa Not found
    aat 34
