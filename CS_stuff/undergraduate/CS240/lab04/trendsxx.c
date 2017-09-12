/*Name:     Yinglai Wang
 *Lab:      lab04
 *Login:    wang1105
 */

#include<stdio.h>
#include"list.c"

int c;
char buf[200];
int getword();
int wlen;
int line=1;
int main()
{
    struct lnode *head, *tail, *node;
    head = tail = NULL;
    while(getword()!=EOF){
        struct lnode *p = head;
        while(p){
            if(nodeGetCount(p) == 1 && line - nodeGetLine(p) >= 100){
             //   printf("deleting:... \n ");
                struct lnode *t = nodeGetNext(p);
                deleteNode(&head, &tail, p);
                p=t;
            }else
                p = nodeGetNext(p);
        }
        p = getNode(&head, &tail, buf, line);
        if(p!=NULL){
            nodeIncCount(p);
           // printf("counting... %s %d\n", nodeGetWord(p), nodeGetCount(p));
        }else
            newNode(&head, &tail, buf, line);
        int i;
        for(i=0; i<wlen; i++){
            buf[i] = '\0';
        }
    }
    for(node = head; node; node = nodeGetNext(node)){
        printf("%s %d %d\n", nodeGetWord(node), nodeGetCount(node), nodeGetLine(node));
    }
}
void unCap(int* c){
    if(*c >= 'A' && *c <= 'Z'){
        *c -= 'A'-'a';
    }
}

int getword(){
    wlen = 0;
    while((c=getchar())!=EOF){
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
            unCap(&c);
            buf[wlen++] = c;
            buf[wlen] = '\0';
        }else if(c == '\n'){
            line++;
            return wlen;
        }else{
            return wlen;
            }
    }
    return EOF;
}
