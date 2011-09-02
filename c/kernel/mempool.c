#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/mempool.h>

#define MIN_ELEMENT 4
#define TEST_ELEMENT 4

typedef struct {
	int number;
	char string[128];
} tmem_element;

int element_count = 0;

static void * mempool_alloc_test(gfp_t gfp_mask, void *pool_data)
{
	tmem_element *data;
	printk("<1> mempool_alloc_test\n");

	data = kmalloc(sizeof(tmem_element) , gfp_mask);
	if (data != NULL) {
		data->number = element_count++;
	}
	return data;
}

static void mempool_free_test(void *element, void *pool_data)
{
	printk("<1> mempool_free_test\n");
	if (element != NULL) {
		kfree(element);
	}
}

static int mempool_init(void)
{
	mempool_t *mp;
	tmem_element *element[TEST_ELEMENT];
	int lp;

	printk("<1> Module mempool test\n");

	memset(element, 0, sizeof(element));

	printk("<1> mempool_create\n");
	mp = mempool_create(MIN_ELEMENT, mempool_alloc_test,
			    mempool_free_test, NULL);
	for (lp = 0; lp < TEST_ELEMENT; lp++) {
		element[lp] = mempool_alloc(mp, GFP_KERNEL);
		if (element[lp] == NULL) {
			printk("<1> allocate fail\n");
		} else {
			sprintf (element[lp]->string, "alloc data %d\n",
				 element[lp]->number);
			printk("<1> %s", element[lp]->string);
		}
	}

	printk("<1> mempool free\n");
	for (lp = 0; lp < TEST_ELEMENT; lp++) {
		if (element[lp] != NULL) {
			mempool_free(element[lp], mp);
		}
	}

	mempool_destroy(mp);
	return 0;
}

module_init(mempool_init);

MODULE_LICENSE("GPL");
