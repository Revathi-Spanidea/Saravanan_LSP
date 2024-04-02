#include <stdio.h>  // for input/output operations 
#include <pthread.h> //multi-threading support

#define NUM_THREADS 5//number of threads to create
#define NUM_INCREMENTS 1000000  //number of increments each thread will perform

int counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // initializes a mutex mutex using PTHREAD_MUTEX_INITIALIZER

void *increment_counter(void *arg) 
{
    for (int i = 0; i < NUM_INCREMENTS; ++i)
    {
        pthread_mutex_lock(&mutex); // Acquire the mutex lock //Locks the mutex to ensure exclusive access to the shared counter.
        counter++; // Increment the shared counter
        pthread_mutex_unlock(&mutex); // Release the mutex lock to allow other threads to acquire it.
    }
    pthread_exit(NULL); //Exits the thread
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ret;

    // Create multiple threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        ret = pthread_create(&threads[i], NULL, increment_counter, NULL);
        if(ret != 0)	
	{
            printf("Error creating thread\n");
            return 1;
        }
	else
	{
		printf("Pthread creation Successfull\n");
	}
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) 
    {
        pthread_join(threads[i], NULL);  //joins each thread, blocking until the thread terminates.
    }

    // Print the final value of the counter
    printf("Final counter value: %d\n", counter);

    return 0;
}

