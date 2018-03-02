#include <stdio.h>
#include <stdlib.h>

bool vertironipepperoni(int *Nums[9][9])
{
	int i;
	bool Result = true;
	int j;
	int k;
	int *CHK[9];
	for(i = 0; i < 9; i++)
	{
		for(j=0;j<9;j++)
		{
			//Nums[row][col]
			n = &Nums[j][i];
			if (&CHK[n-1] == 0)
			{
				&CHK[n-1] = 1;
			}
			else
			{
				printf("Error in col %d", j);
				Result = false;
				break; 
			}
		}
		for(j=0;j<9;j++)
		{
			&CHK[j] = 0;
		}
	}
	return Result;	
}
