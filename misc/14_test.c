#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "14_test.h"

typedef struct student *link;
struct list {
	struct list *next;
};
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

extern link lstud;

void test(void)
{
	struct student *s;
	s = list_entry(lstud->, struct student, 
	printf("%d", lstud->next_id);

	/* i need container_of */
}

		
