/*
 * CS354: Operating Systems. 
 * Purdue University
 * Example that shows how to read one line with simple editing
 * using raw terminal.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "tty-can-mode.c"
#define MAX_BUFFER_LINE 2048


int shift = 0;


// Buffer where line is stored
int line_length;;
char line_buffer[MAX_BUFFER_LINE];

// Simple history array
// This history does not change.
// Yours have to be updated.


typedef struct _History{
    struct _History *next;
    struct _History *previous;
    struct _History *tail;
    struct _History *head;
    char* history;
} History;
History *head;
History *current;
void insert(char*);
void printHistory();



int history_index = 0;
int tempHistory=0;
int end_history = 0;
char * history [100];/* = {
                      "ls -al | grep x",
                      "ps -e",
                      "cat read-line-example.c",
                      "vi hello.c",
                      "make",
                      "ls -al | grep xxx | grep yyy"
                      };*/
int history_length = sizeof(history)/sizeof(char *);

void read_line_print_usage()
{
    char * usage = "\n"
    " ctrl-?       Print usage\n"
    " Backspace    Deletes last character\n"
    " Delete       Deletes charactor in front of cursor\n"
    " up arrow     See last command in the history\n"
    " left arrow   Moves cursor to the left if possible. Typing will start there with insertion.\n"
    " right arrow  Moves cursor to the right if possible.  Typing will start there with insertion.\n"
    " ctrl-a       Moves cursor to begining of prompt.  Typing will start there with insertion. \n"
    " ctrl-e       Moves cursor to end of prompt.  Typing will start at the end of the prompt. \n";
    
    write(1, usage, strlen(usage));
}

/*
 * Input a line with some basic editing.
 */
char * read_line() {
    
    // Set terminal in raw mode
    tty_raw_mode();
    
    line_length = 0;
    
    
    // Read one line until enter is typed
    while (1) {
        
        // Read one character in raw mode.
        char ch;
        read(0, &ch, 1);
        
        //printf("ch: %d\n", ch);
        
        if (ch>=32 && ch != 127) {
            // It is a printable character.
            
            // Do echo
            if(!shift)
                write(1,&ch,1);
            
            // If max number of character reached return.
            if (line_length==MAX_BUFFER_LINE-2) break;
            
            // add char to buffer.
            if(!shift){
                line_buffer[line_length] = ch;
                line_length++;
            }
            else{
                //shift = pos;
                int temp = shift;
                char chtemp;
                for(; temp != 1; temp++){
                    chtemp = line_buffer[line_length+temp];
                    write(1,&ch,1);
                    line_buffer[line_length+temp] = ch;
                    ch = chtemp;
                    
                    
                }
                line_length++;
                temp = shift;
                ch = 8;
                for(; temp != 0; temp++)
                    write(1,&ch,1);
            }
        }
        else if(ch == 5){
            //end key ctrl-e
            int temp = shift;
            char chtemp;
            ch = line_buffer[line_length+temp];
            for(; temp != 1; temp++){
                chtemp = line_buffer[line_length+temp+1];
                write(1,&ch,1);
                line_buffer[line_length+temp] = ch;
                ch = chtemp;
            }
            line_buffer[line_length+temp] = chtemp;
            shift = 0;
        }
        else if(ch == 1){
            //home key ctrl-a
            ch = 8;
            while(shift != -(line_length)){
                write(1,&ch,1);
                shift--;
            }
        }
        else if (ch==10) {
            // <Enter> was typed. Return line
            
            // Print newline
            write(1,&ch,1);
            
            break;
        }
        else if (ch == 31) {
            // ctrl-?
            read_line_print_usage();
            line_buffer[0]=0;
            break;
        }
        else if (ch == 127 || ch == 8) {
            // <backspace> was typed. Remove previous character read.
            
            // Go back one character
            if(line_length+shift > 0){
                if(shift == 0){
                    ch = 8;
                    write(1,&ch,1);
                    
                    // Write a space to erase the last character read
                    ch = ' ';
                    write(1,&ch,1);
                    
                    // Go back one character
                    ch = 8;
                    write(1,&ch,1);
                }else{
                    ch = 8;
                    write(1,&ch,1);
                    int k=shift;
                    for(k; k<0; k++){
                        char cht = line_buffer[line_length+k];
                        write(1,&cht,1);
                        line_buffer[line_length+k-1] = cht;
                    }
                    ch = ' ';
                    write(1,&ch,1);
                    line_buffer[line_length] = ch;
                    k=shift-1;
                    ch = 8;
                    for(k; k<0; k++)
                        write(1,&ch,1);
                }
                
                // Remove one character from buffer
                line_length--;
            }
        }
        else if (ch==27) {
            // Escape sequence. Read two chars more
            //
            // HINT: Use the program "keyboard-example" to
            // see the ascii code for the different chars typed.
            //
            char ch1;
            char ch2;
            read(0, &ch1, 1);
            read(0, &ch2, 1);
            if (ch1==91 && ch2==65) {
                // Up arrow. Print next line in history.
                
                // Erase old line
                // Print backspaces
                if(history_index != 0){
                    int temp = shift;
                    ch = ' ';
                    while(temp != 0){
                        write(1,&ch,1);
                        temp++;
                    }
                    
                    
                    int i = 0;
                    for (i =0; i < line_length; i++) {
                        ch = 8;
                        write(1,&ch,1);
                    }
                    
                    // Print spaces on top
                    for (i =0; i < line_length; i++) {
                        ch = ' ';
                        write(1,&ch,1);
                    }
                    
                    // Print backspaces
                    for (i =0; i < line_length; i++) {
                        ch = 8;
                        write(1,&ch,1);
                    }
                    
                    // Copy line from history
                    
                    strcpy(line_buffer, current->history);
                    line_length = strlen(line_buffer)-1;
                    history_index--;
                    if(history_index != 0)
                        current = current->previous;
                    //history_index=(history_index+1)%history_length;
                    
                    // echo line
                    write(1, line_buffer, line_length);
                    shift = 0;
                }
            }else if(ch1 == 91 && ch2 == 66){
                //down arrow
                if(history_index != tempHistory){
                    int temp = shift;
                    ch = ' ';
                    while(temp != 0){
                        write(1,&ch,1);
                        temp++;
                    }
                    
                    int i = 0;
                    for (i =0; i < line_length; i++) {
                        ch = 8;
                        write(1,&ch,1);
                    }
                    
                    // Print spaces on top
                    for (i =0; i < line_length; i++) {
                        ch = ' ';
                        write(1,&ch,1);
                    }
                    
                    // Print backspaces
                    for (i =0; i < line_length; i++) {
                        ch = 8;
                        write(1,&ch,1);
                    }
                    
                    // Copy line from history
                    if(history_index == 0)
                        history_index++;
                    history_index++;
                    current = current->next;
                    //printf("currentHistroy: %s", current->history);
                    strcpy(line_buffer, current->history);
                    line_length = strlen(line_buffer)-1;
                    
                    // echo line
                    write(1, line_buffer, line_length);
                    shift = 0;
                }else if(history_index == tempHistory){
                    int k=line_length+shift;
                    ch = 8;
                    for(; k>0; k--)
                        write(1,&ch,1);
                    ch = ' ';
                    for(; k<line_length; k++){
                        write(1,&ch,1);
                        line_buffer[k] = ch;
                    }
                    ch = 8;
                    for(; k>0; k--)
                        write(1,&ch,1);
                    
                    
                    line_length = 0;
                    shift = 0;
                }
            }else if(ch1 == 91 && ch2 == 68){
                //left arrow
                if(line_length+shift > 0){
                    ch = 8;
                    write(1,&ch,1);
                    shift--;
                }
            }else if(ch1 == 91 && ch2 == 67){
                //right arrow
                if(line_length != MAX_BUFFER_LINE-2 && shift != 0){
                    ch = line_buffer[line_length + shift];
                    write(1,&ch,1);
                    shift++;
                }
            }else if(ch1 == 79 && ch2 == 72){
                //home key
                ch = 8;
                while(shift != -(line_length)){
                    write(1,&ch,1);
                    shift--;
                }
                
                
            }else if(ch1 == 79 && ch2 == 70){
                //end key
                int temp = shift;
                char chtemp;
                for(; temp != 1; temp++){
                    chtemp = line_buffer[line_length+temp];
                    write(1,&ch,1);
                    line_buffer[line_length+temp] = ch;
                    ch = chtemp;
                }
                shift = 0;
            }else if(ch1 = 91 && ch2 == 51){
                char ch3;
                read(0, &ch3, 1);
                if(ch3 == 126){
                    //delete
                    if(shift != 0){
                        shift++;
                        int j=shift;
                        int k=shift;
                        for(k; k<0; k++){
                            ch = line_buffer[line_length+k];
                            write(1,&ch,1);
                            line_buffer[line_length+k-1] = ch;
                        }
                        ch = ' ';
                        write(1,&ch,1);
                        
                        ch = 8;
                        k=1;
                        for(k; k>shift; k--)
                            write(1,&ch,1);
                        line_length--;
                    }
                }
            }
            
        }
        
    }
    
    /*
     history[end_history] = strdup(line_buffer);
     end_history++;
     history_index++;
     // Add eol and null char at the end of string
     */
    
    line_buffer[line_length]=10;
    line_length++;
    line_buffer[line_length]=0;
    
    if(line_length != 1){
        insert(strdup(line_buffer));
        //printHistory();
        shift = 0;
        tempHistory++;
        history_index = tempHistory;
        current = head->tail;
    }
    
    //printf("Line Buffer: %s\n", line_buffer);
    //printf("line_length: %d\n", line_length);
    //printf("History added: %s\n", history[end_history-1]);
    
    //tty_can_mode();
    return line_buffer;
}


void insert(char* in){
    if(head == NULL){
        head = (History*)malloc(sizeof(History));
        head->history = strdup(in);
        head->head = head;
        head->tail = head;
        current = head;
        return;
    }
    History *newNode = malloc(sizeof(History));
    newNode->history = strdup(in);
    newNode->head = head;
    newNode->previous = head->tail;
    newNode->tail = newNode;
    head->tail->next = newNode;
    head->tail = newNode;
    current = newNode;
}

void printHistory(){
    History *temp = head;
    while(temp->history != NULL){
        printf("history: %s\n", temp->history);
        if(temp->next == NULL)
            break;
        temp = temp->next;
    }
}
