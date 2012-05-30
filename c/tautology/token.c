#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

bool is_whitepace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == 'n');
}

bool is_digits(char c)
{
	return (c >= '0' && c <= '9');
}

bool is_alphabet(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int new_var(char *str, struct token *token, struct symbol_table *sym_table)
{
	int var_name_length = 0;
	char *iter = str;
	char *new_var_name;
	int i;
	token->type = Var;

	while (*str != '\0' && is_alphabet(*(iter++))) {
		var_name_length++;
	}

	bool var_in_table = False;
	for (i = 0; (*(sym_table->name))[i] != NULL; i++) {
		if (strncmp((*(sym_table->name))[i], str, var_name_length) == 0) {
			var_in_table = True;
			token->u.varID = i;
		}
	}

	if (!var_in_table) {
		token->u.varID = i;
		new_var_name = malloc(var_name_length * sizeof(char) + 1);
		strncpy(new_var_name, str, var_name_length);
		new_var_name[var_name_length] = '\0';
		(*(sym_table->name))[i] = new_var_name;
		sym_table->count++;
	}

	return var_name_length;
}

bool scanner(char *str, struct token *tokens, struct symbol_table *sym_table)
{
	char c = *str;

	while (c != '\0') {

		if (is_whitepace(c)) {
			str++;
		} else if (is_alphabet(c)) {
			int x = new_var(str, tokens, sym_table);
			str += x;
			tokens++;
		} else {
			switch (c) {
			case '(' :
				tokens->type = LeftParen;
				break;
			case ')' :
				tokens->type = RightParen;
				break;
			case '&' :
				tokens->type = OpAnd;
				break;
			case '~' :
				tokens->type = OpNot;
				break;
			case '|' :
				tokens->type = OpOr;
				break;
			default:
				return False;
			}
			tokens++;
			str++;
		}
		c = *str;
	}
	return True;
}
