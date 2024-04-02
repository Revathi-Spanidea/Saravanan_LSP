#include <stdio.h> //for standard input/output
#include <stdlib.h> //for standard library functions
#include <dirent.h> //for directory handling
#include <unistd.h> //for system calls
#include <sys/types.h> // provides data types used in system calls.
#include <sys/stat.h>  //to access the mkdir function declaration.
int main() 
{
    // Create a directory
    const char *dirname = "example_directory";

    if (mkdir(dirname, 0777) == -1) 
    {
        printf("mkdir failed to create directory\n");
        exit(EXIT_FAILURE);
    }
    else
    {
    	printf("Directory '%s' created successfully.\n", dirname);
    }

    // Open the directory
    DIR *dir = opendir(dirname);
    if (dir == NULL)
    {
        printf("Failed to opendir\n");
        exit(EXIT_FAILURE);
    }
    else
    {
	    printf("Open Directory is opened Successfully\n");
    }

    // List directory contents
    printf("Contents of directory '%s':\n", dirname);
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        printf("Read Directory Contents %s\n", entry->d_name);
    }
    closedir(dir);

    // Create a file in the directory
    const char *filename = "example_file.txt";
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Failed to open the file\n");
        exit(EXIT_FAILURE);
    }
    else
    {
	    printf("File Opened Successfully\n");
    }

    fprintf(file, "This is a test file.\n");
    fclose(file);
    printf("File '%s' created successfully.\n", filename);

    // Delete the file
    if (unlink(filename) == -1) 
    {
        printf("Failed to unlink\n");
        exit(EXIT_FAILURE);
    }
    else
    {
   	 printf("File '%s' deleted successfully.\n", filename);
    }

    // Delete the directory
    if (rmdir(dirname) == -1)
    {
        printf("Failed to rmdir\n");
        exit(EXIT_FAILURE);
    }
    else
    {
    	printf("Directory '%s' deleted successfully.\n", dirname);
    }

    return 0;
}

