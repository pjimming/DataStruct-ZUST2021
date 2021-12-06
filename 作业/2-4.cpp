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
	if (!L) exit(OVERFLOW);
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

Status ReverseList(LinkList& L) {
	LinkList p0, p1, p2;

	p0 = NULL;
	p1 = NULL;
	p2 = L->next;
	L->next = NULL;
	while (p2) {
		p0 = p2->next;
		p2->next = p1;
		p1 = p2;
		p2 = p0;
	}
	L->next = p1;

	return OK;
}

int main() {
	LinkList L;

	InitList(L);
	printf("现在的动态单链表是\n");
	DisPlayList(L);

	ReverseList(L);
	printf("逆置后的动态单链表\n");
	DisPlayList(L);

	return 0;
}