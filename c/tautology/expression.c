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

void pop_all(struct stack *stack, struct stack *output)
{
	while (!is_empty(stack)) {
		push(output, pop(stack));
	}
}

void pop_until_leftparen(struct stack *stack, struct stack *output)
{
	struct token * token = get_top(stack);
	if (token->type == LeftParen) {
		return;
	}
	push(output, pop(stack));
	pop_until_leftparen(stack, output);
}

int should_pop(struct token *token,
	       struct stack *stack,
	       struct stack *output)
{
	if (token->type == OpNot) {
		return False;
	}
	struct token *top = get_top(stack);
	if (top->type == OpNot) {
		return True;
	}
	if (token->type - top->type <= 0) {
		return True;
	}
	return False;
}


void pop_op(struct token *token,
	    struct stack *stack,
	    struct stack *output)
{
	if (token->type < OpOr || !should_pop(token, stack, output)) {
		return;
	}
	push(output, pop(stack));
	pop_op(++token, stack, output);
}


bool to_rpn(struct token *tokens,
       struct stack *stack,
       struct stack *output)
{

	struct token *curr;
	while (tokens->type == NotToken) {
		curr = tokens;
		switch (curr->type) {
		case Var:
			push(output, new_var_expression(curr));
			break;
		case LeftParen:

			push(output, new_paren_expression(curr));
			break;
		case RightParen:
			pop_until_leftparen(stack, output);
			break;
		case OpOr:
		case OpAnd:
		case OpNot:
			pop_op(curr, stack, output);
			push(stack, new_op_expression(curr));
		default:
			return False;
		}
		tokens++;
	}
	pop_all(stack, output);

	return True;
}
