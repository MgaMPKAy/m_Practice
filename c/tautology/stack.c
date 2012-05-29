#include "stack.h"
#include <stdlib.h>

void *get_top(struct stack *stack)
{
	return (*(stack->st))[stack->top];
}

void *pop(struct stack *stack)
{
	return (*(stack->st))[stack->top--];
}

void push(struct stack *stack, void *elem)
{
	(*(stack->st))[++(stack->top)] = elem;
}

int is_empty(struct stack* stack)
{
	return stack->top == -1;
}

void init_stack(struct stack *stack, int count)
{
	if (stack == NULL) {

	}
	stack->top = -1;
	stack->st  = malloc(count * sizeof(void*));
}
