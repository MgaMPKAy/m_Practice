#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct {
	ElemType *elem;
	int       length;
	int       listsize;
} SqList;

char Compare(SqList A, SqList B)
{
	int lenA = A.length;
	int lenB = B.length;
	int i;

	if (lenA < lenB) {
		return '<';
	} else if (lenA > lenB) {
		return '>';
	} else {
		for (i = 0; i < lenA; i++) {
			if (A.elem[i] == B.elem[i]) {
				continue;
			} else if (A.elem[i] < B.elem[i]) {
				return '<';
			} else {
				return '>';
			}
		}
	}
	return '=';
}
