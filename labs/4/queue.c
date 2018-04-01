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

// Pushes a node to the given queue defined by the head
void push(node_t * head, struct proc newProcess)
{
	// The new node to be added to the queue
	node_t * newNode = (node_t*) malloc(sizeof(node_t));
	newNode->process = newProcess;

	// If head is null, make the head equal to the new node
	if (head == NULL){
		head = newNode;
	}

	// Loop through the list to add the node to the end
	else{
			node_t * current = head;
			while (current->next != NULL)
			{
				current = current->next;
			}
			current->next = newNode;
	}
}

// Removes the given node from the queue defined by the given head
node_t * remove_node(node_t * head, node_t * node_to_remove)
{
	if (head == node_to_remove)
	{
		head = head->next;
	}

	else
	{
		// Current node in iteration
		node_t * current = head;
		while (current->next != node_to_remove)
		{
			current = current->next;
			if (current->next != NULL)
			{
				return NULL;
			}
		}

		// Node to be removed
		node_t * removed_node = current->next;

		// Remove node by setting the next of the node before to the deleted node's next
		current->next = removed_node->next;

		return removed_node;
	}
}

