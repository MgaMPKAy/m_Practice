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

int main(int argc, char *argv[])
{
	struct expression *exp;
	int rval;
	int choice;
	char yesorno;
	int bitmap = 0;
	while (1) {
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
			printf("%s\n", "eval error");
			break;
		case 0:
			printf("%s\n", "False forever");
			printf("%s", "Print truth table? (y/n): ");
			scanf("%c", &yesorno);
			getchar();
			if (yesorno == 'y')
				print_truth_table(exp);
			break;
		case 1:
			printf("%s\n", "True forever");
			printf("%s", "Print truth table? (y/n): ");
			scanf("%c", &yesorno);
			getchar();
			if (yesorno == 'y')
				print_truth_table(exp);
			break;
		case 2:
			printf("%s\n", "Satisfactible");
			printf("Select: "
				"1.Print truth table "
				"2.Enter "
				"0.Return\n");
			scanf("%d", &choice);
			getchar();
			switch (choice) {
			case 0: break;
			case 1: print_truth_table(exp);
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
			}
		}
	}
	return 0;
}


void set_bit(int nth, int *bitmap, int b)
{
	if (b == 1) {
		(*bitmap) |= 1 << nth;
	}
}
