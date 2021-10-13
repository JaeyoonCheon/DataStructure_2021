#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>

#define MAX_SIZE 100

int rowSize, colSize, vSize, nonZero, N = 0;
double er = 0.1;
void initMatrix(double*, int*);
void setX(FILE*, double*);
void setMatrix(FILE*, double*, int*);
void mmult(double*, double*, double*, int*, double*, double*);
void makeS(double*, int*, double*, double*, double*);
double makeAlp(double*, double*);
void steep(double*, double*, double*, double, double*);
int check(double*);

int main() {
	FILE* fa, * fb, * fx, * output1, * output2;
	int* ja;
	double* aa, * b, * x, *x_old, * r, * z, * s, * err, * y;
	int i, n;
	double alp;

	fa = fopen("MatrixA.txt", "r+");
	fb = fopen("VectorB.txt", "r+");
	fx = fopen("VectorX.txt", "r+");
	output1 = fopen("out.txt", "w+");
	output2 = fopen("aprox.txt", "w+");

	// A ����� row, column, nonZero ���� �Է�
	fscanf(fa, "%d %d %d", &rowSize, &colSize, &nonZero);

	// nonZero+1 ũ���� AA, JA �迭 �����Ҵ�(+1 -> 0 index ��� x)
	aa = (double*)calloc(nonZero + 1, sizeof(double));
	ja = (int*)calloc(nonZero + 1, sizeof(int));

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

	r = (double*)calloc(colSize + 1, sizeof(double));
	z = (double*)calloc(colSize + 1, sizeof(double));
	s = (double*)calloc(colSize + 1, sizeof(double));
	y = (double*)calloc(colSize + 1, sizeof(double));

	printf("input finished\n");


	err = (double*)calloc(colSize + 1, sizeof(double));

	printf("n repeat : ");
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		mmult(y, b, aa, ja, x, r);
		makeS(aa, ja, r, z, s);
		alp = makeAlp(z, s);
		printf("alpha : %lf\n", alp);
		steep(x, x_old, z, alp, err);
		if (check(err) == 0) {
			printf("iteration %d,\n", i + 1);
			break;
		}
	}
	printf("steep method finished\n");

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
	int row;
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

void mmult(double* Y, double* B, double* AA, int* JA, double* X, double* R) {
	int i, j, k;
	double temp;
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
		R[i] = B[i] - Y[i];
	}
}

void makeS(double* AA, int* JA, double* R, double* Z, double* S) {
	int i, j, k;
	double temp;

	for (i = 1; i < rowSize + 1; i++) {
		// �밢 ����İ� B ������ i index ��
		Z[i] = (1 / AA[i]) * R[i];
	}

	for (i = 1; i < rowSize + 1; i++) {
		// �밢���а� X ������ i index ��
		temp = AA[i] * Z[i];

		// ������ ���а� X ������ ���� ��
		for (k = JA[i]; k < JA[i + 1]; k++) {
			// j : A ����� �ش� ���� column ����
			j = JA[k];
			temp += AA[k] * Z[j];
		}
		S[i] = (1 / AA[i]) * temp;
	}
}

double makeAlp(double* Z, double* S) {
	int i;
	double temp = 0, temp2 = 0;
	double Alp;

	for (i = 1; i < rowSize + 1; i++) {
		temp += Z[i] * Z[i];
		temp2 += S[i] * Z[i];
	}
	Alp = temp / temp2;

	return Alp;
}

void steep(double* X, double* X_OLD, double* Z, double Alp, double* err) {
	int i;

	for (i = 1; i < rowSize + 1; i++) {
		X[i] += Alp * Z[i];
		err[i] = fabs((X[i] - X_OLD[i]) / X[i]);
		X_OLD[i] = X[i];
	}
}

int check(double* err) {
	int i;

	for (i = 1; i < rowSize + 1; i++) {
		if (err[i] > er) {
			return 1;
		}
	}
	return 0;
}
