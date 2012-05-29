#ifndef _TOKEN_H_
#define _TOKEN_H_

#define False 0
#define True  1

typedef char bool;

typedef enum token_type {
	NotToken,
	Var,
	LeftParen,
	RightParen,
	OpOr,
	OpAnd,
	OpNot,
} token_type;


typedef struct token {
	enum token_type type;
	union {
		int varID; /* for Var, symbol tabel index */
	} u;
} token;

/* Todo: fix symbol_table */
typedef struct symbol_table {
	int count;
	char *name;
} symbol;

bool scanner(char *str, struct token *tokens, struct symbol *symbol_table);

#endif /* _TOKEN_H_ */
