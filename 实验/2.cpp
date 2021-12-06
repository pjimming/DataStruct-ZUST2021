/*
	@author: 潘江明
	Copyright 2021 潘江明
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct {
	char ch;                    //字母与编码
	int weight;                  //权重
	int parent, lchild, rchild;        //父亲与左右孩子
} HTNode, * HuffmanTree;
typedef char** HuffmanCode;

//以下为函数原型声明
void CreateHuffmanTree(HuffmanTree& HT, int w[], char ch[], int n);       //构造HuffmanTree
void Select(HuffmanTree HT, int  n, int& s1, int& s2);   //选择两个权重最小的无父亲的结点
void HTCoding(HuffmanTree HT, HuffmanCode& HC, int n);   //利用HuffmanTree对字符编码
void PrintCode(HuffmanCode HC, int n, char ch[]);                             //输出编码
double AverageLenght(HuffmanTree HT, HuffmanCode HC, int n);           //求平均编码长度
void DeCode(HuffmanTree HT, int n);                                            //解码

int main() {
	int n;
	int i;
	char arrch[20];
	int arrweight[20];
	double avlength;
	char ch;
	HuffmanTree HT;       //HT是一个指针变量，用于指向HuffmanTree
	HuffmanCode HC;      //HC是一个指针变量,用于存放对应字符的编码

	scanf("%d", &n);        //输入字符个数
	while ((ch = getchar()) != '\n');
	if (n > 20 || n < 2)
		exit(0);    //输入的字符数超出要求范围退出；
	for (i = 0; i < n; i++) {      //输入字符和对应的权重
		scanf("%c", &arrch[i]);
		scanf("%d", &arrweight[i]);
		while ((ch = getchar()) != '\n');
	}
	CreateHuffmanTree(HT, arrweight, arrch, n);  //构造HuffmanTree
	HTCoding(HT, HC, n);                   //利用HuffmanTree对字符编码
	PrintCode(HC, n, arrch);                  //输出编码
	avlength = AverageLenght(HT, HC, n);       //求平均编码长度
	printf("平均编码长度为：%f\n", avlength);
	DeCode(HT, n);                        //解码
	for (i = 0; i < n; i++)
		free(HC[i]);
	free(HC);
	free(HT);
}//end_main

void CreateHuffmanTree(HuffmanTree& HT, int w[], char ch[], int n) {
	// w存放n个字符的权值(均>0)，构造哈夫曼树HT，
	int i, m, s1, s2;
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));  // 0号单元不用
	//设有一组权值存放于数组w[]中，对应的字符在数组ch[]中
	for (i = 1; i <= n; i++) {
		HT[i].weight = w[i - 1];
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
		HT[i].ch = ch[i - 1];
	}
	//数组HT后n-1个元素先清空
	for (i = n + 1; i <= m; i++) {
		HT[i].weight = 0;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
		HT[i].ch = '\0';
	}
	for (i = n + 1; i <= m; i++) { // 建哈夫曼树
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}

}

void Select(HuffmanTree HT, int n, int& s1, int& s2) {
	//补充完整
	int i = 1;
	while (HT[i].parent != 0 && i <= n)
		i++;
	s1 = i++;
	while (HT[i].parent != 0 && i <= n)
		i++;
	s2 = i;
	if (HT[s1].weight > HT[s2].weight) {
		int t = s1;
		s1 = s2;
		s2 = t;
	}

	for (int i = 1; i <= n; i++) {
		if (HT[i].parent == 0) {
			if (HT[i].weight < HT[s1].weight)
				s2 = s1, s1 = i;
			if (HT[i].weight < HT[s2].weight && HT[i].weight > HT[s1].weight)
				s2 = i;
		}
	}
}//end_Select

void HTCoding(HuffmanTree HT, HuffmanCode& HC, int n) {
	// 从叶子到根逆向求每个字符的哈夫曼编码
	int i, j, k, start;
	int f;
	int c;
	char* cd;

	HC = (HuffmanCode)malloc((n) * sizeof(char*));
	cd = (char*)malloc(n * sizeof(char));     // 分配求编码的工作空间
	cd[n - 1] = '\0';                         // 编码结束符。
	for (i = 1; i <= n; ++i) {
		// 逐个字符求哈夫曼编码
		start = n - 1;                       // 编码结束符位置
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent) {
			if (HT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		HC[i - 1] = (char*)malloc((n - start) * sizeof(char));
		for (j = start, k = 0; j < n; j++, k++)       // 从cd复制编码(串)到HC
			HC[i - 1][k] = cd[j];
	}
	free(cd);                           // 释放工作空间
} //end_HTCoding

void PrintCode(HuffmanCode HC, int n, char ch[]) { //输出编码
	//补充完整
	printf("\n----------------------------------\n");
	for (int i = 0; i < n; i++) {
		printf("%c %s\n", ch[i], HC[i]);
	}
	printf("----------------------------------\n");
} //end_PrintCode


double AverageLenght(HuffmanTree HT, HuffmanCode HC, int n) { //求平均编码长度
	//补充完整
	double sum_code, sum_weight;
	sum_code = sum_weight = 0;
	for (int i = 1; i <= n; i++) {
		int cnt = strlen(HC[i - 1]);
		sum_code += HT[i].weight * cnt;
		sum_weight += HT[i].weight;
	}
	return sum_code / sum_weight;
} //end_AverageLenght

void DeCode(HuffmanTree HT, int n) { //解码
	int  i;
	char endflag = '#';
	char ch;

	i = 2 * n - 1;                   //从根结点开始往下搜索
	scanf("%c", &ch);            //读入一个二进制码
	while (ch != endflag) {
		if (ch == '0')
			i = HT[i].lchild;
		else
			i = HT[i].rchild;

		if (HT[i].lchild == 0) {     //tree[i] 是叶子结点
			printf("%c", HT[i].ch);
			i = 2 * n - 1;
		}
		scanf("%c", &ch);
	}
	if ((HT[i].lchild != 0) && (i != 2 * n - 1))  //电文读完但没到叶子结点
		printf("\n未能完全解码\n");
	printf("\n");
} //end_DeCode

/*
5
A  8
B  20
C  30
D  15
E  27
0101101110#
*/