#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	//Initialization of variables
	char name[30], age[3], height[4];
	//output printing preset string "Enter your first name: "
	printf("Enter your first name: ");
	//input receiving name as a string
	scanf("%s", name);
	printf("\n");

	printf("Enter your age: ");
	scanf("%s", age);
	printf("\n");

	printf("Enter your height(in cm): ");
	scanf("%s", height);
	printf("\n");

	//printing out the name as a string(%s)
	printf("Entered Name: %s \n", name);
	printf("Entered Age: %s \n", age);
	printf("Entered Height: %s cm \n", height);
}
