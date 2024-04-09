#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "my_char_dev"
#define BUF_SIZE 1024

static int major_num;
static int open_count = 0;
static char kernel_buffer[BUF_SIZE];

// Function prototypes
static int my_char_dev_open(struct inode *, struct file *);
static int my_char_dev_release(struct inode *, struct file *);
static ssize_t my_char_dev_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t my_char_dev_write(struct file *, const char __user *, size_t, loff_t *);

// File operations structure
static struct file_operations fops = {
    .open = my_char_dev_open,
    .release = my_char_dev_release,
    .read = my_char_dev_read,
    .write = my_char_dev_write,
};

// Module initialization
static int __init my_char_dev_init(void) {
    // Register character device
    major_num = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_num < 0) {
        printk(KERN_ALERT "Failed to register a major number\n");
        return major_num;
    }
    printk(KERN_INFO "Registered correctly with major number %d\n", major_num);
    return 0;
}

// Module cleanup
static void __exit my_char_dev_exit(void) {
    unregister_chrdev(major_num, DEVICE_NAME);
    printk(KERN_INFO "Unregistered character device\n");
}

// Called when the device is opened
static int my_char_dev_open(struct inode *inodep, struct file *filep) {
    open_count++;
    printk(KERN_INFO "Device opened %d time(s)\n", open_count);
    return 0;
}

// Called when the device is released
static int my_char_dev_release(struct inode *inodep, struct file *filep) {
    printk(KERN_INFO "Device closed\n");
    return 0;
}

// Called when data is read from the device
static ssize_t my_char_dev_read(struct file *filep, char __user *buffer, size_t len, loff_t *offset) {
    int bytes_to_copy;
    int bytes_not_copied;

    bytes_to_copy = min(len, (size_t)BUF_SIZE - *offset);
    bytes_not_copied = copy_to_user(buffer, kernel_buffer + *offset, bytes_to_copy);
    *offset += bytes_to_copy;
    
    return bytes_to_copy - bytes_not_copied;
}

// Called when data is written to the device
static ssize_t my_char_dev_write(struct file *filep, const char __user *buffer, size_t len, loff_t *offset) {
    int bytes_to_copy;
    int bytes_not_copied;

    bytes_to_copy = min(len, (size_t)BUF_SIZE - *offset);
    bytes_not_copied = copy_from_user(kernel_buffer + *offset, buffer, bytes_to_copy);
    *offset += bytes_to_copy;

    return bytes_to_copy - bytes_not_copied;
}

module_init(my_char_dev_init);
module_exit(my_char_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saravanan");
MODULE_DESCRIPTION("A simple character device driver");

