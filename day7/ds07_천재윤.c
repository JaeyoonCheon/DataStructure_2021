#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

#define MAX_COLS 100
#define MAX_TERMS 100

typedef struct term {
	int row;
	int col;
	int val;
}term;

term* createMatrix(int);
void transpose(term*, term*);
void fastTranspose(term*, term*);
void storeSum(term*, int*, int, int, int*);
void mmult(term*, term*);
void showMatrix(term*);

int main() {
	FILE* in, *out;
	int n, i;
	int row, col, terms;
	term* A, * B, * C, * D;

	printf("��ǻ���к� 2016115430 õ����\n");

	if (!(in = fopen("m.txt", "r")))
		perror("read file error!");
	if (!(out = fopen("out.txt", "w+")))
		perror("file writing error!");


	fscanf(in, "%d %d %d", &row, &col, &terms);

	A = createMatrix(terms);
	B = createMatrix(terms);
	C = createMatrix(terms);
	D = createMatrix(terms);

	A[0].row = row;
	A[0].col = col;
	A[0].val = terms;

	for (i = 1; i <= terms; i++) {
		fscanf(in, "%d %d %d", &A[i].row, &A[i].col, &A[i].val);
	}

	//showMatrix(A);

	/*printf("\nTranspose Matrix\n");
	transpose(A, B);
	showMatrix(B);*/

	//printf("\nFast Transpose Matrix\n");
	fastTranspose(A, C);
	//showMatrix(C);

	for (i = 0; i <= terms; i++) {
		fprintf(out, "%d %d %d\n", C[i].row, C[i].col, C[i].val);
	}

	//printf("\nMatrix Multiplication\n");
	//mmult(A, C, D);
	//showMatrix(D);

	fclose(in);
	fclose(out);
}

term* createMatrix(int n) {
	term* temp;
	
	temp = (term*)malloc(sizeof(term) * (n + 1));

	return temp;
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

void storeSum(term* D, int* totalD, int row, int col, int* sum) {
	if (*sum) {
		if (*totalD < MAX_TERMS) {
			D[++ * totalD].row = row;
			D[*totalD].col = col;
			D[*totalD].val = *sum;
			*sum = 0;
		}
		else {
			fprintf(stderr, "Numbers of terms in product exceeds %d\n", MAX_TERMS);
			exit(EXIT_FAILURE);
		}
	}
}

void mmult(term* A, term* B, term* D) {
	int i, j, col;
	int totalB = B[0].val, totalD = 0;
	int rowsA = A[0].row, colsA = A[0].col, totalA = A[0].val, colsB = B[0].col;
	int rowBegin = 1, row = A[1].row, sum = 0;

	term* newB;
	newB = (term*)malloc(sizeof(term) * MAX_TERMS);

	if (colsA != B[0].row) {
		fprintf(stderr, "Incampatible matrices\n");
		exit(EXIT_FAILURE);
	}

	fastTranspose(B, newB);

	A[totalA + 1].row = rowsA;
	newB[totalB + 1].row = colsB;
	newB[totalB + 1].col = 0;

	for (i = 1; i <= totalA;) {
		col = newB[i].row;
		for (j = 1; j <= totalB + 1;) {
			if (A[i].row != row) {
				storeSum(D, &totalD, row, col, &sum);
				i = rowBegin;
				for (; newB[j].row == col; j++);
				col = newB[j].row;
			}
			else if (newB[j].row != col) {
				storeSum(D, &totalD, row, col, &sum);
				i = rowBegin;
				col = newB[j].row;
			}
			else {
				if (A[i].col < newB[j].col) {
					i++;
				}
				else if (A[i].col == newB[j].col) {
					sum += (A[i++].val * newB[j++].val);
				}
				else {
					j++;
				}
			}
		}
		for (; A[i].row == row; i++);
		rowBegin = i;
		row = A[i].row;
	}
	D[0].row = rowsA;
	D[0].col = colsB;
	D[0].val = totalD;
	printf("totalD : %d\n", totalD);
}

void showMatrix(term* X) {
	int i, j, n = X[0].val;
	int** arr = (int**)malloc(sizeof(int*) * X[0].row);
	for (i = 0; i < X[0].row; i++) {
		arr[i] = (int*)malloc(sizeof(int) * X[0].col);
	}

	for (i = 0; i < X[0].row; i++) {
		for (j = 0; j < X[0].col; j++) {
			arr[i][j] = 0;
		}
	}

	for (i = 1; i <= X[0].val; i++) {
		arr[X[i].row][X[i].col] = X[i].val;
	}

	for (i = 0; i < X[0].row; i++) {
		for (j = 0; j < X[0].col; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return;
}