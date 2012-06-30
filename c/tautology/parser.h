#ifndef _PARSER_H_
#define _PARSER_H_

extern struct token *current_token;
extern struct symbol_table *symbol_table;

struct expression *parse();
struct expression *new_expression();
void   destroy_expression(struct expression*);

#endif /* _PARSER_H_ */
