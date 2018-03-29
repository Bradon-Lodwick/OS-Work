***/*
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

node_t *first = NULL;
node_t *last = NULL;

node_t *push(struct proc newProcess)
{	
	node_t *newNode = (node_t*) malloc(sizeof(node_t));
	newNode.process = newProcess;

	if (first == NULL) {
		first = newNode;
		last = newNode;
	}

	else {
		last.next = newNode;
		last = newNode;
	}
	free(newNode);
}

node_t *pop()
{
	if (first != NULL) {
		node_t *poppedNode = (node_t*) malloc(sizeof(node_t));
		poppedNode = first;
		first = first.next;
		return poppedNode;
	}
	else {
		return NULL;
	}
}

