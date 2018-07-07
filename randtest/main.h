#ifndef MAIN_H
#define MAIN_H

typedef enum {
  std_out,
  file
} outputMode;

typedef enum {
  overwrite,
  append,
  nowrite
} writeMode;

void writeToStdOut(int *A, int len);
writeMode promptFileExists(char *fnamew);

#endif