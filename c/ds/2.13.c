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
	LNode *iter = L;
    	while(iter) {
        	if (iter->data == x) {
            		return iter;
        	}
        	iter = iter->next;
    	}
	return NULL;
}
