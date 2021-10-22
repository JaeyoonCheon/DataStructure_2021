#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>

#define MAX_SIZE 100

typedef struct matrixForm {
	double* aa;
	int* ja;
}matrixForm;

int rowSize, colSize, vSize, nonZero, N = 0;
double er = 0.00001;
void initMatrix(double*, int*);
void setX(FILE*, double*);
void setMatrix(FILE*, double*, int*);
void makeMB(double*, double*, double*);
void jacobi_sequence(double*, int*, double*, double*, double*, double*);
int check(double*);

int main() {
	FILE* fa, * fb, * fx, * output1, * output2;
	int* ja;
	double* aa, * b, * x, * x_old, * mb, * err;
	int i, n;

	fa = fopen("MatrixA.txt", "r+");
	fb = fopen("VectorB.txt", "r+");
	fx = fopen("VectorX.txt", "r+");
	output1 = fopen("out_jacobi.txt", "w+");
	output2 = fopen("aprox_jacobi.txt", "w+");

	// A ����� row, column, nonZero ���� �Է�
	fscanf(fa, "%d %d %d", &rowSize, &colSize, &nonZero);

	// nonZero+1 ũ���� AA, JA �迭 �����Ҵ�(+1 -> 0 index ��� x)
	aa = (double*)calloc(nonZero + 2, sizeof(double));
	ja = (int*)calloc(nonZero + 2, sizeof(int));

	// AA, JA �迭 ����
	setMatrix(fa, aa, ja);

	// X ������ ũ�� �Է� = A ����� column ���̿� ����
	fscanf(fb, "%d", &vSize);
	// colSize+1 ũ���� X �迭 �����Ҵ�(+1 -> 0 index ��� x)

	// X �迭 ����
	b = (double*)calloc(colSize + 1, sizeof(double));
	setX(fb, b);

	fscanf(fx, "%d", &vSize);
	// colSize+1 ũ���� X �迭 �����Ҵ�(+1 -> 0 index ��� x)
	x = (double*)calloc(colSize + 1, sizeof(double));
	x_old = (double*)calloc(colSize + 1, sizeof(double));

	// X �迭 ����
	setX(fx, x);

	for (i = 1; i <= vSize; i++) {
		x_old[i] = x[i];
	}

	printf("input finished\n");

	/*mb = (double*)calloc(colSize + 1, sizeof(double));
	makeMB(aa, b, mb);*/

	err = (double*)calloc(colSize + 1, sizeof(double));

	printf("n repeat : ");
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		//jacobi(aa, ja, x, b, mb, err);
		jacobi_sequence(aa, ja, x, b, x_old, err);
		if (check(err) == 0) {
			printf("iteration %d, error!\n", i + 1);
			break;
		}
	}
	printf("jacobi method finished\n");

	// index 1���� ���Ͽ� ���
	for (i = 1; i <= colSize; i++) {
		fprintf(output1, "%e\n", x[i]);
	}

	// index 1���� ���Ͽ� ���
	for (i = 1; i <= colSize; i++) {
		fprintf(output2, "%e\n", err[i]);
	}

	printf("finished\n");

	return 0;
}

void initMatrix(double* AA, int* JA) {
	//�밢��� ���� �ڸ��� *
	AA[rowSize + 1] = 0;
	//* �Ʒ��ڸ� ��ġ ������ ��� ũ�� index
	JA[rowSize + 1] = nonZero + 2;
}

void setX(FILE* fb, double* B) {
	int i;
	int row, col;
	double val;

	for (i = 0; i < vSize; i++) {
		fscanf(fb, "%d %lf", &row, &val);
		if (row < i) {
			fseek(fb, -13, SEEK_CUR);
			continue;
		}

		B[row] = val;
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

		if (JA[row] == 0)
			JA[row] = s;

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

void makeMB(double* AA, double* B, double* MB) {
	int i;

	for (i = 1; i < rowSize + 1; i++) {
		// �밢 ����İ� B ������ i index ��
		MB[i] = (1 / AA[i]) * B[i];
	}
}

void jacobi_sequence(double* AA, int* JA, double* X, double* B, double* X_OLD, double* err) {
	int i, j, k;
	double temp, temp2;

	for (i = 1; i < rowSize + 1; i++) {
		temp2 = X_OLD[i];
		//�밢 ����� * -triangle * ���� x
		temp = 0;
		for (k = JA[i]; k < JA[i + 1]; k++) {
			j = JA[k];
			temp += AA[k] * X_OLD[j];
		}

		X[i] = (1 / AA[i]) * (B[i] - temp);
		err[i] = fabs((X[i] - X_OLD[i]) / X[i]);
		X_OLD[i] = X[i];
	}
}

int check(double* err) {
	int i;

	for (i = 1; i < rowSize + 1; i++) {
		if (err[i] < er) {
			return 1;
		}
	}
	return 0;
}