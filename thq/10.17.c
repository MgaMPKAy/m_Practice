#include <stdio.h>

int mystrcmp(char *p1, char *p2)
{
	unsigned char c1, c2;
	
	while (1) {
		c1 = *p1++;
		c2 = *p2++;
		if (c1 != c2)
			return c1 < c2 ? (c1 - c2) : (c2 - c1);
		if (!c1)
			break;
	}
    return 0;
}

int main(void)
{
	int n;
	char s1[80], s2[80];

	printf("Enter s1:");
	scanf("%s", s1);
	printf("Enter s2:");
	scanf("%s", s2);
	
	n = mystrcmp(s1, s2);
	printf("%d\n", n);
	
	return 0;
}
