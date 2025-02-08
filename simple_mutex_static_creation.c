#include <stdio.h>
#include <pthread.h>

#define NTHREADS 10

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;


void *thread_function(void* parameters){
    //print the thread id
    printf("Thread Number %ld\n", pthread_self());
    pthread_mutex_lock(&mutex1);
    counter++;
    pthread_mutex_unlock(&mutex1);

}




int main(void){

    pthread_t thread_id[NTHREADS];

    //create N threads
    for(int i = 0; i < NTHREADS; i++){
        pthread_create(&thread_id[i], NULL, thread_function, NULL);
    }

    //wait for those threads
    for(int j = 0; j < NTHREADS; j++){
        pthread_join(thread_id[j], NULL);
    }


    printf("Final Counter Value: %d\n", counter);


}