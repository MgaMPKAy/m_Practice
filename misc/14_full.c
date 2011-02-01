#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define list_entry(ptr, type, member)					\
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define list_for_each(pos, head)				\
	for (pos = (head)->next; pos != NULL; pos = pos->next)

struct list {
	struct list *next;
};
typedef struct student *link;
struct student{
        long id;
	char name[20];
	int engl;
	int math;
	int comp;
	int total;
	link next;
	struct list list_id;
	struct list list_name;
	struct list list_total;
};
static int init(void);
static void menu_add(void);
static void menu_find(void);
static void menu_list(struct list *head);

static link find_student(long id);
static void add_student(long, int, int, int);
static void lsort_id(void);
static void lsort_total(void);

static void get_input(char *, void *,int func(char*, void*), char *);
/* helper func for get_input */
static int greater_than_0(char*, void*);
static int range0_6(char*, void*);
static int yesno(char*, void*);

static void load(void);
static void save(void);
static int is_sort_id, is_sort_total;
FILE *fd;

void test(void)
{
	load();
	get_input(NULL, NULL, NULL, "No data now");
}

static struct list *head_id, *head_name, *head_total;

int main(void)
{
	int choice = -1;
	
	(void)init();
	
	while(!0){
		(void)system("clear");
		printf("-------------------Welcome----------------------\n");
		printf("- 1.Add                                        -\n");
		printf("- 2.Find                                       -\n");
		printf("- 3.Stat                                       -\n");
		printf("- 4.Sort (total score)                         -\n");
		printf("- 5. Load      6. Save                         -\n");
		printf("- 0.Exit                                       -\n");
		printf("------------------------------------------------\n");
		get_input("%d", &choice, range0_6, "Please select (0 ~ 6): ");
		
		switch (choice){
		case 1: menu_add(); break;
		case 2: menu_find(); break;
		case 3:
			if (!is_sort_id) {
				lsort_id();
				is_sort_id = 1;
			}
			menu_list(head_id);
			break;
		case 4:
			if (!is_sort_total) {
				lsort_total();
				is_sort_total = 1;
			}
			menu_list(head_total);
			break;
		case 5: load();break;
		case 6: save();break;
		case 0: exit(EXIT_SUCCESS);
		}
	}
	return 0;
}
	
static int init(void)
{
	head_id = malloc(sizeof(*head_id));
	head_name = malloc(sizeof(*head_name));
	head_total = malloc(sizeof(head_total));
	if (!head_id || !head_name || !head_total)
		exit(EXIT_FAILURE);
	memset(head_id, 0, sizeof(*head_id));
	memset(head_name, 0, sizeof(*head_name));
	memset(head_total, 0, sizeof(*head_total));
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
			is_sort_id = is_sort_total = 0;
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
		else {
			printf("!!!Error: can't find this student\n");
		}
		get_input("%c", (void*)&choice, yesno,
			  "Find another student? (y / n)");
		if (choice == 'n' || choice == 'N')
			return;
	}
}

void menu_list(struct list *head)
{
	struct student *stud;
	struct list *list;
	if (head_id->next == NULL){
		get_input(NULL, NULL, NULL, "No data now");
		return;
	}
	printf("------------------------------------------------\n");
	printf("  Student     English   Math    Comp.   Total\n");
	
	list_for_each(list, head){
		if (head == head_id) {
			stud = list_entry(list, struct student, list_id);
		} else if (head == head_total) {
			stud = list_entry(list, struct student, list_total);
		}
		printf("\t%ld\t%4d\t%4d\t%4d\t%4d\n", stud->id, stud->engl,
		       stud->math,  stud->comp, stud->total);
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
	nstud->comp = comp;
	nstud->total = engl + math + comp;
	
	if (head_id->next == NULL){
		head_id->next = &(nstud->list_id);
		nstud->list_id.next = NULL;
		head_total->next = &(nstud->list_total);
		nstud->list_total.next = NULL;
	}
	else {
		nstud->list_id.next = head_id->next;
		head_id->next = &(nstud->list_id);
		nstud->list_total.next = head_total->next;
		head_total->next = &(nstud->list_total);
	}
}

link find_student(long id)
{
	struct list *iter;
	struct student *stud;
	list_for_each(iter, head_id){
		stud = list_entry(iter, struct student, list_id);
		if (stud->id == id)
			return stud;
	}
	return NULL;
}

void lsort_total(void)
{
	/* ugly bubble sort */
	struct list *i, *jp, *j, *jn;
	static int c = 0;
	for (i = head_total; i!= NULL; i = i->next) {
		for (jp = head_total; jp != NULL
			     && (j = jp->next) != NULL
			     && (jn = j->next) != NULL; jp = jp->next) {
			if ((list_entry(j, struct student, list_total)->total)
			    < (list_entry(jn, struct student, list_total)->total)) {
				j->next = jn->next;
				jn->next = j;
				jp->next = jn;
			}
		}
	}
	if ((c = !c))
		lsort_total();
}

void lsort_id(void)
{
	/* ugly bubble sort */
	struct list *i, *jp, *j, *jn;
	static int c = 0;
	for (i = head_id; i != NULL; i = i->next) {
		for (jp = head_id; jp != NULL && (j = jp->next) != NULL
			     && (jn = j->next) != NULL; jp = jp->next) {
			if ((list_entry(j, struct student, list_id)->id)
			    > (list_entry(jn, struct student, list_id)->id)) {
				j->next = jn->next;
				jn->next = j;
				jp->next = jn;
			}
		}
	}
	if ((c = !c))
		lsort_id();
}

static void load(void)
{
	int score[3];
	long id;
	char input[80];
	fd = fopen("./data", "r");
	if (fd == NULL) {
		exit(EXIT_FAILURE);
	}
	if (fd == NULL)
		exit(1);
	while (fgets(input, 80, fd) != 0) {
		sscanf(input, "%ld %d %d %d",&id, score , score + 1, score + 2);
		add_student(id, score[0],score[1], score[2]);
	}
	fclose(fd);
}

static void save(void)
{
	struct list *iter;
	struct student *stud;
	char output[80];
	fd = fopen("./data", "w");
	if (fd == NULL) {
		exit(EXIT_FAILURE);
	}
	list_for_each(iter, head_id) {
		stud = list_entry(iter, struct student, list_id);
		sprintf(output, "%ld %d %d %d\n",
			 stud->id, stud->engl, stud->math, stud->comp);
		fputs(output, fd);
	}
	fclose(fd);
}

/* universal input & check */
void get_input(char *pattern, void *containr, int ok(char*, void*), char *greet)
{
	char input[80];
	if (!pattern || !containr || !ok) {
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
	if (strcmp(pattern, "%ld") == 0) {
		if (*(long *)data >= 0)
			return 1;
		else
			return 0;
	}
	if (strcmp(pattern, "%d") == 0) {
		if (*(int *)data >= 0)
			return 1;
		else
			return 0;
	}
	return 0;
}

int range0_6(char *pattern, void *data)
{
	if (strcmp(pattern, "%d") == 0) {
		if (*(int *)data >= 0 && *(int *)data <= 6)
			return 1;
		else
			return 0;
	}
	return 0;
}

int yesno(char *pattern, void *data)
{
	char c = *(char *)data;
	if (strcmp(pattern, "%c") == 0) {
		if (c == 'y' || c =='Y'|| c == 'n' || c == 'N')
			return 1;
		else
			return 0;
	}
	return 0;
}
