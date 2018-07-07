#ifndef FILEIO_H
#define FILEIO_H

#include "main.h"
#include <stdio.h>


int searchForFile(char *dname, char *fname);
FILE *openFile(char *fname, char *mode);
void writeToFile(int *A, int len, writeMode wrmode, char *dnamew, char *fnamew);

#endif