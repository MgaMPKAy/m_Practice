#include "token.h"
#include "expression.h"

#ifndef _EVAL_H_
#define _EVAL_H_

int eval_single(struct expression *, int);
void print_truth_table(struct expression *, struct symbol_table *);
int eval_all(struct expression *, struct symbol_table *);
#endif /* _EVAL_H_ */
