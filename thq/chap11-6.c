#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct date {
	int year, month, day;
};

struct student{
	char name[20];
	char sex;
	struct date birth;
	struct student *next;
};

int compare(struct date x, struct date y)
{
	if (x.year == y.year) {
		if (x.month == y.month) {
			return x.day < y.day;
		} else {
			return x.month < y.month;
		}
	} else {
		return x.year < y.year;
	}
}

struct student * findOldest(struct student *head)
{
	struct student *old;
	if (head->next == NULL)
		return head;

	old = findOldest(head->next);
	if (compare(head->birth, old->birth))
		return head;
	else
		return old;
}
int main(void)
{
	int i, c;
	struct student *tmp;
	struct student *head = malloc(sizeof(*head));	
	bzero(head, sizeof(*head));
	head->next = NULL;
	
	for (i = 0; i < 4; i++) {
		tmp = malloc(sizeof(*tmp));
		printf("Name: ");
		scanf("%s", tmp->name);
		printf("Sex: ");
		while((c = getchar()) != '\n' && c != EOF);
		scanf("%c", &(tmp->sex));
		printf("Year: ");
		scanf("%d",&(tmp->birth.year));
		printf("Month: ");
		scanf("%d", &(tmp->birth.month));
		printf("Day: ");
		scanf("%d", &(tmp->birth.day));
		printf("-----------------\n");
		tmp->next = head->next;
		head->next = tmp;
	}

	tmp = findOldest(head->next);
	
	printf("%s\n", tmp->name);
	return 0;
}		
