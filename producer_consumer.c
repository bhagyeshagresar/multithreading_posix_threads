
// A simple problem to demonstrate producer/consumer problem using the pthreads API.
// A Shared Buffer of specific size is shared between a single producer and a consumer
// Producer does n write operations and consumer thread keeps reading from the buffer
// The problem involves using mutex to lock critical section and counting semaphores to keep track of elements filled


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>




#define BUFFER_SIZE 5           //Size of the buffer
static volatile int num_writes = 10;      //Number of Writes performed by the producer
//static volatile int x = 0;      //value that gets stored in a buffer
static int buffer[BUFFER_SIZE]; //Shared Circular Buffer
static int head = 0;            //Index to write to the buffer
static int tail = 0;            //Index to read from the buffer
pthread_mutex_t lock;           //Mutex to lock the resource
sem_t sem_full;                 //Counting semaphore to keep track of number of elements filled
sem_t sem_empty;                //Counting semaphore to keep track of number of empty elements



int wait(int s){
    return --s;
}

int release(int s){
    return ++s;
}

void* producer(void* parameters){

    int num = *(int*)parameters;

    for(int i = 0; i < num_writes; i++){
        sem_wait(&sem_empty);
        pthread_mutex_lock(&lock);
        buffer[head] = num;
        int temp = head;
        head = (head+1)%BUFFER_SIZE;
        printf("Producer produced an item: %d at %d\n", buffer[head], temp);
        pthread_mutex_unlock(&lock);
        sem_post(&sem_full);

    }

    //pthread_exit(NULL);

    
}

void* consumer(void* parameters){
    int val = 0;
    while(1){

        sem_wait(&sem_full);
        pthread_mutex_lock(&lock);
        val = buffer[tail];
        int temp = tail;
        tail = (tail+1)%BUFFER_SIZE;
        printf("Consumer consumed an item: %d at %d\n", buffer[tail], temp);
        pthread_mutex_unlock(&lock);
        sem_post(&sem_empty);
        

    }

}

//Producer should go to sleep when buffer is full
//When consumer removes data, it notifies producer and producer starts putting data again
//Consumer goes to sleep when buffer is empty.
//


int main(int argc, char* argv[]){

    if(pthread_mutex_init(&lock, NULL) != 0){
        perror("Mutex Initialisation failed \n");
        exit(1);
    }

    if(sem_init(&sem_full, 0, 0) != 0){
        perror("Error in initializing counting semaphore for full\n");
        exit(1);
    }

    if(sem_init(&sem_empty, 0, BUFFER_SIZE) != 0){
        perror("Error in initializing counting semaphore for empty\n");
        exit(1);
    }

    
    // create the thread objs
    pthread_t thread1 = 0;
    pthread_t thread2 = 1;

    int x = 100;

    //Create the new threads
    int result1 = pthread_create(&thread1, NULL, producer, (void*)&x);
    int result2 = pthread_create(&thread2, NULL, consumer, NULL);

    if(result1 != 0){
        perror("Error creating the producer thread");
        exit(1);
    }

    if(result2 != 0){
        perror("Error creating the consumer thread");
        exit(1);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;


}

