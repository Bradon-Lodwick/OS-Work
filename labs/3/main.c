#include<stdio.h>
#include <string.h>
#include <pthread.h>

// Defines the 2D array that holds the given sudoku
int sudoku[9][9] = {
	{5, 3, 4, 6, 7, 8, 9, 1, 2},
	{6, 7, 2, 1, 9, 5, 3, 4, 8},
	{1, 9, 8, 3, 4, 2, 5, 6, 7},

	{8, 5, 9, 7, 6, 1, 4, 2, 4},
	{4, 2, 6, 8, 5, 3, 7, 9, 1},
	{7, 1, 3, 9, 2, 4, 8, 5, 6},

	{9, 6, 1, 5, 3, 7, 2, 8, 4},
	{2, 8, 7, 4, 1, 9, 6, 3, 5},
	{3, 4, 5, 2, 8, 6, 1, 7, 9}
};

int *horizontalThread()
{
	int i;  // Loop counter for row loop
	int result = 1;  // Bool value for if the answer was right
	int j;  // Loop counter for column loop
	int k;  // Loop counter for reset
	int CHK[9] = {0};  // Bool array holding if each number in row passes check
	int n;  // Current number being checked

	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			//Nums[row][col]
			n = sudoku[i][j];

			if (CHK[n-1] == 0)
			{
				CHK[n-1] = 1;
			}
			else
			{
				printf("Horizontal error in row %d, col %d\n", i + 1, j + 1);
				result = 0;
				break; 
			}
		}
		for(k = 0; k < 9; k++)
		{
			CHK[k] = 0;
		}
	}
	return result;
}

// Thread for vertical check
int *verticalThread()
{
	int i;  // Loop counter for column loop
	int result = 1;  // Bool value for if the answer was right
	int j;  // Loop counter for row loop
	int k;  // Loop counter for reset
	int CHK[9] = {0};  // Bool array holding if each number in column passes check
	int n;  // Current number being checked

	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			//Nums[row][col]
			n = sudoku[j][i];

			if (CHK[n-1] == 0)
			{
				CHK[n-1] = 1;
			}
			else
			{
				printf("Vertical error in row %d, col %d\n", j + 1, i + 1);
				result = 0;
				break; 
			}
		}
		for(k = 0; k < 9; k++)
		{
			CHK[k] = 0;
		}
	}
	return result;	
}

// Thread for square check
int *squareThread()
{
	int blank[9] = {0};

	int i, j, k;
	int bL = 0;
	int bR = 2;
	int bT = 0;
	int bB = 2;
	int value;
	int result = 1;
	int z;

	for(i = 0; i < 9; i++)
	{
		for(z = 0; z < 5; z++)
		{
			blank[z] = 0;
		}

		for(j = bT; j <= bB; j++)
		{
			for(k = bL; k <= bR; k++)
			{
				value = sudoku[j][k] - 1;
				if(blank[value] == 1)
				{
					printf("Squaerror in square %d\n", i + 1);
					result = 0;
					break;
				}
				if(blank[value] == 0)
				{
					blank[value] = 1;
				}
				else
				{
					printf("Wat?");
				}
			}
			bL += 3;
			bR += 3;
			if(blank[value] == 1)
			{
				break;
			}


		}
		if(((i + 1) % 3) == 0)
		{
			bT += 3;
			bB += 3;
			bL = 0;
			bR = 2;
		}
	}
	return result;

}

int main()
{
	
	// Calls the threads that will be used
	pthread_t horizontal, vertical, square;
	// Start the horizontal thread
	pthread_create(&horizontal, NULL, horizontalThread, NULL);
	// Start the vertical thread
	pthread_create(&vertical, NULL, verticalThread, sudoku);
	// Start the square thread
	pthread_create(&square, NULL, squareThread, sudoku);
	// Join the threads
	pthread_join(horizontal, NULL);
	pthread_join(vertical, NULL);
	pthread_join(square, NULL);
}
