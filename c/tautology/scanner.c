#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

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

char *get_varname(char *s)
{
	return NULL;
}

bool new_op_or(struct token *token)
{
	if (!token) {

	}
	token->type = Operator;
	token->u.op.name = '|';
	token->u.op.precedence = 1;
	token->u.op.assoc = LeftAssoc;
	return True;
}

bool new_op_and(struct token *token)
{
	if (!token) {

	}
	token->type = Operator;
	token->u.op.name = '&';
	token->u.op.precedence = 2;
	token->u.op.assoc = LeftAssoc;
	return True;
}

bool new_op_not(struct token *token)
{
	if (!token) {

	}
	token->type = Operator;
	token->u.op.name = '~';
	token->u.op.precedence = 3;
	token->u.op.assoc = None;
	return True;
}

int new_var(char *str, struct token *token, struct symbol *symbol_table)
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
	for (i = 0; symbol_table[i].name != NULL; i++) {
		if (strncmp(symbol_table[i].name, str, var_name_length) == 0) {
			var_in_table = True;
			token->u.varID = i;
		}
	}

	if (!var_in_table) {
		token->u.varID = i;
		new_var_name = malloc(var_name_length * sizeof(char) + 1);
		strncpy(new_var_name, str, var_name_length);
		new_var_name[var_name_length] = '\0';
		symbol_table[i].name = new_var_name;
	}

	return var_name_length;
}

bool scanner(char *str, struct token *tokens, struct symbol *symbol_table)
{
	char c = *str;

	while (c != '\0') {

		if (is_whitepace(c)) {
			str++;
		} else if (is_alphabet(c)) {
			int x = new_var(str, tokens, symbol_table);
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
				new_op_and(tokens);
				break;
			case '~' :
				new_op_not(tokens);
				break;
			case '|' :
				new_op_or(tokens);
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
