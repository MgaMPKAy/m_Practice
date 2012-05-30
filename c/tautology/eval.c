#include <stdio.h>
#include <string.h>
#include "token.h"
#include "expression.h"

bool get_bit(int n, int decimal)
{
	return (decimal & (1 << n));
}

int eval_single(struct expression *expr, int bitmap)
{
	if (expr == NULL)
		return -2;
	int x = 0;
	switch (expr->type) {
	case VarExp:
		x = get_bit(expr->u.varID, bitmap);
		printf("var = %d\n", x);
		return x;
		break;
	case OpExp:
		switch (expr->u.op) {
		case OpNot:
			return ! eval_single(expr->u.left, bitmap);
		case OpAnd:
			return eval_single(expr->u.left, bitmap)
				&& eval_single(expr->u.right, bitmap);
		case OpOr:
		default:
			return eval_single(expr->u.left, bitmap)
				|| eval_single(expr->u.right, bitmap);
			break;
		}
		break;
	default:
		break;
	}
	return -1;
}

int eval_all(struct expression *expr, struct symbol_table *sym_table)
{
	int bitmap = 0;
	int count = sym_table->count;
	int pre = eval_single(expr, 0);
	int max = 1 << count;
	int next;
	printf("count = %d\n", count);
	printf("max   = %d\n", 1<<(count));

	for (; bitmap < max; bitmap++) {
		printf("bitmap = %d\n", bitmap);

		next = eval_single(expr, bitmap);
		printf("next = %d\n", next);

		if (next != pre) {
			return -1;
		}
		pre = next;
		printf("%s\n", "----");

	}
	return pre;
}

void print_truth_table(struct expression *expr,
		       struct symbol_table *sym_table)
{
	int count  = sym_table->count;
	char *(*name) = *(sym_table->name);
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
