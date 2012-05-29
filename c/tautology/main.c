#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "types.h"
#include "scanner.h"

int main(int argc, char *argv[])
{

	int maxTokens = 10;

	// char input[maxTokens * 2];
	char *input = malloc(100 * sizeof(char));
	token *tokens = malloc(sizeof(token) * maxTokens);
	symbol *symbol_table = malloc(sizeof(struct symbol) * maxTokens);

	bzero(tokens, sizeof(struct token) * maxTokens);
	bzero(symbol_table, sizeof(struct symbol) * maxTokens);

	// char *input = malloc(maxTokens * 2 * sizeof(char));

	gets(input);
	printf("%s\n", input);

	scanner(input, tokens, symbol_table);

	int i;
	for (i = 0; i < maxTokens && tokens->type != NotToken; tokens++) {
		printf("type: %d , ", tokens->type);
		printf("assoc: %d , ", tokens->u.op.assoc);
		printf("precednece: %d \n", tokens->u.op.precedence);
	}



	for (i = 0; i < maxTokens && symbol_table[i].name != NULL; i++) {
		printf("tb: %d %s\n", i, symbol_table[i].name);
	}

	return 0;
}
