/*
 *Learn to use pthread
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_NUM 5
void *rountine0(void *);
void *rountine1(void *);
void *rountine2(void *);
void *rountine3(void *);
void *rountine4(void *);
void *rountine5(void *);

pthread_t tid[THREAD_NUM];
pthread_attr_t tattr[THREAD_NUM];

int main(void)
{
	int ret;
	
	pthread_attr_init(&tattr[0]);
	ret = pthread_create(&tid[0], NULL, rountine0, &tid[0]);
	
	pthread_join(tid[0], NULL);
	return 0;
}

void *rountine0(void *data)
{
	printf("Thread with default attr, tid = %ld\n",
	       *(unsigned long *)data);
	
	/* because of pthread_join, it's ok to pass stack arg to rountine1 */
	pthread_create(&tid[1], NULL, rountine1, data);
	sleep(1);
	pthread_join(tid[1], NULL);
	return NULL;
}

void *rountine1(void *data)
{
	int i;
	for (i = 0; i < 5; i++){
		printf("rountine1 %ld\n", *(unsigned long *)data);
		fflush(stdout);
	}
	pthread_create(&tid[2], NULL, rountine2, NULL);
	pthread_detach(tid[2]); /* !!! */
	pthread_create(&tid[3], NULL, rountine3, NULL);
	pthread_join(tid[3], NULL);
	return data;
}

void *rountine2(void *data)
{
	int i, j;
	for (i = 0; i < 5; i++){
		printf("rountine2 \n");
		for(j = 0; j < 200000; j++);
	}
	return data;
}

void *rountine3(void *data)
{
	printf("Hello");
}

