#include <stdlib.h>
/*
 * Name:    Yinglai Wang
 * Course:  CS240
 * Lab:     lab02
 * Login:   wang1105
 */
/**
 * Test if {ch} is a letter (a - z or A - Z).
 * Return 1 if yes, otherwise 0.
 */
int isAlpha(char ch) {
  /* FILL IN HERE */
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

/**
 * Return the length of the zero terminated string {s}.
 * The \0 character is not counted, e.g. the length of "abc" is 3.
 */
int strLen(char* s) {
  /* FILL IN HERE */
	int count = 0;

	while(*s!='\0')
	{
		s++;
		count++;
	} 	 
	
	return count;
}

/**
 * Compare the first {n} characters of string {s1} and {s2}.
 * If identical, return 1. Otherwise return 0.
 */
int strNCmp(char* s1, char* s2, int n) {
  /* FILL IN HERE */
    int i;
    for(i=0; i < n; i++, s1++, s2++){
        if( *s1 != *s2)
            return 0; 
    }
    return 1;
}

/**
 * Replace every character of {s} with a white space.
 * {len} indicates the length of {s}.
 */
void spaceOut(char* s, int len) {
  /* FILL IN HERE */
    int i;
    for(i=0; i < len; i++)
        *s++ = ' ';
}
