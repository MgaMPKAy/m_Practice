#include <stdio.h>
#include <string.h>
#define list_entry(ptr, type, member)					\
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))
#define list_for_each(head, temp){}					\
		for (temp = &head; temp != NULL; temp = temp->next){}

#define list_for_each2(pos, head)					\
	for (pos = (head)->next; pos != NULL; pos = pos->next)

struct data {
	int id;
	float sc;
};

struct list_head {
	struct list_head *next;
};
struct student {
	long id;
	int score;
	struct student * next_id;
	struct student * next_sc;
	struct list_head lnext_id;
	struct list_head lnext_sc;
};

int main(void)
{
	struct data basic = {12, 34.1};
	struct data test = {56, 78.2};
	
	struct student head, *temp;
	struct list_head *temp2, *temp3;
	struct student s1 = {1, 80, 0, 0};
	struct student s2 = {2, 90, 0, 0};
	struct student s3 = {3, 70, 0, 0};

	memset(&head, 0, sizeof(head));
	head.next_id = &s1;
	s1.next_id = &s2;
	s2.next_id = &s3;
	
	s1.lnext_id.next = &s2.lnext_id;
	s2.lnext_id.next = &s3.lnext_id;
	s3.lnext_id.next = NULL;
	
	head.next_sc = &s2;
	s2.next_sc = &s1;
	s1.next_sc = &s3;

	head.lnext_sc.next = &s2.lnext_sc;
	s2.lnext_sc.next = &s1.lnext_sc;
	s1.lnext_sc.next  = &s3.lnext_sc;
	s3.lnext_sc.next = NULL;
	
	for (temp = head.next_id; temp != NULL; temp = temp->next_id)
		printf("id = %ld, sc = %d\n", temp->id, temp->score);
	for (temp = head.next_sc; temp != NULL; temp = temp->next_sc)
		printf("id = %ld, sc = %d\n", temp->id, temp->score);

	struct student * temp4;
	list_for_each2(temp3, &head.lnext_sc){
		temp4 = list_entry(temp3, struct student, lnext_sc);
		printf("!!id = %ld, sc = %d\n", temp4->id, temp4->score);
	};
	
	for (temp2 = &s1.lnext_id; temp2 != NULL; temp2 = temp2->next) {
		printf("!!!id = %ld, sc = %d\n",
		       list_entry(temp2, struct student, lnext_id)->id,
		       list_entry(temp2, struct student, lnext_id)->score);
	}

			
	
	float *psc = &(test.sc);
	printf("hello, &test.id = %p, &test.sc = %p &test = %p\n",
	       &(test.id), &(test.sc), &test.sc);


	((struct data *)((char *)psc - ((char *)&(basic.sc) - (char *)&basic)))->id = 0;
	printf("hello, test.id = %d\n", test.id);

	((struct data *)((char *)(psc) - (unsigned long)(&((struct data *)0)->sc)))->id = 11;
	printf("hello, test.id = %d\n", test.id);
	
	list_entry(psc, struct data, sc)->id = 22;
	printf("hello, test.id = %d\n", test.id);
	
	return 0;
}
	
