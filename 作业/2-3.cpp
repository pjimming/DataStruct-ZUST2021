/*
	author: 潘江明
*/
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <process.h>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1

typedef int Status;
typedef int ElemType;
typedef struct LNode {
	ElemType data;
	struct LNode* next;
}LNode, * LinkList;

Status InitList(LinkList& L) {
	LinkList p, s;

	L = (LinkList)malloc(sizeof(struct LNode));
	if (!L)
		exit(OVERFLOW);
	L->next = NULL;

	p = L;
	for (int i = 0; i < 10; i++) {
		s = (LinkList)malloc(sizeof(struct LNode));
		s->data = i * 3;
		s->next = NULL;
		p->next = s;
		p = p->next;
	}

	return OK;
}

Status DisPlayList(LinkList L) {
	while (L->next) {
		L = L->next;
		printf("%d ", L->data);
	}
	puts("");

	return OK;
}

Status InsertElem(LinkList& L, ElemType x) {
	LinkList p = L, s;

	while (p->next && p->next->data < x) {
		p = p->next;
	}

	s = (LinkList)malloc(sizeof(struct LNode));
	s->data = x;
	s->next = p->next;
	p->next = s;

	return OK;
}

int main() {
	LinkList L;

	InitList(L);
	printf("原来的顺序表是：\n");
	DisPlayList(L);

	InsertElem(L, -1);
	printf("插入-1后：\n");
	DisPlayList(L);

	InsertElem(L, 8);
	printf("插入8后：\n");
	DisPlayList(L);

	InsertElem(L, 30);
	printf("插入30后：\n");
	DisPlayList(L);

	return 0;
}