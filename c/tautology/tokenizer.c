#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "types.h"

struct token *current_token;
struct symbol_table *symbol_table;

bool is_alphabet(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool is_digits(char c)
{
	return (c >= '0' && c <= '9');
}

struct symbol_table *new_symbol_table(int count)
{
	struct symbol_table *st = malloc(sizeof(struct symbol_table));
	st->count = 0;
	st->name  = malloc(count * sizeof(char*));
	bzero(st->name, count * sizeof(char *));
	return st;
}

void advanceToken()
{
	char *new_var_name;
	int max_length = 10;
	int ch = getchar();
	int i = 0;
	int j = 0;

	if (current_token != NULL) {
		free(current_token);
		current_token = NULL;
	}
	current_token = malloc(sizeof(struct token));

	/* skip whitespaces */
	while (ch == ' ' || ch == '\t') {
		ch = getchar();
	}

	/* token_type -> Var */
	/* ugly code, should be factored out */
	if (is_alphabet(ch) || is_digits(ch)) {
		current_token->type = Var;
		new_var_name = malloc(sizeof(char) * max_length);

		while (is_alphabet(ch) || is_digits(ch)) {
			new_var_name[i++] = ch;
			if (i >= max_length) {current_token = NULL; return;};
			ch = getchar();
		}
		ungetc(ch, stdin);
		new_var_name[i] = '\0';

		bool in_table = False;
		for (j = 0; j < symbol_table->count; j++) {
			if (strcmp((*(symbol_table->name))[j], new_var_name) == 0) {
				in_table = True;
				current_token->u.var_id = j;
				break;
			}
		}

		if (!in_table) {
			current_token->u.var_id = j;
			(*(symbol_table->name))[j] = new_var_name;
			symbol_table->count++;
		}
		return;
	}

	switch (ch) {
	case '(':
		current_token->type = LeftParen;
		break;
	case ')':
		current_token->type = RightParen;
		break;
	case '~':
		current_token->type = OpNot;
		break;
	case '&':
		current_token->type = OpAnd;
		break;
	case '|':
		current_token->type = OpOr;
		break;
	case '\n':
	case '\0':
		current_token->type = End;
		break;
	default:
		free(current_token);
		current_token = NULL;
		printf("tokenize error: unexpected char");
		break;
	}
}

void init()
{
	if (symbol_table != NULL) {
		free(symbol_table);
		symbol_table = NULL;
	}
	symbol_table = new_symbol_table(32);

	if (current_token != NULL) {
		free(current_token);
		current_token = NULL;
	}
}
