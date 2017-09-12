//
//  main.c
//  copyFile
//

//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
int main()
{
    int c;
    
    c = getchar();
    while ((c = getchar())!= EOF) {
	printf("%6d",c); 
        putchar(c);
    }
}
