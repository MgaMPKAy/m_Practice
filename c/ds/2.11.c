#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct {
	ElemType *elem;
	int       length;
	int       listsize;
} SqList;

void InsertOrderList(SqList *L, ElemType x)
{
	int i, m;
	ElemType *elems = L->elem;

	if (L->listsize == L->length) {
		return;
	}

	for (m = 0; m < L->length; m++) {
		if (x < elems[m])
			break;
	}
	for (i = L->listsize; i > m; i--) {
		elems[i] = elems[i - 1];
	}
	elems[m] = x;
	L->length++;
}


int main(int argc, char *argv[])
{
	int length = 7;

	int elem[10] = {-1, -2, 1, 2, 5, 6, 7};

	SqList list = {elem, length, 10};
	InsertOrderList(&list, 0);
	int i;
	for (i = 0; i < 10; i++) {
		printf("%d\n", elem[i]);
	}
	return 0;
}
