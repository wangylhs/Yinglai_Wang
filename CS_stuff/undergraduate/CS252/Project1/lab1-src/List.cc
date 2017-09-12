//
// Implement the List class
//

#include <stdio.h>
#include "List.h"
#include <limits.h>
//
// Inserts a new element with value "val" in
// ascending order.
//
void List::insertSorted( int val )
{
	ListNode *p = _head, *t;

	while(p -> _next && p -> _next -> _value < val) {
		p = p -> _next;
	}

	t = new ListNode();
	t -> _value = val;
	t -> _next = p -> _next;
	p -> _next = t;
}

//
// Inserts a new element with value "val" at
// the end of the list.
//
void List::append( int val )
{
	ListNode *p = _head;
	while(p -> _next)
		p = p -> _next;
	p = p -> _next = new ListNode();
	p -> _value = val;
	p -> _next = NULL;
}

//
// Inserts a new element with value "val" at
// the beginning of the list.
//
void List::prepend( int val )
{
	ListNode *p = new ListNode();
	p -> _value = val;
	p -> _next = _head -> _next;
	_head -> _next = p;
}

// Removes an element with value "val" from List
// Returns 0 if succeeds or -1 if it fails
int List:: remove( int val )
{
	ListNode *p = _head, *t;
	
	while(p -> _next) {
		if (p -> _next -> _value == val) {
			t = p -> _next;
			p -> _next = t -> _next;
			delete t;
			return 0;
		}
		p = p -> _next;
	}
	
	return -1;
}

// Prints The elements in the list. 
void List::print()
{
	ListNode *p = _head -> _next;

	while(p) {
		printf("%d ", p -> _value);
		p = p -> _next;
	}

	printf("\n");
}

//
// Returns 0 if "value" is in the list or -1 otherwise.
//
int List::lookup(int val)
{
	ListNode *p = _head -> _next;

	while(p) {
		if (p -> _value == val) {
			return 0;
		}
		p = p -> _next;
	}

	return -1;
}

//
// List constructor
//
List::List()
{
	_head = new ListNode();
	_head -> _value = INT_MIN;
	_head -> _next = NULL;
}

//
// List destructor: delete all list elements, if any.
//
List::~List()
{
	ListNode *p, *t;

	p = _head;
	while(p) {
		t = p;
		p = p -> _next;
		delete t;
	}

	_head = NULL;
}

