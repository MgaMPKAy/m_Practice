#include <stdio.h>

int main(void)
{
	int m, n, t1, t2, t3, gcd;
	printf("Enter m n: ");
	scanf("%d %d", &m, &n);

	if (n > m){
		t1 = n; n = m; m =t1;
	}
	
	t1 = m; t2 = n;
	while (t2 != 0){
		t3 = t2;
		t2 = t1 % t2;
		t1 = t3;
	}
	gcd = t1;

	
	printf("gcd = %d\n", gcd);
	printf("xxx = %d\n", m * n / gcd); 
	return 0;
}
