#include <stdio.h>
#include <stdlib.h>
struct Student{
	char ID[9];
	int age;
	int StartYear;
};

void save_student(struct Student S);

int main(void)
{
	struct Student NewStudent;
	printf("Enter Student ID (100xxxxxx): ");
	scanf("%s", &NewStudent.ID);
	printf("\n");
	printf("Enter Students Age: ");
	scanf("%d", &NewStudent.age);
	printf("\n");
	printf("Enter Start Year of Student: ");
	scanf("%d", &NewStudent.StartYear);
	printf("\n");
	save_student(NewStudent);
}

void save_student(struct Student S)
{
	printf("Saving Student...\n");
	FILE *FS;
	FS = fopen("students.txt", "w");
	fprintf(FS,"%s, %d, %d",S.ID,S.age,S.StartYear);
	printf("Saving Complete.\n");
	fclose(FS);
}
