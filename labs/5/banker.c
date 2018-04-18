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
#include <unistd.h>
#include "banker.h"

// Put any other macros or constants here using #define
// May be any values >= 0
#define NUM_CUSTOMERS 5
#define NUM_RESOURCES 3


// Put global environment variables here
// Available amount of each resource
int available[NUM_RESOURCES];

int rand_customer;

// Maximum demand of each customer
int maximum[NUM_CUSTOMERS][NUM_RESOURCES];

// Total resources the system contains
int total_available[NUM_RESOURCES];

// Amount currently allocated to each customer
int allocation[NUM_CUSTOMERS][NUM_RESOURCES];

// Remaining need of each customer
int need[NUM_CUSTOMERS][NUM_RESOURCES];

// The lock to be used by the threads
pthread_mutex_t lock;

// Thread function for customers making a request
// arg is the customer number
void* customer_thread(void *arg)
{
    while (1)
    {
        if (rand_customer == (int)arg)
        {
            // Lock the thread
            pthread_mutex_lock(&lock);

            int i;
            int resource;
            int request[NUM_RESOURCES];
            // Randomly generate the requests
            for (i = 0; i < NUM_RESOURCES; i++)
            {
                request[i] = rand() % (need[(int)arg][i] + 1);
            }

            printf("Thread for customer %d:\n", arg);

            // Perform the request
            printf("The following resources were requested:\n");
            int j;
            for (j = 0; j < NUM_RESOURCES; j++)
            {
                printf("Type %d: %d resources\n", j, request[j]);
            }
            bool request_result = request_res((int)arg, request);
            // Notifies of request result
            if (request_result)
            {
                printf("Request granted, system would be in a safe state\n");
            }
            else
            {
                printf("Request denied, system would be in an unsafe state\n");
            }
            // Free Resources
            int release[NUM_RESOURCES];
            for (i = 0; i < NUM_RESOURCES; i++)
            {
                release[i] = rand() % (allocation[(int)arg][i] + 1);
            }
            release_res((int)arg, release);
            printf("Resources released\n");

            // Update random
            rand_customer = rand() % NUM_CUSTOMERS;
            pthread_mutex_unlock(&lock);
        }
    }
}


//allocates the required resources
void alloc_res(int n_cust, int req[])
{	
	int j;
	for (j=0;j<NUM_RESOURCES;j++)
	{
		available[j] = available[j] - req[j];
		allocation[n_cust][j] = allocation[n_cust][j] + req[j];
		need[n_cust][j] = need[n_cust][j] - req[j];
	}
}

bool safe_state(int n_cust, int request[])
{
	bool finish[NUM_CUSTOMERS] = {false};
	bool change = true;
	bool res_avail;
	int work[NUM_RESOURCES];
	int i=0,j=0;
	
	for(j=0;j<NUM_RESOURCES;j++)
	{
		work[j] = available[j] - request[j];
		//the resources are temporarily allocated to the customer, are free'd at the end of loop
		allocation[n_cust][j] = allocation[n_cust][j] + request[j];
	}

	//while there are changes in each iteration (avoids stuck in loop errors)
	while(true)
	{
		if(finish[i] == false)
		{
			res_avail = true;
			for(j=0;j<NUM_RESOURCES;j++)
			{
				if(work[j] < need[i][j])
				{
					res_avail=false;
					break;
				}
			}
			if(res_avail)
			{
				finish[i] = true;
				change = true;
				for(j=0;j<NUM_RESOURCES;j++)
				{
					work[j] += allocation[i][j];
				}
			}
		}
		i++;
		if(i == NUM_CUSTOMERS)
		{
			if (change == false)
			{
				break;
			}
			else
			{
				change = false;
				i=0;
			}
		}
	}
	for (i=0;i<NUM_RESOURCES;i++)
	{
		allocation[n_cust][i] -= request[i];
	}
	for(i=0;i<NUM_CUSTOMERS;i++)
	{
		//if any of them are not done after an exit from the loop
		if(finish[i] == false)
		{
			return false;
		}
	}
	return true;
}

void reset_customer(int customer_no, int total_available[])
{
    int j;
    int cheapo;
    //if the customer requires less (50% change, this adds randomness)
    //generates a random # (either 1 or 2)
    cheapo = (rand() % 2) + 1;
    for (j = 0; j < NUM_RESOURCES; j++)
    {

        maximum[customer_no][j] = rand() % ((total_available[j] + 1)/cheapo);
        need[customer_no][j] = maximum[customer_no][j];
    }
}

void reset_all_customers(int total_available[])
{
    int i;
    for (i = 0; i < NUM_CUSTOMERS; i++)
    {
        reset_customer(i, total_available);
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
			return false;
		}
	}
	for (i=0;i<NUM_RESOURCES;i++)
	{
		if (request[i] <= available[i])
		{
			//do nothing again, so far its good
		}
		else
		{
			return false;
		}
	}
	//checks if the state is safe before allocation
	if (safe_state(n_customer, request))
	{
		alloc_res(n_customer, request);
		return true;
	}
	else
	{
		return false;
	}
}

// Release resources, returns true if successful
bool release_res(int n_customer, int release[])
{
	int j;
	for (j=0;j<NUM_RESOURCES;j++)
	{
		available[j] = available[j] + release[j];
		allocation[n_customer][j] = allocation[n_customer][j]  - release[j];
		need[n_customer][j] = need[n_customer][j] + release[j];
	}
	return true;
}


int main(int argc, char *argv[])
{
    // ==================== YOUR CODE HERE ==================== //
    time_t t;
    srand((unsigned) time(&t));
    rand_customer = 0;

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
            total_available[i - 1] = atoi(argv[i]);
			available[i - 1] = atoi(argv[i]);
		}
    }

    // Initialize the pthreads, locks, mutexes, etc.
	// Initializes the mutex lock
	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		printf("Mutex init failed\n");
		return 1;
	}
	// Create the array of threads
	pthread_t * threads = malloc(sizeof(pthread_t) * NUM_CUSTOMERS);

    // set all customers up
    reset_all_customers(total_available);

    // Create the threads
    int thread;
    int result;
    for (thread = 0; thread < NUM_CUSTOMERS; thread++)
    {
        result = pthread_create(&threads[thread], NULL, &customer_thread, thread);
        if (result != 0)
        {
            printf("Error creating the threads.\n");
            exit(-1);
        }
    }

    while (1){
    }

    /*
    for (thread = 0; thread < NUM_CUSTOMERS; thread++)
    {
        pthread_join(&threads[thread], NULL);
    }
    */

    // The threads will request and then release random numbers of resources

    // If your program hangs you may have a deadlock, otherwise you *may* have
    // implemented the banker's algorithm correctly
    
    // If you are having issues try and limit the number of threads (NUM_CUSTOMERS)
    // to just 2 and focus on getting the multithreading working for just two threads

    return EXIT_SUCCESS;
}
