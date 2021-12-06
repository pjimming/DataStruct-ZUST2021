/*
	author: 潘江明
*/

#include <stdio.h>
#include <malloc.h>
#include <process.h>

typedef int ElemType;
typedef int Boolean;

#define TRUE 1
#define OVERFLOW -2
#define list_init_size 20

typedef struct {
	ElemType* elem;
	int length;
	int listsize;
} Sqlist;

Boolean InitList(Sqlist& L) {
	ElemType* q;

	L.elem = (ElemType*)malloc(list_init_size * sizeof(ElemType));
	if (!L.elem)
		exit(OVERFLOW);
	q = L.elem;
	L.length = 0;
	L.listsize = list_init_size;

	for (int i = 0; i < 10; i++) {
		*q = i / 2;
		L.length++;
		q++;
	}

	return TRUE;
}

Boolean DisplayList(Sqlist L) {
	for (int j = 0; j < L.length; j++)
		printf("%d ", *(L.elem + j));
	printf("\n");

	return TRUE;
}

Boolean Delete_Repetition(Sqlist& L) {
	int i = 0;

	while (i < L.length - 1) {
		if (*(L.elem + i) == *(L.elem + i + 1)) {
			for (int j = i + 1; j < L.length - 1; j++)
				*(L.elem + j) = *(L.elem + j + 1);
			L.length--;
		}
		else {
			i++;
		}
	}

	return TRUE;
}

int main() {
	Sqlist L;
	InitList(L);
	printf("原来的线性表：\n");
	DisplayList(L);

	Delete_Repetition(L);

	printf("现在的线性表：\n");
	DisplayList(L);

	free(L.elem);

	return 0;
}