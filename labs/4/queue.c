/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Define your FIFO queue functions here, these will most likely be the
// push and pop functions that you declared in your header file

node_t first_0;
node_t last_0;
node_t first_1;
node_t last_1;
node_t first_2;
node_t last_2;
node_t first_3;
node_t last_3;

node_t *push(int level, struct proc newProcess)
{	
	node_t *first;
	node_t *last;
	if (level == 0) {
		first = &first_0;
		last = &last_0;
	}
	else if (level == 1) {
		first = &first_1;
		last = &last_1;

	}
	else if (level == 2) {
		first = &first_2;
		last = &last_2;

	}
	else if (level == 3) {
		first = &first_3;
		last = &last_3;

	}
	else{
		printf("invalid priority level");
		return 0;
	}

	node_t *newNode = (node_t*) malloc(sizeof(node_t));
	newNode->process = newProcess;

	if (first == NULL) {
		first = newNode;
		last = newNode;
	}

	else {
		last->next = newNode;
		last = newNode;
	}
	free(newNode);
}

node_t *pop(int level)
{
	node_t *first;
	node_t *last;
	if (level == 0) {
		first = &first_0;
		last = &last_0;
	}
	else if (level == 1) {
		first = &first_1;
		last = &last_1;

	}
	else if (level == 2) {
		first = &first_2;
		last = &last_2;

	}
	else if (level == 3) {
		first = &first_3;
		last = &last_3;

	}
	else{
		printf("invalid priority level");
		return 0;
	}


	if (first != NULL) {
		node_t *poppedNode = (node_t*) malloc(sizeof(node_t));
		poppedNode = first;
		first = first->next;
		return poppedNode;
	}
	else {
		return NULL;
	}
}

