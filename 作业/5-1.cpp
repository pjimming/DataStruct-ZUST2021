/*
	author: 潘江明
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define MAXSIZE 1010
#define MAXC 100

typedef int Status;
typedef int ElemType;
typedef struct {
	int i, j;
	ElemType e;
}Triple;
typedef struct {
	Triple data[MAXSIZE + 1];
	ElemType rpos[MAXC + 1];
	int nu, mu, tu;
}Matrix;

Matrix mul(Matrix A, Matrix B, Matrix C) {
	if (A.nu != B.mu) return C;

	C.mu = A.mu, C.nu = B.nu, C.tu = 0;
	if (A.tu * B.tu == 0) return C;

	int arow, ccol;
	for (arow = 1; arow <= A.mu; arow++) {
		int ctemp[MAXC + 1] = {};
		C.rpos[arow] = C.tu + 1;

		int acnt;
		if (arow < A.mu)
			acnt = A.rpos[arow + 1];
		else
			acnt = A.tu + 1;

		int brow, p;
		for (p = A.rpos[arow]; p < acnt; p++) {
			brow = A.data[p].j;

			int bcnt;
			if (brow < B.mu)
				bcnt = B.rpos[brow + 1];
			else
				bcnt = B.tu + 1;

			int q;
			for (q = B.rpos[brow]; q < bcnt; q++) {
				ccol = B.data[q].j;
				ctemp[ccol] += A.data[p].e * B.data[q].e;
			}
		}

		for (ccol = 1; ccol <= C.nu; ccol++) {
			if (ctemp[ccol]) {
				if (++C.tu > MAXSIZE) return C;
				else {
					C.data[C.tu].e = ctemp[ccol];
					C.data[C.tu].i = arow;
					C.data[C.tu].j = ccol;
				}
			}
		}
	}

	return C;
}

Status DisplayMatrix(Matrix A) {
	int cnt = 1, i, j;

	for (i = 1; i <= A.mu; i++) {
		for (j = 1; j <= A.nu; j++) {
			if (i == A.data[cnt].i && j == A.data[cnt].j) {
				printf("%3d", A.data[cnt++].e);
			}
			else {
				printf("  0");
			}
		}
		puts("");
	}

	return OK;
}

int main() {
	Matrix M, N, Q;

	M.mu = 3, M.nu = 4, M.tu = 4;
	M.data[1] = { 1,1,3 };
	M.data[2] = { 1,4,5 };
	M.data[3] = { 2,2,-1 };
	M.data[4] = { 3,1,2 };
	M.rpos[1] = 1, M.rpos[2] = 3, M.rpos[3] = 4;

	N.mu = 4, N.nu = 2, N.tu = 4;
	N.data[1] = { 1,2,2 };
	N.data[2] = { 2,1,1 };
	N.data[3] = { 3,1,-2 };
	N.data[4] = { 3,2,4 };
	N.rpos[1] = 1, N.rpos[2] = 2, N.rpos[3] = 3, N.rpos[4] = 5;

	printf("M矩阵为：\n");
	DisplayMatrix(M);

	printf("N矩阵为：\n");
	DisplayMatrix(N);

	Q = mul(M, N, Q);

	printf("Q矩阵为：\n");
	DisplayMatrix(Q);

	return 0;
}