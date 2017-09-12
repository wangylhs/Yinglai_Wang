#include "answer07.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List * List_createNode(const char * str){
	List *l = malloc(sizeof(List));
	l -> str = strdup(str);
	l -> next = NULL;
	return l;
}

void List_destroy(List * list){
	if(list == NULL)	return;
	List_destroy(list->next);
  free(list->str);
  free(list);
}

int List_length(List * list){
	int len = 0;
	while(list != NULL){
		++len;
		list = list -> next;
	}
	return len;
}

List * List_merge(List * lhs, List * rhs, int (*compar)(const char *, const char*)){
	if (lhs == NULL) return rhs;
  if (rhs == NULL) return lhs; 
  List *head = NULL;
  List *tail = NULL;
  while (lhs != NULL && rhs != NULL) {
		int cmp = compar(lhs->str, rhs->str);
    if (cmp <= 0) {
    	if (tail == NULL){
      	head = lhs;
        tail = lhs;
     	}else{
        tail -> next = lhs;
        tail = lhs;
      }
      lhs = lhs -> next;
      tail -> next = NULL;
  	}else{

      if (tail == NULL){
       	head = rhs;
        tail = rhs;
     	}else{
       	tail -> next = rhs;
      	tail = rhs;
     	}
      rhs = rhs -> next;
      tail -> next = NULL;
 		}
	}
	if(lhs == NULL)
		tail -> next = rhs;
	else
		tail -> next = lhs;
	return head;
}

List * List_sort(List * list, int (*compar)(const char *, const char*)){
	int length = List_length(list);
  if (length <= 1) return list;    
  int mid = length / 2;
  List *lhs = list;
  List *lhs_tail = list;
  while (--mid > 0){
  	lhs_tail = lhs_tail -> next;
  }
  List *rhs = lhs_tail -> next;
  lhs_tail -> next = NULL;
  
  lhs = List_sort(lhs, compar);
  rhs = List_sort(rhs, compar);
	return List_merge(lhs, rhs, compar);

}
