/*
    @author: 潘江明
    Copyright © 2021  潘江明
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <limits.h>
//补齐代码

#define  INFINITY 100000	   //最大值   ∞
#define  MAX_VERTEX_NUM 20        //最大顶点个数

typedef struct ShortestPath {
	char vtxedge[MAX_VERTEX_NUM];	//用于存储最短路所经过的路程
	int cnt;
	int dist, visited;
}ShortestPath;
typedef struct {
	char vexs[MAX_VERTEX_NUM];  		            //顶点向量
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];	//邻接矩阵
	int vexnum, arcnum;		//图的当前顶点和弧数
} MGraph;
typedef struct {
	ShortestPath S[MAX_VERTEX_NUM];
}ANS;	//最短路

void CreateUDN(MGraph& G);		  //创建无向网络
int LocateVex(MGraph G, char v);	      //结点的在顶点向量中的下标
void PrintUDN(MGraph G);			  //输出存储结构示意图
void Dijkstra(MGraph G, ANS& ans);	//dijkstra-shortest paths
void PrintDist(MGraph G, ANS ans);	//打印最终答案

int main() {
	MGraph G;
	ANS S;

	CreateUDN(G);
	printf("该图的邻接矩阵存储示意图如下：\n");
	PrintUDN(G);
	printf("\n");

	Dijkstra(G, S);
	PrintDist(G, S);

	return 0;
}

void CreateUDN(MGraph& G) {
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
		G.arcs[A][B] = edge;
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

void Dijkstra(MGraph G, ANS& ans) {
	for (int i = 0; i < G.vexnum; i++) {
		ans.S[i].visited = false, ans.S[i].dist = INFINITY;
		ans.S[i].cnt = 0;
	}
		
	ans.S[0].dist = 0;
	ans.S[0].vtxedge[0] = G.vexs[0], ans.S[0].cnt = 1;

	for (int i = 0; i < G.vexnum; i++) {
		int t = -1;
		for (int j = 0; j < G.vexnum; j++)
			if (!ans.S[j].visited && (t == -1 || ans.S[t].dist > ans.S[j].dist))
				t = j;
		
		ans.S[t].visited = true;

		for (int j = 0; j < G.vexnum; j++) {
			if (ans.S[j].dist > ans.S[t].dist + G.arcs[t][j]) {
				ans.S[j].dist = ans.S[t].dist + G.arcs[t][j];

				for (int k = 0; k < ans.S[t].cnt; k++) {
					ans.S[j].vtxedge[k] = ans.S[t].vtxedge[k];
				}

				ans.S[j].vtxedge[ans.S[t].cnt] = G.vexs[j];
				ans.S[j].cnt = ans.S[t].cnt + 1;
			}
		}
	}
}

void PrintDist(MGraph G, ANS ans) {
	for (int i = 1; i < G.vexnum; i++) {
		if (ans.S[i].dist == INFINITY) {
			printf("A-->%c\t无路径\n", G.vexs[i]);
		}
		else {
			for (int j = 0; j < ans.S[i].cnt - 1; j++)
				printf("%c-->", ans.S[i].vtxedge[j]);
			printf("%c", ans.S[i].vtxedge[ans.S[i].cnt - 1]);

			printf("\t长度%d\n", ans.S[i].dist);
		}
	}
}


/*
6  8
ABCDEF
AC  10
AE  30
AF  100
BC  5
CD  50
DF  10
ED  20
EF  60
*/