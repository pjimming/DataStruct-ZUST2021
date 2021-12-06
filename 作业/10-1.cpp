/*
	@author: 潘江明
*/

#include <stdio.h>

#define MAX_SIZE 20

typedef int ElemType;
ElemType array[MAX_SIZE];
int length;

void CreateArray(ElemType A[]) {
	printf("请输入元素个数:\n");
	scanf_s("%d", &length);

	printf("请输入所有元素:\n");
	for (int i = 0; i < length; i++) {
		scanf_s("%d", &A[i]);
	}
}

void Print(ElemType A[], int gap) {
	printf("\n----------------------------\n");
	if (gap != 0)
		printf("增量%d：", gap);
	else
		printf("原数组为：");
	for (int i = 0; i < length; i++)
		printf("%d ", A[i]);
	printf("\n----------------------------\n");
}

void ShellSort(ElemType A[]) {
	for (int gap = 5; gap > 0; gap -= 2) {
		for (int i = gap; i < length; i++) {
			int temp = A[i];
			int j;
			for (j = i - gap; j >= 0 && A[j] > temp; j -= gap)
				A[j + gap] = A[j];
			A[j + gap] = temp;
		}

		Print(A, gap);
	}
}

int main() {
	CreateArray(array);

	Print(array, 0);

	ShellSort(array);

	return 0;
}

/*
13
21 27 10 14 75 45 9 28 16 55 70 18 32
*/