/*
	author: 潘江明
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

#define STACK_INIT_SIZE 10
#define STACKINCREMENT 2
typedef struct SqStack {
	ElemType* base;
	ElemType* top;
	int stacksize;
} SqStack;

Status InitStack(SqStack& S) {
	S.base = (ElemType*)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	if (!S.base) exit(OVERFLOW);

	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;

	return OK;
}

Status StackEmpty(SqStack S) {
	if (S.top == S.base)
		return true;
	else
		return false;
}

Status Push(SqStack& S, ElemType e) {
	if (S.top - S.base > STACK_INIT_SIZE) {
		S.base = (ElemType*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(ElemType));
		if (!S.base) exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*(S.top)++ = e;

	return OK;
}

Status Pop(SqStack& S, ElemType& e) {
	if (S.base == S.top) return ERROR;
	e = *--S.top;
	
	return OK;
}

Status Conversion(ElemType num) {
	ElemType e;
	SqStack S;
	InitStack(S);

	while (num) {
		Push(S, num % 2);
		num /= 2;
	}

	while (!StackEmpty(S)) {
		Pop(S, e);
		printf("%d", e);
	}
	puts("");

	return OK;
}

int main() {
	Conversion(17);

	return 0;
}