#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock1, lock2;


//we may or may not get deadlock based on race conditions

void* resource1(){

    pthread_mutex_lock(&lock1);

    printf("Job started in resource 1...\n");
    sleep(2);

    printf("trying to get resource2...\n");
    pthread_mutex_lock(&lock2);
    printf("acquired resource2\n");
    pthread_mutex_unlock(&lock2);

    printf("job finished in resource1..\n");

    pthread_mutex_unlock(&lock1);

    

}



void* resource2(){

    pthread_mutex_lock(&lock2);

    printf("Job started in resource 2...\n");
    sleep(2);

    printf("trying to get resource1...\n");
    pthread_mutex_lock(&lock1);
    printf("acquired resource1\n");
    pthread_mutex_unlock(&lock1);

    printf("job finished in resource2..\n");

    pthread_mutex_unlock(&lock2);

    

}







int main(){
    
    //initialise the mutex
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    pthread_t t1, t2;

    pthread_create(&t1, NULL, resource1, NULL);
    pthread_create(&t2, NULL, resource2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}