#include <stdio.h>
#include "to_rpn.h"
#include "token.h"
#include "stack.h"
#include "expression.h"

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
