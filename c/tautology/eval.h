#include "token.h"
#include "expression.h"

#ifndef _EVAL_H_
#define _EVAL_H_

bool eval_single(struct expression *, int);
void eval_all(struct expression *);
void print_truth_table(struct expression *);
#endif /* _EVAL_H_ */
