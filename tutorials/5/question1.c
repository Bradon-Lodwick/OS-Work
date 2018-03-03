#include <stdio.h>
#include <string.h>
#include <pthread.h>

// Thread function to print hello
void *hello()
{
	printf("Hello");
}

// Thread function to print goodbye
void *goodbye()
{
	printf("Goodbye");
}

int main()
{
	pthread_id pid1, pid2;
	pthread_create(&pid1, NULL, hello, NULL);
	pthread_create(&pid2, NULL, goodbye, NULL);
	pthread_join(&pid1);
	ptherad_join(&pid2);
}
