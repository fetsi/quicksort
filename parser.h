#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

typedef struct {
  int lines;
  int longest;
} lineInfo;

typedef struct {
  int *ptr;
  int len;
} arrayInfo;

arrayInfo readListFromFile(char *fname);
lineInfo countLines(FILE *fptr);

#endif

