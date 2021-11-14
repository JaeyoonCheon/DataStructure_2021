#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ERR 0.00001

double h1, h2, q1, q2, Tr;

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

void kConst(double* K, double* X) {
    int i;

    for (i = 0; i < 33; i++) {
        if (i < 30) {
            K[i] = 2.3 + 2.25 * powf(10, 5) / X[i] * exp(-12410 / X[i]);
        }
        else {
            K[i] = 12.767 - 5.4338 * powf(10, -4) * X[i] + 8.9818 * powf(10, -6) * powf(X[i], 2);
        }
    }
    K[33] = 12.767 - 5.4338 * powf(10, -4) * (310.0 + 273.0) + 8.9818 * powf(10, -6) * powf((310.0 + 273.0), 2);
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
            matrix[i][0] = -1 * (K[i - 1] + K[i]) / 2 * R[i - 1] / h1;
            matrix[i][1] = ((K[i - 1] + K[i]) / 2 * R[i - 1] / h1 + (K[i] + K[i + 1]) / 2 * R[i] / h2);
            matrix[i][2] = -1 * (K[i] + K[i + 1]) / 2 * R[i] / h2;
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
        matrix[i][0] = -1 * (K[i - 1] + K[i]) / 2 * R[i - 1] / step;
        matrix[i][1] = ((K[i - 1] + K[i]) / 2 * R[i - 1] + (K[i] + K[i + 1]) / 2 * R[i]) / step;
        matrix[i][2] = -1 * (K[i] + K[i + 1]) / 2 * R[i] / step;
        B[i] = expq * Vm[i] + expq * Vp[i];
    }
    matrix[0][0] = 0;
    matrix[32][2] = 0;
    B[32] += (K[32] + K[33]) / 2 * R[32] / h2 * Tr;
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
    int i, j, flag = 0;
    double err;

    double** matrix;
    double* B, * X, * K, * R, * r, * Vm, * Vp, * X_OLD;

    h1 = 0.413 * powf(10, -2) / 30;
    h2 = 0.635 * powf(10, -3) / 3;
    q1 = 300.0 * powf(10, 6), q2 = 0.0;
    Tr = 310.0 + 273.0;

    matrix = (double**)malloc(sizeof(double*) * 33);
    for (i = 0; i < 33; i++) {
        matrix[i] = (double*)calloc(3, sizeof(double));
    }

    B = (double*)calloc(33, sizeof(double));
    X = (double*)calloc(33, sizeof(double));
    X_OLD = (double*)calloc(33, sizeof(double));
    K = (double*)calloc(33, sizeof(double));
    R = (double*)calloc(33, sizeof(double));
    r = (double*)calloc(33, sizeof(double));
    Vm = (double*)calloc(33, sizeof(double));
    Vp = (double*)calloc(33, sizeof(double));

    for (i = 0; i < 33; i++) {
        X[i] = 1.0;
        X_OLD[i] = 1.0;
    }

    initConst(R, r, Vp, Vm, B);

    i = 0;
    while (1) {
        flag = 0;
        kConst(K, X);
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
            i++;
            break;
        }
        i++;
    }

    for (i = 0; i < 33; i++) {
        for (j = 0; j < 3; j++) {
            printf("%.3f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\nR vector\n");
    for (i = 0; i < 33; i++) {
        printf("%.8f\n", R[i]);
    }
    printf("\nB vector\n");
    for (i = 0; i < 33; i++) {
        printf("%.3f\n", B[i]);
    }

    printf("\n%d iteration\n", i);

    printf("\nX vector\n");
    for (i = 0; i < 33; i++) {
        printf("%.3f\n", X[i]);
    }
}