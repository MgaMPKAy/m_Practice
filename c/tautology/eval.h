#ifndef _EVAL_H_
#define _EVAL_H_

extern struct token *current_token;
extern struct symbol_table *symbol_table;

int eval_single(struct expression *, int);
int eval_all(struct expression *);
void print_truth_table(struct expression *);

#endif /* _EVAL_H_ */
