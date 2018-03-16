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
	char *filename = "dispatchlist";
	// Count the number of lines in the dispatchlist
	int lines = countlines(filename);
    // Load the dispatchlist
	FILE *dispatchlist;
	dispatchlist = fopen(filename, "r");
	// Checks to make sure the dispatchlist was loaded correctly
	if (dispatchlist == NULL) {
		printf("Error opening dispatchlist\n");
		return -1;
	}
	else {
		struct process processes[lines];
		int processIndex;
		for (processIndex =0; processIndex < lines; processIndex++){
			fscanf(dispatchlist, "%d, %d, %d, %d, %d, %d, %d, %d\n", 
								&processes[processIndex].arrivalTime, &processes[processIndex].priority, &processes[processIndex].processorTime, 
								&processes[processIndex].mBytes, &processes[processIndex].numPrinters, &processes[processIndex].numScanners, 
								&processes[processIndex].numModems, &processes[processIndex].numCDs);
		}
	}
    // Add each process structure instance to the job dispatch list queue

    // Iterate through each item in the job dispatch list, add each process
    // to the appropriate queues

    // Allocate the resources for each process before it's executed

    // Execute the process binary using fork and exec

    // Perform the appropriate signal handling / resource allocation and de-alloaction

    // Repeat until all processes have been executed, all queues are empty
     
    return EXIT_SUCCESS;
}

int countlines(char *file) {
	FILE *fp = fopen(file, "r");
	int ch = 0;
	int lines = 0;
	if (fp == NULL) {
		printf("error counting lines: can't open file");
		return -1;
	}
	else {
		lines++;
		while(!feof(fp)) {
				ch = fgetc(fp);
				if (ch == '\n') {
					lines++;
				}
		}
		return lines;
	}
};

