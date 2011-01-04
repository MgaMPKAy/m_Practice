#include <stdio.h>
#include <stdlib.h>
#define N 100


static void menu_main(void);
static void menu_add(void);
static void menu_find(void);

static long get_id(const char *str);
static short get_score(const char *str);

static void add(long id, short, short, short);
static int find(long id);
static void sort(void);
static void retrieve_all(void);

static long id_arr[N];
static short score_arr[N][4];
static int top;

int main(void)
{
	while (!0){
		(void)system("clear");  // windows下改为system("cls")
		menu_main();
	}
	return 0;
}

void menu_main(void)
{
	int choice = -1, c;
	while(!0){
		/* */
		(void)system("clear");
		printf("-------------------Welcome----------------------\n");
		printf("- 1.Add                                        -\n");
		printf("- 2.Find                                       -\n");
		printf("- 3.Stat                                       -\n");
		printf("- 4.Sort                                       -\n");
		printf("- 0.Exit                                       -\n");
		printf("------------------------------------------------\n");
		/* */
		choice = -1;
		while (choice < 0 || choice > 4){
			printf("Please selct (0 ~ 4): ");
			scanf("%d", &choice);
			while((c = getchar()) != '\n' && c != EOF);
		}
		
		switch (choice){
		case 1: menu_add(); break;
		case 2: menu_find(); break;
		case 3: retrieve_all(); break;
		case 4: sort();retrieve_all();break;
		case 0: exit(EXIT_SUCCESS);
		}
	}
	
}


void menu_add(void)
{
	long id;
	short score[3];
	char choice = '\0';
	int c = -1;
	while (!0){
		printf("------------------------------------------------\n");
		if (top >= N - 1){
			printf("Error: too many student\n");
			return;
		}
		
		id = get_id("Enter student's id: ");
		
		score[0] = get_score("Enter English score: ");
		score[1] = get_score("Enter Math score: ");
		score[2] = get_score("Enter Computer score: ");
		
		if (find(id) < 0){
			printf("OK");
			add(id, score[0],score[1], score[2]);
		}
		else {
			printf("Error:the same student\n");
		}
		choice = '\0';
		while (choice != 'y' && choice != 'n'){
			printf("continue? (y / n): ");
			scanf("%c", &choice);
			while((c = getchar()) != '\n' && c != EOF);
		}
		if (choice == 'n')
			return;

	}
}

void  menu_find(void)
{
        long id;
	int i;
	char tmp[2];
	printf("------------------------------------------------\n");
	id = get_id("Enter student's id: ");
	
	if ((i = find(id)) >= 0){
		printf("  Student     English   Math    Comp.   Total\n");
		printf("\t%ld\t%4d\t%4d\t%4d\t%4d\n", id_arr[i],
		       score_arr[i][0], score_arr[i][1], score_arr[i][2], score_arr[i][3]);
	}
	else
		printf("Error: no such student\n");
	fgets(tmp, 2, stdin);
}


void sort(void)
{
        int  i, j , k;
	short t_score;
        long t_id;
	for (i = 0; i < top; i++){
		for(j = (top - 1); j > 0; j--){
			if (score_arr[j][3] > score_arr[j-1][3]){
				for(k = 0; k < 4; k++){
					t_score = score_arr[j-1][k];
					score_arr[j-1][k] = score_arr[j][k];
					score_arr[j][k] = t_score;
				}
				t_id = id_arr[j-1];
				id_arr[j-1] = id_arr[j];
				id_arr[j] = t_id;
			}
		}
	}
}


void retrieve_all(void)
{
	int i;
	char tmp[2];
	printf("------------------------------------------------\n");
	printf("  Student     English   Math    Comp.   Total\n");
	for (i = 0; i < top; i++){
		printf("\t%ld\t%4d\t%4d\t%4d\t%4d\n", id_arr[i],
		       score_arr[i][0], score_arr[i][1], score_arr[i][2], score_arr[i][3]);
	}
	fgets(tmp, 2, stdin);
}


short get_score(const char * str)
{
	short score = -1;
	int c;
	while (score < 0){
		printf("%s", str);
		(void)scanf("%hd", &score);
		while((c = getchar()) != (int)'\n' && c != EOF);
	}
	return score;
}

long get_id(const char * str)
{
	long id = 0;
	int c;
	while (id <= 0){
		printf("%s", str);
		(void)scanf("%ld", &id);
		while((c = getchar()) != (int)'\n' && c != EOF);
	}
	return id;
}

void add(long id, short s0, short s1, short s2)
{
	
	id_arr[top] = id;
	score_arr[top][0] = s0;
	score_arr[top][1] = s1;
	score_arr[top][2] = s2;
	score_arr[top][3] = (s0 + s1 + s2);
	top++;
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
