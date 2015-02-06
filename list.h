/*
 * list.h
 *
 *  Created on: Feb 6, 2015
 *      Author: Anuj
 */

#ifndef LIST_H_
#define LIST_H_

typedef struct Node_ {
	struct Node_ * link;
	void* data;
} Node;


typedef struct {
	Node * head;
	Node * tail;
} List;

void list_create();

// Add to the list end
void list_push(List*, void*);
// Add to the list start
void list_shift(List*, void*);

// get first element of list
void* list_pop(List*);
void* list_last(List*);

#endif /* LIST_H_ */
