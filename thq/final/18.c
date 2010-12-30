#include <stdio.h>
#include <stdlib.h>

typedef  struct node *link;
struct node{
	int n;
	link next;
};

int main(void)
{
	int n, m, i;
	link tmp, tmp2;
	link head = malloc(sizeof(link));
	head->next = head;
	head->n = 1;
	
	printf("Enter n m: ");
	(void)scanf("%d %d", &n, &m);
	
	if (n < m || n < 1 || m < 1)
		exit(EXIT_SUCCESS);

	if (m == 1){
		printf("Result = %d\n", n);
		exit(EXIT_SUCCESS);
	}

	for (i = 2; i <= n; i++){
		tmp = malloc(sizeof(link));
		tmp->n = n - i + 2;
		tmp->next = head->next;;
		head->next = tmp;
	}	
	

	tmp = head;
	while(tmp->next != tmp){
		for (i = 0; i < m - 1; i++){
			tmp2 = tmp;
			tmp = tmp->next;
		}
		printf("Delete %d\n", tmp->n);
		tmp2->next = tmp->next;
		free(tmp);
		tmp = tmp2->next;
	}
	
	printf("Result = %d\n", tmp->n);
		
	return 0;
}
