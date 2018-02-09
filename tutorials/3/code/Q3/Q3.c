#include <stdio.h>
#include <stdlib.h>
//Creates a Structure(similar to an object) Of student with its own attributes
struct Student{
	//Initialization of ID attribute of 9 characters (100xxxxxx)
	//These properties are shared by all Student structure "Objects"
	char ID[9];
	int age;
	int StartYear;
};

//initializing the other methods for the compiler to recognize when called
void save_student(struct Student S);

int main(void)
{
	//Creates new Student "Object" called NewStudent
	struct Student NewStudent;
	//prompts user to enter an input
	printf("Enter Student ID (100xxxxxx): ");
	//Reads input of up to 9 character long string for ID and assigns it to NewStudent's ID
	scanf("%s", &NewStudent.ID);
	//clears and makes a new line
	printf("\n");
	printf("Enter Students Age: ");
	//reads input as an int and assigns it to NewStudent's attributes
	scanf("%d", &NewStudent.age);
	printf("\n");
	printf("Enter Start Year of Student: ");
	scanf("%d", &NewStudent.StartYear);
	printf("\n");
	//Calls the save_student method
	save_student(NewStudent);
}

void save_student(struct Student S)
{
	//outputs status of code
	printf("Saving Student...\n");
	//initialization of FS file
	FILE *FS;
	//Sets FS to open students.txt with the write properties to make changes to it
	FS = fopen("students.txt", "w");
	//prints to FS's set file (students.txt) the properties of the Student received in the method
	fprintf(FS,"%s, %d, %d",S.ID,S.age,S.StartYear);
	printf("Saving Complete.\n");
	//closes the file
	fclose(FS);
}
