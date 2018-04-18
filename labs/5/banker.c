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

// Test function for testing the threads, TODO can be removed after testing complete
void* test(void *arg)
{
	printf("thread created\n");
}

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

//checks if the given request will result in a safe state
bool safe_state(int n_cust, int request[])
{
	bool finish[NUM_CUSTOMERS] = {false};
	bool allfin = false;
	int work[NUM_RESOURCES];
	int i=0;
	int j=0;
	int fincount=0;
	//This section also clones available into work since it cannot be set in a single line because C is a beautiful and efficient language
	//start by simulating the requested resources going to the customer asking
	for(j=0;j<NUM_RESOURCES;j++)
	{
		work[j] = available[j] - request[j];
		//the resources are temporarily allocated to the customer, are free'd at the end of loop
		allocation[n_cust][j] = allocation[n_cust][j] + request[j];
	}
	bool res_avail = true;
	while(allfin == false)
	{
		//fincount is an integer to assure that this loop exits when no changes happen for 2 loop iterations
		fincount = 0;
		for(i=0;i<NUM_CUSTOMERS;i++)
		{
			res_avail = true;

			//checks if the needed resources for customer i are available
			for(j=0;j<NUM_RESOURCES;j++)
			{
				if (work[j] > need[n_cust][j])
				{
					res_avail = false;
				}
			}
			//if the resources can be allocated afterwards
			if(res_avail && finish[n_cust] == false)
			{
				//free up resources
				for(j=0;j<NUM_RESOURCES;j++)
				{
					work[j] = work[j] +  allocation[n_cust][j];
				}
				finish[i] = true;
			}
			//otherwise if the customer was already finished last step
			else if (finish[i])
			{
				//increment the deadlock counter
				fincount++;
			}

			//every time we iterate through all customers check if they're all done
			if (i == 4)
			{
				allfin = true;
				for(j=0;j<NUM_CUSTOMERS;j++)
				{
					//if any of them aren't done the system isnt done
					if(finish[i] == false)
					{
						allfin = false;
						//increment the deadlock counter
						fincount++;
					}
				}
				//if no changes occured within the last iteration
				if(fincount == NUM_CUSTOMERS)
				{
					allfin = true;
				}
			}
		}
	}
	//free the temporary resources
	for(j=0;j<NUM_RESOURCES;j++)
	{
		allocation[n_cust][j] = allocation[n_cust][j] - request[j];
	}
	//if the exit of the loop was due to an unsafe state
	if(fincount == NUM_CUSTOMERS)
	{
		return false;
	}
	else
	{
		return true;
	}

}

void reset_customer(int customer_no, int total_available[])
{
    int j;
    for (j = 0; j < NUM_RESOURCES; j++)
    {
        maximum[customer_no][j] = rand() % (total_available[j] + 1);
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
			//TODO: RAISE ERROR CONDITION
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
			//Process must wait
			return false;
		}
	}
	//checks if the state is safe before allocation
	if (safe_state(n_customer, request))
	{
		//TODO: try and remember how to pass an entire list in C
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
        // Creates the thread TODO change to actual function
        result = pthread_create(&threads[thread], NULL, &customer_thread, thread);
        if (result != 0)
        {
            printf("Error creating the threads.\n");
            exit(-1);
        }
    }

    for (thread = 0; thread < NUM_CUSTOMERS; thread++)
    {
        pthread_join(&threads[thread], NULL);
    }

    // The threads will request and then release random numbers of resources

    // If your program hangs you may have a deadlock, otherwise you *may* have
    // implemented the banker's algorithm correctly
    
    // If you are having issues try and limit the number of threads (NUM_CUSTOMERS)
    // to just 2 and focus on getting the multithreading working for just two threads

    return EXIT_SUCCESS;
}
