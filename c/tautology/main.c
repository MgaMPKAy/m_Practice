#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "types.h"
#include "tokenizer.h"
#include "parser.h"
#include "eval.h"
#include "print_prop.h"

void set_bit(int nth, int *bitmap, int b);
void handle_error();
void handle_true(struct expression*);
void handle_false(struct expression*);
void handle_satisfactible(struct expression*);

int main(int argc, char *argv[])
{
	struct expression *exp;
	int rval;
	int choice;
	char yesorno;
	int bitmap = 0;
	int tmp_char;
	while (1) {
		printf("*************************************************\n");
		printf("%s","Enter a proposition: ");
		exp = parse();
		if (exp == NULL) {
			printf("%s\n", "parser error");
			continue;
		}
		// print_prop(exp);
		rval = eval_all(exp);
		switch (rval) {
		case -1:
			handle_error();
			break;
		case 0:
			handle_false(exp);
			break;
		case 1:
			handle_true(exp);
			break;
		case 2:
			handle_satisfactible(exp);
		}
		destroy_expression(exp);
	}
	return 0;
}

void set_bit(int nth, int *bitmap, int b)
{
	if (b == 1) {
		(*bitmap) |= 1 << nth;
	}
}

void handle_error()
{
	printf("%s\n", "eval error");
}

void handle_false(struct expression *exp)
{
	char yesorno;
	int tmp_char;
	printf("%s\n", "False forever");
	printf("%s", "Print truth table? (y/n): ");
	scanf("%c", &yesorno);
	while((tmp_char = getchar()) != '\n');
	if (yesorno == 'y')
		print_truth_table(exp);
}

void handle_true(struct expression *exp)
{
	char yesorno;
	int tmp_char;

	printf("%s\n", "True forever");
	printf("%s", "Print truth table? (y/n): ");
	scanf("%c", &yesorno);
	while((tmp_char = getchar()) != '\n');
	if (yesorno == 'y')
		print_truth_table(exp);
}

void handle_satisfactible(struct expression *exp)
{
	int choice, bitmap, rval, tmp_char;
	char yesorno;

	printf("%s\n", "Satisfactible");
interact:
	printf("Select: "
	       "1.Print truth table "
	       "2.Interact "
	       "0.Return: ");
	scanf("%d", &choice);
	getchar();
	switch (choice) {
	case 0: break;
	case 1: print_truth_table(exp);
		goto interact;
		break;
	case 2:
		bitmap = 0;
		for (int i = 0; i < symbol_table->count; i++) {
			printf("%s = ",
			       (*(symbol_table->name))[i]);
			scanf("%d", &choice);
			getchar();
			set_bit(i, &bitmap, choice);
		}
		rval = eval_single(exp, bitmap);
		switch (rval) {
		case -1:
			printf("%s\n", "eval error");
			break;
		case 0:
			printf("%s\n", "False");
					break;
		case 1:
			printf("%s\n", "True");
			break;
		}
		goto interact;
	default:
		goto interact;
	}
}
