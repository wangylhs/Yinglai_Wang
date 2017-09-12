#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "callstack.h"
//#include "tweetIt.h"

static char *correctPassword = "ceriaslyserious";
char *message = NULL;

int validate(char *password) {
    printf("Validating %p\n", password);
    if (strlen(password) > 128) return 0;

    char *passwordCopy = malloc(strlen(password) + 1);
    strcpy(passwordCopy, password);
    int valid = badguy(passwordCopy);
    return valid;
}

int check(char *password, char *expectedPassword) {
    return (strcmp(password, expectedPassword) == 0);
}

int main() {
    char *password = "wrongpassword";
    char *expectedPassword = correctPassword;
    //printf("EXP: %x\n", &expectedPassword);
    if (!validate(password)) {
        printf("Invalid password!\n");
        return 1;
    }
    if (check(password, expectedPassword)) {
        if (message == NULL) {
            printf("No message!\n");
            return 1;
        } else {
//           tweetIt(message, strlen(message));
            printf("Message sent.\n");
        }
    } else {
        printf("Incorrect password!\n");
    }
    return 0;
}
