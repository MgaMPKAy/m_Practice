#include <stdio.h>

char* bubble(char *str)
{
    int i, j, s, t;
    for (s = 0; str[s] != '\0'; s++);
    
    for (i = 0; i < s - 1; i++){
	for (j = s - 1; j > i; j--){
	    if (str[j-1] > str[j]){
		t = str[j];
		str[j] = str[j-1];
		str[j-1] = t;
	    }
	}
    }
    return str;
}

int main(void)
{
    char s[80];
    printf("Enter 10 char:");
    scanf("%s", s);
    
    printf("%s\n", bubble(s));
    return 0;
}
