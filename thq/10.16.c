#include <stdio.h>

int main(void)
{
    char str[80];
    char *begin, *end;
    int n = 0;
    printf("Enter a string:");
    fgets(str, 80, stdin);
    
    for (begin = str; *begin != '\0'; begin++){
	if (*begin >= '0' && *begin <= '9'){
	    for (end = begin; *end >= '0' && *end <= '9'; end++){
		printf("%c", *end);
	    }
	    printf("\n");
	    begin = end;
	    n++;
	}
    }
    printf("total %d numbers\n", n);
    return 0;
}
	    
