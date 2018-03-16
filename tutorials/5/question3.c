#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct student
{
	char Name[20];
	char StudentID[9];
	double grade;
};

void *bellcurve(struct student *BS)
{
	(*BS).grade = (*BS).grade * 1.50;
}

int main()
{
	struct student S[5];
	int i;
	pthread_t id[5];
	printf("Please Enter 5 Students info: \n");
	for (i=0;i<5;i++)
	{
		printf(" Name: ");
		scanf("%s", &S[i].Name);
		printf("\n Student ID:");
		scanf("%s", &S[i].StudentID);
		printf("\n Grade:");
		scanf("%lf", &S[i].grade);
		printf("\n \n");
	}
	for (i=0;i<5;i++)
	{
		pthread_create(&id[i],NULL,bellcurve,&S[i]);
	}
	for(i=0;i<5;i++)
	{
		pthread_join(id[i], NULL);
	}
	for(i=0;i<5;i++)
	{
		printf("Name: %s \n", S[i].Name);
		printf("Student ID: %s \n", S[i].StudentID);
		printf("Grade: %lf \n", S[i].grade);
	}
}
