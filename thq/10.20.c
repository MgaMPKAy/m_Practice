#include <stdio.h>
#include <string.h>
int main(void)
{
	char str[5][80];
	int i, j;
	char *s[5], *t;
	
	for (i = 0; i < 5; i++){
		fgets(str[i], 80, stdin);
		str[i][strlen(str[i]) - 1] = '\0';
		s[i] = str[i];
	}
	
	for (i = 0; i < 5; i++){
		for (j = 4; j > i; j--){
			if (!strcmp(s[j-1], s[j])){
				t = s[j-1];
				s[j-1] = s[j];
				s[j] = t;
			}
		}
	}
	
	printf("Sorted:\n");
	for (i = 0; i < 5; i++){
		printf("%s\n", s[i]);
	}
	
	return 0;
}
