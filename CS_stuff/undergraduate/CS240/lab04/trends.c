/*Name:     Yinglai Wang
 *Lab:      lab04
 *Login:    wang1105
 */

#include<stdio.h>
#include"list.h"

int c;
char buf[200];
int getword(char*, int, int*, int*);
int readMsg(char*);
void unCap(char*);
int wlen;
int line=0;

int main() {
    char msg[140];
    int length = 0;
    int start = 0;
    int end = 0;
    int wlength = 0;
    int line = 1;
    struct lnode *head, *tail, *node;
    head = tail = NULL;

    while ((length = readMsg(msg))!=EOF) {
        line++;
        start = 0;
        end = 0;
        while (getWord(msg, length, &start, &end)) {
            int i = start;
            while(i<=end){
                unCap(msg+i);
                i++;
            }
            msg[end] = '\0';
            struct lnode *p = head;
            while(p){
                if(nodeGetCount(p) == 1 && line - nodeGetLine(p) >= 100){
                    struct lnode *t = nodeGetNext(p);
                    deleteNode(&head, &tail, p);
                    p=t;
                }else
                    p = nodeGetNext(p);
            }
            p = getNode(&head, &tail, (msg+start), line);
            if(p!=NULL){
                nodeIncCount(p);
            }else
                newNode(&head, &tail, (msg+start), line);
        }
    }

    for(node = head; node; node = nodeGetNext(node)){
        if(nodeGetCount(node)>1)
            printf("%s %d\n", nodeGetWord(node), nodeGetCount(node));
    }
    return 0;
}
void unCap(char* c){
    if(*c >= 'A' && *c <= 'Z'){
        *c -= 'A'-'a';
    }
}
int readMsg(char* buf) {
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
int getWord(char* msg, int len, int* start, int* end) {
    *start = -1;
    for( ; *end < len; (*end)++){
        if((*(msg+*end) >= 'a' && *(msg+*end) <= 'z') ||
           (*(msg+*end) >= 'A' && *(msg+*end) <= 'Z'))
        {
            if(*start == -1){
                *start = *end;
            }
        }else if(*start != -1){
            return 1;
        }
    }
    return 0;
}