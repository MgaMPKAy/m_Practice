#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct {
	ElemType *elem;
	int       length;
	int       listsize;
} SqList;

void Inverse(SqList *L)
{
	ElemType *elems = L->elem;
	int len = L->length;
	int mid = len / 2;
	int tmp, i;
	for (i = 0; i < mid; i++) {
		tmp = elems[i];
		elems[i] = elems[len - i - 1];
		elems[len - i - 1] = tmp;
	}
}

int main(int argc, char *argv[])
{
	int elems[1] = {0};

	int len = 0;
	int mid = len / 2;
	int tmp, i;

	for (i = 0; i < mid; i++) {
		tmp = elems[i];
		elems[i] = elems[len - i - 1];
		elems[len - i - 1] = tmp;
	}

	for (i = 0; i < len; i++) {
		printf("%d\n", elems[i]);
	}
	return 0;
}
