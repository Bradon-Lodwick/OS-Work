/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"
#include "utility.h"
#include "hostd.h"

// Put macros or constants here using #define
#define MEMORY 1024

// Put global environment variables here

// Define functions declared in hostd.h here
// Defines a function that counts the number of lines in a file
int countlines(char *file);

int main(int argc, char *argv[])
{
    // ==================== YOUR CODE HERE ==================== //
    // The name of the file with all the processes in it
	int i=0;
	char *filename = "dispatchlist";
	// Loads the dispatch lst into an array of processes
	int lines = countlines(filename);
	struct proc processes[lines];
	load_dispatch(filename, &processes, lines);
	
	//TODO IMPORTANT: WHEN KILLING A PROCESS DECREASE RUN BY 1

	struct resources freeres;
	freeres.printer = 2;
	freeres.scanner = 1;
	freeres.modem = 1;
	freeres.CD = 2;
	memset(freeres.memory, 0, sizeof freeres.memory);
	
	//puts all processes into the job dispatch list queue
	int time = 0;
	int memP = -1;
	int run = lines;
	node_t * tempProc;
	while(run > 0)
	{
		for (i=0;i < lines;i++)
		{
			//pushes the processes
			if (processes[i].arrivalTime == time)
			{
				//put that shit in the appropriate queue
				//this means either the realtime queue
				//or the user job queue
				if (processes[i].priority == 0)
				{
					push(0, processes[i]);
				}
				else
				{
					push(4, processes[i]);
				}
			}
		}
		
		//TODO: THIS PART (REALTIME STUFF)
		//first iterate through the realtime queue looking for the first process
		//with enough free resources and fork into it	
		//this is because realtime processes have priority over resources
		
		
		
		//iterate through user job queue for the same reason
		for(...)
		{
			tempProc = pop(4);
			//if theres enough free resources
			if (check_res(freeres, tempProc->process) == 1)
			{
				//if theres enough free memory it will be allocated
				memP = alloc_mem(freeres, tempProc->process.mBytes);
				if(memP > 0)
				{
					//save the pointer to memory to process, and allocate resources
					tempProc->process.memPointer = memP;
					alloc_res(freeres, tempProc->process);
					//put the process in the correct queue based on its priority
					//also fork it and immediately pause it
					tempProc->process.pid = fork();
					if (tempProc->process.pid == 0)
					{
						//child
						execv("./process %d", tempProc->process.processorTime);
					}
					else
					{
						//parent
						//interrupt child here
						signal(SIGINT, tempProc->&process.pid);
					}
				}
			}
			else
			{
				//resources couldn't be allocated
			}
		}
		
		//Now we can finally execute one time segment for the user jobs
		//Pop the head in each of the priority 1-3 queues and enqueue that to the lower priority
		node_t * P1 = pop(1);
		node_t * P2 = pop(2);
		node_t * P3 = pop(3);
		
		//resume each of those popped heads, sleep for 1 second, then pause them again
		signal(SIGCONT, P1->process.pid);
		signal(SIGCONT, P2->process.pid);
		signal(SIGCONT, P3->process.pid);
		P1->process.processorTime -= 1; P2->process.processorTime -= 1; P3->process.processorTime -= 1;
		sleep(1);
		signal(SIGTSTP, P1->process.pid);
		signal(SIGTSTP, P2->process.pid);
		signal(SIGTSTP, P3->process.pid);
		if (P1->process.processorTime > 0)
		{
			push(2, P1);
		}else{ signal(SIGINT,P1->process.pid); run++;}
		if (P2->process.processorTime > 0)
		{
			push(3, P2);
		}else { signal(SIGINT,P2->process.pid); run++;}

		if(P3->process.processorTime > 0)
		{
			push(3, P3);
		}else { signal(SIGINT,P3->process.pid); run++;}

		

		time++;
	}
	
    // Add each process structure instance to the job dispatch list queue

    // Iterate through each item in the job dispatch list, add each process
    // to the appropriate queues

    // Allocate the resources for process before it's executed

    // Execute the process binary using fork and exec

    // Perform the appropriate signal handling / resource allocation and de-alloaction

    // Repeat until all processes have been executed, all queues are empty
     
    return EXIT_SUCCESS;
}

