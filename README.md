# Multithreading Challenges 

## Challenge 1 : Classic Producer-Consumer problem
A simple problem to demonstrate producer/consumer problem using the pthreads API.
A Shared Buffer of specific size is shared between a single producer and a consumer
Producer does n write operations and consumer thread keeps reading from the buffer
The problem involves using mutex to lock critical section and counting semaphores to keep track of elements filled
