#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct grade
{
	int student_id;
	int mark;
};

void grade_students(struct grade *grades, int num_students)
{
	FILE *F;
	F = fopen("grades.txt", "w");
	int i;
	int sum;
	sum = 0;
	for (i=0;i<num_students;i++)
	{
		sum += grades[i].mark;
		fprintf(F,"%d, %d \n", grades[i].mark, grades[i].student_id);
	}
	float avg;
	avg = sum/num_students;
	fprintf(F, "average = %f \n", avg);
	float SD;
	SD = 0.0;
	for(i=0;i<num_students;i++)
	{
		SD += pow(grades[i].mark - avg,2);
	}
	SD = sqrt(SD/num_students);
	fprintf(F, "Standard Deviation = %f \n", SD);
}

int main(void)
{
	char *professor = calloc(1,256*sizeof(char));
	int NumStudents;
	printf("Please Enter your name: ");
	scanf("%s", professor);
	printf("Please Enter the number of students to mark: ");
	scanf("%d", &NumStudents);
	int j;

	struct grade *grades = calloc(NumStudents, 12);

	for(j=0;j<NumStudents;j++)
	{
		printf("Enter the Student id: ");
		scanf("%d", &grades[j].student_id);
		printf("\n");
		printf("Enter the Grade: ");
		scanf("%d", &grades[j].mark);
		printf("\n");
	}
	grade_students(grades, NumStudents);
	free(professor);
	free(grades);
}
