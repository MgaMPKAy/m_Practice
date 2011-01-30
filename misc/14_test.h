#define list_entry(ptr, type, member)					\
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define list_for_each(pos, head)				\
	for (pos = (head)->next; pos != NULL; pos = pos->next)

void test(void);
