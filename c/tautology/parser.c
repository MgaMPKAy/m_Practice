#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "tokenizer.h"
#include "parser.h"
#include "expression.h"

struct expression *parse_term();
struct expression *parse_exp();
struct expression *parse_prop();

struct expression *parse_term()
{
	struct expression *term;

	if (current_token == NULL) return NULL;

	switch (current_token->type) {
	case Var:
		term = new_var_expression(current_token->u.var_id);
		advanceToken();
		return term;
	case LeftParen:
		advanceToken();
		term = parse_prop();
		if (is_empty_expression(term)) {
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
		term = new_op_expression(NotExp, parse_term(), NULL);
		if (is_left_child_empty(term)) {
			destroy_expression(term);
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
	if (is_empty_expression(term))
		return NULL;

	if (current_token == NULL) return NULL;

	switch (current_token->type) {
	case OpAnd:
		advanceToken();
		struct expression *exp =
			new_op_expression(AndExp, term, parse_exp());
		if (is_right_child_empty(exp)) {
			destroy_expression(exp);
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

	if (is_empty_expression(exp) || current_token == NULL)
		return NULL;

	switch (current_token->type) {
	case OpOr:
		advanceToken();
		struct expression *prop =
			new_op_expression(OrExp, exp, parse_prop());
		if (is_right_child_empty(prop)) {
			destroy_expression(exp);
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

	if (is_empty_expression(prop) || current_token == NULL
	    || current_token->type != End) {
		return NULL;
	}
	return prop;
}
