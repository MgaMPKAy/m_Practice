#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "expression.h"

struct expression *new_expression()
{
 	struct expression *exp = malloc(sizeof(struct expression));
	bzero(exp, sizeof(struct expression));
	return exp;
}

void destroy_expression(struct expression *exp)
{
	if (exp == NULL) return;
	if (exp->type != VarExp) {
		destroy_expression(exp->u.left);
		destroy_expression(exp->u.right);
	}
	free(exp);
}

struct expression *new_op_expression(expression_type type,
				     struct expression * left,
				     struct expression *right)
{
	struct expression *exp = new_expression();
	exp->type = type;
	exp->u.left = left;
	exp->u.right = right;
	return exp;
}

struct expression *new_var_expression(int var_id)
{
	struct expression *exp = new_expression();
	exp->type = VarExp;
	exp->u.var_id = var_id;
	return exp;
}

void set_left_child(struct expression *exp, struct expression *child)
{
	exp->u.left = child;
}
void set_right_child(struct expression *exp, struct expression *child)
{
	exp->u.right = child;
}

int is_empty_expression(struct expression *exp)
{
	return exp == NULL;
}

int is_left_child_empty(struct  expression *exp)
{
	return exp->u.left == NULL;
}

int is_right_child_empty(struct  expression *exp)
{
	return exp->u.right == NULL;
}
