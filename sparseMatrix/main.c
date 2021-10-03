#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>


#define MAX_SIZE 100

int rowSize, colSize, vSize, nonZero;
double min = INT_MAX, max = INT_MIN;
int minIdx, maxIdx;

int* createMatrix();
void initMatrix(double*, int*);
void setX(FILE*, double*);
void setMatrix(FILE*, double*, int*);
void mmult(double*, double*, int*, double*);

int main() {
	FILE* fa, * fx, * output1, * output2;
	int* ja;
	double* aa, * x, * result;
	int i;
	double norm = 0.0;

	fa = fopen("MatrixA.txt", "r+");
	fx = fopen("VectorX.txt", "r+");
	output1 = fopen("out.txt", "w+");
	output2 = fopen("out_norm.txt", "w+");

	// A ����� row, column, nonZero ���� �Է�
	fscanf(fa, "%d %d %d", &rowSize, &colSize, &nonZero);

	// nonZero+1 ũ���� AA, JA �迭 �����Ҵ�(+1 -> 0 index ��� x)
	aa = (double*)calloc(nonZero + 1, sizeof(double));
	ja = (int*)calloc(nonZero + 1, sizeof(int));

	// AA, JA �迭 ����
	setMatrix(fa, aa, ja);

	// X ������ ũ�� �Է� = A ����� column ���̿� ����
	fscanf(fx, "%d", &vSize);
	// colSize+1 ũ���� X �迭 �����Ҵ�(+1 -> 0 index ��� x)
	x = (double*)calloc(colSize + 1, sizeof(double));

	// X �迭 ����
	setX(fx, x);

	printf("input finished\n");

	// ��� �� ����� ���� ���� �迭 ����(X�� ������ A ��� column ���� + 1)
	result = (double*)calloc(colSize + 1, sizeof(double));

	mmult(result, aa, ja, x);
	
	printf("multiplication finished\n");

	// index 1���� ���Ͽ� ���
	for (i = 1; i < colSize; i++) {
		fprintf(output1, "%e\n", result[i]);
	}

	// element ������ �� ����
	for (i = 1; i < colSize; i++) {
		norm += powf(result[i], 2);
	}

	// norm ���
	norm = sqrtf(norm);

	printf("norm : %e\n", norm);

	for (i = 1; i < colSize; i++) {
		fprintf(output2, "%e\n", result[i] / norm);
	}

	if (max > -1 * min) {
		printf("���밪 �ִ� : %e\n", result[maxIdx] / norm);
	}
	else {
		printf("���밪 �ִ� : %e\n", result[minIdx] / norm);
	}

	printf("finished\n");

	return 0;
}

int* createMatrix() {
	int i, j;
	int* temp;
	int matSIze = nonZero + 1;

	temp = (int*)calloc(matSIze, sizeof(int));

	return temp;
}

void initMatrix(double* AA, int* JA) {
	//�밢��� ���� �ڸ��� *
	AA[rowSize + 1] = 0;
	//* �Ʒ��ڸ� ��ġ ������ ��� ũ�� index
	JA[rowSize + 1] = nonZero + 2;
}

void setX(FILE* fx, double* X) {
	int i;
	int row, col;
	double val;

	for (i = 0; i < vSize; i++) {
		fscanf(fx, "%d %d %lf", &row, &col, &val);

		X[row] = val;
	}
}

void setMatrix(FILE* fa, double* AA, int* JA) {
	int i;
	// t : �밢���� ���� ������, s : ������ ��Ҽ��� ���� ������
	int t = 1, s = colSize + 2;
	int row, col;
	double val;
	int size = nonZero + 1;


	initMatrix(AA, JA);

	for (i = 0; i < nonZero; i++) {
		fscanf(fa, "%d %d %lf", &row, &col, &val);

		// row == col�� ��� �밢������ ���� 1���� ����
		if (row == col) {
			AA[t] = val;
			t++;
		}
		// row != col�� ��� ������ colSize + 2���� ����
		else {
			// �� �ڸ��� index�� ó�� �������� ��� �ѹ��� �������� ���
			if (JA[row] == 0)
				JA[row] = s;
			// s index�� column ���� ���
			JA[s] = col;
			// AA �迭 ���� ��ġ�� �� ���
			AA[s] = val;
			s++;
		}
	}
}

void mmult(double* Y, double* AA, int* JA, double* X) {
	int i, j, k;
	long double temp;

	for (i = 1; i < rowSize + 1; i++) {
		// �밢���а� X ������ i index ��
		temp = AA[i] * X[i];
		
		// ������ ���а� X ������ ���� ��
		for (k = JA[i]; k < JA[i + 1]; k++) {
			// j : A ����� �ش� ���� column ����
			j = JA[k];
			temp += AA[k] * X[j];
		}
		Y[i] = temp;

		// min, max���� index�� ����Ͽ� �ִ� ���밪 ���� ���� �� ���
		if (Y[i] < min) {
			min = Y[i];
			minIdx = i;
		}
		if (Y[i] > max) {
			max = Y[i];
			maxIdx = i;
		}
	}
}