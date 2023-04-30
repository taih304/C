#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void *suspend_thread_func(void *ptr);
void *resume_thread_func(void *ptr);

int number = 0;
int suspendFlag = 0;
int suspend_thread_return, resume_thread_return;

pthread_t suspend_thread, resume_thread;
pthread_mutex_t suspendMutex;
pthread_cond_t resumeCond;

void suspendThread()
{
    if(!pthread_mutex_lock(&suspendMutex)){
        suspendFlag = 1;
        pthread_mutex_unlock(&suspendMutex);
    }
}

void resumeThread()
{ 
    if(!pthread_mutex_lock(&suspendMutex)){
        suspendFlag = 0;
        pthread_cond_broadcast(&resumeCond);
        pthread_mutex_unlock(&suspendMutex);
    }
}

// if suspended, suspend until resumed
void checkSuspend()
{ 
    if (!pthread_mutex_lock(&suspendMutex)){
        while (suspendFlag != 0) pthread_cond_wait(&resumeCond, &suspendMutex);
        pthread_mutex_unlock(&suspendMutex);
    }
}

int main(void){
    pthread_mutex_init(&suspendMutex, NULL);
    pthread_cond_init(&resumeCond, NULL);
	
	suspend_thread_return = pthread_create(&suspend_thread, NULL, suspend_thread_func, NULL);
    resume_thread_return = pthread_create(&resume_thread, NULL, resume_thread_func, NULL);

	pthread_join(suspend_thread, NULL);
    pthread_join(resume_thread, NULL);

    pthread_mutex_destroy(&suspendMutex);
    pthread_cond_destroy(&resumeCond);

	return 0;
}

void *suspend_thread_func(void *ptr){
    while (1){
		number += 1;
        printf("number %d\n", number);
		if (number==3) {
            printf("Task is suspended\n");
            suspendThread();
            checkSuspend();
            printf("Task is resumed\n");
    	}
		sleep(1);
	}
}

void *resume_thread_func(void *ptr){
    while (1){
		if (number == 3){
            sleep(3);
            resumeThread();
            printf("Has delay for 3 seconds in resume_thread\n");
        }
        // Wait for 2 seconds which is bigger than 1 second wait in suspend_thread
        // so that number is increased properly
        sleep(2);
    }	
}