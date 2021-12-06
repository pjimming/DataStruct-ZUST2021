/*
	二叉树如图：
					5
				 /     \
				6	    7
			  /   \    /
			 8    -1  8

	输入顺序：
		5 6 8 0 0 -1 0 0 7 8 0 0 0
*/

/*
	author: 潘江明
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1

typedef int TElemType;
typedef int Status;
typedef struct BiTNode {
	TElemType data;
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;

Status InitTree(BiTree* T) {
	*T = NULL;
	return OK;
}

Status CreateTree(BiTree* T) {
	int e;

	scanf_s("%d", &e);

	if (e == 0) {
		*T = NULL;
	}
	else {
		(*T) = (BiTree)malloc(sizeof(BiTNode));
		if (!*T) exit(OVERFLOW);

		(*T)->data = e;
		CreateTree(&(*T)->lchild);
		CreateTree(&(*T)->rchild);
	}
}

TElemType NumTreeNode(BiTree* T) {
	int t = 0;

	if ((*T) == NULL) return t;

	if ((*T)->data > 0)
		t++;
	t += NumTreeNode(&(*T)->lchild) + NumTreeNode(&(*T)->rchild);

	return t;
}

int main() {
	BiTree T;

	InitTree(&T);

	CreateTree(&T);

	printf("结点大于0的数量为：%d\n", NumTreeNode(&T));

	return 0;
}