#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE_PATH "/dev/my_char_dev"

int main() {
    int fd;
    char buf[1024];
    ssize_t bytes_read, bytes_written;

    // Open the character device
    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device");
        exit(EXIT_FAILURE);
    }

    // Read from the device
    bytes_read = read(fd, buf, sizeof(buf));
    if (bytes_read < 0) {
        perror("Failed to read from the device");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Read %zd bytes: %s\n", bytes_read, buf);

    // Write to the device
    bytes_written = write(fd, "Hello from user-space!", 22);
    if (bytes_written < 0) {
        perror("Failed to write to the device");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Wrote %zd bytes to the device\n", bytes_written);

    // Close the device
    close(fd);

    return 0;
}

