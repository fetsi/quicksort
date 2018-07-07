#include "fileIO.h"
#include "main.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

/* Looks for a file in directory dname matching filename fname
 * On a match, returns 1, otherwise 0 */
int searchForFile(char *dname, char *fname) {
	DIR *dp;
	struct dirent *dirp;

	if ((dp = opendir(dname)) == NULL) {
		printf("Can't open directory %s", dname);
		exit(1);
	}

	while ((dirp = readdir(dp)) != NULL) {
		if(!strcmp(dirp->d_name, fname))
		return 1;
	}
	closedir(dp);
	return 0;
}




/* Attempts to open a file handle for reading/writing. Takes the filename as a parameter
 * and returns a FILE pointer.*/
FILE *openFile(char *fname, char *mode) {
  FILE *fptr;
  fptr = fopen(fname, mode);
  if(fptr == NULL) {
    printf("Error opening file %s\n", fname);
    exit(1);
  }
  return fptr;
}

void writeToFile(int *A, int len, writeMode wrmode, char *dnamew, char *fnamew) {
	//printf("Entering writeToFile");
	FILE *fptr;
	char fpath[100];

	sprintf(fpath, "%s/%s", dnamew, fnamew);
	//printf("Path to write: %s", fpath);

	switch(wrmode) {
		case overwrite:
			fptr = openFile(fpath, "w");
			//printf("Overwrite selected");
			break;
		case append:
			fptr = openFile(fpath, "a");
			break;
		default:
			break;
	}

	char buf[12];
	for(int i = 0; i < len; ++i) {
		
		sprintf(buf, "%d", A[i]);
		fputs(buf, fptr);
		if(i != (len-1)) {
			fputs("\n", fptr);
		}
	}
}

