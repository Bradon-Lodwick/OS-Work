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
		if(res.MEMORY[i] == 0)
		{
			BlockFound = 1;
			for(j=i;(j-i) < size;j++)
			{
				//if the scanned block has an allocated spot
				if (res.MEMORY[j] == 1)
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
					res.MEMORY[j] = 1;
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
		res.MEMORY[index+i] = 0;
	}
	return 1;
}

//void load_dispatch(char *dispatch_file, node_t *queue)
//{
//	
//}
