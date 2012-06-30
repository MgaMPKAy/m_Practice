#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include "types.h"


struct expression *new_expression();
struct expression *new_op_expression(expression_type,
				     struct expression*,
				     struct expression*);
struct expression *new_var_expression(int);
void destroy_expression(struct expression*);
void set_left_child(struct expression*, struct expression*);
void set_right_child(struct expression*, struct expression*);
int is_empty_expression(struct expression*);
int is_left_child_empty(struct  expression*);
int is_right_child_empty(struct  expression*);

#endif /* _EXPRESSION_H_ */
