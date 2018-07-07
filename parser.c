#include "fileIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "quicksort.h"






/*Reads the contents of the list that is to be sorted from a file
 *specified by the user, copies the contents to an int array and
 * returns a pointer to the array*/
arrayInfo readListFromFile(char *fname) {
  arrayInfo ai = {NULL, 0};
  FILE *fptr = openFile(fname, "r");
  lineInfo li = countLines(fptr);
  //Move FILE pointer back to the start of file
  rewind(fptr);
  
  if (li.lines == 0) {
    return ai;
  }
  //Create an array where the contents of the file are placed
  int *A = (int*)malloc(li.lines * sizeof(int));
  if(A == NULL) {
    printf("Couldn't allocate memory for the array\n");
    return ai;
  }

  //Create line buffer
  int bufSize = li.longest + 1;
  char buf[bufSize];

  //Read file line by line into the array
  for(int i = 0; i <= li.lines-1; ++i) {
    if(fgets(buf, bufSize, fptr) != NULL) {
      //Remove trailing newline
      buf[strcspn(buf, "\n")] = 0;
      A[i] = (int)strtol(buf, NULL, 10);
    }
  }
  ai.ptr = A;
  ai.len = li.lines;
  return ai; 
}



/*Scans the file looking for newline characters. Returns a struct containing
*the number of lines in the file and length of the longest line found in the file*/
lineInfo countLines(FILE *fptr) {
  int c;
  int content = 0;
  int lines = 0;
  int longest = 0;
  int len = 0;
  lineInfo li;
  while(1) {
    c = fgetc(fptr);
    //Check for End-Of-File
    if(feof(fptr)) {
      if(content && (lines == 0)) lines = 1;
      break;
    }
    ++len;
    
    //There is at least 1 char in the file, so there is at least 1 line
    if(!content){
      content = 1;
    }

    if(c == '\n') {
      ++lines;
      //Check to see if this is the longest line yet
      if(len > longest) longest = len;
      //Reset line lenght because this is the end of the line
      len = 0;
    }
  }
  li.lines = lines;
  li.longest = longest;
  return li;
}

