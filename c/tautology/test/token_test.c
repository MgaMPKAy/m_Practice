#include <stdio.h>
#include <stdlib.h>
#include "../token.h"

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
	return 0;
}
