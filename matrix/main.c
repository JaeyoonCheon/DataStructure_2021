#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

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

	if (!(in = fopen("in.txt", "r")))
		perror("read file error!");
	if (!(fscanf(in, "%d", &n)))
		perror("read term size error!");

	term* A = (term*)malloc(sizeof(term) * n);
	term* B = (term*)malloc(sizeof(term) * n);

	for (i = 0; i <= n; i++) {
		fscanf(in, "%d %d %d", &A[i].row, &A[i].col, &A[i].val);
	}

	showMatrix(A);

	transpose(A, B);
	showMatrix(B);
	//fastTranspose(A, B);
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

void showMatrix(term* X) {
	int i, n = X[0].val;

	for (i = 0; i < n; i++) {
		printf("matrix[%d] row: %d col: %d val: %d\n", i, X[i].row, X[i].col, X[i].val);
	}

	return;
}