#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ERR 0.00001
#define X_SIZE 1.0
#define Y_SIZE 1.0
#define DX 0.05
#define DY 0.05

void jacobi_sequence(double** matrix, double* X, double* B, double* X_OLD) {
	int i, j, k;
	double temp, temp2;

	for (i = 0; i < 69; i++) {
		temp = matrix[i][0] * X_OLD[i - 1] + matrix[i][2] * X_OLD[i + 1];
		if (i == 0) {
			temp = matrix[i][2] * X_OLD[i + 1];
		}
		if (i == 68) {
			temp = matrix[i][0] * X_OLD[i - 1];
		}

		X[i] = (1 / matrix[i][1]) * (B[i] - temp);
		//X_OLD[i] = X[i];
	}
}

double** initMatrix(double** A, double** B, double** C, double** D, double** E, double** Q, double** k, double** q)
{
	int i, j;

	for (i = 1; i < 21; i++) {
		for (j = 1; j < 21; j++) {
			A[i][j] = -(k[i - 1][j - 1] * DX + k[i][j - 1] * DX) / (2 * DY);
			B[i][j] = -(k[i - 1][j - 1] * DX + k[i - 1][j] * DX) / (2 * DY);
			D[i][j] = -(k[i][j - 1] * DX + k[i][j] * DX) / (2 * DY);
			E[i][j] = -(k[i - 1][j] * DX + k[i][j] * DX) / (2 * DY);
			C[i][j] = -(A[i][j] + B[i][j] + D[i][j] + E[i][j]);
			Q[i][j] = (q[i - 1][j - 1] + q[i][j - 1] + q[i - 1][j] + q[i][j]) * (DX / 2 * DY / 2);
		}
	}
}

int main() {
	int i, j, flag = 0;
	double Tf = 0, Tr = 40.0;

	double** k, ** q;
	double** A, ** B, ** C, ** D, ** E;
	double** matrix, ** Q, ** T, ** T_OLD;

	// step 20
	k = (double**)malloc(sizeof(double*) * 21);
	for (i = 0; i < 21; i++) {
		k[i] = (double*)calloc(21, sizeof(double));
	}

	for (i = 0; i < 20; i++) {
		for (j = 0; j < 20; j++) {
			if (i < 16 || j < 16) {
				k[i][j] = 5.0;
			}
			else {
				k[i][j] = 10.0;
			}
		}
	}

	// step 20
	q = (double**)malloc(sizeof(double*) * 21);
	for (i = 0; i < 21; i++) {
		q[i] = (double*)calloc(21, sizeof(double));
	}

	for (i = 0; i < 20; i++) {
		for (j = 0; j < 20; j++) {
			if (i < 16 || j < 16) {
				q[i][j] = 10000.0;
			}
			else {
				q[i][j] = 0.0;
			}
		}
	}

	// ABCDE matrix
	matrix = (double**)malloc(sizeof(double*) * 21);
	for (i = 0; i < 21; i++) {
		matrix[i] = (double*)calloc(21, sizeof(double));
	}

	// Q
	Q = (double**)malloc(sizeof(double*) * 21);
	for (i = 0; i < 21; i++) {
		Q[i] = (double*)calloc(21, sizeof(double));
	}

	// T, T-old
	T = (double**)malloc(sizeof(double*) * 21);
	for (i = 0; i < 21; i++) {
		T[i] = (double*)calloc(21, sizeof(double));
	}
	T_OLD = (double**)malloc(sizeof(double*) * 21);
	for (i = 0; i < 21; i++) {
		T_OLD[i] = (double*)calloc(21, sizeof(double));
	}

	for (i = 0; i < 21; i++) {
		for (j = 0; j < 21; j++) {
			matrix[i][j] =
		}
	}

	for (i = 0; i < 21; i++) {
		for (j = 0; j < 3; j++) {
			printf("%.3f ", matrix[i][j]);
		}
		printf("\n");
	}

	printf("\nB vector\n");
	for (i = 0; i < 21; i++) {
		printf("%.3f\n", B[i]);
	}

	i = 0;
	while (1) {
		flag = 0;
		jacobi_sequence(matrix, X, B, X_OLD);
		for (j = 0; j < 21; j++) {
			err = (X[j] - X_OLD[j]) / X[j];
			if (err > MAX_ERR) {
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			for (j = 0; j < 69; j++) {
				X_OLD[j] = X[j];
			}
		}
		else {
			i++;
			break;
		}
		i++;
	}

	printf("\n%d iteration\n", i);

	printf("\nX vector\n");
	for (i = 0; i < 69; i++) {
		printf("%.3f\n", X[i]);
	}
}