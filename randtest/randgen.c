#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "fileIO.h"

int *createSorted(int len);
void shuffle(int *A, int len);

int main(int argc, char **argv) {
	
	if(argc != 2) {
		printf("Exactly 1 argument expected: length of array to be created (integer)\n");
		return 1;
	}

	int len = strtol(argv[1], NULL, 10);
	if(errno == ERANGE) {
		printf("Entered value is out of bounds\n");
		return 1;
	}
	else if(len <= 0) {
		printf("Entered value must a number greater than 0\n");
		return 1;
	}

	int *arr = createSorted(len);
	shuffle(arr, len);
	writeToFile(arr, len, overwrite, ".", "rnumbers.txt");
	/*
	for(int i = 0; i < len; ++i) {
		printf("%d  -- ind:%d\n", arr[i], i);
	}
	*/

	free(arr);
}

int *createSorted(int len) {

	int *A = (int*) malloc(len * sizeof(int));
	if(A == NULL) {
		printf("Couldn't allocate memory for array of size %d", len);
		return NULL;
	}

	//Fill array with contiguous values from 0 to len
	for(int i = 0;  i < len; ++i) {
		A[i] = i + 1;
	}
	return A;
}


void shuffle(int *A, int len) {

	srand(time(NULL));

	//Shuffle 10 times. Should be sufficient xD
	//for(int i = 0; i < 10; ++i) {
		for(int j = 0; j < len; ++j) {
			int r = rand() % len;

			//Swap A[i] with A[r]
			int temp = A[j];
			A[j] = A[r];
			A[r] = temp;
			/*
			A[j] = A[j] ^ A[r];
			A[r] = A[r] ^ A[j];
			A[j] = A[j] ^ A[r];
			*/
		}
	//}
}