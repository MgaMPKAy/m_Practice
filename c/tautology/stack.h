#ifndef _STACK_H_
#define _STACK_H_

typedef struct stack {
	int top;
	void *(*st)[];
} stack;

void *get_top(struct stack*);
void *pop(struct stack*);
void push(struct stack*, void*);
int is_empty(struct stack*);
void init_stack(struct stack*, int);

#endif /* _STACK_H_ */
