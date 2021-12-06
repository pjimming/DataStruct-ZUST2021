/*
    @author: 潘江明
    Copyright © 2021  潘江明
*/

#include <stdio.h>

#define MAX_NUM 20

typedef int ElemType;
typedef struct Array {
    int numelem;
    ElemType arr[MAX_NUM];
}Array;

void CreateArray(Array& A);
void QuickSort(Array& A, int l, int r);
void SwapElem(int& a, int& b);
void PrintArray(Array A);

int main() {
    Array A;

    CreateArray(A);

    printf("原数组：\n");
    PrintArray(A);

    QuickSort(A, 0, A.numelem - 1);

    printf("排序后：\n");
    PrintArray(A);

    return 0;
}

void CreateArray(Array& A) {
    scanf("%d", &A.numelem);

    for (int i = 0; i < A.numelem; i++) {
        scanf("%d", &A.arr[i]);
    }
}

void QuickSort(Array& A, int l, int r) {
    if (l >= r)
        return;

    int i = l - 1, j = r + 1, x = A.arr[l + r >> 1];
    while (i < j) {
        do i++; while (A.arr[i] < x);
        do j--; while (A.arr[j] > x);
        if (i < j)
            SwapElem(A.arr[i], A.arr[j]);
    }

    QuickSort(A, l, j), QuickSort(A, j + 1, r);
}

void SwapElem(int& a, int& b) {
    int t;
    t = a, a = b, b = t;
}

void PrintArray(Array A) {
    for (int i = 0; i < A.numelem; i++)
        printf("%d ", A.arr[i]);
    printf("\n");
}

/*
10
26  7  3  18  21  6  28  157  16  53
*/