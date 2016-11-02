/*
 * This is a demo Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/ioport.h>

#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/io.h>
#include <linux/uaccess.h>
#include <linux/interrupt.h>
#include <asm/signal.h>
#include <linux/poll.h>
#include <asm/siginfo.h>
#include <linux/signal.h>
#include <linux/moduleparam.h>
#include <linux/kdev_t.h>

#include "efm32gg.h"


#define DRIVER "gamepad"



struct cdev gamepad_cdev;
struct class *cl;
dev_t devno;
struct resource *resource;

static int open_gamepad(struct inode *node, struct file *filp);
static int release_gamepad(struct inode *inode, struct file *filp);
static ssize_t read_gamepad(struct file *filp, char __user *buff, size_t count, loff_t *offp);
static ssize_t write_gamepad(struct file *filp, const char __user *buf, size_t count, loff_t *offp);


static struct file_operations gamepad_fops = {
	.owner = THIS_MODULE, 
	.read = read_gamepad,
	.write = write_gamepad,
	.open = open_gamepad,
	.release = release_gamepad,

};

static int __init gamepad_init(void)
{
	

	alloc_chrdev_region(&devno, 0, 1, DRIVER);

	cdev_init(&gamepad_cdev, &gamepad_fops);  	   
	gamepad_cdev.owner = THIS_MODULE;
	cdev_add(&gamepad_cdev, devno, 1);

	cl = class_create(THIS_MODULE, DRIVER);
	device_create(cl, NULL, devno, NULL, DRIVER);
	
	/* Request memory region of the GPIO registers */
	resource = request_mem_region(GPIO_PC_BASE,GPIO_IFC - GPIO_PA_BASE, DRIVER);
	
	if(resource != NULL){
		printk("Got requested memory region\n");
	}
	
	
	
	iowrite32(0x33333333, GPIO_PC_MODEL);
	iowrite32(0xff, GPIO_PC_DOUT);

	printk("Gamepad init !\n");

	return 0;
}



static void __exit gamepad_cleanup(void)
{
	 cdev_del(&gamepad_cdev);
	 release_mem_region(GPIO_PC_BASE, GPIO_IFC - GPIO_PA_BASE);
	 printk("Gamepad exit finished...\n");
}

static int open_gamepad(struct inode *node, struct file *filp){
	printk("Gamepad open \n");

	return 0;
}

/*User program close the driver*/
static int release_gamepad(struct inode *inode, struct file *filp){
	printk("Gamepad released\n");
	return 0;
}


/*User program reads from the driver */
static ssize_t read_gamepad(struct file *filp, char __user *buff, size_t count, loff_t *offp){

	uint32_t data = ioread32(GPIO_PC_DIN);
	copy_to_user(buff, &data, 1);
	
	return 1;

}


static ssize_t write_gamepad(struct file *filp, const char __user *buf, size_t count, loff_t *offp){
	return 0;
}

module_init(gamepad_init);
module_exit(gamepad_cleanup);

MODULE_DESCRIPTION("Small module, demo only, not very useful.");
MODULE_LICENSE("GPL");



/*
FILE *driver;
driver = fopen("/dev/gamepad", "rb");
int *ppos = NULL;
//loff_t (*llseek) (driver, ppos, int);

char buf[0];
read_gamepad(driver, buf, 1, ppos);
printf("Buttons = %i \n", buf);
*/
