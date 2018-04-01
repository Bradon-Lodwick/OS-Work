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
	int RealTimeRunning = 0; node_t * RealTimeNode;
	int memP = -1;
	int run = lines;
	node_t * tempProc; node_t * RealProc;
	node_t * Priority_1; node_t * Priority_2; node_t * Priority_3;
	node_t * Realtime; node_t * UserJob;
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
					push(&Realtime, processes[i]);
				}
				else
				{
					push(&UserJob, processes[i]);
				}
			}
		}
		
		//first iterate through the realtime queue looking for the first process with enough free resources and fork into it	
		//this is because realtime processes have priority over resources
		RealProc = &Realtime;
		while((RealProc->next != NULL)&&(RealTimeRunning == 0))
		{
			if (check_res(freeres, RealProc->process) == 1)
			{
				memP = alloc_mem(freeres, RealProc->process.mBytes);
				if(memP > 0)
				{
					//save the pointer to memory to process, and allocate resources
					RealProc->process.memPointer = memP;
					alloc_res(freeres, RealProc->process);
					//put the process in the correct queue based on its priority
					//also fork it and immediately pause it
					RealProc->process.pid = fork();
					if (RealProc->process.pid == 0)
					{
						//child
						execv("./process %d", RealProc->process.processorTime);
					}
					else
					{
						//parent
						//interrupt child here
						signal(SIGINT, RealProc->process.pid);
						RealTimeNode = remove_node(&Realtime, RealProc);
						RealTimeRunning = 1;
					}
				}
			}
			RealProc = RealProc->next;
		}
		
		
		
		tempProc = &UserJob;
		//iterate through user job queue for the same reason as above
		do 
		{
			//if theres enough free resources
			if (check_res(freeres, tempProc->process) == 1)
			{
				//if theres enough free memory it will be allocated
				memP = alloc_mem(&freeres, tempProc->process.mBytes);
				if(memP > 0)
				{
					//save the pointer to memory to process, and allocate resources
					tempProc->process.memPointer = memP;
					alloc_res(&freeres, tempProc->process);
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
						signal(SIGINT, tempProc->process.pid);
					}
				}
			}
			else
			{
				//resources couldn't be allocated
			}
			tempProc = tempProc->next;
		}while(tempProc != NULL);
		
		//Now we can finally execute one time segment for the user jobs
		//Pop the head in each of the priority 1-3 queues and enqueue that to the lower priority
		node_t * P1 = remove_node(&Priority_1, Priority_1);
		node_t * P2 = remove_node(&Priority_2, Priority_2);
		node_t * P3 = remove_node(&Priority_3, Priority_3);
		
		//resume each of those popped heads, sleep for 1 second, then pause them again
		signal(SIGCONT, P1->process.pid);
		signal(SIGCONT, P2->process.pid);
		signal(SIGCONT, P3->process.pid);
		
		signal(SIGCONT, RealTimeNode->process.pid);

		P1->process.processorTime -= 1; P2->process.processorTime -= 1; P3->process.processorTime -= 1;
		RealTimeNode->process.processorTime -= 1;
		sleep(1);
		signal(SIGTSTP, P1->process.pid);
		signal(SIGTSTP, P2->process.pid);
		signal(SIGTSTP, P3->process.pid);
		signal(SIGTSTP, RealTimeNode->process.pid);
		//check if any of the processes have completed their runtime
		if (P1->process.processorTime > 0)
		{
			push(&Priority_2, P1->process);
		}else{ signal(SIGINT,P1->process.pid); run++; free_mem(freeres, P1->process.memPointer, P1->process.mBytes)}
		if (P2->process.processorTime > 0)
		{
			push(&Priority_3, P2->process);
		}else { signal(SIGINT,P2->process.pid); run++; free_mem(freeres, P2->process.memPointer, P2->process.mBytes)}
		if(P3->process.processorTime > 0)
		{
			push(&Priority_3, P3->process);
		}else { signal(SIGINT,P3->process.pid); run++; free_mem(freeres, P3->process.memPointer, P3->process.mBytes)}
		
		if(RealTimeNode->process.processorTime == 0)
		{
			RealTimeRunning = 0;
			signal(SIGINT, RealTimeNode->process.pid);
			run++;
			free_mem(freeres, RealTimeNode->process.memPointer, RealTimeNode->process.mBytes);
		}

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

