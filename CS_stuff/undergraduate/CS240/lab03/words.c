/*
 *Name:    Yinglai Wang
 *Lab: 	   Lab03
 *CSlogin: wang1105
 */




#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "words.h"

/**
 * Read one line from standard input into {buf}. \n will be put in {buf} too
 * if there is one. Returns the length of the message. Return EOF if there are
 * no more lines to read.
 */
int readMsg(char* buf) {
  /*  FILL IN HERE  */
    int count = 0;
    while(1){
        int c = getchar();
        if(c == EOF)
            return EOF;
        *buf = c;
        count++;
        if(*buf == '\n')
            return count;
        buf++;
    }
}

/**
 * Find the next word. {msg} is a pointer to an array of characters.
 * {len} is the length of the {msg} array. {end} is a pointer to an integer that
 * holds the current position in the array of characters.
 *
 * The function finds the next word, starting from the position given by the
 * initial value of {end}.
 *
 * If a word was found the function returns 1, and updates {start} to point to
 * the index of the first character in the word, {end} to point to the index of
 * the first character after the word.
 *
 * If no word was found, the function returns 0.
 */
int getWord(char* msg, int len, int* start, int* end) {
  /*  FILL IN HERE  */
    *start = -1;
    for( ; *end < len; (*end)++){
        if((*(msg+*end) >= 'a' && *(msg+*end) <= 'z') || 
           (*(msg+*end) >= 'A' && *(msg+*end) <= 'Z'))
        {
            if(*start == -1)
                *start = *end;
            else if(*start != -1)
                return 1;
    }
    return 0;
}

/**
 * Check if {word} is contained in {keywords}. If yes, erase {word} with
 * white spaces. {len} indicates the length of {word}, and {num} indicates
 * the length of the keyword list.
 */
void checkWord(char* word, int len, char** keywords, int num) {
  /*  FILL IN HERE  */
    int i;
    int j;
    for(i=0; i<num; i++){
        for(j=0; j<len; j++){
            if(*(word+j)!= *(*(keywords+i)+j))
                break;
            else if(*(*(keywords+i)+j)==0)
                break;
        }
        if(j==len && *(*(keywords+i)+j) == 0){
            for(j=0; j<len; j++)
                *(word+j) = ' ';
        }
    }
    
}

/*
 * Change the character pointed by {c} to lower case if it is a capital.
 */
void unCapitalize(char* c) {
  /*  FILL IN HERE  */
    if(*c >= 'A' && *c <= 'Z'){
        *c -= 'A'-'a';
    }

}
