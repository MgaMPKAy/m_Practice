#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "token.h"
#include "stack.h"
#include "expression.h"
#include "eval.h"

int main(int argc, char *argv[])
{

	int maxTokens = 60;
	char *input = malloc(maxTokens * sizeof(char));
	struct token *tokens = malloc(maxTokens * sizeof(token));
	struct symbol_table *sym_table = new_symbol_table(maxTokens);
	struct stack *st = new_stack(maxTokens);
	struct stack  *expr_stack = new_stack(maxTokens);
	struct expression  *expr = NULL;

	bzero(tokens, sizeof(struct token) * maxTokens);

	// char *input = malloc(maxTokens * 2 * sizeof(char));

	gets(input);
	printf("%s\n", input);

	scanner(input, tokens, sym_table);

	to_rpn(tokens, st, expr_stack);

	expr = build_tree(expr_stack);

	int rval = eval_all(expr, sym_table);

	switch (rval) {
	case -2:
		printf("%s\n", "error");
		break;
	case -1:
		printf("%s\n", "Stastifible");
		break;
	case 0:
		printf("%s\n","Always false");
		break;
	case 1:
		printf("%s\n", "Always true");
		break;
	}
}
