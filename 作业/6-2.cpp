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
	struct BitNode *lchild, * rchild;
} BitNode, * BitTree;

BitTree pre = NULL;

Status InitTree(BitTree *T) {
	*T = NULL;
	return OK;
}

// 前序生成二叉树
Status CreateTree(BitTree *T) {
	TElemType data;
	scanf("%d", &data);

	if (data == 0) {
		*T = NULL;
	} else {
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

// 前序递归线索化二叉树
Status FThreadTree(BitTree p) {
	if (p) {
		// 设置p的前驱结点
		if (!p->lchild) {
			p->ltag = Thread;
			p->lchild = pre;
		}

		// 设置pre的后继结点
		if (pre && !pre->rchild) {
			pre->rtag = Thread;
			pre->rchild = p;
		}

		pre = p;
		if (p->ltag == Link)
			FThreadTree(p->lchild);
		if (p->rtag == Link)
			FThreadTree(p->rchild);
	}

	return OK;
}

Status PreOrder(BitTree p) {
	while (p) {
		while (p->ltag == Link) {
			printf("%d ", p->data);
			p = p->lchild;
		}
		printf("%d ", p->data);
		p = p->rchild;
	}
	puts("");

	return OK;
}

// 前序搜索二叉树的前驱结点(递归)
Status FSearchTree_front(BitTree p) {
	if (p) {
		if (p->ltag == Thread) {
			printf("%d的前驱结点是%d\n", p->data, p->lchild->data);
		} else if (pre) {
			printf("%d的前驱结点是%d\n", p->data, pre->data);
		} else {
			printf("%d没有前驱结点\n", p->data);
		}
		pre = p;
		if (p->ltag == Link)
			FSearchTree_front(p->lchild);
		if (p->rtag == Link)
			FSearchTree_front(p->rchild);
	}

	return OK;
}

// 前序搜索二叉树的后继结点(递归)
Status FSearchTree_back(BitTree p) {
	if ((p)) {
		if (p->lchild && p->ltag == Link) {
			printf("%d的后继结点是%d\n", (p)->data, (p)->lchild->data);
		} else if (p->rchild) {
			printf("%d的后继结点是%d\n", p->data, p->rchild->data);
		} else {
			printf("%d没有后继结点\n", p->data);
		}
		if (p->ltag == Link)
			FSearchTree_back(p->lchild);
		if (p->rtag == Link)
			FSearchTree_back(p->rchild);
	}

	return OK;
}


int main() {
	BitTree T;
	InitTree(&T);

	printf("前序输入二叉树\n");
	CreateTree(&T);

	FThreadTree(T);

	printf("线索遍历得出前序序列如下：\n");
	PreOrder(T);

	printf("前序搜索出二叉树结点的后继结点如下：\n");
	FSearchTree_back(T);

	pre = NULL;
	printf("\n前序搜索出二叉树结点的前驱结点如下：\n");
	FSearchTree_front(T);

	return 0;
}
