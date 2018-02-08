#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE *Nums;
	Nums = fopen("nums.txt", "r");
	if (Nums == NULL)
	{
		printf("File Not Found \n");
		exit (0);
	}
	int NumArray[10];
	int i;

	for (i=0;i<10;i++)
	{
		fscanf(Nums, "%d", &NumArray[i]);
	}
	fclose(Nums);

	printf("NumArray: \n");
	for (i=0;i<10;i++)
	{
		printf("%d \n", NumArray[i]);
	}
}

