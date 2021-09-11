#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

#define MAX_COLS 100

typedef struct term {
	int row;
	int col;
	int val;
}term;

void transpose(term*, term*);
void fastTranspose(term*, term*);
void showMatrix(term*);

int main() {
	FILE* in;
	int n, i;
	term* A, * B, * C;

	if (!(in = fopen("in.txt", "r")))
		perror("read file error!");
	if (!(fscanf(in, "%d", &n)))
		perror("read term size error!");

	A = (term*)malloc(sizeof(term) * n);
	B = (term*)malloc(sizeof(term) * n);
	C = (term*)malloc(sizeof(term) * n);

	for (i = 0; i <= n; i++) {
		fscanf(in, "%d %d %d", &A[i].row, &A[i].col, &A[i].val);
	}

	showMatrix(A);

	printf("\nTranspose Matrix\n");
	transpose(A, B);
	showMatrix(B);

	printf("\nFast Transpose Matrix\n");
	fastTranspose(A, C);
	showMatrix(C);
}

void transpose(term* A, term* B) {
	int curr = 1, i, j;
	int n = A[0].val;
	B[0].row = A[0].col;
	B[0].col = A[0].row;
	B[0].val = A[0].val;

	if (n > 0) {
		for (i = 0; i < A[0].col; i++) {
			for (j = 1; j <= n; j++) {
				if (i == A[j].col) {
					B[curr].row = A[j].col;
					B[curr].col = A[j].row;
					B[curr].val = A[j].val;
					curr++;
				}
			}
		}
	}
}

void fastTranspose(term* A, term* B) {
	int rowTerms[MAX_COLS], startingPos[MAX_COLS];
	int i, j;
	int numCols = A[0].col, numTerms = A[0].val;
	B[0].row = numCols, B[0].col = A[0].row, B[0].val = numTerms;

	if (numTerms > 0) {
		for (i = 0; i < numCols; i++) { //rowTerm�� ���� �ʱ�ȭ
			rowTerms[i] = 0;
		}
		for (i = 1; i <= numTerms; i++) { //A�� col�� �� ���� ���Ұ� �ִ� �� rowTerms�� ����
			rowTerms[A[i].col]++;
		}

		//�� startingPos�� ���� startingPos + ���� ������� matrix�� �� row�� ���� ����
		//startingPos�� ���������ν� ���� ��������� term B�� index ������� �ش� row ���� ������ŭ ���� �� �ִ�.
		startingPos[0] = 1;
		for (i = 1; i < numCols; i++) {
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1]; 
		}
		for (i = 1; i <= numTerms; i++) {
			j = startingPos[A[i].col]++;
			B[j].row = A[i].col, B[j].col = A[i].row, B[j].val = A[i].val;
		}
	}
}

void showMatrix(term* X) {
	int i, n = X[0].val;

	for (i = 0; i < n+1; i++) {
		printf("matrix[%d] row: %d col: %d val: %d\n", i, X[i].row, X[i].col, X[i].val);
	}

	return;
}