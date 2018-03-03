#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *bellcurve(double *grade)
{
	*grade = *grade * 1.50;
}

int main()
{
	int i;
	double grades[5];
	pthread_t id[5];
	printf("Please Enter 5 Grades: \n");
	for (i=0;i<5;i++)
	{
		scanf("%lf", &grades[i]);
	}
	for (i=0;i<5;i++)
	{
		pthread_create(&id[i],NULL,bellcurve,&grades[i]);
	}
	for(i=0;i<5;i++)
	{
		pthread_join(id[i], NULL);
	}
	for(i=0;i<5;i++)
	{
		printf("Grade %d : %lf \n", i, grades[i]);
	}
}
