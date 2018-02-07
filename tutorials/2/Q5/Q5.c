#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double euclid_dist(double x1, double x2, double y1, double y2);

int main(void)
{
	srand(time(NULL));
	double x1,x2,y1,y2;
	for (int i=0;i<10;i++)
	{
		x1 = rand() % 101;
		x2 = rand() % 101;
		y1 = rand() % 101;
		y2 = rand() % 101;
		printf ("Vector 1: x = %lf, y = %lf \n",x1,y1);
		printf ("Vector 2: x = %lf, y = %lf \n",x2,y2);
		printf ("Euclidean Distance = %lf \n", euclid_dist(x1,y1,x2,y2));
	}
}

double euclid_dist(double x1,double y1,double x2,double y2)
{
	return sqrt(pow(x1-x2,2) + (pow(y1-y2,2)));
}
