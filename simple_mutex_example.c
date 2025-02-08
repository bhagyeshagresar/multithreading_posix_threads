#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t lock = NULL;

//Global Variable
int j = 0;

void* do_process(){
    pthread_mutex_lock(&lock);
    int i = 0;
    j++;

    while(i < 5){
        printf("%d", j);
        sleep(1);
        i++;
    }

    printf("...done\n");

    pthread_mutex_unlock(&lock);

}







int main(void){
    int err = 0;
    pthread_t t1, t2;

    //dynamic initialization
    if(pthread_mutex_init(&lock, NULL) != 0){
        printf("Mutex Initialization Failed.\n");
        return 1;
    }

    j = 0;
    pthread_create(&t1, NULL, do_process, NULL);
    pthread_create(&t2, NULL, do_process, NULL);

    //main thread will wait until the threads are done executing
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;


}