#include <stdio.h>
#include <string.h>
#include <pthread.h>

int errorFound = 0;  // Holds whether or not an error was found globally so all threads can stop if an error was found in the user's solution

// Thread for horizontal check
void *horizontalThread(void *args)
{
}
// Thread for vertical check
void *verticalThread(void *args)
{
}
// Thread for square check
void *squareThread(void *args)
{
}

int main()
{
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

	// Calls the threads that will be used
	pthread_t horizontal, vertical, square;
	printf("to be printed before the threading");
	// Start the horizontal thread
	pthread_create(&horizontal, NULL, horizontalThread, sudoku);
	// Start the vertical thread
	pthread_create(&vertical, NULL, verticalThread, sudoku);
	// Start the square thread
	pthread_create(&square, NULL, squareThread, sudoku);
	// Join the threads
	pthread_join(horizontal, NULL);
	pthread_join(vertical, NULL);
	pthread_join(square, NULL);
}
