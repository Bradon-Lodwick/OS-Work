#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	for (int i=1;i <= 10;i++)
	{
			printf("%d - ", i);
			if (i%2 == 0)
			{
				printf("Even \n");
			}
			else
			{
				printf("Odd \n");
			}
	}
}
