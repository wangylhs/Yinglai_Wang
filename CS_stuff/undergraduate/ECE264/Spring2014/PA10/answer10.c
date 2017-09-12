#include "answer10.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

Stack * Stack_create()
{
  Stack *stk = malloc(sizeof(Stack));
  stk -> list = NULL;

  return stk;
}


void Stack_destroy(Stack * stack)
{
  if (stack == NULL) return;
  ListNode *p;
  while((stack -> list) != NULL)
    {
      p = stack -> list -> next;
      free(stack -> list);
      stack -> list = p;
    }
  free(stack);
}

int Stack_isEmpty(Stack * stack)
{
  if (stack == NULL) return TRUE;
  return FALSE;
}

int Stack_popFront(Stack *stack)
{
  ListNode *p = stack -> list;
  if(p == NULL) return;
  int temp = (int) (p -> value);
  free(p);
  p = p -> next;
  return temp;
}

void Stack_pushFront(Stack * stack, int value)
{
  ListNode *p = malloc(sizeof(ListNode));
  p -> value = value;
  p -> next = stack -> list;
  stack -> list = p;
}

void stackSort(int * array, int len)
{
  
}

int isStackSortable(int * array, int len)
{
  if (len < 3) return TRUE;
  
  int i;
  int max = array[0];
  int max_i = 0;
  for(i = 0; i < len; i++)
    {
      if(array[i] > max)
	{
	  max = array[i];
	  max_i = i;
	}
    }

  int max_left = 0;
  int min_right = max;

  int *left = malloc(sizeof(max_i));
  for(i = 0; i < max_i; i++)
      left[i] = array[i];
  int *right = malloc(sizeof(len-max_i-1));
  for(i = 0; i < len_max_i-1; i++)
      right[i] = array[i];
  for(i = 0; i < max_i; i++)
      if(array[i] > max_left) max_left = array[i];
  for(i = max_i; i<len; i++)
    if(array[i] < min_right) min_right = arrar[i];
  if(max_i ==0 && isStackSortable(right, len-max_i-1)) return TRUE;
  if(max_left < min_right)
    {
      return TRUE;
    }
  else
    {
      return FALSE;
    }
  if(isStackSortable(left, max_i)&&isStackSortable(right, len-max_i-1))
    {
      free(left);
      free(right);
      return TRUE;
    }

  free(left);
  free(right);
  return FALSE;
}

void genShapes(int n);
{
  int *arr = malloc(sizeof(k));
  int i;
  for(i = 0; i < k; i++)
    {
      arr[i] = i;
    }
  permute(arr,0,k);
  free(arr);
}
