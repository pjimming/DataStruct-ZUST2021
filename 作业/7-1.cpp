/*
	@author: 潘江明
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_VERTEX_SIZE 20
#define MAX_NAME_SIZE 5

typedef char VertexType;
typedef int EdgeType;
typedef struct EdgeNode {
	EdgeType weight;
	int adjvex;
	struct EdgeNode *next;
} EdgeNode;

typedef struct VertexNode {
	int idx;
	EdgeNode *firstedge;
} VertexNode;

typedef struct {
	int numNodes, numEdges;
	VertexNode adjlist[MAX_VERTEX_SIZE];
} GraphAdjList;

int visited[MAX_VERTEX_SIZE];

int LocateVer(GraphAdjList *gp, int v) {
	for (int i = 1; i <= gp->numNodes; i++) {
		if (gp->adjlist[i].idx == v)
			return i;
	}
}

void CreateGraph(GraphAdjList *gp) {
	EdgeNode *p;

	printf("请输入节点数和边数：\n");
	scanf("%d%d", &gp->numNodes, &gp->numEdges);

	printf("请输入结点的名称：\n");
	for (int i = 1; i <= gp->numNodes; i++) {
		gp->adjlist[i].firstedge = NULL;
		scanf("%d", &gp->adjlist[i].idx);
	}

	printf("请输入（v1, v2, e）v1 -e-> v2\n");
	for (int i = 0; i < gp->numEdges; i++) {
		int v1, v2, e;
		scanf("%d%d%d", &v1, &v2, &e);

		p = (EdgeNode *)malloc(sizeof(EdgeNode));
		p->weight = e;
		p->adjvex = LocateVer(gp, v2);
		p->next = gp->adjlist[v1].firstedge;
		gp->adjlist[LocateVer(gp, v1)].firstedge = p;
	}

	for (int i = 1; i <= gp->numNodes; i++) {
		visited[i] = false;
	}
}

void GraphDFS(GraphAdjList *gp, int idx) {
	printf("v%d, ", gp->adjlist[LocateVer(gp, idx)].idx);
	visited[LocateVer(gp, idx)] = true;

	GraphAdjList *p = gp;
	while (p->adjlist[LocateVer(gp, idx)].firstedge) {
		int j = p->adjlist[LocateVer(gp, idx)].firstedge->adjvex;
		if (!visited[j])
			GraphDFS(gp, j);
		p->adjlist[LocateVer(gp, idx)].firstedge = p->adjlist[LocateVer(gp, idx)].firstedge->next;
	}
}

int main() {
	GraphAdjList gp;

	CreateGraph(&gp);

	GraphDFS(&gp, 1);

	return 0;
}

/*
8 13
1 2 3 4 5 6 7 8
1 6 50
1 4 1
1 2 6
2 4 11
2 5 6
2 3 43
3 8 8
4 5 12
5 7 24
5 3 38
6 7 12
6 5 1
7 8 20
*/