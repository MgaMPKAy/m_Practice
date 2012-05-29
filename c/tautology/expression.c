#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "token.h"
#include "expression.h"

expression *new_var_expression(struct token *token)
{
	expression * expr = malloc(sizeof(expression));
	expr->type = VarExp;
	expr->u.varID = token->u.varID;
	return expr;
}

expression *new_paren_expression(struct token *token)
{
	expression * expr = malloc(sizeof(expression));
	expr->type = ParenExp;
	expr->u.paren = token->type;
	return expr;
}

expression *new_op_expression(struct token *token)
{
	expression * expr = malloc(sizeof(expression));
	expr->type = OpExp;
	expr->u.left = NULL;
	expr->u.right = NULL;
	expr->u.op = token->type;
	return expr;
}

expression * build_tree(struct stack *stack)
{
	struct expression *expr;
	for (int i = 0; i < stack->top; i++) {
		expr = (*(stack->st))[i];
		switch (expr->type) {
		case VarExp:
		case ParenExp:
			/* skip, do nothinh */
			break;
		case OpExp:
			switch(expr->u.op) {
			case OpAnd:
			case OpOr:
				expr->u.left = (*(stack->st))[i - 1];
				expr->u.left = (*(stack->st))[i - 2];
				break;
			case OpNot:
				expr->u.left = (*(stack->st))[i - 1];
				break;
			default:
				break;
			}
		}
	}
	return expr;
}
