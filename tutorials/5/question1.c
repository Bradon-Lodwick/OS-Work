#include <stdio.h>
#include <string.h>
#include <pthread.h>

// Thread function to print hello
void *hello()
{
	int random = rand() % 10;
	sleep(random);
	printf("Hello");
}

// Thread function to print goodbye
void *goodbye()
{
	int random = rand() % 10;
	sleep(random);
	printf("Goodbye");
}

int main()
{
	pthread_t pid1; 
	pthread_t pid2;
	pthread_create(&pid1, NULL, hello, NULL);
	pthread_create(&pid2, NULL, goodbye, NULL);
	pthread_join(pid1, NULL);
	pthread_join(pid2, NULL);
}
