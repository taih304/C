#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define PSHARED 0
#define SEM_VAL	1

#define RANGE 10000

int share_value;

void *thread_function(void *ptr);

sem_t mutex;

int main()
{  
    sem_init(&mutex, PSHARED, SEM_VAL);

	pthread_t thread_1, thread_2, thread_3;
	int thread_1_return, thread_2_return, thread_3_return;

	thread_1_return = pthread_create(&thread_1, NULL, thread_function, "Thread 1");
    thread_2_return = pthread_create(&thread_2, NULL, thread_function, "Thread 2");
    thread_3_return = pthread_create(&thread_3, NULL, thread_function, "Thread 3");
	pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    pthread_join(thread_3, NULL);
    printf("share_value after executing 2 threads: %d\n", share_value);//30000
}

void *thread_function(void *ptr){
	for (int i = 0; i < RANGE; i++) {
		if (!sem_wait(&mutex)){
			share_value++;
			sem_post(&mutex);
		} else printf("%s fails to lock\n", (char*)ptr);
   }   
}