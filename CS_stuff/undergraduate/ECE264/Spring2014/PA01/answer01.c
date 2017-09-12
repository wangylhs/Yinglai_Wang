#include <stdlib.h>
#include "answer01.h"

int arraySum(int * array, int len)
{
    int sum = 0;
    int i = 0;
    for(i = 0; i < len; i++)
    {
        sum = sum + array[i];
    }
    return sum;
}

int arrayCountNegative(int * array, int len)
{
    int cont = 0;
	int i = 0;
    for(i = 0; i < len; i++)
    {
        if(array[i] < 0)
            cont++;
    }
    return cont;
}

int arrayIsIncreasing(int * array, int len)
{
    int isInc = 1;
	int i = 1;
    if(len < 2)
    {
        isInc = isInc*1;
    }else{
        for(i = 1; i < len; i++)
        {
            if(array[i] < array[i-1])
            {
                isInc = isInc*0;
            }else{
                isInc = isInc*1;
            }
        }
    }
    return isInc;
}

int arrayIndexRFind(int needle, const int * haystack, int len)
{
	int i= 0;
    int index = -1;
    for(i = 0; i < len; i++)
    {
        if(haystack[i] == needle)
        {
            index = i;
        }
    }
    return index;
}

int arrayFindSmallest(int * array, int len)
{
    int min;
    int index = 0;
	int i = 1;
    if(len == 0)
    {
        min = 0;
        index = 0;
    }else{
        min = array[0];
        for(i = 1; i < len; i++)
        {
            if(array[i] < min)
            {
                min = array[i];
                index = i;
            }
        }
    }
    
    return index;
}
