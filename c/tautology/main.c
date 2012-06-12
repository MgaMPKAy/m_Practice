#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "types.h"
#include "tokenizer.h"
#include "parser.h"
#include "eval.h"

int main(int argc, char *argv[])
{
	while (1) {
		init();
		advanceToken();
		struct expression *exp = parse();
		if (exp == NULL) {
		printf("%s\n", "parser error");
		}
		int rval = eval_all(exp);
		printf("rval = %d\n", rval);
	}
	return 0;
}
