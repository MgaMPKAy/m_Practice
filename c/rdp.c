#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
typedef int Boolean;
Boolean is_formula(char **s);

Boolean match(char **s, char token)
{
	if ((*s)[0] == token) {
		*s = *s + 1;
		return TRUE;
	}
	return FALSE;
}

Boolean is_proposition(char **s)
{
	char *orgin = *s;

	if (match(s, 'p') && ((*(s)[0] == '#') || (((*s)[0] != 'p') && (*s)[0] != '(')))
		return TRUE;
	*s = orgin;
	return FALSE;
}

Boolean is_left_paren(char **s)
{
	char *orgin = *s;

	if (match(s, '(') && (*s)[0] != '+')
		return TRUE;
	*s = orgin;
	return FALSE;
}

Boolean is_right_paren(char **s)
{
	char *orgin = *s;
	if (match(s, ')') && (*s)[0] != 'p' && (*s)[0] != '-')
		return TRUE;
	*s = orgin;
	return FALSE;
}

Boolean is_unary_op(char **s)
{
	char *orgin = *s;

	if (match(s, '-') && (*s)[0] != ')')
		return TRUE;
	*s = orgin;
	return FALSE;
}

Boolean is_binary_op(char **s)
{
	char *orgin = *s;

	if (match(s, '+') && (*s)[0] != '+' && (*s)[0] != ')' &&(*s)[0] != '#')
		return TRUE;
	*s = orgin;
	return FALSE;
}

Boolean is_end(char **s)
{
	if ((*s)[0] == '\n')
		return TRUE;
	else
		return FALSE;
}

Boolean is_term(char **s)
{
	char *orgin = *s;

	/* <term> ::= (<formula>) */
	if (is_left_paren(s) && is_formula(s) && is_right_paren(s))
		return TRUE;
	else
		*s = orgin;

	/* <term> ::= p */
	if (is_proposition(s) && (*s)[0] != '(' && (*s)[0] != '-')
		return TRUE;
	else
		*s = orgin;


	return FALSE;
}


Boolean is_formula(char **s)
{
	char *orgin = *s;

	/* <formula> ::= <term> */
	if (is_term(s) && (*s)[0] != '+' && (*s)[0] != '-' && (*s)[0] != 'p')
		return TRUE;
	else
		*s = orgin;

	/* <formula> ::= <formula>+<term>*/
	if (is_term(s) && is_binary_op(s) && is_formula(s))
		return TRUE;
	else
		*s = orgin;

	/* <formula> ::= -<formula> */
	if (is_unary_op(s) && is_formula(s))
		return TRUE;
	else
		*s = orgin;
	return FALSE;
}

Boolean is_formula_w(char **s)
{
	return is_formula(s) && is_end(s);
}

void test(char **input)
{
	printf("%s\n", is_formula_w(input) ? "Ture" : "False");
}

char *example = "(-(p)+(p))+-(-p+-p)+--p\n";

int main(void)
{
	char *input = malloc(sizeof(char) * 80);;
	char *orgin = input;
	
	printf("%s",example);
	test(&example);

	for (;;) {
		fgets(input, 80, stdin);

		test(&input);
		input = orgin;
	}
	return 0;
}
