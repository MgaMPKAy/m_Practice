#include <stdio.h>
#include <string.h>
#define N 1000
char *itoa(long num, char *str)
{
	int i = 0;
	do {
		str[i] = num % 10 + '0';
		num /= 10;
		i++;
	} while (num >= 10);
	str[i] = num + '0';
	str[i+1] = '\0';
	return str;
}

int isp(char *str)
{
	int i, j;
	for(i = 0, j = strlen(str) - 1; i < j; i++, j--){
		if (str[i] != str[j])
			return 0;
	}
	return 1;
}

int main(void)
{
	long a, b, max = 0, tmp;
	char str[10];
	
	for (a = 100; a < N; a++){
		for (b = 100; b < N; b++){
			if (isp(itoa(tmp = a * b, str))){
				if (tmp > max){
					max = tmp;
				}
			}
		}
	}
	printf("max = %ld\n", max);
       	return 0;
}
