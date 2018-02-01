#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	double arr[5] = {1.2, 5.5, 2.1, 3.3, 3.3};
	for (int i=1;i < 5; i++)
	{
		if (arr[i-1] < arr[i])
		{
			printf("Greater Than \n");
		}
		else if (arr[i-1] > arr[i])
		{
			printf("Less Than \n");
		}
		else
		{
			printf("the same \n");
		}
	}
}
