#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() 
{
    // Define an array of commands to be executed by child processes
    char *commands[] = {"ls", "echo Hello", "date", "uname -a", NULL}; //NULL indicates the end of the array

    // Iterate over the commands array
    for (int i = 0; commands[i] != NULL; i++)
    {
        pid_t pid = fork(); // Create a child process

        if (pid == -1)
       	{
            // Error handling for fork failure
            printf("fork failed to craete child process\n");
            exit(EXIT_FAILURE);
        } 
	else if (pid == 0) 
	{
            // Child process
            printf("Child process (PID: %d) executing command: %s\n", getpid(), commands[i]);
          
	    // Execute the command using execlp
            execlp("/bin/sh", "sh", "-c", commands[i], NULL); //The execlp() function replaces the current process image with a new one specified by the command.
	                                                      ///bin/sh is the shell, -c indicates that the next argument is a command to be executed, 
          
	    // execlp will only return if an error occurs
            printf("execlp function failed");
            exit(EXIT_FAILURE);
        }
    }

    // Parent process
    // Wait for all child processes to complete
    int status;
    pid_t child_pid;
    while ((child_pid = wait(&status)) > 0) // This calls the wait function, passing the address of the status variable as an argument. 
    {
        if (WIFEXITED(status))  // checks if the child process exited normally.
       	{
            printf("Child process (PID: %d) exited with status: %d\n", child_pid, WEXITSTATUS(status));
        } 
	else
       	{
            printf("Child process (PID: %d) terminated abnormally\n", child_pid);
        }
    }

    printf("All child processes have completed.\n");
    return 0;
}

