#include <sys/types.h>

/*
 * Implement the following string procedures.
 *
 * Type "man strstr" to find what each of the functions should do.
 *
 * For example, mystrcpy should do the same as strcpy.
 *
 * IMPORTANT: DO NOT use predefined string functions.
 */

char *mystrcpy(char * s1, const char * s2)
{
    if (!s1 || !s2) return s1;

	char *p = s1;
	
	while(*p++ = *s2++);
	
	return s1;
}

size_t mystrlen(const char *s)
{
	int i;
	for(i=0; s[i]; i++);
	return i;
}

char *mystrdup(const char *s1)
{
	int l = mystrlen(s1);
	char *p = (char*)malloc(l+1);
	
	return mystrcpy(p, s1);
}

char *mystrcat(char * s1, const char * s2)
{
	int l = mystrlen(s1);

	return mystrcpy(s1+l, s2);
}

char *mystrstr(char * s1, const char * s2)
{
	int i, j;
	for(i=0; s1[i]; i++) {
		j = 0;
		while(s1[i+j]==s2[j] && s2[j]) {
			j++;
		}
		if (s2[j]==0) return s1+i;
	}

	return 0;
}

int mystrcmp(const char *s1, const char *s2) {
	while(*s1==*s2 && *s2) {
		s1++;
		s2++;
	}
	
	return *s1 - *s2;
}
