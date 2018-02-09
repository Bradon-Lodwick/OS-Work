#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//creates structure called grade (is very similar to an object) with its variable properties
struct grade
{
	int student_id;
	int mark;
};

void grade_students(struct grade *grades, int num_students)
{
	//initializes file F
	FILE *F;
	//Sets file F to write into grades.txt
	F = fopen("grades.txt", "w");
	//initialization of i variable for the for loop ahead
	int i;
	//initialization and set of sum
	int sum;
	sum = 0;
	//iterates through all students
	for (i=0;i<num_students;i++)
	{
		//adds all grades read from pointer object to sum
		sum += grades[i].mark;
		//writes the pointer object's properties to the file F (grades.txt) and makes a new line for next write
		fprintf(F,"%d, %d \n", grades[i].mark, grades[i].student_id);
	}
	//initialization and set of average
	float avg;
	avg = sum/num_students;
	//writes average to file as Float
	fprintf(F, "average = %f \n", avg);
	//initialization and set of Standard Deviation
	float SD;
	SD = 0.0;
	for(i=0;i<num_students;i++)
	{
		//follows the Standard Deviation formula by squaring the difference between each mark and the average
		SD += pow(grades[i].mark - avg,2);
	}
	//follows the Standard Deviation formula by then square rooting the current difference sum divided by the total number of students
	SD = sqrt(SD/num_students);
	//writes standard deviation to file
	fprintf(F, "Standard Deviation = %f \n", SD);
	//closes output file
	fclose(F);
}

int main(void)
{
	//allocates enough memory for professor string pointer
	char *professor = calloc(1,256*sizeof(char));
	int NumStudents;
	printf("Please Enter your name: ");
	scanf("%s", professor);
	printf("Please Enter the number of students to mark: ");
	scanf("%d", &NumStudents);
	//intialization of j variable for the for loop ahead (needed in C)
	int j;
	//creates new grade object as a pointer and allocates (9 characters + 3 digit number) bytes to it
	struct grade *grades = calloc(NumStudents, 12);

	//loops through all students
	for(j=0;j<NumStudents;j++)
	{
		//prompts user for input
		printf("Enter the Student id: ");
		//receives input as int and sets it to object j of the pointer object's student id
		scanf("%d", &grades[j].student_id);
		printf("\n");
		printf("Enter the Grade: ");
		scanf("%d", &grades[j].mark);
		printf("\n");
	}
	//calls for grade_students function, gives the pointer object grades, and the number of students
	grade_students(grades, NumStudents);
	//frees allocated memory
	free(professor);
	free(grades);
}
