#ifndef _TYPES_H_
#define _TYPES_H_

#define False 0
#define True  1

typedef int bool;

typedef enum token_type {
	End,
	Var,
	LeftParen,
	RightParen,
	OpOr,
	OpAnd,
	OpNot,
} token_type;

struct token {
	enum token_type type;
	union {
		int var_id; /* for Var, symbol tabel index */
	} u;
};

struct symbol_table {
	int count;
	char *(*name)[];
};

typedef enum expression_type {
	VarExp,
	AndExp,
	OrExp,
	NotExp,
} expression_type;

struct expression {
	enum expression_type type;
	union {
		struct {
			struct expression *left;
			struct expression *right;
		};
		int var_id;
	} u;
};

#endif /* _TYPES_H_ */
