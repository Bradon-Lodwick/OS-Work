#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	//allocates 256 characters in bytes of memory to the professor string pointer
	char *professor = calloc(1,256*sizeof(char));
	int NumStudents;
	//prompts user for input
	printf("Please Enter your name: ");
	//recieves input in form of string and sets it to professor string pointer
	scanf("%s", professor);
	printf("Please Enter the number of students to mark: ");
	scanf("%d", &NumStudents);
	//allocates enough memory for all students id's to be saved (each is 9 characters)
	int *student_ids = (int *) malloc(NumStudents*9);
	//allocates enough memory for all grades to be saved (is a 3 digit number)
	int *grades = (int *) malloc(NumStudents*3);
	//frees memory allocated to the professor pointer
	free(professor);
	free(student_ids);
	free(grades);
}
