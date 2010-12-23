#include <stdio.h>

int main(void)
{
	int c;
	int ch = 0, num = 0,space = 0, other= 0;
	while ((c = getchar()) != EOF && c != '\n'){
		if ((c > 'a' && c < 'z' )||( c > 'A' && c < 'z')){
			ch++; continue;
		}
		else if (c > '0' && c < '9'){
			num++; continue;
		}
		else if (c == ' '){
			space++; continue;
		}
		else
			other++;
	}
		
	printf("char= %d, num= %d, space= %d, other= %d\n",
	       ch, num, space, other);
	return 0;
}
