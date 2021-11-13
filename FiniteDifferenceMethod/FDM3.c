#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ERR 0.00001
#define X_SIZE 1.0
#define Y_SIZE 1.0
#define DX 0.05
#define DY 0.05

void jacobi_sequence(double** matrix, double* T, double* Q, double* T_OLD) {
	int i, j, k, m;
	double temp, temp2;

	for (i = 0; i < 441; i++) {
		// 대각성분 아닌 값과 x값 곱한거
		// 1. (0,0)
		if (i == 0) {
			temp = matrix[i][1] * T_OLD[1] + matrix[i][21] * T_OLD[21];
			T[i] = (1 / matrix[i][0]) * (Q[i] - temp);
		}
		else if (i > 1 && i < 21)  {
			temp = matrix[i][i - 1] * T_OLD[i-1] + matrix[i][i+1] * T_OLD[i+1] + matrix[i][i + 21] * T_OLD[i + 21];
			T[i] = (1 / matrix[i][i]) * (Q[i] - temp);
		}
		else if (i != 0 && i % 21 == 0) {
			temp = matrix[i][i - 21] * T_OLD[i - 21] + matrix[i][i + 1] * T_OLD[i + 1] + matrix[i][i + 21] * T_OLD[i + 21];
			T[i] = (1 / matrix[i][i]) * (Q[i] - temp);
		}
		else {
			temp = matrix[i][i - 21] * T_OLD[i - 21] + matrix[i][i - 1] * T_OLD[i - 1] + matrix[i][i + 1] * T_OLD[i + 1] + matrix[i][i + 21] * T_OLD[i + 21];
			T[i] = (1 / matrix[i][i]) * (Q[i] - temp);
		}
	}
}

double** initMatrix(double** A, double** B, double** C, double** D, double** E, double* Q, double** k, double** q, double** matrix)
{
	int i, j, m, n;

	// A, B, C, D, E
	for (i = 0; i < 21; i++) {
		if (i == 0) {
			for (j = 0; j < 21; j++) {
				// x == 0, y == 0
				if (j == 0) {
					D[i][j] = -(k[i][j] * DY) / (2 * DX);
					E[i][j] = -(k[i][j] * DX) / (2 * DY);
					C[i][j] = -(D[i][j] + E[i][j]);
					Q[j] = q[i][j] * (DX / 2 * DY / 2);
				}
				// x == 0
				else {
					A[i][j] = -(k[i][j - 1] * DX) / (2 * DY);
					B[i][j] = 0;
					D[i][j] = -(k[i][j - 1] * DX + k[i][j] * DX) / (2 * DY);
					E[i][j] = -(k[i][j] * DX) / (2 * DY);
					C[i][j] = -(A[i][j] + B[i][j] + D[i][j] + E[i][j]);
					Q[i+21*j] = (q[i][j - 1] + q[i][j]) * (DX / 2 * DY / 2);
				}
			}
		}
		else {
			for (j = 0; j < 21; j++) {
				// y == 0
				if (j == 0) {
					B[i][j] = -(k[i - 1][j] * DY) / (2 * DX);
					D[i][j] = -(k[i][j] * DY) / (2 * DX);
					E[i][j] = -(k[i - 1][j] * DX + k[i][j]*DX) / (2 * DY);
					C[i][j] = -(B[i][j] + D[i][j] + E[i][j]);
					Q[i] = (q[i - 1][j] + q[i][j]) * (DX / 2 * DY / 2);
				}
				else {
					A[i][j] = -(k[i - 1][j - 1] * DX + k[i][j - 1] * DX) / (2 * DY);
					B[i][j] = -(k[i - 1][j - 1] * DX + k[i - 1][j] * DX) / (2 * DY);
					D[i][j] = -(k[i][j - 1] * DX + k[i][j] * DX) / (2 * DY);
					E[i][j] = -(k[i - 1][j] * DX + k[i][j] * DX) / (2 * DY);
					C[i][j] = -(A[i][j] + B[i][j] + D[i][j] + E[i][j]);
					Q[i*21+j] = (q[i - 1][j - 1] + q[i][j - 1] + q[i - 1][j] + q[i][j]) * (DX / 2 * DY / 2);
				}
			}
		}
	}

	// matrix
	for (i = 0; i < 21; i++) {
		for (j = 0; j < 21; j++) {
			// case 1. (0, 0)
			if (i == 0 && j == 0) {
				matrix[i][0] = C[i][j];
				matrix[i][1] = D[i][j];
				matrix[i][21] = E[i][j];
				continue;
			}
			//case 2. (i, 0)
			if (i != 0 && i < 21 && j == 0) {
				matrix[i][i - 1] = B[i][j];
				matrix[i][i] = C[i][j];
				matrix[i][i + 1] = D[i][j];
				matrix[i][i + 21] = E[i][j];
				continue;
			}
			//case 3. (0, j)
			m = i + 21 * j;
			if (m % 21 == 0) {
				matrix[m][m - 21] = A[i][j];
				matrix[m][m] = C[i][j];
				matrix[m][m + 1] = D[i][j];
				matrix[m][m + 21] = E[i][j];
				continue;
			}

			n = i * 21 + j;
			matrix[n][n - 21] = A[i][j];
			matrix[n][n - 1] = B[i][j];
			matrix[n][n] = C[i][j];
			matrix[n][n + 1] = D[i][j];
			matrix[n][n + 21] = E[i][j];
		}
	}
}

int main() {
	int i, j, flag = 0;
	double Tf = 0, Tr = 40.0, err = 0, tempStep = 0;

	double** k, ** q;
	double** A, ** B, ** C, ** D, ** E;
	double** matrix, * Q, * T, * T_OLD;

	// step 20
	A = (double**)malloc(sizeof(double*) * 21);
	for (i = 0; i < 21; i++) {
		A[i] = (double*)calloc(21, sizeof(double));
	}

	// step 20
	B = (double**)malloc(sizeof(double*) * 21);
	for (i = 0; i < 21; i++) {
		B[i] = (double*)calloc(21, sizeof(double));
	}

	// step 20
	C = (double**)malloc(sizeof(double*) * 21);
	for (i = 0; i < 21; i++) {
		C[i] = (double*)calloc(21, sizeof(double));
	}

	// step 20
	D = (double**)malloc(sizeof(double*) * 21);
	for (i = 0; i < 21; i++) {
		D[i] = (double*)calloc(21, sizeof(double));
	}

	// step 20
	E = (double**)malloc(sizeof(double*) * 21);
	for (i = 0; i < 21; i++) {
		E[i] = (double*)calloc(21, sizeof(double));
	}

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
	matrix = (double**)malloc(sizeof(double*) * 441);
	for (i = 0; i < 441; i++) {
		matrix[i] = (double*)calloc(441, sizeof(double));
	}

	// Q
	Q = (double*)calloc(441, sizeof(double));

	// T, T-old
	T = (double*)calloc(441, sizeof(double));
	T_OLD = (double*)calloc(441, sizeof(double));

	tempStep = 0;
	for (i = 0; i < 441; i++) {
		// 상부 경계
		if (i > 419) {
			tempStep += DX;
			T[i] = 50.0 - 10.0 * powf(tempStep, 2);
		}

		// 우측 경계
		if (i % 21 == 20) {
			T[i] = 40.0;
		}
	}

	initMatrix(A, B, C, D, E, Q, k, q, matrix);

	i = 0;
	while (1) {
		flag = 0;
		jacobi_sequence(matrix, T, Q, T_OLD);
		tempStep = 0;
		for (i = 0; i < 441; i++) {
			// 상부 경계
			if (i > 419) {
				tempStep += DX;
				T[i] = 50.0 - 10.0 * powf(tempStep, 2);
			}

			// 우측 경계
			if (i % 21 == 20) {
				T[i] = 40.0;
			}
		}
		for (j = 0; j < 441; j++) {
			err = (T[j] - T_OLD[j]) / T[j];
			if (err > MAX_ERR) {
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			for (j = 0; j < 441; j++) {
				T_OLD[j] = T[j];
			}
		}
		else {
			i++;
			break;
		}
		i++;
	}

	printf("\n%d iteration\n", i);

	for (i = 0; i < 40; i++) {
		for (j = 0; j < 40; j++) {
			printf("%.3f ", matrix[i][j]);
		}
		printf("\n");
	}

	printf("\nT vector\n");
	for (i = 0; i < 441; i++) {
		printf("%.3f\n", T[i]);
	}
}