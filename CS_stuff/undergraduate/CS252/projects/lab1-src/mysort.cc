#include "mysort.h"
#include <alloca.h>
#include <assert.h>
#include <string.h>

//
// Sort an array of element of any type
// it uses "compFunc" to sort the elements.
// The elements are sorted such as:
//
// if ascending != 0
//   compFunc( array[ i ], array[ i+1 ] ) <= 0
// else
//   compFunc( array[ i ], array[ i+1 ] ) >= 0
//
// See test_sort to see how to use mysort.
//

void myswap(char *a, char *b, int size)
{
	char t;
	int i;
	for(i=0; i<size; i++) {
		t = a[i];
		a[i] = b[i];
		b[i] = t;
	}
}

void mysort( int n,                      // Number of elements
	     int elementSize,            // Size of each element
	     void * array,               // Pointer to an array
	     int ascending,              // 0 -> descending; 1 -> ascending
	     CompareFunction compFunc )  // Comparison function.
{
	int i, j;
	char *s = (char*)array;

	if (ascending) {
		for(i=1; i<n; i++) {
			for(j=0; j<(n-i)*elementSize; j+=elementSize) {
				if (compFunc(s+j, s+j+elementSize)>0) {
					myswap(s+j, s+j+elementSize, elementSize);
				}
			}
		}
	} else {
		for(i=1; i<n; i++) {
			for(j=0; j<(n-i)*elementSize; j+=elementSize) {
				if (compFunc(s+j, s+j+elementSize)<0) {
					myswap(s+j, s+j+elementSize, elementSize);
				}
			}
		}
	}
}

