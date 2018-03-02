#include <stdio>
#include <stdlib>

int subMatrix(int matrix[9][9])
{
	int blank[9];

	int i, j, k;
	int bL = 0;
	int bR = 2;
	int bT = 0;
	int bB = 2;
	int value;
	int result = 1;

	for(i = 0; i < 9; i++)
	{
		blank[9] = {0,0,0,0,0,0,0,0,0};
		for(j = bT; i <= bB; i++)
		{
			for(k = bL; i= <bR; i++)
			{
				value = matrix[j][k];
				if(blank[value] == 1)
				{
					printf("error in square %d", i);
					result = 0;
					break;
				}
				if(blank[value] == 0)
				{
					blank[value] = 1;
				}

			}

			if(blank[value] == 1)
			{
				break;
			}

			bL += 3;
			bR += 3;
		}
		if(((i + 1) % 3) == 0)
		{
			bT += 3;
			bB += 3;
			bL = 0;
			bR = 0;
		}
	}
	return result;
}
