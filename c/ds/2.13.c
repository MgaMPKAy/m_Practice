#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct {
	ElemType *elem;
	int       length;
	int       listsize;
} SqList;

ElemType *Locate(SqList *L, ElemType x)
{
	int len = L->length;
	ElemType *elems = L->elem;
	int i = 0;
	for (i = 0; i < len; i++) {
		if (elems[i] == x) {
			return elems + i;
		}
	}
	return NULL;
}
