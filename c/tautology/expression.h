#include "stack.h"
#include "token.h"

#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

typedef enum expression_type {
	OpExp,
	VarExp,
	ParenExp
} expression_type;

typedef struct expression {
	enum expression_type type;
	union {
		struct {
			struct expression *left;
			struct expression *right;
			enum token_type op;
		};
		enum token_type paren;
		int varID;
	} u;
} expression;

expression * new_var_expression(struct token *token);
expression * new_paren_expression(struct token *token);
expression * new_op_expression(struct token *token);
expression * build_tree(struct stack *);

#endif
