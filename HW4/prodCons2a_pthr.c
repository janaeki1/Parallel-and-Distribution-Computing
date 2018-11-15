/*************************************************************
 * Producer/Consumer in PThreads (Part 2a)
 * Author: Jerome Anaeki
 * Date : 10/31/2018
 *
 * This program implements the producer-consumer problem, a
 * classic example of a multi-process synchronization problem.
 * It will use conditional locks, have a single producer, and
 * multiple consumers.
 *
 * compile string:
 * gcc -lpthread prodCons2a_pthr.c -o prodCons2a
 *
 * pthreads requires the addition of the -lpthread switch
 *************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define BUF_SIZE 5
#define MAX 100000000
#define NUM_PROD 1
#define NUM_CONS 4


typedef int buf_item;

pthread_mutex_t lock; // mutex lock
pthread_cond_t pCond, cCond; // conditional locks
buf_item buf[BUF_SIZE]; // buffer
int bufCount; // counter
pthread_t pid, cid; // thread ID for producer and consumer

void *producer(void *param); // producer function prototype
void *consumer(void *param); // consumer function prototype

/* Producer Thread */
void *producer(void *param) {
   buf_item item;

   while(1) {
      int randGen = rand() / MAX;
      sleep(randGen); // sleep for random period of time

      item = rand(); // generate random number

      pthread_mutex_lock(&lock); // acquire lock
      
      insert_item(item);
      printf("Producer produces %d\n", item);

	  pthread_cond_signal(&cCond); // wakes up consumer
      pthread_mutex_unlock(&lock); // release lock
   }
}

/* Consumer Thread */
void *consumer(void *param) {
   buf_item item;

   while(1) {
      int randGen = rand() / MAX;
      sleep(randGen); // sleep for random period of time

      pthread_mutex_lock(&lock); // acquire lock
      
      remove_item(&item);
      printf("Consumer consumes %d\n", item);
      
      pthread_cond_signal(&pCond); // wakes up producer
      pthread_mutex_unlock(&lock); // release lock
   }
}

/* Inserts item into buffer when buffer is not full */
int insert_item(buf_item item) {
   if(bufCount < BUF_SIZE) {
   	  pthread_cond_wait(&pCond, &lock); // wait
      buf[bufCount] = item; // insert item
      bufCount++; // increment counter
      return 0;
   }
   else {
      return -1; // return negative when buffer is full
   }
}

/* Removes item from buffer when buffer is not empty */
int remove_item(buf_item *item) {
   if(bufCount > 0) {
   	  pthread_cond_wait(&cCond, &lock); // wait
      *item = buf[(bufCount-1)]; // removes item
      bufCount--; // decrement counter
      return 0;
   }
   else {
      return -1; // return negative when buffer is empty
   }
}

int main(int argc, char *argv[]) {
   
   int i;

   pthread_mutex_init(&lock, NULL); // initialize lock
   pthread_cond_init(&pCond, NULL); // initialize conditional lock for producer
   pthread_cond_init(&cCond, NULL); // initialize conditional lock for consumer

   bufCount = 0; // initialize buffer counter

   /* Creates producer threads */
   for(i = 0; i < NUM_PROD; i++) {
      pthread_create(&pid, NULL, producer, NULL);
    }

   /* Creates consumer threads */
   for(i = 0; i < NUM_CONS; i++) {
      pthread_create(&cid, NULL, consumer, NULL);
   }
   
   /* Waits for threads to finish */
   for(i = 0; i < NUM_PROD; i++){
	  pthread_join(&pid, NULL);
   }
   
   /* Waits for threads to finish */
   for(i = 0; i < NUM_CONS; i++){
   	  pthread_join(&cid, NULL);
   }
   
   pthread_mutex_destroy(&lock); // uninitialize lock
   pthread_cond_destroy(&pCond); // uninitialize conditional lock
   pthread_cond_destroy(&cCond); // uninitialize conditional lock
   
   exit(0);
}

