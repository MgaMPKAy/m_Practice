#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "setjmp.h"
#include "types.h"
#include "tokenizer.h"
#include "parser.h"
#include "eval.h"
#include "print_prop.h"

int main(int argc, char *argv[])
{
	struct expression *exp;
	int rval;

	while (1) {
		init();
		exp = parse();
		if (exp == NULL) {
			printf("%s\n", "parser error");
			continue;
		}
		print_prop(exp);
		rval = eval_all(exp);
		switch (rval) {
		case -1:
			printf ("%s\n", "eval error");
			break;
		case 0:
			printf ("%s\n", "False forever");
			break;
		case 1:
			printf ("%s\n", "True forever");
			break;
		case 2:
			printf ("%s\n", "Satisfactible");
			break;
		}
	}
	return 0;
}
