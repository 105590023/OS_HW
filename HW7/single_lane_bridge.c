#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t accessible;

void *ThroughBridge()
{
	sem_wait(&accessible);
	printf("Someone is crossing bridge.\n");
	sleep(1);
	sem_post(&accessible);
}

int main(int argc, char **argv)
{
	int southboundNumber = atoi(argv[1]);
	int northboundNumber = atoi(argv[2]);
	int i;
	void *ret;
	pthread_t southbound[southboundNumber], northbound[northboundNumber];
	sem_init(&accessible, 0, 1);
	
	for(i = 0; i < southboundNumber; i++)
	{
        pthread_create(&southbound[i], NULL, ThroughBridge, NULL);
    }
    for(i = 0; i < northboundNumber; i++)
    {
        pthread_create(&northbound[i], NULL, ThroughBridge, NULL);
    }
    for(i = 0; i < southboundNumber; i++)
	{
        pthread_join(southbound[i], NULL);
    }
    for(i = 0; i < northboundNumber; i++)
    {
        pthread_join(northbound[i], NULL);
    }
}

