#include <stdio.h>
#include <string.h>

int main()
{
	// Defines the 2D array that holds the given sudoku
	int sudoku[9][9];
	// Initializes the array to the answer the user gave for their sudoku puzzle
	sudoku[9][9] = 
	{
		{5, 3, 4, 6, 7, 8, 9, 1, 2},
		{6, 7, 2, 1, 9, 5, 3, 4, 8},
		{1, 9, 8, 3, 4, 2, 5, 6, 7},

		{8, 5, 9, 7, 6, 1, 4, 2, 4},
		{4, 2, 6, 8, 5, 3, 7, 9, 1},
		{7, 1, 3, 9, 2, 4, 8, 5, 6},

		{9, 6, 1, 5, 3, 7, 2, 8, 4},
		{2, 8, 7, 4, 1, 9, 6, 3, 5},
		{3, 4, 5, 2, 8, 6, 1, 7, 9}
	}
}
