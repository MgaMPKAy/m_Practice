#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/cdev.h>

#define CALL_DEV_NAME "call_dev"

dev_t call_dev_nr;
struct cdev call_dev;

int call_open(struct inode *inode, struct file *filp)
{
	int num = MINOR(inode->i_rdev);
	printk(KERN_ALERT "call open -> minor : %d\n", num);
	return 0;
}

loff_t call_llseek(struct file *filp, loff_t off, int whence)
{
	printk(KERN_ALERT "call llseek -> off : %08x, whence :%08x\n",
	       off, whence);
	return 0x23;
}

ssize_t call_read(struct file *filp, char *buf, size_t count, loff_t *fops)
{
	printk(KERN_ALERT "call read ->buf :%08x, count : %08x\n",
	       buf, count);
	return 0x33;
}

ssize_t call_write(struct file *filp, const char *buf, size_t count, loff_t *fops)
{
	printk(KERN_ALERT "call write ->buf :%08x, count : %08x\n",
	       buf, count);
	return 0x43;
}

long call_ioctl(struct file *filp,  unsigned int cmd, unsigned long arg)
{
	
	printk("call ioctl -> cmd : %08X, arg : %08X\n", cmd, arg );
	return 0x53;
}

int call_release(struct inode *inode, struct file *filp)
{
	printk("call release \n" );
	return 0;
}

struct file_operations call_fops ={
	.owner         = THIS_MODULE,
	.llseek        = call_llseek,
	.read          = call_read,
	.write         = call_write,
	.compat_ioctl  = call_ioctl,
	.open          = call_open,
	.release       = call_release,
};

static int call_init(void)
{
	printk ("call call_init \n");
	
	cdev_init(&call_dev, &call_fops);
	call_dev.owner = THIS_MODULE;

	alloc_chrdev_region(&call_dev_nr, 0, 1, CALL_DEV_NAME);

	cdev_add(&call_dev, call_dev_nr, 1);
			
	return 0;
}

static void call_exit(void)
{
	printk ("call call_exit \n");
	cdev_del(&call_dev);
}

module_init (call_init);
module_exit (call_exit);

MODULE_LICENSE ("GPL");
