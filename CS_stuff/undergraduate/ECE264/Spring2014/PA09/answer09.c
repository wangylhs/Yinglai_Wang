#include "answer09.h"
#include <stdlib.h>
#include <stdio.h>

HuffNode * HuffNode_create(int value)
{
  HuffNode * huf = malloc(sizeof(HuffNode));
  huf -> left = NULL;
  huf -> right = NULL;
  huf -> value = value;
  return huf;
}

void HuffNode_destroy(HuffNode * tree)
{
  if(tree == NULL) return;
  HuffNode_destroy(tree -> left);
  HuffNode_destroy(tree -> right);
  free(tree);
}


Stack *Stack_create()
{
  Stack *stk = malloc(sizeof(Stack));
  stk -> head = NULL;
  return stk;
}

void Stack_destroy(Stack * stack)
{
  if(stack == NULL) return;
  StackNode *p = stack->head;
  while(p!= NULL)
    {
      StackNode *temp = p->next;
      HuffNode_destroy(temp->tree);
      free(temp);
      p = temp;
    }
  free(stack);
}

int Stack_isEmpty(Stack * stack)
{
  if (stack->head == NULL) return 1;
  return 0;
}

HuffNode * Stack_popFront(Stack * stack)
{
  if(Stack_isEmpty(stack)) return NULL;
  StackNode *p = stack -> head;
  HuffNode *tree = stack -> head -> tree; 
  stack -> head = stack -> head -> next;
  free(p);
  return tree;
}

void Stack_pushFront(Stack * stack, HuffNode * tree)
{
  if(stack == NULL) return;
  StackNode *p = malloc(sizeof(StackNode));
  p -> tree = tree;
  p -> next = stack -> head;
  stack -> head = p;
}

void Stack_popPopCombinePush(Stack * stack)
{
  HuffNode *new_node = HuffNode_create(0);
  new_node -> right = Stack_popFront(stack);
  new_node -> left = Stack_popFront(stack);
  Stack_pushFront(stack,new_node);
}

size_t Stack_size(Stack *stack)
{
  if(stack == NULL) return 0;
  size_t count = 0;
  StackNode *node = stack -> head;
  while(node != NULL)
    {
      count++;
      node = node -> next;
    }
  return count; 
}


HuffNode * HuffTree_readTextHeader(FILE * fp)
{
  Stack *stack = Stack_create();
  int val;
  while((val = fgetc(fp)) != EOF)
    {
      if(val == '1')
	{
	  val = fgetc(fp);
	  Stack_pushFront(stack, HuffNode_create(val));
	}
      else if (val == '0')
	{
	  if(Stack_size(stack) == 1) break;
	  Stack_popPopCombinePush(stack);
	}
    }
  HuffNode *tree = Stack_popFront(stack);
  Stack_destroy(stack);
  return tree;
}

typedef struct {
FILE * fp;
unsigned char byte;
int position;
} BitFile;

BitFile * BitFile_create(FILE * fp)
{
BitFile * bitfile = malloc(sizeof(BitFile));
bitfile -> fp = fp;
bitfile -> byte = 0;
bitfile -> position = 8; // forces a first read
return bitfile;
}

void BitFile_destroy(BitFile * bitfile)
{
free(bitfile);
}

int BitFile_nextBit(BitFile * bitfile)
{
if (bitfile -> position == 8){
bitfile -> position = 0;
if (fread(&(bitfile -> byte), sizeof(unsigned char), 1, bitfile -> fp) !=1){
return -1;
}
}
int val = (bitfile -> byte >> (7 - bitfile -> position)) & 1;
bitfile -> position++;
return val;
}

int BitFile_nextByte(BitFile * bf)
{
int ret = 0;
int pos;
for (pos = 0; pos < 8; pos++){
int bit = BitFile_nextBit(bf);
if (bit < 0) return -1;
ret = ret | (bit << (7 - pos));
}
return ret;
}

HuffNode * HuffTree_readBinaryHeader(FILE * fp)
{
Stack * stack = Stack_create();
BitFile * bf = BitFile_create(fp);
int val = BitFile_nextBit(bf);
while (val >= 0){
if (val == 1){
val = BitFile_nextByte(bf);
Stack_pushFront(stack, HuffNode_create(val));
}
else if (val == 0){
if (Stack_size(stack) == 1) break;
Stack_popPopCombinePush(stack);
}
val = BitFile_nextBit(bf);
}
HuffNode * tree = Stack_popFront(stack);
Stack_destroy(stack);
BitFile_destroy(bf);
return tree;
}


