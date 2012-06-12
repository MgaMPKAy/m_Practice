#ifndef _PARSER_H_
#define _PARSER_H_

extern struct token *current_token;
extern struct symbol_table *symbol_table;

struct expression *parse();
#endif /* _PARSER_H_ */
