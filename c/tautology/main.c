#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "parser.h"
#include "eval.h"
#include "expression.h"

void handle_true(struct expression*);
void handle_false(struct expression*);
void handle_satisfactible(struct expression*);
void set_bit(int nth, int *bitmap, int b);

int main(int argc, char *argv[])
{
	struct expression *exp;
	int tmp_char, rval;

	while (1) {
		system("clear");
		printf("************ Tautology checker ************\n");
		printf("%s","Enter a proposition: ");
		exp = parse();
		if (exp == NULL) {
			printf("%s\n", "parser error");
			while((tmp_char = getchar()) != '\n');
			continue;
		}
		rval = eval_all(exp);
		switch (rval) {
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
	printf("Print truth table? (y/n): ");
	scanf("%c", &yesorno);
	while((tmp_char = getchar()) != '\n');
	if (yesorno == 'y')
		print_truth_table(exp);
}

void handle_satisfactible(struct expression *exp)
{
	int choice, bitmap, rval, tmp_char;
	char yesorno;

	system("clear");
	printf("%s\n", "Satisfactible");
interact:
	printf("*************************************\n"
	       "*   1. Print truth table            *\n"
	       "*   2. Interact                     *\n"
	       "*   3. Enter another expression     *\n"
	       "*   0. Quit                         *\n"
	       "*************************************\n"
	       "Select: ");
	scanf("%d", &choice);
	getchar();
	switch (choice) {
	case 0: exit(0);
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
	case 3:
		break;
	default:
		goto interact;
	}
}

void set_bit(int nth, int *bitmap, int b)
{
	if (b == 1) {
		(*bitmap) |= 1 << nth;
	}
}
