#include <pthread.h>
#include "UID.h"
#include <stdio.h>

#define THREADS_NUM 10
#define SIZE 1000
#define NUM 100
UID_t uids[SIZE];

void *CreateUID1(void *index)
{
	int i = (size_t)index * NUM + 1;
	int limit = i + NUM;
	for (; i < limit; i++)
	{
		uids[i] = UIDCreate();
	}
	return NULL;
}

int main()
{
	pthread_t threads[THREADS_NUM];
	size_t i = 0, j = 0;

	for (i = 0; i < THREADS_NUM; ++i)
	{
		pthread_create(&threads[i], NULL, CreateUID1, (void *)i);
	}

	for (i = 0; i < THREADS_NUM; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	for (i = 0; i < SIZE; i++)
	{
		printf("time : %ld\n", uids[i].time);
		for (j = i + 1; j < SIZE; j++)
		{

			if (UIDIsSame(uids[i], uids[j]) && i != j)
				printf("%s i: %ld j: %ld pid of i: %d pid of j: %d\n", "true", i, j, uids[i].pid, uids[j].pid);
		}
	}

	return 0;
}
