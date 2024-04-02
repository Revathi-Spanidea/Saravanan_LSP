#include <stdio.h>  // Include standard input-output library for functions like printf and perror.
#include <stdlib.h> // Include standard library for memory allocation and other utility functions.
#include <unistd.h> // Include POSIX operating system API library for system calls like open, read, and write.
#include <sys/types.h> // provides data types used in system calls.
#include <sys/wait.h> //Wait macros defnitions
#include <semaphore.h>  //semaphore handling
#include <fcntl.h>  // Include file control options library for file-related functions and constants.
#include <sys/stat.h> //to access the mkdir function declaration.

#define Num 10 // Number of numbers to generate

sem_t *sem; // Semaphore for synchronization

void generateNumbers() 
{
    printf("Generating numbers...\n");
    for (int i = 1; i <= Num; i++)  //iterates from 1 to N.
    {
        printf("%d ", i);
        sem_post(sem); // Increment semaphore after generating each number
    }
    printf("\n");
}

void calculateSum() {
    int sum = 0;
    printf("Calculating sum...\n");
    for (int i = 1; i <= Num; i++) {
        sem_wait(sem); // Wait until the semaphore is incremented by the generateNumbers() function.
        sum += i; // Add the number to the sum
    }
    printf("Sum: %d\n", sum);
}

int main() {
    sem = sem_open("my_semaphore", O_CREAT, 0777, 0); // Create a named semaphore with initial value 0.
    if (sem == SEM_FAILED)
    {
        printf("sem_open is Failed\n");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid < 0) 
    {
        printf("Failed fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // Child process (generate numbers)
        generateNumbers();
        exit(EXIT_SUCCESS);
    }
    else
    {
        // Parent process (calculate sum)
        calculateSum();
        wait(NULL); // Wait for child process to finish
        sem_unlink("my_semaphore"); // Unlink semaphore
        sem_close(sem); // Close semaphore
    }

    return 0;
}

