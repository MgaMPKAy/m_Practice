#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

typedef struct student *link;
struct student{
        long id;
	int engl;
	int math;
	int comp;
	int total;
	link next;
};

void menu_main(void);
void menu_add(void);
void menu_find(void);
void menu_list(void);


link find_student(long id);
void add_student(long, int, int, int);
void lsort(void);

void get_input(const char * type, void *,int func(void *, char*), char * greet);
int greater_than_0(void *, char *);
int long_greater_than_0(void *, char*);
int int_greater_than_0(void *, char*);
int range0_4(void *,char*);
int yesno(void *, char *);

link lstud;

int main(void)
{
	while(!0){
		system("clear");
		menu_main();
	}
	return 0;
}

void menu_main(void)
{
	/* init -> init() */
	lstud = malloc(sizeof(struct student));
	lstud->next = NULL;

	int choice = -1;
	while(!0){
		(void)system("clear");
		printf("-------------------Welcome----------------------\n");
		printf("- 1.Add                                        -\n");
		printf("- 2.Find                                       -\n");
		printf("- 3.Stat                                       -\n");
		printf("- 4.Sort (b                                    -\n");
		printf("- 0.Exit                                       -\n");
		printf("------------------------------------------------\n");
		/* */
		
		choice = -1;
		get_input("int", &choice, range0_4,
			  "Please select (0 ~ 4): ");
		
		switch (choice){
		case 1: menu_add(); break;
		case 2: menu_find(); break;
		case 3: menu_list(); break;
		case 4: lsort();menu_list(); break;
		case 0: exit(EXIT_SUCCESS);
		}
	}
	
}

void menu_add(void)
{
	long id;
	int score[3];
	char choice = -1;
	// char *name = malloc(sizeof(char) * 25);
	while (!0){
		printf("------------------------------------------------\n");
		
		get_input("long", &id, greater_than_0,
			  "Enter student's id: ");
		/*get_input("char*", name, NULL,
		  "Enter student's name: "); */
		get_input("int", &score[0], greater_than_0,
			  "Enter English score: ");
		get_input("int", &score[1], greater_than_0,
			  "Enter Math score: ");
		get_input("int", &score[2], greater_than_0,
			  "Enter Computer score: ");
		
		if (!find_student(id)){
			printf("OK\n");
		      	add_student(id, score[0],score[1], score[2]);
		}
		else {
			printf("Error:the same student\n");
		}
		
		
		get_input("char", &choice, yesno,
			  "Add another student? (y / n)");
		if (choice == 'n' || choice == 'N')
			return;
	}
}

void menu_find(void)
{
	long id;
	int choice;
	struct student *stud;
	while(!0){
		printf("------------------------------------------------\n");
		get_input("long", &id, greater_than_0,
			  "Enter student's id: ");
		if ((stud = find_student(id))){
			printf("  Student     English   Math    Comp.   Total\n");
			printf("\t%ld\t%4d\t%4d\t%4d\t%4d\n", stud->id, stud->engl,
			       stud->math,  stud->comp, stud->total);
		}
		else{
			printf("!!!Error: can't find this student\n");
		}
		get_input("char", &choice, yesno,
			  "Find another student? (y / n)");
		if (choice == 'n' || choice == 'N')
			return;
	}
}

void menu_list(void)
{
	link iter = lstud;
       	if (iter->next == NULL){
		get_input("none", NULL, NULL, "No student");
		return;
	}
	printf("------------------------------------------------\n");
	printf("  Student     English   Math    Comp.   Total\n");
	iter = iter->next;
	while(iter != NULL){
		printf("\t%ld\t%4d\t%4d\t%4d\t%4d\n", iter->id, iter->engl,
		       iter->math,  iter->comp, iter->total);
		iter = iter->next;
	}
	get_input("none", NULL, NULL, "Press any key to continue ");
}
void add_student(long id, int engl, int math, int comp)
{
	link nstud = malloc(sizeof(struct student));
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
	link head = lstud;
	if (head == NULL)
		return NULL;
	while(head != NULL && head->id!= id)
		head = head->next;
	return head;
}

void lsort(void)
{
	/* bubble */
	link i ,j, jn, jnn;
	for (i = lstud; i != NULL; i = i->next){
		for (j = i; j!= NULL && (jn = j->next) != NULL
			     && (jnn = j->next->next) != NULL; j = j->next){
			if (jn->total < jnn->total){
				j->next = jnn;
				jn->next = jnn->next;
				jnn->next = jn;
			}
		}
	}
}


void get_input(const char * type, void * data, int func(), char * greet)
{
	// change scanf to fgets + sscanf
	int ire = -1;
	long lre = -1;
	char *input = malloc(sizeof(char) * 80), ch;
	int tmp;
	if (strcmp(type, "int") == 0){
		do {
			printf("%s", greet);
			scanf("%d", &ire);
			while((tmp = getchar()) != (int)'\n' && tmp != EOF);
		} while (!func(&ire, type));
		*(int *)data = ire;
		return;
	}
	if (strcmp(type, "long") == 0){
		do {
			printf("%s", greet);
			scanf("%ld", &lre);
			while((tmp = getchar()) != (int)'\n' && tmp != EOF);
		} while (!func(&lre, type));
		*(long*)data = lre;
		return;
	}
	if (strcmp(type, "char") == 0){
		do {
			printf("%s", greet);
			scanf("%c", &ch);
			while((tmp = getchar()) != (int)'\n' && tmp != EOF);
		} while (!func(&ch, type));
		*(char*)data = ch;
		return;
	}
	if (strcmp(type, "none") == 0){
		printf("%s", greet);
		while((tmp = getchar()) != (int)'\n' && tmp != EOF);
	}
	/* bug 
	if (strcmp(type, "char*") == 0){
		printf("%s", greet);
		fgets(input, 25, stdin);
		*(char *)data = input; //bug
		return;
	}
	*/
	free(input);
}

int greater_than_0(void * data, char * type)
{
	if (strcmp(type, "long") == 0){
		if (*(long *)data > 0)
			return 1;
		else
			return 0;
	}
	if (strcmp(type, "int") == 0){
		if (*(int *)data > 0)
			return 1;
		else
			return 0;
	}
	return 0;
}

int range0_4(void * data, char *type)
{
	if (strcmp(type, "int") == 0){
		if (*(int *)data >= 0 && *(int *)data <= 4)
			return 1;
		else
			return 0;
	}
	return 0;
}

int yesno(void *data, char *type)
{
	char c = *(char *)data;
	if (strcmp(type, "char") == 0){
		if (c == 'y' || c =='Y'
		    || c == 'n' || c == 'N')
			return 1;
		else
			return 0;
	}
	return 0;
}







