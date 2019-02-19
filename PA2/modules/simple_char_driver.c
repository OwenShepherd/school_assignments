#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

#include<linux/fs.h>
#include<linux/slab.h>
#include<asm/uaccess.h>
#include<linux/uaccess.h>

#define BUFFER_SIZE 1024
#define DEVICE_NAME "simple_char_device"
#define DEVICE_NUMBER 240

/* Define device_buffer and other global data structures you will need here */

static char devBuff[BUFFER_SIZE];
static int numOpen;
static int numClosed;


// Function prototypes
ssize_t simple_char_driver_read (struct file *pfile, char __user *buffer, size_t length, loff_t *offset);
ssize_t simple_char_driver_write (struct file *pfile, const char __user *buffer, size_t length, loff_t *offset);
int simple_char_driver_open (struct inode *pinode, struct file *pfile);
int simple_char_driver_close (struct inode *pinode, struct file *pfile);
loff_t simple_char_driver_seek (struct file *pfile, loff_t offset, int whence);


struct file_operations fops = {
	.owner   = THIS_MODULE,
	.read = simple_char_driver_read,
	.write = simple_char_driver_write,
	.open = simple_char_driver_open,
	.release = simple_char_driver_close,
	.llseek = simple_char_driver_seek
	/* add the function pointers to point to the corresponding file operations. look at the file fs.h in the linux souce code */
};


ssize_t simple_char_driver_read (struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{

	int bytesToRead = BUFFER_SIZE-*offset;

	if (BUFFER_SIZE == *offset) {
		printk(KERN_ALERT "Reached end of file.");
		length = 0;
		bytesToRead = 0;
	}
	else {
		copy_to_user(buffer, devBuff + *offset, bytesToRead);
	}
	*offset += bytesToRead; // We've gone up length # of bytes
	printk(KERN_ALERT "Bytes read: %d",bytesToRead);
	return 0;

}



ssize_t simple_char_driver_write (struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
	// The amount of free bytes remaining in the buffer
	int remainingBytes = BUFFER_SIZE-*offset;

	if (length > remainingBytes) {
		printk(KERN_ALERT "Not enough space for full write.  Input will be shortened.");
		length = remainingBytes;
	}

	copy_from_user(devBuff+*offset, buffer, length);
	*offset += length;


	printk(KERN_ALERT "Bytes written: %d",length);
	return length;


}


int simple_char_driver_open (struct inode *pinode, struct file *pfile)
{
	numOpen++;
	printk(KERN_ALERT "The file will now be opened.");
	printk(KERN_ALERT "The file has been opened %d times.",numOpen);
	/* print to the log file that the device is opened and also print the number of times this device has been opened until now*/
	return 0;
}

int simple_char_driver_close (struct inode *pinode, struct file *pfile)
{
	numClosed++;
	printk(KERN_ALERT "The device has now been closed.");
	printk(KERN_ALERT "The device has been closed %d times.",numClosed);
	/* print to the log file that the device is closed and also print the number of times this device has been closed until now*/
	return 0;
}

loff_t simple_char_driver_seek (struct file *pfile, loff_t offset, int whence)
{

	printk(KERN_ALERT "Inside seek function.");

	loff_t newPosition;

	/* Update open file position according to the values of offset and whence */
	switch (whence) {
		case 0 :
			newPosition = offset;
		break;

		case 1 :
			newPosition += offset;
		break;

		case 2 :
			// Don't know how to implement this one...
			newPosition = BUFFER_SIZE - offset;
		break;

		default :
			printk(KERN_ALERT "Incorrect value of whence used.");
	}

	if ((newPosition < 0) || (newPosition >= BUFFER_SIZE)) {
			printk(KERN_ALERT "Out of bounds.  Position unchanged");
	}
	else {
		pfile->f_pos = newPosition;
	}

	return 0;
}

static int simple_char_driver_init(void)
{
	int major;
	numOpen = 0;
	numClosed = 0;
	currPos = 0;
	printk(KERN_ALERT "Simple_Char Init function has been called.");

	// Registering the device
	major = register_chrdev(DEVICE_NUMBER, DEVICE_NAME, &fops);
	printk(KERN_ALERT "Registered with return: %d",major);

	/* print to the log file that the init function is called.*/
	/* register the device */
	return 0;
}

static void simple_char_driver_exit(void)
{
	printk(KERN_ALERT "Driver exit function has been called.");
	unregister_chrdev(DEVICE_NUMBER, DEVICE_NAME);
	/* print to the log file that the exit function is called.*/
	/* unregister  the device using the register_chrdev() function. */
}

/* add module_init and module_exit to point to the corresponding init and exit function*/
module_init(simple_char_driver_init);
module_exit(simple_char_driver_exit);
