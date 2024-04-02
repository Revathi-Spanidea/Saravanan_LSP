#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    const char *filename = "testfile.txt";
    int fd;
    
    // Create a file with read-only permissions for the owner
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR);
    if (fd == -1) 
    {
        printf("Failed to creating file");
        exit(EXIT_FAILURE);
    }
    else
    {
	    printf("File opned Successfully\n");
	    printf("Value of the fd %d\n",fd);
    }
    
    printf("File created successfully with read-only permission for the owner.\n");
    
    // Close the file
    if (close(fd) == -1) 
    {
        printf("Failed to  closing file");
        exit(EXIT_FAILURE);
    }

   
    // Change file permissions to allow read and write for the owner
    if (chmod(filename, S_IRUSR | S_IWUSR) == -1) {
        printf("Error changing file permissions");
        exit(EXIT_FAILURE);
    }
    
    printf("File permissions changed to allow read and write for the owner.\n");
    
    return 0;
}
