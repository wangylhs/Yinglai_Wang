/*
    Name: Yinglai Wang
    Course: CS 240
    Lab: Lab02
 */


#include <stdio.h>
#include "words.h"


int main(int argc, char** argv) {
    char msg[SIZE];
    int length = 0;
    int start = 0;
    int end = 0;
    int wlength = 0;

  // read in every line of the tweets
    while ((length = readMsg(msg)) != EOF) {
        start = 0;
        end = 0;
        // get every word in the current line
        while (getWord(msg, length, &start, &end)) {
            int i = start;
            
            // turn the word to small case
            while(i<=end)
            {
                unCapitalize(msg+i);
                i++;
            }
            
            // check and process the word
            wlength = end - start;
            checkWord(msg+start, wlength, argv, argc);
        }
        
        // output the processed message
        int count=0;
        while(count < length){
            printf("%c", *(msg+count));
            count++;
        }
    }
    return 0;
}
