#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define FILE_PATH "example.txt"
#define FILE_SIZE 1000

int main() {
    int fd;
    struct stat fileStat;
    char *file_contents;
    char new_content[] = "Hope for the best in future let it try !!!";

    // Open the file in read-write mode
    fd = open(FILE_PATH, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR,0644);
    if (fd == -1) 
    {
        printf("Failed to open\n");
	//printf("Value of fd %d\n",fd);
	printf("Failed to open file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    else
    {
	    printf("File opned successfully\n");
	    printf("Value of fd %d\n",fd);
    }

    // Get file size
    if (ftruncate(fd, FILE_SIZE) == -1)
    {
        printf("ftruncate is failed to open file associated with the file descriptor fildes, and shall write it to the area pointed to by buf.\n");
	printf("Failed to open file: %s\n", strerror(errno));
        close(fd);
        exit(EXIT_FAILURE);
    }
    else
    {
	    printf("Ftruncate() is opened successfully and written to a buf\n");
    }

    // Map the file into memory
    file_contents = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (file_contents == MAP_FAILED)
    {
        printf("mmap is failed to map the content\n");
	printf("Failed to open file: %s\n", strerror(errno));
        close(fd);
        //exit(EXIT_FAILURE);
    }
    else
    {
	    printf("Value of the file_content %s\n",file_contents);
    }

    // Modify the contents of the mapped memory
    strcpy(file_contents, new_content);

    // Unmap the memory
    if (munmap(file_contents, FILE_SIZE) == -1) {
        perror("munmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Close the file
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    printf("Changes written to the file successfully.\n");

    return EXIT_SUCCESS;
}

