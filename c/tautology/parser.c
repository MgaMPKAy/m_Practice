#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "types.h"
#include "tokenizer.h"
#include "parser.h"

struct expression *parse_term();
struct expression *parse_exp();
struct expression *parse_prop();
struct expression *new_expression();
void   destroy_expression(struct expression*);

struct expression *parse_term()
{
	struct expression *term;

	if (current_token == NULL) return NULL;
	switch (current_token->type) {
	case Var:
		term = new_expression();
		term->type = VarExp;
		term->u.var_id = current_token->u.var_id;
		advanceToken();
		return term;
	case LeftParen:
		advanceToken();
		term = parse_prop();
		if (term == NULL) {
			return NULL;
		}
		switch (current_token->type) {
		case RightParen:
			advanceToken();
			return term;
		default:
			return NULL;
		}
	case OpNot:
		advanceToken();
		term = new_expression();
		term->type = NotExp;
		term->u.right = NULL;
		term->u.left = parse_term();
		if (term->u.left == NULL) {
			free(term);
			return NULL;
		}
		return term;
	default:
		return NULL;
	}
}

struct expression *parse_exp()
{
	struct expression *term = parse_term();
	if (term == NULL) {
		return NULL;
	}

	if (current_token == NULL) return NULL;

	switch(current_token->type) {
	case OpAnd:
		advanceToken();
		struct expression *exp = new_expression();
		exp->type = AndExp;
		exp->u.left = term;
		exp->u.right = parse_exp();
		if (exp->u.right == NULL) {
			free(exp);
			return NULL;
		}
		return exp;
	default:
		return term;
	}
}

struct expression *parse_prop()
{
	struct expression *exp = parse_exp();
	if (exp == NULL) {
		return NULL;
	}
	if (current_token == NULL) return NULL;
	switch(current_token->type) {
	case OpOr:
		advanceToken();
		struct expression *prop = new_expression();
		prop->type = OrExp;
		prop->u.left = exp;
		prop->u.right = parse_prop();
		if (prop->u.right == NULL) {
			free(exp);
			return NULL;
		}
		return prop;
	default:
		return exp;
	}
}

struct expression *parse()
{
	init();
	advanceToken();
	struct expression *prop = parse_prop();

	if (prop == NULL) {
		return NULL;
	}
	if (current_token == NULL) return NULL;
	switch(current_token->type) {
	case End:
		return prop;
	default:
		return NULL;
	}
}

struct expression *new_expression()
{
	struct expression *exp = malloc(sizeof(struct expression));
	bzero(exp, sizeof(struct expression));
	return exp;
}

void destroy_expression(struct expression *exp)
{
	if (exp == NULL) return;
	if (exp->type != VarExp) {
		destroy_expression(exp->u.left);
		destroy_expression(exp->u.right);
	}
	free(exp);
}
