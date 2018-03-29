/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#ifndef QUEUE_H_
#define QUEUE_H_

#include "utility.h"

// Your linked list structure for your queue
typedef struct NODE{
	struct proc process;
	struct node_t *next;
} node_t;
// Include your relevant FIFO queue functions declarations here they must start 
// with the extern keyword such as in the following examples:


// Add a new process to the queue, returns the address of the next node added
// to the linked list

extern node_t *push(struct proc newProcess);

extern node_t *pop();


#endif /* QUEUE_H_ */