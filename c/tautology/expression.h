#include "stack.h"
#include "token.h"

#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

typedef enum expression_type {
	VarExp,
	ParenExp,
	OpExp,
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

expression * build_tree(struct stack *);
bool to_rpn(struct token *,struct stack *, struct stack *);
#endif
