/*
	@author: 潘江明
	Copyright © 2021  潘江明
*/

#include <stdio.h>
#include <stdlib.h>

#define  INFINITY 100000	   //最大值   ∞
#define  MAX_VERTEX_NUM 20     //最大顶点个数
typedef struct {
	char vexs[MAX_VERTEX_NUM];  		        //顶点向量
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];	//邻接矩阵
	int vexnum, arcnum;					        //图的当前顶点和弧数
} MGraph;

typedef struct {
	int adjvex;
	int	endvex;
	int lowcost;
} closedge[MAX_VERTEX_NUM];

void CreateUDN(MGraph &G);		  //创建无向网络
int LocateVex(MGraph G, char v);	      //结点的在顶点向量中的下标
void PrintUDN(MGraph G);			  //输出存储结构示意图
void MiniSpanTree_PRIM(MGraph G, closedge &minedge); //求最小生成树的算法
void PrintMinEdge(MGraph G, closedge minedge);       //输出最小生成树的边

int main() {
	MGraph G;//定义一个图的变量
	closedge minedge;

	CreateUDN(G);
	printf("该图的邻接矩阵存储示意图如下：\n");
	PrintUDN(G);
	printf("\n");

	MiniSpanTree_PRIM(G, minedge);
	printf("该图生成树的边如下：\n");
	PrintMinEdge(G, minedge);
	printf("\n");

	return 0;
}

void CreateUDN(MGraph &G) {
	//补充代码
	scanf("%d%d", &G.vexnum, &G.arcnum);
	scanf("%s", G.vexs);

	for (int i = 0; i < G.vexnum; i++)
		for (int j = 0; j < G.vexnum; j++) {
			if (i != j)
				G.arcs[i][j] = INFINITY;
			else
				G.arcs[i][j] = 0;
		}

	getchar();
	for (int i = 0; i < G.arcnum; i++) {
		char a, b;
		int edge;
		scanf("%c%c %d", &a, &b, &edge);
		getchar();
		int A = LocateVex(G, a), B = LocateVex(G, b);
		G.arcs[A][B] = G.arcs[B][A] = edge;
	}
} //End_CreateUDN
int LocateVex(MGraph G, char v) {
	//补充代码
	for (int i = 0; i < G.vexnum; i++) {
		if (G.vexs[i] == v)
			return i;
	}
}

void PrintUDN(MGraph G) {
	//补充代码
	printf("    ");
	for (int i = 0; i < G.vexnum; i++)
		printf("%-4c", G.vexs[i]);
	puts("");
	for (int i = 0; i < G.vexnum; i++) {
		printf("%-4c", G.vexs[i]);
		for (int j = 0; j < G.vexnum; j++) {
			if (G.arcs[i][j] == INFINITY)
				printf("∞  ");
			else
				printf("%-4d", G.arcs[i][j]);
		}
		puts("");
	}
}

void MiniSpanTree_PRIM(MGraph G, closedge &minedge) {
	int i, j, k, z;
	int temp;
	int currentmin;
	k = 0;

	for (j = 1; j < G.vexnum; ++j) {   // 辅助数组初始化
		minedge[j - 1].adjvex = k;
		minedge[j - 1].endvex = j;
		minedge[j - 1].lowcost = G.arcs[k][j];
	}
	for (i = 0; i < G.vexnum - 1; ++i) {
		currentmin = minedge[i].lowcost;
		k = i;
		for (j = i + 1; j < G.vexnum - 1; j++) { //选择最小的边
			if (minedge[j].lowcost < currentmin) {
				currentmin = minedge[j].lowcost;
				k = j;
			}
		}
		//第k个元素与第i个进行交换
		temp = minedge[i].adjvex;
		minedge[i].adjvex = minedge[k].adjvex;
		minedge[k].adjvex = temp;
		temp = minedge[i].endvex;
		minedge[i].endvex = minedge[k].endvex;
		minedge[k].endvex = temp;
		temp = minedge[i].lowcost;
		minedge[i].lowcost = minedge[k].lowcost;
		minedge[k].lowcost = temp;

		for (j = i + 1; j < G.vexnum - 1; ++j) {
			z = minedge[i].endvex; //z为找到的新顶点
			k = minedge[j].endvex;
			if (k != z) {
				if (G.arcs[z][k] < minedge[j].lowcost) {
					minedge[j].adjvex = z;
					minedge[j].lowcost = G.arcs[z][k];
				}
			}
		}
	}
} // MiniSpanTree

void PrintMinEdge(MGraph G, closedge minedge) {
	//补充代码
	for (int i = 0; i < G.vexnum - 1; i++) {
		printf("%c%c %d\n", G.vexs[minedge[i].adjvex], G.vexs[minedge[i].endvex], minedge[i].lowcost);
	}
}

/*
5  8
ABCDE
AB  8
AC  4
AE  3
BD  8
BE  6
CD  10
CE  13
DE  12
*/