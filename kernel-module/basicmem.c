#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/mm.h>

static void kmalloc_test(void)
{
	char *buff;
	printk(KERN_ALERT "kmalloc test\n");

	buff = kmalloc(1024, GFP_KERNEL);
	if (buff != NULL) {
		printk(KERN_ALERT "kmalloc tset ok: buff = %p\n", buff);
		kfree(buff);
	}
	
	buff = kmalloc(32 * PAGE_SIZE, GFP_KERNEL);
	if (buff != NULL){
		printk("kmalloc big memory tset ok, buff = %p\n", buff);
		kfree(buff);
	}
}

static void vmalloc_test(void)
{
	char *buff;
	printk(KERN_ALERT "vmalloc test\n");
	
	buff = vmalloc(33 * PAGE_SIZE);
	if (buff != NULL) {
		sprintf(buff, "vmalloc test ok, buff =  %p\n", buff);
		printk(buff);
		vfree(buff);
	}
}

static void pages_test(void)
{
	unsigned long buff;
	struct page *test_pages;
	int order;
	
	printk(KERN_ALERT "page test\n");

	test_pages = alloc_pages(GFP_KERNEL, 2);
	if (free_pages != NULL) {
		printk(KERN_ALERT "page_adderss = %p", page_address(test_pages));
		__free_pages(test_pages, 2);
	}
	
	order = get_order(8192 * 10);
	buff = __get_free_pages(GFP_KERNEL, order);
	if (buff) {
		sprintf(buff, "__get_free_page test ok [%d]\n", order);
		printk(KERN_ALERT "%s page_address = %p\n", buff, buff);
		free_pages(buff, order);
	}
}

static int memtest_init(void)
{
	printk(KERN_ALERT "Module Memory Test\n");

	kmalloc_test();
	vmalloc_test();
	pages_test();

	return 0;
}

static void memtest_exit(void)
{
	printk(KERN_ALERT "Module Memory test end\n");
}

module_init(memtest_init);
module_exit(memtest_exit);

MODULE_LICENSE("GPL");

		   
