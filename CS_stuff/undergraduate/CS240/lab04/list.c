/*
 *Name:  Yinglai Wang
 *Lab:   lab04
 *Login: wang1105
 */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "list.h"

struct lnode {
    /* FILL THIS IN */
    struct lnode* next;
    struct lnode* previous;
    char *word;
    int count;
    int line;
};

/**
 * In the linked list with *head and *tail as head and tail pointers,
 * add a newly-created node to the tail of the list. The new node has
 * the given word and line, and a count of 1. You must duplicate word,
 * as the original word may be modified by the calling function. Return
 * value is the newly-created node.
 */
struct lnode *newNode(struct lnode **head, struct lnode **tail, char *word, int line) {
    /* FILL THIS IN */
    struct lnode *p = (struct lnode*)malloc(sizeof(struct lnode));
    if(*head == NULL){
        p -> next = p -> previous = NULL;
        p -> word = strdup(word);
        p -> count = 1;
        p -> line = line;
        *head = *tail = p;
    }else{
        p -> next = NULL;
        p -> previous = *tail;
        (*tail) -> next = p;
        *tail = p;
        p -> word = strdup(word);
        p -> count = 1;
        p -> line = line;
    }
    return p;
}

/**
 * Removes the specified node from the list, and frees all memory the node is using.
 * Remember that if *head or *tail are the node, they will need to be updated!
 */
void deleteNode(struct lnode **head, struct lnode **tail, struct lnode *node) {
    /* FILL THIS IN */
    struct lnode *previous = node -> previous;
    struct lnode *next = node -> next;
    free(node->word);
    free(node);
    if(previous){
        previous -> next = next;
    }else{
        *head = next;
    }
    if(next){
        next -> previous = previous;
    }else{
        *tail = previous;
    }
}

/**
 * Simply returns the next node in the list, or NULL if there are no further nodes.
 */
struct lnode *nodeGetNext(struct lnode *node) {
    /* FILL THIS IN */
    return node -> next;
}

/**
 * Simply returns the word in the given node.
 */
char *nodeGetWord(struct lnode *node) {
    /* FILL THIS IN */
    return node -> word;
}

/**
 * Simply returns the line in the given node.
 */
int nodeGetLine(struct lnode *node) {
    /* FILL THIS IN */
    return node -> line;
}

/**
 * Simply returns the count in the given node.
 */
int nodeGetCount(struct lnode *node) {
    /* FILL THIS IN */
    return node -> count;
}

/**
 * Increments the count in the given node, and returns the new count.
 */
int nodeIncCount(struct lnode *node) {
    /* FILL THIS IN */
    return ++(node -> count);
}

/**
 * If the linked list with *head and *tail as head and tail pointers contains
 * a node with the specified word, that node is returned, with its line updated
 * to the specified line. Otherwise, returns NULL.
 */
struct lnode *getNode(struct lnode **head, struct lnode **tail, char *word, int line) {
    /* FILL THIS IN */
    struct lnode *p = *head;
    while(p!=NULL){
        if(strcmp(p->word, word)==0){
            p -> line = line;
            return p;
        }
        p = p -> next;
    }
    return NULL;
}

/**
 * Deletes every node in the list with *head and *tail as head and tail pointers.
 * After calling this function, all memory used by the list should be freed,
 * and *head and *tail should both be NULL.
 */
void deleteList(struct lnode **head, struct lnode **tail) {
    /* FILL THIS IN */
    struct lnode *p = *head;
    while(p){
        struct lnode *temp = p -> next;
        free(p->word);
        free(p);
        p = temp;
    }
    *head = *tail = NULL;
}
