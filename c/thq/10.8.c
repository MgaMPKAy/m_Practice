#include <stdio.h>

int main(void)
{
	int up = 0, low = 0, sp = 0, num = 0, ot = 0;
	char str[80], *s;
	
	printf("Enter a string:");
	fgets(str, 80, stdin);
	
	for (s = str; *s != '\0'; s++){
		if (*s == '\0' || *s == '\n')
			break;
		else if (*s >= 'A' && *s <= 'Z'){
			up++; continue;
		}
		else if (*s >= 'a' && *s <= 'z'){
			low++; continue;
		}
		else if (*s >= '0' && *s <= '9'){
			num++; continue;
		}
		else if (*s == ' '){
			sp++; continue;
		}
		else
			ot++;
	}
	
	printf("%d %d %d %d %d",
	       up, low, sp, num, ot);
	return 0;
}
