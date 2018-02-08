#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	char name[30], age[3], height[4];
	printf("Enter your first name: ");
	scanf("%s", name);
	printf("\n");

	printf("Enter your age: ");
	scanf("%s", age);
	printf("\n");

	printf("Enter your height(in cm): ");
	scanf("%s", height);
	printf("\n");

	printf("Entered Name: %s \n", name);
	printf("Entered Age: %s \n", age);
	printf("Entered Height: %s cm \n", height);
}
