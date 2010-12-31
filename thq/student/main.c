#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node *link;
struct node {
	long id;
	char *name;
	float engl, comp, math;
	float aver;
	link next;
};
link head;
/* menu */
void menu_main(void);
void menu_sort(void);
void menu_require(void);
void menu_add(void);
void menu_modify(void);
void menu_delete(void);
void menu_load(void);
void menu_save(void);
int get_choice(const char * str, int mode);
float get_score(const char * str);
long get_id(const char * str);

/* data */
link list_init(link head);
link add(long id, char * name, float engl,
	 float comp, float math, link head);
void delete(link pos);
void require_all(link head);
void require(link pos);
link find(long id, link head);
link modify(long id, char * name, float engl,
	    float comp, float math, link pos);
void load(link head);
void save(link head);
link last(link head);
void isort_num(link head);
void isort_name(link head);
void isort_aver(link head);



int main(void)
{
	head = list_init(NULL);
	while (!0){
		(void)system("clear");
		menu_main();
	}
	return 0;
}


/* 对全局的HEAD，有必要吗？*/
link list_init(link head)
{
	head = malloc(sizeof(struct node));
	if (head == NULL){
		perror("Malloc");
		exit(EXIT_FAILURE);
	}
	head->id = -1;
	head->next = NULL;
	return head;
}

/* menu.c & menu.h*/

void menu_main(void)
{
	int choice = 0;
	(void)system("clear");
	printf("********** Welcome to the Student Score MIS *****\n");
	printf("********** Main Menu ***********\n");
	printf("* 1. Add      2. Require \n");
	printf("* 3. Delete   4. Modify \n");
	printf("* 5. Sort     6. Save \n");
	printf("* 7. Load     8. Exit \n");
	/* 避免意外输入字符进入无限循环, 独立出一个函数get_choice*/
	while (choice < 1 || choice > 8){
		choice = get_choice("Please choice (1 ~ 8): ", 1);
	}

	(void)system("clear");
	
	switch (choice){
	case 1: menu_add();
		break;
	case 2: menu_require();
		break;
	case 3: menu_delete();
		break;
	case 4: menu_modify();
		break;
	case 5: menu_sort();
		break;
	case 6: menu_save();
		break;
	case 7: menu_load();
		break;
	case 8: exit(EXIT_SUCCESS);
	}
	return;
}

void menu_add(void)
{
	long id = -1;
	char name_str[80], *name;
	float engl = -1, comp = -1, math = -1;
	link pos;
	int choice = -1;
	int c;
	
	id = get_id("Enter student's ID: ");

	printf("Enter student's Name: ");
	scanf("%s", name_str);

	//清空缓冲区！
	while((c = getchar()) != '\n' && c != EOF);
	//fgets(name, 80, stdin);

	engl = get_score("Enter English Score: ");
	math = get_score("Enter Math Score: ");
	comp = get_score("Enter Computer: ");

	// name_str[strlen(name_str) - 1] = '\0';

	name = malloc(sizeof(char) * (strlen(name_str) + 1));
	strcpy(name, name_str);
		
	if ((pos = find(id, head)) != NULL){
		/* 显示原来的记录 */
		printf("The same student exist:\n");
		require(pos);
		while (choice != 'y' && choice != 'n'){
			choice = get_choice("Modify? (y/n) :", 0);
		}
		switch(choice){
		case 'y': modify(id, name, engl, comp,
				 math, pos);
			/* menu_modify先保存/显示初值 */
			printf("Modified\n");
			break;
		case 'n': printf("xzxczxc\n");
			break;
		}
	}
	else {
		add(id, name, engl, comp, math, head);
	}
	// getchar();
	// 停下来，要在main_menu的最后清空缓冲区
}

link
add(long id, char* name, float engl,
    float comp, float math, link head)
{

	/* 如果用整个结构体作为参数 */
	/* 注意参数顺序， 和结构体的里定义顺序一样 */
	
	link new = malloc(sizeof(struct node));
	
	new->id = id;
	new->name = name;
	new->engl = engl;
	new->comp = comp;
	new->math = math;
	new->aver = (engl + comp + math) * 0.33;

	new->next = head->next;
	head->next = new;
	return new;
}

link
modify(long id, char * name, float engl,
       float comp, float math,link pos)
{
	free(pos->name);
	pos->name = name;
	pos->id = id;
	pos->engl = engl;
	pos->comp = comp;
	pos->math = math;
	pos->aver = (engl + comp + math) * 0.33;
	return pos;
}

link find(long id, link head)
{
	link l = head;
	if (l == NULL)
		return NULL;
	while(l != NULL && l->id != id){
		/* 判断顺序很重要 */
		l = l->next;
	}
	return l;
}

void require(link pos)
{
	if (pos == NULL)
		return;
	printf("ID NAME ENG COM MAT\n");
	printf("%ld %s %.2f  %.2f  %.2f  %.2f \n",
	       pos->id, pos->name, pos->engl, pos->comp, pos->math, pos->aver);
}
void require_all(link head)
{
	link pos = head;
	if (pos == NULL)
		return;
	pos = pos->next;
	/*  对齐！ */
	printf("**************************************************************\n");
	printf("* ID        NAME      ENGLISH    COMPUTER    MATH     AVERAGE* \n");
	while(pos != NULL){
		printf("*%-13ld %-15s %4.1f  %4.1f  %4.1f  %4.1f *\n",
		       pos->id, pos->name, pos->engl, pos->comp, pos->math, pos->aver);
		pos = pos->next;
	}
	printf("**************************************************************\n");
}

void menu_require(void)
{
	int choice = -1;
	long id = -1;
	link tmp;
	while (1){
		choice = -1;
		printf("*********************Require Records *************************\n");
		printf("*          2.1  Require Certain Record by Num                *\n");
		printf("*          2.2  Require All the Records                      *\n");
		printf("*          2.3  Back to MainMenu                             *\n");
		printf("**************************************************************\n");
		while (!(choice >= 1 && choice <= 3))
			choice = get_choice("Please select (0 ~ 3): ", 1);
		switch (choice){
		case 1:
			id = get_id("Please Enter Student's ID: ");
			if ((tmp = find(id, head))){
				require(tmp);
				get_choice("Press any key to continue ", 2);
			}
			else {
				get_choice("No such student", 2);
			}
			system("clear");
			break;
		case 2:
			require_all(head);
			get_choice("Press any key to continue ", 2);
			system("clear");
			break;
		case 3:
			return;
		}
	}
}

void menu_delete(void)
{
	
}

void menu_modify(void)
{
	
}

void menu_sort(void)
{
	int choice = -1;

	while (1){
		choice = -1;
		printf("*********************  Sort Records **************************\n");
		printf("*          5.1  Sort Records by Num                          *\n");
		printf("*          5.2  Sort Records by name                         *\n");
		printf("*          5.3  Sort Records by Average Score                *\n");
		printf("*          5.4  Back to MainMenu                             *\n");
		printf("**************************************************************\n");
		while (!(choice > 0 && choice < 5))
			choice = get_choice("Please select (0 ~ 3): ", 1);
		switch (choice){
		case 1:
			get_choice("Sorted ", 2);
			system("clear");
			break;
		case 2:
			get_choice("Sorted ", 2);
			system("clear");
			break;
		case 3:
			get_choice("Sorted ", 2);
			system("clear");
			
		case 4:
			return;
		}
	}
}

void menu_save(void)
{
	
}

void menu_load(void)
{
	
}

/* TODO: 把scanf换成fgets+sscanf */
int get_choice(const char * str, int mode)
{
	// mode : 0 -> char; 1->int; 2->anything
	// const 的用法 
	int choice = 0, c;
	char tmp[2];
	printf("%s", str);
	if (mode == 0){
		choice = getchar();
		while((c = getchar()) != '\n' && c != EOF);
	}
	else if (mode == 1){
		scanf("%d", &choice);
		while((c = getchar()) != '\n' && c != EOF);
	}
	else {
		fgets(tmp, 1, stdin);
		while((c = getchar()) != '\n' && c != EOF);
	}
	return choice;
}


float get_score(const char * str)
{
	// const 的用法 
	float score = -1;
	int c;
	while (score < 0){
		printf("%s", str);
		scanf("%f", &score);
		while((c = getchar()) != '\n' && c != EOF);
	}
	return score;
}

long get_id(const char * str)
{
	// const 的用法 
 	long id = -1;
	int c;
	while (id < 0){
		printf("%s", str);
		scanf("%ld", &id);
		while((c = getchar()) != '\n' && c != EOF);
	}
	return id;
}

/* 可以改用stdlib的qsort?*/
void isort_num(link head)
{
	link tail = head, iter, min, tmp, pre;
	/* get last node */
	while (tail->next != NULL){
		tail = tail->next;
	}
	
}
