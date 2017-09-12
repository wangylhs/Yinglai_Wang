#include<stdlib.h>
#include<string.h>

char * strcat_ex(char * * dest, int * n, const char * src) {
    if (!n || !src) return NULL;

    int srclen = strlen(src);
    int destlen = *dest ? strlen(*dest) : (*n=0);

    if (srclen >= *n - destlen) {
        *n = 1 + 2 * (destlen + srclen);
        char *newstr = malloc(*n * sizeof(char));
        if (*dest) {
            strcpy(newstr, *dest);
            free(*dest);
        }
        *dest = newstr;
    }

    strcpy(*dest+destlen, src);

    return *dest;

    /*    if(*dest == NULL || strlen(src) > (*n - strlen(*dest))){
        char * temp = malloc(1 + 2 * (strlen(*dest) + strlen(src)));
        *n = 1 + 2 * (strlen(*dest) + strlen(src));
        strcpy(temp, *dest);
        if(*dest != NULL)
            free(*dest);
        *dest = temp;
        strcat(*dest, src);
    }else{
        strcat(*dest, src);
    }
    return *dest;*/
}

char * * explode(const char * str, const char * delims, int * arrLen)
{
    if (!str || !delims) {
        *arrLen = 0;
        return NULL;
    }

    const char *p;
    *arrLen = 1;
    for(p=str; *p; p++) {
        if (strchr(delims, *p)) {
            (*arrLen)++;
        }
    }

    char **arr = (char**)malloc((*arrLen)*sizeof(char*)), **a=arr;
    const char *start = str;
    int l;
    for(p=str; ; p++) {
        if (strchr(delims, *p) || !*p) {
            l = p - start;
            *a = (char*)malloc((l+1)*sizeof(char));
            memcpy(*a, start, l);
            (*a)[l] = '\0';
            a++;
            start = p+1;
            if (!*p) return arr;
        }
    }

    return NULL;
}

char * implode(char * * strArr, int len, const char * glue)
{
    int newLen = 0;
    int i;
    for(i=0; i<len; i++) {
        newLen += strlen(strArr[i]);
    }
    newLen += strlen(glue)*(len>0?len-1:0);

    char *newStr = (char*)malloc((newLen+1)*sizeof(char));
    *newStr = '\0';
    for(i=0; i<len; i++) {
        strcat(newStr, strArr[i]);
        if (i!=len-1) strcat(newStr, glue);
    }

    return newStr;
}

int cmpfunc (const void * a, const void * b)
{
    return strcmp(*(const char **) a, *(const char **) b);
}

void sortStringArray(char * * arrString, int len){
    qsort(arrString, len, sizeof (char *), cmpfunc);
}

int charcomfunc (const void * a, const void * b)
{
    return *(const char *) a - *(const char *) b;
}
void sortStringCharacters(char * str)
{
    if (!str) return ;
    qsort(str, strlen(str), sizeof(char), charcomfunc);
}

void destroyStringArray(char * * strArr, int len)
{
    if (!strArr) return ;
    int i;
    for(i=0; i<len; i++) {
        free(strArr[i]);
    }
    free(strArr);
}

