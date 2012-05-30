#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "token.h"
#include "expression.h"

expression *new_var_expression(struct token *token)
{
	expression * expr = malloc(sizeof(struct expression));
	expr->type = VarExp;
	expr->u.varID = token->u.varID;
	return expr;
}

expression *new_paren_expression(struct token *token)
{
	expression * expr = malloc(sizeof(struct expression));
	expr->type = ParenExp;
	expr->u.paren = token->type;
	return expr;
}

expression *new_op_expression(struct token *token)
{
	expression * expr = malloc(sizeof(struct expression));
	expr->type = OpExp;
	expr->u.left = NULL;
	expr->u.right = NULL;
	expr->u.op = token->type;
	return expr;
}

expression *build_tree(struct stack *stack)
{
	struct expression *expr = NULL;
	int j = 0;
	for (int i = 0; i <= stack->top; i++) {
		j = i;
		expr = (*(stack->st))[i];
		switch (expr->type) {
		case VarExp:
			expr = (*(stack->st))[i];
			break;
		case OpExp:
			switch(expr->u.op) {
			case OpAnd:
			case OpOr:
				expr = (*(stack->st))[i];
				for (j = i; j > 0; j--) {
					if ((*(stack->st))[j]) break;
				}
				expr->u.left = (*(stack->st))[j];
				(*(stack->st))[j] = NULL;
				for (;j > 0; j--) {
					if ((*(stack->st))[j]) break;
				}
				expr->u.left = (*(stack->st))[j];
				(*(stack->st))[j] = NULL;
				break;
			case OpNot:
				expr = (*(stack->st))[i];
				for (int j = i; j > 0; j--) {
					if ((*(stack->st))[j]) break;
				}
				expr->u.left = (*(stack->st))[j];
				(*(stack->st))[j] = NULL;
				break;
			default:
				break;
			}
		case ParenExp:
			printf("%s\n", "error");
			break;
		}
	}
	return expr;
}

void pop_all(struct stack *stack, struct stack *output)
{
	while (!is_empty(stack)) {
		printf("stack->top = %d\n", stack->top);
		push(output, pop(stack));
	}
}

void pop_until_leftparen(struct stack *stack, struct stack *output)
{
	printf("%d\n", stack->top);

	if (is_empty(stack)) {
		printf("%s\n", "error: stack empty");
		return;
	}
	struct expression *expr = get_top(stack);
	if (expr->type == ParenExp && expr->u.paren == LeftParen) {
		return;
	}
	push(output, pop(stack));
	pop_until_leftparen(stack, output);
}

int should_pop(struct token *token,
	       struct stack *stack,
	       struct stack *output)
{
	printf("%s\n", "in should pop");
	if (is_empty(stack)) {
		printf("%s\n", "stack empty -> don't pop");
		return False;
	}
	if (token->type == OpNot) {
		printf("%s\n", "unary -> don't pop");
		return False;
	}
	struct expression *top = get_top(stack);
	if (top->type == OpExp && top->u.op == OpNot) {
		printf("%s\n", "unary -> don't pop");
		return True;
	}
	if (token->type - top->type <= 0) {
		printf("%s\n", "binary and pred ok ->  pop");
		return True;
	}
	return False;
}


void pop_op(struct token *token,
	    struct stack *stack,
	    struct stack *output)
{
	printf("%s\n", "in pop op");
	if (token->type < OpOr || !should_pop(token, stack, output)) {
		printf("%s\n", "should not pop");
		return;
	}
	printf("%s\n", "should  pop");
	push(output, pop(stack));
	pop_op(++token, stack, output);
}


bool to_rpn(struct token *tokens,
       struct stack *stack,
       struct stack *output)
{

	struct token *curr = tokens;

	while (tokens->type != NotToken) {
		curr = tokens;
		switch (curr->type) {
		case Var:
			printf("%s\n", "++push Var exp to output");
			push(output, new_var_expression(curr));
			break;
		case LeftParen:
			printf("%s\n", "++push LeftParen exp to stack");
			push(stack, new_paren_expression(curr));
			break;
		case RightParen:
			printf("%s\n", "++pop util LeftParen");
			pop_until_leftparen(stack, output);
			pop(stack);
			break;
		case OpOr:
		case OpAnd:
		case OpNot:
			printf("%s\n", "++pop util Op");
			pop_op(curr, stack, output);
			push(stack, new_op_expression(curr));
			break;
		default:
			printf("%s\n", "error");
		}
		tokens++;
	}
	printf("%s\n", "++pop all");
	pop_all(stack, output);

	return True;
}

