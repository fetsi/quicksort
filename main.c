#include "parser.h"
#include "quicksort.h"
#include "fileIO.h"
#include "main.h"
#include <stdlib.h>
#include <stdio.h>





int main(int argc, char *argv[] ) {

  outputMode outpmode;
  char *fnamer = NULL;
  char *dnamew = NULL;
  char *fnamew = NULL;

  switch(argc) {
    case 2:
      outpmode = std_out;
      fnamer = argv[1];
      break;
    case 4:
      outpmode = file;
      fnamer = argv[1];
      dnamew = argv[2];
      fnamew = argv[3];
      break;
    default:
        printf("Wrong number of arguments. Usage: execname readfilepath\nOR execname readfilepath dirofwritefile nameofwritefile\n");
        exit(1);
  }

  arrayInfo ai = readListFromFile(fnamer);
  if(ai.ptr == NULL || ai.len == 0) {
    //No contents in file, just exit without outputting anything
    return 0;
  }

  int *A = ai.ptr;
  int len = ai.len;
  
  //Sort the array
  quickSort(A, 0, len-1);

  switch(outpmode) {
    case std_out:
      writeToStdOut(A, len);
      break;

    case file: {
      writeMode wrmode;
      if( searchForFile(dnamew, fnamew) ) {
        //File already exists, ask user what to do
        wrmode = promptFileExists(fnamew);
      } else {
        wrmode = overwrite;
      }
      writeToFile(A, len, wrmode, dnamew, fnamew);
      break;
    }

    default:
      break;
  }

  free(A);
}

void writeToStdOut(int *A, int len) {
    for(int i = 0; i < len; ++i) {
      printf("%d\n", A[i]);
    }
}


/* Notify user that the filename entered for writing the output already exists
 * Let user decide, which write mode should be used
 * Returns enum writeMode*/
writeMode promptFileExists(char *fnamew) {
  printf("File %s already exists in the specified directory. Type \"o\" to overwrite, \"a\" to append, \"c\" to cancel\n", fnamew);

  writeMode wrmode;
  char command[2];
  int validCmd = 0;

  while(1) {

    fgets(command, 2, stdin);

    switch(command[0]) {
      case 'o':
        validCmd = 1;
        wrmode = overwrite;
        break;
      case 'a':
        validCmd = 1;
        wrmode = append;
        break;
      case 'c':
        exit(0);
      default:
        printf("Invalid command. Type \"o\", \"a\" or \"c\"\n");
    }

    if(validCmd) break;
  }
  return wrmode;
}



