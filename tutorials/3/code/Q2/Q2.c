#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	//File Initialization
	FILE *Nums;
	//Opening file nums.txt in read mode under Nums Object
	Nums = fopen("nums.txt", "r");
	//If the file cannot be read
	if (Nums == NULL)
	{
		//print an error and exit
		printf("File Not Found \n");
		exit (0);
	}
	int NumArray[10];
	int i;

	//for loop for 10 iterations
	for (i=0;i<10;i++)
	{
		//reads lines of the file one by one and assigns them to NumArray
		fscanf(Nums, "%d", &NumArray[i]);
	}
	//closes the file
	fclose(Nums);

	printf("NumArray: \n");
	for (i=0;i<10;i++)
	{
		//prints each value in NumArray(which was read from nums.txt)
		printf("%d \n", NumArray[i]);
	}
}

