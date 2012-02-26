#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct LNode{
    ElemType      data;
    struct LNode *next;
} LNode, *LinkList;

int Length(LinkList L)
{
	if (L->next == NULL) {
		return 0;
	} else {
		return 1 + Length(L->next);
	}
}

int main(int argc, char *argv[])
{
	LNode n1 = {2, NULL};
	LNode head = {1, &n1};
	printf("%d\n", Length(&head));
	return 0;
}
