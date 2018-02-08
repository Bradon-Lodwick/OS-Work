#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *professor = calloc(1,256*sizeof(char));
	int NumStudents;
	printf("Please Enter your name: ");
	scanf("%s", professor);
	printf("Please Enter the number of students to mark: ");
	scanf("%d", &NumStudents);
	int *student_ids = (int *) malloc(NumStudents*9);
	int *grades = (int *) malloc(NumStudents*3);
	free(professor);
	free(student_ids);
	free(grades);
}
