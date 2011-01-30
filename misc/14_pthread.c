#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct student *link;
struct student{
        long id;
	int engl;
	int math;
	int comp;
	int total;
	link next;
};
	
static void menu_add(void);
static void menu_find(void);
static void menu_list(void);


static link find_student(long id);
static void add_student(long, int, int, int);
static void lsort(void);

static void get_input(char *, void *,int func(char*, void*), char *);
/* helper func for get_input */
static int greater_than_0(char*, void*);
static int range0_4(char*, void*);
static int yesno(char*, void*);

static link lstud;
static pthread_mutex_t global_mutex;

int main(void)
{
	int choice = -1;
	pthread_mutex_init(&global_mutex, NULL);
	pthread_t tid_lsort;
	
	while(!0){
		(void)system("clear");
		printf("-------------------Welcome----------------------\n");
		printf("- 1.Add                                        -\n");
		printf("- 2.Find                                       -\n");
		printf("- 3.Stat                                       -\n");
		printf("- 4.Sort (total score)                         -\n");
		printf("- 0.Exit                                       -\n");
		printf("------------------------------------------------\n");
		
		get_input("%d", &choice, range0_4, "Please select (0 ~ 4): ");
		
		switch (choice){
		case 1: menu_add(); break;
		case 2: menu_find(); break;
		case 3: menu_list(); break;
		case 4: pthread_create(&tid_lsort, NULL, lsort, NULL);
			pthread_join(tid_lsort, NULL);
			menu_list(); break;
		case 0: exit(EXIT_SUCCESS);
		}
	}
	return 0;
}

/* submenus */
void menu_add(void)
{
	long id;
	int score[3];
	char choice = '\0';
	
	while (!0){
		printf("------------------------------------------------\n");
		
		get_input("%ld",(void*) &id, greater_than_0,
			  "Enter student's id: ");
		get_input("%d", (void*)&score[0], greater_than_0,
			  "Enter English score: ");
		get_input("%d", (void*)&score[1], greater_than_0,
			  "Enter Math score: ");
		get_input("%d", (void*)&score[2], greater_than_0,
			  "Enter Computer score: ");
		
		if (!find_student(id)){
			printf("OK\n");
		      	add_student(id, score[0],score[1], score[2]);
		} else {
			printf("Error:the same student\n");
		}
		
		get_input("%c", &choice, yesno,
			  "Add another student? (y / n)");
		if (choice == 'n' || choice == 'N')
			return;
	}
}

void menu_find(void)
{
	long id;
	char choice;
	link stud;
	while(!0){
		printf("------------------------------------------------\n");
		get_input("%ld", (void*)&id, greater_than_0,
			  "Enter student's id: ");
		if ((stud = find_student(id))){
			printf("  Student     English   Math    Comp.   Total\n");
			printf("\t%ld\t%4d\t%4d\t%4d\t%4d\n", stud->id, stud->engl,
			       stud->math,  stud->comp, stud->total);
		}
		else{
			printf("!!!Error: can't find this student\n");
		}
		get_input("%c", (void*)&choice, yesno,
			  "Find another student? (y / n)");
		if (choice == 'n' || choice == 'N')
			return;
	}
}

void menu_list(void)
{
	link iter = lstud;

       	if (iter == NULL){
		get_input(NULL, NULL, NULL, "No data now");
		return;
	}
	printf("------------------------------------------------\n");
	printf("  Student     English   Math    Comp.   Total\n");
    	while(iter != NULL){
		printf("\t%ld\t%4d\t%4d\t%4d\t%4d\n", iter->id, iter->engl,
		       iter->math,  iter->comp, iter->total);
		iter = iter->next;
	}
	get_input(NULL, NULL, NULL, "Press Enter to continue ");
}

/* operate on lits & data*/
void add_student(long id, int engl, int math, int comp)
{
	link nstud = malloc(sizeof(* nstud));
	nstud->id = id;
	nstud->engl = engl;
	nstud->math = math;
	nstud->comp =comp;
	nstud->total = engl + math + comp;

	if (lstud == NULL){
		lstud = nstud;
		nstud->next = NULL;
	}
	else {
		nstud->next = lstud->next;
		lstud->next = nstud;
	}
}


link find_student(long id)
{
	link iter = lstud;
	if (iter == NULL)
		return NULL;
	while(iter != NULL && iter->id!= id)
		iter = iter->next;
	return iter;
}

void lsort(void)
{
	/* damm slow but easy bubble sort*/
	link i ,jp, j, jn;
	link tmp_head = malloc(sizeof(*tmp_head));
	tmp_head->next = lstud;
	for (i = tmp_head; i != NULL; i = i->next){
		for (jp = i; jp != NULL && (j = jp->next)!= NULL
			     && (jn = j->next)!= NULL; jp = jp->next){
			if (j->total < jn->total){
				j->next = jn->next;
				jn->next = j;
				jp->next = jn;
			}
		}
	}
	lstud = tmp_head->next;
	free(tmp_head);
}

/* universal input & check */
void get_input(char *pattern, void *containr, int ok(char*, void*), char *greet)
{
	char input[80];
	if (!pattern || !containr || !ok){
		printf("%s", greet);
		fgets(input, 79, stdin);
		return;
	}
	do {
	begin:
		printf("%s", greet);
		fgets(input, 79, stdin);
		if (sscanf(input, pattern, containr) != 1)
			goto begin;
	}while (!ok(pattern, containr));	
}

/* helper function for get_input*/
int greater_than_0(char *pattern, void *data)
{
	if (strcmp(pattern, "%ld") == 0){
		if (*(long *)data >= 0)
			return 1;
		else
			return 0;
	}
	if (strcmp(pattern, "%d") == 0){
		if (*(int *)data >= 0)
			return 1;
		else
			return 0;
	}
	return 0;
}

int range0_4(char *pattern, void *data)
{
	if (strcmp(pattern, "%d") == 0){
		if (*(int *)data >= 0 && *(int *)data <= 4)
			return 1;
		else
			return 0;
	}
	return 0;
}

int yesno(char *pattern, void *data)
{
	char c = *(char *)data;
	if (strcmp(pattern, "%c") == 0){
		if (c == 'y' || c =='Y'|| c == 'n' || c == 'N')
			return 1;
		else
			return 0;
	}
	return 0;
}
