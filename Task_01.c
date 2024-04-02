#include <stdio.h>  // Include standard input-output library for functions like printf and perror.
#include <stdlib.h> // Include standard library for memory allocation and other utility functions.
#include <fcntl.h> // Include file control options library for file-related functions and constants.
#include <unistd.h> // Include POSIX operating system API library for system calls like open, read, and write.

# define Buffer_Size 4096 //Define a macro BUF_SIZE with value 4096 for the buffer size used in reading and writin

int main(int argc, char *argv[])
{
       int source_file, dest_file;
       int bytes_read, bytes_written;
       char buffer[Buffer_Size];
       if(argc != 3)
       {
               //printf("Value of argc %d\n",argc);
               printf("Usage: %s <source> <destination>\n", argv[0]);
               exit(EXIT_FAILURE);
       }
       else
       {
               printf("Value of argc %d\n",argc);
       }
       printf("\n");
       source_file = open(argv[1], O_RDONLY);
       if(source_file < 0)
       {
               printf("Failed to open the sourec file\n");
               exit(EXIT_FAILURE);
       }
       else
       {
               printf("Value of the source file is : %d\n",source_file);
               printf("Source file opened successfully\n");
       }
        printf("\n");
       dest_file = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC );
       if(dest_file < 0)
       {
               printf("Failed to open the dest_file\n");
               exit(EXIT_FAILURE);
       }
       else
       {
               printf("Value of the dest file is : %d\n",dest_file);
               printf("Destination file opened successfully\n");
       }       
       printf("\n");
       bytes_read = read(source_file, buffer, Buffer_Size);
       if(bytes_read < 0)
       {
               printf("Failed to read the sourec file\n");
       }
       else
       {
               printf("Value of bytes_read is %d\n",bytes_read);
               printf("Source_ file read buffer:%s\n",buffer);
       }
       printf("\n");
       bytes_written = write(dest_file, buffer, bytes_read);
       if (bytes_written > 0)
       {
               printf("Value of bytes_written:%d\n",bytes_written);
               printf("Destination file written buffer : %s\n",buffer);
       }
       else
       {
               printf("Failed to  write the destination file \n");
       }
       
       printf("\n");
       if(bytes_written != bytes_read)
       {
               printf("Source file is not matched with the destination file\n");
               exit(EXIT_FAILURE);
       }
       else
       {
               printf("Both the data matched in souce file and destination file\n");
       }
       /*printf("Before while loop\n");
       while(bytes_read = read(source_file, buffer, Buffer_Size) > 0)
       {
               printf("Value of bytes_read is %d\n",bytes_read);
               printf("Source_ file read buffer:%s\n",buffer);
               bytes_written = write(dest_file, buffer, bytes_read);
               printf("Value of bytes_written:%d\n",bytes_written);
               printf("Destination file written buffer : %s\n",buffer);
       }*/
       printf("\n");
       if(close(source_file) < 0)
       {
               printf("Failed to close source file\n");
       }
       else
       {
               printf("Source file closed successfully\n");
       }
       
       printf("\n");
      if(close(dest_file) < 0)
       {
               printf("Failed to close destination file\n");
       }
       else
       {
               printf("Destination file closed successfully\n");
       }

       printf("File copied Successfully\n");
       return 0;
}



