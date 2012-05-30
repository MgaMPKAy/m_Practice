#include <stdlib.h>
#include <stdio.h>
#include "../stack.h"

int main(int argc, char *argv[])
{
	struct stack *st = new_stack(100);

	char *s = malloc(sizeof(char) * 10);
	for (int i = 0; i < 10; i++) {
		printf("%c\n", 'a' + i);
		s[i] = 'a' + i;
	}
	printf("%s\n", "pop");

	for (int i = 0; i < 10; i++) {
		push(st, s + i);
	}
	while (!is_empty(st)) {
		char *c = pop(st);
		printf("%c\n", *c);
	}

	return 0;
}

