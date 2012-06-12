#include <stdio.h>
#include "types.h"
#include "tokenizer.h"
#include "parser.h"

void print_expression_level(struct expression *exp, int level)
{
	if (exp == NULL) {
		printf("%s\n", "Empty Expression");
		return;
	}

	switch (exp->type) {
	case VarExp:
		for (int i = 0; i < level; i++) {
			printf ("%s", "    ");
		}
		printf("VarExp: ");
		printf("var_id = %d ", exp->u.var_id);
		printf("name= %s\n", (*(symbol_table->name))[exp->u.var_id]);
		break;
	case NotExp:
		for (int i = 0; i < level; i++) {
			printf ("%s", "    ");
		}
		printf("NotExp:\n ");
		print_expression_level(exp->u.left, level + 1);
		break;
	case AndExp:
		for (int i = 0; i < level; i++) {
			printf ("%s", "    ");
		}
		printf("AndExp:\n");
		print_expression_level(exp->u.left, level + 1);
		print_expression_level(exp->u.right, level + 1);
		break;
	case OrExp:
		for (int i = 0; i < level; i++) {
			printf ("%s", "    ");
		}
		printf("OrExp:\n");
		print_expression_level(exp->u.left, level + 1);
		print_expression_level(exp->u.right, level + 1);
		break;
	}
}

void print_prop(struct expression*exp)
{
	print_expression_level(exp, 0);
}
