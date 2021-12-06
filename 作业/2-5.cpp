/*
	author: 潘江明
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1

typedef int ElemType;
typedef int Status;
typedef struct LNode {
	ElemType data;
	struct LNode* next;
}LNode, * LinkList;

Status InitList(LinkList& L) {
	L->data = 0;
	L->next = L;

	return OK;
}

Status CreateList(LinkList& L) {
	LinkList node = NULL, r = L;

	r->data = 0;
	for (int i = 1; i < 10; i++) {
		node = (LinkList)malloc(sizeof(LNode));
		node->data = i * 3;
		node->next = r->next;
		r->next = node;
		r = r->next;
	}

	return OK;
}

Status DisPlayList(LinkList L) {
	LinkList p = L;

	while (p->next != L) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("%d \n", p->data);

	return OK;
}

Status DeletePreS(LinkList& L) {
	LinkList p = L, s = p;

	while (p->next != L) {
		s = p;
		p = p->next;
	}
	s->next = L;
	free(p);

	return OK;
}

int main() {
	LinkList L;

	L = (LinkList)malloc(sizeof(struct LNode));

	InitList(L);
	CreateList(L);
	printf("原来的循环链表是：\n");
	DisPlayList(L);

	DeletePreS(L->next->next->next->next);
	printf("删去12的直接前驱结点后：\n");
	DisPlayList(L);

	return 0;
}