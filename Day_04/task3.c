#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>

#define SHARED_MEMORY_NAME "/message_shared_memory"
#define SEMAPHORE_NAME "/message_semaphore"
#define MESSAGE_SIZE 256

typedef struct {
    char message[MESSAGE_SIZE];
    int written;
} SharedMemory;

int main() 
{
    int shm_fd = 0;
    sem_t *semaphore;
    SharedMemory *shared_memory;
    pid_t pid;

    // Create shared memory
    shm_fd = shm_open(SHARED_MEMORY_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) 
    {
        printf("shm_open is failed to open\n");
        exit(EXIT_FAILURE);
    }
    else
    {
	    printf("shm_open is successfull\n");
    }

    ftruncate(shm_fd, sizeof(SharedMemory));

    // Map the shared memory
    shared_memory = (SharedMemory *) mmap(NULL, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_memory == MAP_FAILED) 
    {
        printf("mmap is failed to memory mapping\n");
        exit(EXIT_FAILURE);
    }
    else
    {
	    printf("mmap is successfull\n");
    }

    // Create semaphore
    semaphore = sem_open(SEMAPHORE_NAME, O_CREAT, 0666, 1);
    if (semaphore == SEM_FAILED)
    {
        printf("sem_open is failed to open\n");
        exit(EXIT_FAILURE);
    }
    else
    {
	    printf("sem_open is successfull\n");
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) 
    {
        printf("fork is failed\n");
        exit(EXIT_FAILURE);
    }
    /*else
    {
	    printf("Fork creation is successfull\n");
	    printf("Value of pid %d\n",pid);
    }*/

    if (pid == 0) 
    {
        // Child process reads messages
        while (1)
       	{
            sem_wait(semaphore);
	   // printf("Entering into while loop\n");
            if (shared_memory->written)
	    {
                printf("Child process received: %s\n", shared_memory->message);
                shared_memory->written = 0; // Reset flag
            }
            sem_post(semaphore);
            usleep(500000); // Wait for 0.5 seconds
        }
    } 
    else
    {
        // Parent process writes messages
        while (1) 
	{
            sem_wait(semaphore);
            if (!shared_memory->written)
	    {
                printf("Enter message to send: ");
                fgets(shared_memory->message, MESSAGE_SIZE, stdin);
                shared_memory->written = 1; // Set flag
            }
            sem_post(semaphore);
            usleep(500000); // Wait for 0.5 seconds
        }
    }

    // Cleanup
    sem_close(semaphore);
    sem_unlink(SEMAPHORE_NAME);
    shm_unlink(SHARED_MEMORY_NAME);

    return 0;
}
