/*
 * Banker's Algorithm for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include "banker.h"

// Put any other macros or constants here using #define
// May be any values >= 0
#define NUM_CUSTOMERS 5
#define NUM_RESOURCES 3


// Put global environment variables here
// Available amount of each resource
int available[NUM_RESOURCES];

// Maximum demand of each customer
int maximum[NUM_CUSTOMERS][NUM_RESOURCES];

// Amount currently allocated to each customer
int allocation[NUM_CUSTOMERS][NUM_RESOURCES];

// Remaining need of each customer
int need[NUM_CUSTOMERS][NUM_RESOURCES];


//allocates the required resources
void alloc_res(int n_cust, int req[])
{	
	int j;
	for (j=0;j<NUM_RESOURCES;j++)
	{
		available[j] = available[j] - req[j];
		allocation[n_cust][j] = allocation[n_cost][j] + req[j];
		need[n_cust][j] = need[n_cust][j] - req[j]
	}
}


// Define functions declared in banker.h here
bool request_res(int n_customer, int request[])
{
	int i;
	for (i=0;i<NUM_RESOURCES;i++)
	{
		if (request[i] <= need[n_customer][i])
		{
			//do nothing, so far its good
		}
		else
		{
			//TODO: RAISE ERROR CONDITION
			return false;
		}
	}
	for (i=0;i<NUM_RESOURCES;i++)
	{
		if (request[i] <= Available)
		{
			//do nothing again, so far its good
		}
		else
		{
			//Process must wait
			return false;
		}
	}
	alloc_res(n_customer, request[])
	return true;
}

// Release resources, returns true if successful
bool release_res(int n_customer, int release[])
{
	int j;
	for (j=0;j<NUM_RESOURCES;j++)
	{
		available[j] = available[j] + release[j];
		allocation[n_customer][j] = allocation[n_cust][j]  - release[j];
		need[n_customer][j] = need[n_customer][j] + release[j];
	}
	return true;
}


int main(int argc, char *argv[])
{
    // ==================== YOUR CODE HERE ==================== //

    // Read in arguments from CLI, NUM_RESOURCES is the number of arguments   
	// Checks to make sure proper number of arguments were given
	if (argc != NUM_RESOURCES + 1)
	{
		printf("Invalid number of arguments. Please give %d arguments\n", NUM_RESOURCES + 1);
		exit(-1);

	}
	// Put available resources into the available array
	else
	{
		int i;
		for (i = 1; i <= NUM_RESOURCES; i++)
		{
			available[i - 1] = atoi(argv[i]);
		}
	}
    
    // Allocate the available resources

    // Initialize the pthreads, locks, mutexes, etc.

    // Run the threads and continually loop

    // The threads will request and then release random numbers of resources

    // If your program hangs you may have a deadlock, otherwise you *may* have
    // implemented the banker's algorithm correctly
    
    // If you are having issues try and limit the number of threads (NUM_CUSTOMERS)
    // to just 2 and focus on getting the multithreading working for just two threads

    return EXIT_SUCCESS;
}
