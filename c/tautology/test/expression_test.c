#include <stdio.h>
#include <stdlib.h>
#include "../token.h"
#include "../expression.h"

void print_token(struct token *token)
{
	switch(token->type) {
	case Var :
		printf("Var %d\n", token->u.varID);
		break;
	case LeftParen:
		printf("LeftParen\n");
		break;
	case RightParen:
		printf("RightParen\n");
		break;
	case OpOr:
		printf("OpOr\n");
		break;
	case OpAnd:
		printf("OpAnd\n");
		break;
	case OpNot:
		printf("OpNot\n");
		break;
	default:
		printf("%s\n", "error");
		}
}

void print_expression(struct expression *expr)
{
	switch(expr->type) {
	case VarExp:
		printf("Var %d\n", expr->u.varID);
		break;
	case ParenExp:
		printf("Paren\n");
		break;
	case OpExp:
		switch(expr->u.op) {
		case OpOr:
			printf("OpOr\n");
			break;
		case OpAnd:
			printf("OpAnd\n");
			break;
		case OpNot:
			printf("OpNot\n");
			break;
		}
		break;
	default:
		printf("%s\n", "error");
	}
}


int main(int argc, char *argv[])
{
	char input[100];
	gets(input);
	struct symbol_table *sym_table = new_symbol_table(100);
	struct token *tokens = malloc(100 * sizeof(token));
	scanner(input, tokens, sym_table);

	printf("tokens: \n");
	for (int i = 0; tokens[i].type != NotToken; i++) {
		switch(tokens[i].type) {
		case Var :
			printf("%d: Var %d\n", i, tokens[i].u.varID);
			break;
		case LeftParen:
			printf("%d: LeftParen\n", i);
			break;
		case RightParen:
			printf("%d: RightParen\n", i);
			break;
		case OpOr:
			printf("%d: OpOr\n", i);
			break;
		case OpAnd:
			printf("%d: OpAnd\n", i);
			break;
		case OpNot:
			printf("%d: OpNot\n", i);
			break;
		default:
			printf("%s\n", "error");
		}
	}

	printf("sym_table\n");
	for (int i = 0; i < sym_table->count; i++) {
		printf("idd %d: %s\n", i, (*(sym_table->name))[i]);
	}

	printf("----to_rpn------- \n");
	struct stack *st = new_stack(100);
	struct stack *output = new_stack(100);
	to_rpn(tokens, st, output);

	printf("----to_rpn end--- \n");
	printf("st->top = %d\n", st->top);
	printf("output->top = %d\n", output->top);

	printf("tokens should change\n");
	for (int i = 0; tokens[i].type != NotToken; i++) {
		switch(tokens[i].type) {
		case Var :
			printf("%d: Var %d\n", i, tokens[i].u.varID);
			break;
		case LeftParen:
			printf("%d: LeftParen\n", i);
			break;
		case RightParen:
			printf("%d: RightParen\n", i);
			break;
		case OpOr:
			printf("%d: OpOr\n", i);
			break;
		case OpAnd:
			printf("%d: OpAnd\n", i);
			break;
		case OpNot:
			printf("%d: OpNot\n", i);
			break;
		default:
			printf("%s\n", "error");
		}
	}

	printf("stack st should be empty\nst:\n");
	for (int i = 0; i < st->top; i++) {
		printf("%d ", i);
		print_expression((*(st->st))[i]);
	}

	printf("stack output should not be empty:\noutput:\n");
	for (int i = 0; i <= output->top; i++) {
		printf("%d ", i);
		print_expression((*(output->st))[i]);
	}

	printf("-----------expression test---------\n");
	struct expression *expr = NULL;
	expr = build_tree(output);
	printf("%x\n", (*(output->st))[output->top]);

	printf("expr = %x\n", expr);


	return 0;
}
