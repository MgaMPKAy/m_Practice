#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define N 100

void enter(unsigned long id, unsigned short score);
int find(unsigned long id);
void sort(void);
void stat(void);
void retrieve_all(void);
void menu_main(void);
void menu_enter(void);
void menu_find(void);

unsigned long id_arr[N];
unsigned short score_arr[N];
int top;;

int main(void)
{
	int choice;
		
	while (1){
		system("clear");
		menu_main();
		scanf("%d", &choice);
		switch (choice){
		case 1: menu_enter(); break;
		case 2: menu_find(); break;
		case 3: stat(); break;
		case 4: sort(); break;
		case 5: retrieve_all();break;
		case 0: return 0;
		}
	}
	return 0;
}

void menu_main(void)
{
	printf("-------------------Welcome---------------------\n");
	printf("1.Enter\n2.Find\n3.Stat\n4.Sort(score)\n");
	printf("5.List\n");
	printf("0.Exit\n");
	printf("Please selct (0 ~ 4): ");
}

void enter(unsigned long id, unsigned short score)
{
	if (top >= N - 1)
		printf("Error: too many student\n");
	else {
		id_arr[top] = id;
		score_arr[top++] = score;
	}
}
		
void menu_enter(void)
{
	unsigned long id;
	unsigned short score;
	system("clear");
	menu_main();
	printf("\nEnter student's id: ");
	scanf("%ld", &id);
	printf("Enter student's score: ");
	scanf("%hd", &score);
	/* if (!isdigit(id) && !isdigit(score)){
		printf("Eror\n");
		return;
	}
	*/
	if (find(id) < 0){
		printf("OK\n");
		enter(id, score);
	}
	else 
		printf("Error:the same student\n");
	getchar();getchar();
}

int find(unsigned long id)
{
	int i;
	for (i = 0; i < top; i++){
		if (id == id_arr[i]){
			return i;
		}
	}
	return -1;
}

void  menu_find(void)
{
	unsigned long id;
	int i;
	system("clear");
	menu_main();
	printf("\nEnter student's id: ");
	scanf("%ld", &id);
	if ((i = find(id)) >= 0){
		printf("Student    Score\n");
		printf("%7ld     %4hd\n", id_arr[i], score_arr[i]);
	}
	else
		printf("Error: no such student\n");
	// system("pause");
	getchar();getchar();
}
		
void sort(void)
{
	unsigned short i, j , t_score;
	unsigned long t_id;
	for (i = 0; i < top; i++){
		for(j = top - 1; j > 0; j--){
			if (score_arr[j] > score_arr[j-1]){
				t_score = score_arr[j-1];
				score_arr[j-1] = score_arr[j];
				score_arr[j] = t_score;
				t_id = id_arr[j-1];
				id_arr[j-1] = id_arr[j];
				id_arr[j] = t_id;
			}
		}
	}
	system("clear");
	menu_main();
	printf("\nOK");
	getchar();getchar();
}

void stat(void)
{
	int i, a, b, c, d, e;
	float sum;
	a = b = c = d = e = 0; // global
	system("clear");
	menu_main();
	printf("\nA:\n");
	for (i = 0; i < top; i++){
		if (score_arr[i] >= 90){
			printf("%ld ", id_arr[i]);
			a++;
		}
	}
	printf("\nB:\n");
	for (i = 0; i < top; i++){
		if (score_arr[i] >= 80 && score_arr[i] < 90){
			printf("%ld ", id_arr[i]);
			b++;
		}
	}
	printf("\nC:\n");
	for (i = 0; i < top; i++){
		if (score_arr[i] >= 70 && score_arr[i] < 80){
			printf("%ld ", id_arr[i]);
			c++;
		}
	}
	printf("\nD:\n");
	for (i = 0; i < top; i++){
		if (score_arr[i] >= 60 && score_arr[i] < 70){
			printf("%ld ", id_arr[i]);
			d++;
		}
	}
	printf("\nE:\n");
       	for (i = 0; i < top; i++){
		if (score_arr[i] < 60){
			printf("%ld ", id_arr[i]);
			e++;
		}
	}
	for (i = 0, sum = 0; i < top; i++){
		sum+= score_arr[i];
	}
	printf("\nAverage= %f\n", sum / top);
	printf("A: %d, B: %d, C: %d, D: %d, E: %d,\n", a, b, c, d, e);
	getchar();getchar();
}


void retrieve_all(void)
{
	int i;
	system("clear");
	menu_main();
	putchar('\n');
	printf("Student    Score\n");
	for (i = 0; i < top; i++){
		printf("%7ld    %4hd\n", id_arr[i], score_arr[i]);			  				
	}
	getchar();getchar();
}

