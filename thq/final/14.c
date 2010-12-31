#include <stdio.h>
#include <stdlib.h>
#define N 100


void menu_main(void);
void menu_add(void);
void menu_find(void);

int get_choice(const char *str);
long get_id(const char *str);
short get_score(const char *str);

void add(long id, short score);
int find(long id);
void sort(void);
void stat(void);
void retrieve_all(void);

long id_arr[N];
short score_arr[N];
int top;

int main(void)
{
	while (!0){
		system("clear");  // windows下改为system("cls")
		menu_main();
	}
	return 0;
}

void menu_main(void)
{
	int choice = -1, c;
	while(1){
		system("clear");
		printf("-------------------Welcome---------------------\n");
		printf("1.Add\n2.Find\n3.Stat\n4.Sort(score)\n");
		printf("5.List\n");
		printf("0.Exit\n");

		choice = -1;
		while (choice < 0 || choice > 5){
			choice = get_choice("Please selct (0 ~ 5): ");
		}
		switch (choice){
		case 1: menu_add(); break;
		case 2: menu_find(); break;
		case 3: stat(); break;
		case 4: sort();
		case 5: retrieve_all();break;
		case 0: exit(EXIT_SUCCESS);
		}
		while((c = getchar()) != '\n' && c != EOF);
	}
	
}


void menu_add(void)
{
	long id;
	short score;
	
	if (top >= N - 1){
		printf("Error: too many student\n");
		return;
	}
	
	id = get_id("Enter student's id: ");
	
	score = get_score("Enter student's score: ");
	
	if (find(id) < 0){
		printf("OK\n");
		add(id, score);
	}
	else {
		printf("Error:the same student\n");
	}
	getchar();
}

void  menu_find(void)
{
        long id;
	int i;
	id = get_id("Enter student's id: ");

	if ((i = find(id)) >= 0){
		printf("Student    Score\n");
		printf("%7ld     %4d\n", id_arr[i], score_arr[i]);
	}
	else
		printf("Error: no such student\n");
	getchar();
}


void sort(void)
{
        short i, j , t_score;
        long t_id;
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
}

void stat(void)
{
	int i, a, b, c, d, e;
	float sum;
	a = b = c = d = e = 0;
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
	getchar();
}


void retrieve_all(void)
{
	int i;
	
	putchar('\n');
	printf("Student    Score\n");
	for (i = 0; i < top; i++){
		printf("%7ld    %4d\n", id_arr[i], score_arr[i]);			  				
	}
	getchar();
}

int get_choice(const char * str)
{
	
	int choice = -1;
	int c;
	printf("%s", str);
	scanf("%d", &choice);
	while((c = getchar()) != '\n' && c != EOF);
	return choice;
}


short get_score(const char * str)
{
	short score = 0;
	int c;
	while (score <= 0){
		printf("%s", str);
		scanf("%hd", &score);
		while((c = getchar()) != '\n' && c != EOF);
	}
	return score;
}

long get_id(const char * str)
{
	long id = 0;
	int c;
	while (id <= 0){
		printf("%s", str);
		scanf("%ld", &id);
		while((c = getchar()) != '\n' && c != EOF);
	}
	return id;
}

void add(long id, short score)
{
	
	id_arr[top] = id;
	score_arr[top++] = score;
}

int find(long id)
{
	int i;
	for (i = 0; i < top; i++){
		if (id == id_arr[i]){
			return i;
		}
	}
	return -1;
}
