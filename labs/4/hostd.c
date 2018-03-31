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

	struct res freeres;
	freeres.printer = 2;
	freeres.scaner = 1;
	freeres.modem = 1;
	freeres.CD = 2;
	memset(freeres.memory, 0, sizeof freeres.memory);

	//TODO: FIGURE OUT HOW TO DECLARE QUEUES FOR Priority1, Priority2, and Priority3 and Realtime
	
	//puts all processes into the job dispatch list queue
	int time = 0;
	int run = lines;
	while(run > 0)
	{
		for (i=0;i < lines;i++)
		{
			
			if (processes[i].arrivalTime == time)
			{
				//put that shit in the appropriate queue
				//this means either the realtime queue
				//or the user job queue
			}
		}

		//TODO: THIS PART (REALTIME STUFF)
		//first iterate through the realtime queue looking for the first process
		//with enough free resources and fork into it	
		//this is because realtime processes have priority over resources
		
		//TODO: FIGURE OUT WHAT TO DO FOR THIS FOR LOOP
		//iterate through user job queue for the same reason
		for(...)
		{
			//if theres enough free resources
			if (check_res(freeres, current process) == 1)
			{
				//if theres enough free memory it will be allocated
				mem = alloc_mem(freeres, current process.mBytes);
				if(memP > 0)
				{
					//save the pointer to memory to process, and allocate resources
					Current Proc.memPointer = memP;
					alloc_res(freeres, current process);
					//put the process in the correct queue based on its priority
					//also fork it and immediately pause it
					processes[i].pid = fork();
					if (process[i].pid == 0)
					{
						//child
						execv(sigtrap.c process[i].processorTime);
					}
					else
					{
						//parent
						//interrupt child here
						signal(SIGINT, &process[i].pid);
					}
				}
		}
		
		//Now we can finally execute one time segment for the user jobs
		//Pop the head in each of the priority 1-3 queues and enqueue that to the lower priority
		proc P1 = Priority1.Pop();
		proc P2 = Priority2.Pop();
		proc P3 = priority3.Pop();
		
		//resume each of those popped heads, sleep for 1 second, then pause them again
		signal(SIGCONT, &P1.pid);
		signal(SIGCONT, &P2.pid);
		signal(SIGCONT, &P3.pid);
		P1.processorTime -= 1; P2.processorTime -= 1; P3.processorTime -= 1;
		sleep(1);
		signal(SIGINT, &P1.pid);
		signal(SIGINT, &P2.pid);
		signal(SIGINT, &P3.pid);
		if (P1.processorTime > 0)
		{
			Priority2.Enqueue(P1);
		}else{     }
		//TODO: ADD KILLING OF PROCESSES IN ELSE STATEMENT
		if (P2.processorTime > 0)
		{
			Priority3.enqueue(P2);
		}else {     }

		if(P3.processorTime > 0)
		{
			Priority3.Enqueue(P3);
		}else {     }
		

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

