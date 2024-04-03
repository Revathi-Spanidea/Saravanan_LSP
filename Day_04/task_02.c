#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>

int main() {
    pid_t pid;
    int status;
    int priority;

    // Create child processes with different priorities
    for (int i = 1; i <= 5; i++) 
    {
        pid = fork();
        if (pid == 0) 
	{ // Child process
            printf("Child process %d created with PID: %d\n", i, getpid());
	    sleep(2);

            // Set process priority using the nice command
            priority = i * 5; // Adjust priority based on the iteration
            if (nice(priority) == -1) //The nice system call allows a process to adjust its priority relative to its parent process.  
	    {
                printf("nice is failed\n");
                exit(EXIT_FAILURE);
            }

            // Child process logic
            printf("Child process %d executing with priority %d\n", i, getpriority(PRIO_PROCESS, 0));
            sleep(2); // Simulate some work
            printf("Child process %d completed\n", i);
            exit(EXIT_SUCCESS);
        } 
	else if (pid < 0)
       	{ // Error handling for fork failure
            printf("fork is completed\n");
            exit(EXIT_FAILURE);
        }
    }

    // Parent process waits for all child processes to complete
    while ((pid = wait(&status)) > 0)
    {                        // This calls the wait function, passing the address of the status variable as an argument.
        if (WIFEXITED(status)) // checks if the child process exited normally.
       	{
            printf("Child process %d exited with status: %d\n", pid, WEXITSTATUS(status));
        }
       	else
       	{
            printf("Child process %d terminated abnormally\n", pid);
        }
    }

    return 0;
}

