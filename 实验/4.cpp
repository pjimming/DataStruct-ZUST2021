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

#define  INFINITY 100000       //最大值   ∞  
#define  MAX_VERTEX_NUM 20        //最大顶点个数  

typedef struct ShortestPath {
	int pre;    //用于存储最短路路径中该结点的上一个结点
	int dist, visited;
} ShortestPath;

typedef struct {
	char vexs[MAX_VERTEX_NUM];  //顶点向量
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   //邻接矩阵
	int vexnum, arcnum;     //图的当前顶点和弧数
	ShortestPath sp[MAX_VERTEX_NUM];
} MGraph;

void CreateUDN(MGraph &G);        //创建无向网络
int LocateVex(MGraph G, char v);          //结点的在顶点向量中的下标
void PrintUDN(MGraph G);              //输出存储结构示意图
void Dijkstra(MGraph &G);   //dijkstra-shortest paths
void PrintDist(MGraph G);   //打印最终答案
void PrintVer(MGraph G, int u); //如果最短路存在， 打印路径

int main() {
	MGraph G;

	CreateUDN(G);
	printf("该图的邻接矩阵存储示意图如下：\n");
	PrintUDN(G);
	printf("\n");

	Dijkstra(G);
	PrintDist(G);

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

void Dijkstra(MGraph &G) {
	for (int i = 0; i < G.vexnum; i++) {
		G.sp[i].visited = false, G.sp[i].dist = INFINITY, G.sp[i].pre = -1;
	}

	G.sp[0].dist = 0;

	for (int i = 0; i < G.vexnum; i++) {
		int t = -1;
		for (int j = 0; j < G.vexnum; j++)
			if (!G.sp[j].visited && (t == -1 || G.sp[t].dist > G.sp[j].dist))
				t = j;

		G.sp[t].visited = true;

		for (int j = 0; j < G.vexnum; j++) {
			if (G.sp[j].dist > G.sp[t].dist + G.arcs[t][j]) {
				G.sp[j].dist = G.sp[t].dist + G.arcs[t][j];
				G.sp[j].pre = t;
			}
		}
	}
}

void PrintDist(MGraph G) {
	for (int i = 1; i < G.vexnum; i++) {
		if (G.sp[i].dist == INFINITY) {
			printf("A-->%c\t无路径\n", G.vexs[i]);
		} else {
			PrintVer(G, i);

			printf("\t 长度%d\n", G.sp[i].dist);
		}
	}
}

void PrintVer(MGraph G, int u) {
	if (G.sp[u].pre != -1) {
		PrintVer(G, G.sp[u].pre);
		printf("-->");
	}
	printf("%c", G.vexs[u]);
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