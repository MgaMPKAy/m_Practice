#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

static ssize_t globalvar_read(struct file *, char *, size_t, loff_t *);
static ssize_t globalvar_write(struct file *,const char *, size_t, loff_t *);

struct file_operations globalvar_fops = {
	.read = globalvar_read,
	.write = globalvar_write,
};
static int global_var = 0;
struct cdev globalvar_cdev;
dev_t globalvar_nr;

static int __init globalvar_init(void)
{
	int ret;
	ret = alloc_chrdev_region(&globalvar_nr, 0, 1, "globalvar");
	if (ret){
		printk(KERN_NOTICE "alloc_chrdev_region fail\n");
		return -1;
	} else {
		printk(KERN_NOTICE "alloc_chrdev_region success\n");
	}
	cdev_init(&globalvar_cdev, &globalvar_fops);
	globalvar_cdev.owner = THIS_MODULE;
	cdev_add(&globalvar_cdev, globalvar_nr, 1);
	return 0;
}

static void __exit globalvar_exit(void)
{
	cdev_del(&globalvar_cdev);
	unregister_chrdev_region(globalvar_nr, 1);
}

static ssize_t
globalvar_read(struct file *filp, char *buf, size_t len, loff_t *off)
{
	if (copy_to_user(buf, &global_var, sizeof(int))){
		return -EFAULT;
	}
	return sizeof(int);
}

static ssize_t
globalvar_write(struct file *filp, const char *buf,size_t len, loff_t *off)
{
	if (copy_from_user(&global_var, buf, sizeof(int))){
		return -EFAULT;
	}
	return sizeof(int);
}

module_init(globalvar_init);
module_exit(globalvar_exit);
MODULE_LICENSE("GPL");
