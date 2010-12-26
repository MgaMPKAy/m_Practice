#include <stdio.h>

void count(char *str)
{
	int en = 0, num = 0, sp = 0, ot = 0;
	int i, ch;
	for (i = 0; (ch = *(str + i)) != '\0'; i++){
		if ((ch >= 'a' && ch <= 'z')
		    || (ch >= 'A' && ch <= 'Z')){
			en++; continue;
		}
		else if (ch >= '0' && ch <= '9'){
			num++; continue;
		}
		else if (ch == ' '){
			sp++; continue;
	}
		else if (ch != '\n')
	    ot++;
	}
	
	printf("%d %d %d %d\n", en, num, sp, ot);
}

int main(void)
{
	char str[80];
	printf("Enter a string:");
	
	fgets(str, 80, stdin);
	// scanf("%s", str);  
	count(str);
	return 0;
}
