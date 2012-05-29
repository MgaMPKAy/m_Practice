#ifndef _TYPES_H_
#define _TYPES_H_

#define False 0
#define True  1

typedef char bool;

typedef enum token_type {
	NotToken,
	Var,
	Const,
	LeftParen,
	RightParen,
	Operator,
} token_type;

typedef enum associativity {
	None,
	LeftAssoc,
	RightAssoc
} associativity;


typedef struct operator {
	char name;
	int precedence;
	enum associativity assoc;
} operator;


typedef struct token {
	enum token_type type;
	union {
		int varID; /* for Var, symbol tabel index */
		bool bool; /* for Const */
		struct operator op; /* for Operator */
	} u;
} token;

typedef struct symbol {
	char *name;
} symbol;

#endif
