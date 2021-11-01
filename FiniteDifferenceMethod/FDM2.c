#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ERR 0.00001

void 

void jacobi_sequence(double** matrix, double* X, double* B, double* X_OLD) {
    int i, j, k;
    double temp, temp2;

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
    double h1 = 0.413 * 10 ^ -2 / 30, h2 = 0.635 * 10 ^ -3;
    //double k[i] = 2.3 + 2.25 * 10^5 / T[i] * exp(-12410 / T[i]) /* 0~29*/ , k2[i] = 12.767 - 5.4348 * 10^-4 * T[i] - 8.9818 * 10^-6 * T[i]^2 ;/* 30~32*/ => 어떻게 구현할지 (T를 구해야하는데 T가 식에 포함됨)  
    double q1 = 300 * 10 ^ 6, q2 = 0;
    double Tr = 310.0;
    //double r[i] = h1 / 2 + h1 * i, /* 0~29*/ r[i] = h1 / 2 + h1 * 29 + h2 * [i-29]; /* 30~32*/
    //double v[0] = r[0]^2 / 2, v[i] = (r[i]^2 - r[i-1]^2) / 2;
    double exp, expq, step, err;

    double** matrix;
    double* B, * X, * X_OLD;

    matrix = (double**)malloc(sizeof(double*) * 33);
    for (i = 0; i < 33; i++) {
        matrix[i] = (double*)calloc(3, sizeof(double));
    }

    B = (double*)calloc(33, sizeof(double));
    X = (double*)calloc(33, sizeof(double));
    X_OLD = (double*)calloc(33, sizeof(double));

    for (i = 0; i < 33; i++) {
        if (i == 0) {
            matrix[i][1] = k1 / h1;
            matrix[i][2] = -1 * k1 / h1;
            continue;
        }
        if (i == 30) {
            matrix[i][0] = -1 * k2 / h2;
            matrix[i][1] = (k1 / h1 + k2 / h2);
            matrix[i][2] = -1 * k1 / h1;
            B[i] = (q1 * v[i - 1]) / 2 + q2 * ((r[i] ^ 2 - (r[i - 1] - h1) ^ 2) / 2) / 2;
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
        matrix[i][0] = -1 * k[i - 1] * r[i - 1] / step;
        matrix[i][1] = k[i - 1] * r[i - 1] + k[i] * r[i] / step;
        matrix[i][2] = -1 * k[i] * r[i] / step;
        B[i] = expq * v[i];
    }
    matrix[0][0] = 0;
    matrix[33][2] = 0;
    B[32] += k[32] * r[32] / h2 * Tr;

    for (i = 0; i < 33; i++) {
            for (j = 0; j < 3; j++) {
                printf("%.3f ", matrix[i][j]);
            }
        printf("\n");
    }

    printf("\nB vector\n");
    for (i = 0; i < 33; i++) {
        printf("%.3f\n", B[i]);
    }

    i = 0;
    while (1) {
        flag = 0;
        jacobi_sequence(matrix, X, B, X_OLD);
        for (j = 0; j < 33; j++) {
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
