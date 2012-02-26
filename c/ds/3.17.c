Status match(char *str)
{
	Stack *s;
	int i = 0;
	SElemType c, d;
	InitStack(s);

	for (i = 0; (c = str[i]) && c != '&' && c != '@'; i++) {
		Push(s, c);
	}

	if (c != '&') return FALSE;

	for (i++; (c = str[i]) && c != '@'; i++) {
		Pop(s, &d);
		if (d != c) return FALSE;
	}
	if (!StackEmpty(s)) {
		return FALSE;
	} else {
		return TRUE;
	}
}

typedef char SElemType;
Status InitStack(Stack &s);
Status Push(Stack &s, SElemType e);
Status Pop(Stack &s, SElemType &e);
Status StackEmpty(Stack s);
Status GetTop(Stack s, SElemType &e);
