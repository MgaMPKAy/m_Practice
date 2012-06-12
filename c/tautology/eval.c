#include <stdio.h>
#include <string.h>
#include "types.h"
#include "eval.h"

bool get_bit(int n, int decimal)
{
	return (decimal & (1 << n));
}

int eval_single(struct expression *expr, int bitmap)
{
	if (expr == NULL) return -1;

	switch (expr->type) {
	case VarExp:
		return get_bit(expr->u.var_id, bitmap);
	case NotExp:
		return ! eval_single(expr->u.left, bitmap);
	case AndExp:
		return eval_single(expr->u.left, bitmap)
			&& eval_single(expr->u.right, bitmap);
	case OrExp:
		return eval_single(expr->u.left, bitmap)
			|| eval_single(expr->u.right, bitmap);
	}
	return -1;
}

int eval_all(struct expression *expr)
{
	int bitmap = 0;
	int count = symbol_table->count;
	int pre = eval_single(expr, 0);
	int max = 1 << count;
	int next;

	for (; bitmap < max; bitmap++) {

		next = eval_single(expr, bitmap);
		if (next != pre) {
			return -1;
		}
		pre = next;
	}
	return pre;
}

void print_truth_table(struct expression *expr)
{
	int count  = symbol_table->count;
	char *(*name) = *(symbol_table->name);
	int bitmap = 0;
	int result = 0;
	int len    = 0;

	for (int i = 0; i < count; i++) {
		printf("%s ", name[i]);
	}
	printf("result\n");
	printf("%s",   "-----------------------------------------------");
	printf("%s\n", "-----------------------------------------------");

	for (; bitmap < (1<<count); bitmap++) {
		for (int i = 0; i < count; i++) {
			len = strlen(name[i]);
			for(int j = 0; j < len / 2; j++) {
				printf("%c",' ');
			}
			printf("%c", get_bit(i, bitmap) ? 'T' : 'F');

			for(int j = 0; j < len / 2; j++) {
				printf("%c",' ');
			}
		}
		printf(" | ");
		result = eval_single(expr, bitmap);
		printf("  %c\n", result ? 'T' : 'F');
	}
}
