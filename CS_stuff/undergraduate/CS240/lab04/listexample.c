#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main()
{
    struct lnode *head, *tail, *node;
    char buf[2];

    /* list starts empty */
    head = tail = NULL;

    for (char c = 'a'; c < 'z'; c++) {
        /* add this letter, as a word, to the list */
        buf[0] = c; buf[1] = '\0';
        newNode(&head, &tail, buf, 1);
    }

    /* we don't like the letter 'f' */
    node = getNode(&head, &tail, "f", 1);
    if (node == NULL) {
        fprintf(stderr, "We forgot f???\n");
    } else {
        deleteNode(&head, &tail, node);
    }

    /* now let's print every node */
    for (node = head; node != NULL; node = nodeGetNext(node)) {
        /* increment its count */
        nodeIncCount(node);

        /* then show it */
        printf("%s: %d %d\n", nodeGetWord(node), nodeGetLine(node), nodeGetCount(node));
    }

    /* get rid of our list */
    deleteList(&head, &tail);

    return 0;
}
