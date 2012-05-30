#include "stack.h"
#include <stdlib.h>
#include <strings.h>

void *get_top(struct stack *stack)
{
	return (*(stack->st))[stack->top];
}

void *pop(struct stack *stack)
{
	return (*(stack->st))[(stack->top)--];
}

void push(struct stack *stack, void *elem)
{
	(*(stack->st))[++(stack->top)] = elem;
}

int is_empty(struct stack* stack)
{
	return stack->top == -1;
}

struct stack *new_stack(int count)
{
	struct stack *st = malloc(sizeof(struct stack));
	st->top = -1;
	st->st  = malloc(count * sizeof(void*));
	bzero(st->st, count * sizeof(void*));
	return st;
}
