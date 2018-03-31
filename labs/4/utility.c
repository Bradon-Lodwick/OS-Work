/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

// Define your utility functions here, you will likely need to add more...

int alloc_mem(resources res, int size)
{
	int i=0;
	int j;
	int BlockFound = 0;
	for (i=0;i<1024;i++)
	{
		if(res.memory[i] == 0)
		{
			BlockFound = 1;
			for(j=i;(j-i) < size;j++)
			{
				//if the scanned block has an allocated spot
				if (res.memory[j] == 1)
				{
					i=j;
					BlockFound = 0;
					break;
				}
			}
			//if the entiner block is clear
			if(BlockFound == 1)
			{
				//allocate the memory
				for(j=i;(j-i) < size;j++)
				{
					res.memory[j] = 1;
				}
				return i;
			}
		}
	}
	return -1;
}

int free_mem(resources res, int index, int size)
{
	int i;
	for (i=index;i < size;i++)
	{
		res.memory[index+i] = 0;
	}
	return 1;
}

#if 1 is returned then there are enough resources available
int check_res(resources res, proc P)
{
	#if the process requires more printers then available
	if (P.numPrinters > res.printer){return 0;}
	if (P.numScanners > res.scanner){return 0;}
	if (P.numModems > res.modem){return 0;}
	if (P.numCDs > res.modem){return 0;}
	return 1;
}

void alloc_res(resources res, proc P)
{
	res.printer -= P.numPrinters;
	res.scanner -= P.numScanners;
	res.modem -= P.numModems;
	res.CD -= P.numCDs;
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

void *load_dispatch(char *dispatchlistname, struct proc *processes, int lines)
{
	// Load the dispatchlist
	FILE *dispatchlist;
	dispatchlist = fopen(dispatchlistname, "r");
	if (dispatchlist == NULL) {
		printf("Error opening dispatchlist\n");
	}
	else {
		int processIndex;
		for (processIndex = 0; processIndex < lines; processIndex++){
			fscanf(dispatchlist, "%d, %d, %d, %d, %d, %d, %d, %d\n", 
								&processes[processIndex].arrivalTime, &processes[processIndex].priority, &processes[processIndex].processorTime, 
								&processes[processIndex].mBytes, &processes[processIndex].numPrinters, &processes[processIndex].numScanners, 
								&processes[processIndex].numModems, &processes[processIndex].numCDs);
		}
	}
			
}
