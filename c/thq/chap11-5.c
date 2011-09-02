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

int main(void)
{
	int i, c;
	struct student *tmp, *iter;
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

	for (tmp = iter = head->next; iter!= NULL; iter = iter->next) {
		if (compare(iter->birth, tmp->birth))
			tmp = iter;
	}
	printf("%s\n", tmp->name);
	return 0;
}		
