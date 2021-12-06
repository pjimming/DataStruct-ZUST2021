/*
	二叉树如图：
					1
				 /     \
				2	    5
			  /   \    /
			 3     4  6
			  \
			   7
	输入顺序（前序）：
		1 2 3 0 7 0 0 4 0 0 5 6 0 0 0
*/

/*
	author: 潘江明
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define Link 0
#define Thread 1

typedef int Status;
typedef int TElemType;
typedef struct BitNode {
	TElemType data;
	TElemType ltag, rtag;
	struct BitNode* lchild, * rchild;
}BitNode, * BitTree;

BitTree pre = NULL;

Status InitTree(BitTree* T) {
	*T = NULL;
	return OK;
}

// 前序生成二叉树
Status CreateTree(BitTree* T) {
	TElemType data;
	scanf_s("%d", &data);

	if (data == 0) {
		*T = NULL;
	}
	else {
		(*T) = (BitTree)malloc(sizeof(BitNode));
		if (!(*T)) {
			printf("申请内存失败\n");
			exit(OVERFLOW);
		}
		(*T)->data = data;
		(*T)->ltag = (*T)->rtag = Link;
		CreateTree(&(*T)->lchild);
		CreateTree(&(*T)->rchild);
	}

	return OK;
}

// 前序线索化二叉树
Status FThreadTree(BitTree p) {
	if (p) {
		if (pre && !pre->lchild) {
			pre->rtag = Thread;
			pre->rchild = p;
		}

		pre = p;
		FThreadTree(p->lchild);

		pre = p;
		FThreadTree(p->rchild);
	}

	return OK;
}

// 前序搜索二叉树的后继结点
Status FSearchTree(BitTree p) {
	if ((p)) {
		if ((p)->lchild) {
			printf("%d的后继结点是%d\n", (p)->data, (p)->lchild->data);
		}
		else if (p->rtag == Thread) {
			printf("%d的后继结点是%d\n", p->data, p->rchild->data);
		}
		else {
			printf("%d没有后继结点\n", p->data);
		}
		FSearchTree(p->lchild);
		FSearchTree(p->rchild);
	}

	return OK;
}

int main() {
	BitTree T;
	InitTree(&T);

	printf("前序输入二叉树\n");
	CreateTree(&T);

	FThreadTree(T);

	printf("前序搜索出二叉树结点的后继结点如下：\n");
	FSearchTree(T);

	return 0;
}