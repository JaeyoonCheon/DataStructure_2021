#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ERR 0.00001

double h1, h2, q1, q1_old, q2, q2_old, q1_old_t, r1, r2, Tr;

void initConst(double* R, double* r, double* Vp, double* Vm, double* B) {
	int i;

	for (i = 0; i < 33; i++) {
		if (i < 30) {
			R[i] = h1 / 2 + h1 * i;
			r[i] = h1 * i;
		}
		else {
			R[i] = 0.413 * powf(10, -2) + h2 / 2 + h2 * (i - 30);
			r[i] = 0.413 * powf(10, -2) + h2 * (i - 30);
		}

		if (i == 0) {
			Vp[i] = powf(R[i], 2) / 2;
		}
		else {
			Vm[i] = (powf(r[i], 2) - powf(R[i - 1], 2)) / 2;
			Vp[i] = (powf(R[i], 2) - powf(r[i], 2)) / 2;
		}
	}
}

void varConst(double* K, double* Cp, double* X) {
	int i;

	for (i = 0; i < 33; i++) {
		if (i < 30) {
			K[i] = 2.3 + 2.25 * powf(10, 5) / X[i] * exp(-12410 / X[i]);
			Cp[i] = 193.2 + 0.3257 * X[i] - 3.120 * powf(10, -4) * powf(X[i], 2) + 1.168 * powf(10, -7) * powf(X[i], 3) - 9.753 * powf(10, -12) * powf(X[i], 4) - 2.644 * powf(10, 6) * powf(X[i], -2);
		}
		else {
			K[i] = 12.767 - 5.4338 * powf(10, -4) * X[i] + 8.9818 * powf(10, -6) * powf(X[i], 2);
			Cp[i] = 255.66 + 0.1024 * X[i];
		}
	}
}

void makeMatrix(double** matrix, double* X, double* R, double* K, double* B, double* Vm, double* Vp) {
	int i;
	double expq, step;

	for (i = 0; i < 33; i++) {
		if (i == 0) {
			matrix[i][1] = K[i] * R[i] / h1;
			matrix[i][2] = -1 * K[i] * R[i] / h1;
			B[i] = q1 * Vp[i];
			continue;
		}
		if (i == 30) {
			matrix[i][0] = -1 * K[i - 1] * R[i - 1] / h1;
			matrix[i][1] = K[i - 1] * R[i - 1] / h1 + K[i] * R[i] / h2;
			matrix[i][2] = -1 * K[i] * R[i] / h2;
			B[i] = q1 * Vm[i] + q2 * Vp[i];
			continue;
		}
		if (i < 30) {
			expq = q1;
			step = h1;
		}
		else {
			expq = q2;
			step = h2;
		}
		matrix[i][0] = -1 * K[i - 1] * R[i - 1] / step;
		matrix[i][1] = (K[i - 1] * R[i - 1] + K[i] * R[i]) / step;
		matrix[i][2] = -1 * K[i] * R[i] / step;
		B[i] = expq * Vm[i] + expq * Vp[i];
	}
	matrix[0][0] = 0;
	matrix[32][2] = 0;
	B[32] += K[32] * R[32] / h2 * Tr;
}
void makeMatrix_time(double** matrix, double* X, double* T, double* R, double* K, double* K_PREV, double* Cp, double* Cp_PREV, double* B, double* Vm, double* Vp) {
	int i;
	double expq, expq_old, step, rho;

	for (i = 0; i < 33; i++) {
		//T_old = T, Cp_old = Cp, K_old = K, Rho는 그대로 
		if (i == 0) {
			matrix[i][1] = K[i] * R[i] / (2 * h1) + r1 * Cp[i] * Vp[i];
			matrix[i][2] = -1 * K[i] * R[i] / (2 * h1);
			B[i] = (q1_old + q1) *Vp[i] / 2 - ((K_PREV[i] * R[i] / (2 * h1)) - r1 * Cp_PREV[i] * Vp[i]) * T[i] + K_PREV[i] * R[i] / (2 * h1) * T[i + 1];
			continue;
		}
		if (i == 30) {
			matrix[i][0] = -K[i - 1] * R[i - 1] / (2 * h1);
			matrix[i][1] = K[i - 1] * R[i - 1] / (2 * h1) + K[i] * R[i] / (2 * h2) + Cp[i] * (r1 * Vm[i] + r2 * Vp[i]);
			matrix[i][2] = -K[i] * R[i] / (2 * h2);
			B[i] = ((q1_old + q1) * Vm[i] + q2 * Vp[i]) / 2 + K_PREV[i - 1] * R[i - 1] / (2 * h1) * T[i - 1] - ((K_PREV[i - 1] * R[i - 1] / (2 * h1)) + (K_PREV[i] * R[i] / (2 * h2)) - Cp_PREV[i] * (r1 * Vm[i] + r2 * Vp[i])) * T[i] + K_PREV[i] * R[i] / (2 * h2) * T[i + 1];
			continue;
		}
		if (i < 30) {
			expq = q1;
			expq_old = q1_old;
			step = h1;
			rho = r1;
		}
		else {
			expq = q2;
			expq_old = q2;
			step = h2;
			rho = r2;
		}
		matrix[i][0] = -K[i - 1] * R[i - 1] / (2 * step);
		matrix[i][1] = K[i - 1] * R[i - 1] / (2 * step) + K[i] * R[i] / (2 * step) + rho * Cp[i] * (Vm[i] + Vp[i]);
		matrix[i][2] = -K[i] * R[i] / (2 * step);
		B[i] = ((expq_old + expq) * Vm[i] + (expq_old + expq) * Vp[i]) / 2 + K_PREV[i - 1] * R[i - 1] / (2 * step) * T[i - 1] - ((K_PREV[i - 1] * R[i - 1] / (2 * step)) + (K_PREV[i] * R[i] / (2 * step)) - rho * Cp_PREV[i] * (Vm[i] + Vp[i])) * T[i] + K_PREV[i] * R[i] / (2 * step) * T[i + 1];
		if (i == 32) {
			B[i] = ((expq_old + expq) * Vm[i] + (expq_old + expq) * Vp[i]) / 2 + K_PREV[i - 1] * R[i - 1] / (2 * step) * T[i - 1] - ((K_PREV[i - 1] * R[i - 1] / (2 * step)) + (K_PREV[i] * R[i] / (2 * step)) - rho * Cp_PREV[i] * (Vm[i] + Vp[i])) * T[i] + K_PREV[i] * R[i] / (2 * step) * Tr + K[i] * R[i] / (2 * step) * Tr;
		}
	}
	matrix[0][0] = 0;
	matrix[32][2] = 0;
}

void jacobi_sequence(double** matrix, double* X, double* B, double* X_OLD) {
	int i;
	double temp;

	for (i = 0; i < 33; i++) {
		temp = matrix[i][0] * X_OLD[i - 1] + matrix[i][2] * X_OLD[i + 1];
		if (i == 0) {
			temp = matrix[i][2] * X_OLD[i + 1];
		}
		if (i == 32) {
			temp = matrix[i][0] * X_OLD[i - 1];
		}

		X[i] = (1 / matrix[i][1]) * (B[i] - temp);

	}
}

int main() {
	int i, j, count, flag = 0, time = 0;
	double err;

	double** matrix;
	double* B, * X, * X_OLD, * T, * K, *K_OLD, *K_PREV, * Cp, * Cp_OLD, *Cp_PREV, * R, * r, * Vm, * Vp;

	h1 = 0.413 * powf(10, -2) / 30;
	h2 = 0.635 * powf(10, -3) / 3;
	q1 = 300.0 * powf(10, 6), q2 = 0.0;
	q1_old = q1;
    q1_old_t = 100.0 * powf(10, 6);
	r1 = 10970, r2 = 6520;
	Tr = 310.0 + 273.0;

	matrix = (double**)malloc(sizeof(double*) * 33);
	for (i = 0; i < 33; i++) {
		matrix[i] = (double*)calloc(3, sizeof(double));
	}

	B = (double*)calloc(33, sizeof(double));
	X = (double*)calloc(33, sizeof(double));
	X_OLD = (double*)calloc(33, sizeof(double));
	T = (double*)calloc(33, sizeof(double));
	K = (double*)calloc(33, sizeof(double));
	K_OLD = (double*)calloc(33, sizeof(double));
	K_PREV = (double*)calloc(33, sizeof(double));
	Cp = (double*)calloc(33, sizeof(double));
	Cp_OLD = (double*)calloc(33, sizeof(double));
	Cp_PREV = (double*)calloc(33, sizeof(double));
	R = (double*)calloc(33, sizeof(double));
	r = (double*)calloc(33, sizeof(double));
	Vm = (double*)calloc(33, sizeof(double));
	Vp = (double*)calloc(33, sizeof(double));

	for (i = 0; i < 33; i++) {
		X[i] = 1.0;
		X_OLD[i] = 1.0;
	}

	initConst(R, r, Vp, Vm, B);

	count = 0;


	while (1) {
		flag = 0;

		varConst(K, Cp, X);

		makeMatrix(matrix, X, R, K, B, Vm, Vp);
		jacobi_sequence(matrix, X, B, X_OLD);
		for (j = 0; j < 33; j++) {
			err = (X[j] - X_OLD[j]) / X[j];
			if (err > MAX_ERR) {
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			for (j = 0; j < 33; j++) {
				X_OLD[j] = X[j];
			}
		}
		else {
			count++;
			break;
		}
		count++;
	}
	for (i = 0; i < 33; i++) {
		T[i] = X[i];
		K_PREV[i] = K[i];
		Cp_PREV[i] = Cp[i];
	}
	printf("------------------------------------------------------------------\n");
	printf("\nX vector at %d\n", time);
	for (i = 0; i < 33; i++) {
		printf("%.3f\n", X[i]);
	}
	
	for (i = 0; i < 15; i++) {
		time++;
		//matrix = (double**)malloc(sizeof(double*) * 33);
		//for (j = 0; j < 33; j++) {
		//	matrix[j] = (double*)calloc(3, sizeof(double));
		//}
		//B = (double*)calloc(33, sizeof(double));
		if (time == 5) {
			q1_old = q1_old_t;
		}
		if (time == 10) {
			q1_old = q1;
		}
		while (1) {
			flag = 0;
			for (j = 0; j < 33; j++) {
				K_OLD[j] = K[j];
				Cp_OLD[j] = Cp[j];
			}
			varConst(K, Cp, X);

			makeMatrix_time(matrix, X, T, R, K, K_PREV, Cp, Cp_PREV, B, Vm, Vp);
			jacobi_sequence(matrix, X, B, X_OLD);
			for (j = 0; j < 33; j++) {
				err = (X[j] - X_OLD[j]) / X[j];
				if (err > MAX_ERR) {
					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				for (j = 0; j < 33; j++) {
					X_OLD[j] = X[j];
				}
			}
			else {
				count++;
				break;
			}
			count++;
		}

		for (j = 0; j < 33; j++) {
			T[j] = X[j];
			K_PREV[j] = K[j];
			Cp_PREV[j] = Cp[j];
		}

		printf("------------------------------------------------------------------\n");
		printf("\nX vector at %d\n", time);
		for (j = 0; j < 33; j++) {
			printf("%.3f\n", X[j]);
		}
	}
	printf("\n%d iteration\n", count);

}