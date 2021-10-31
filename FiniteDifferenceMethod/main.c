#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ERR 0.00001

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

int main() {
    int i, j, flag = 0;
    double h1 = 0.01, h2 = 0.04;
    double k1 = 20.0, k2 = 3.0;
    double q1 = 0.0, q2 = 1.5;
    double Tl = 20.0, Tr = 30.0;
    double exp, expq, step, err;

    double** matrix;
    double* B, * X, * X_OLD;

    matrix = (double**)malloc(sizeof(double*) * 69);
    for (i = 0; i < 69; i++) {
        matrix[i] = (double*)calloc(3, sizeof(double));
    }

    B = (double*)calloc(69, sizeof(double));
    X = (double*)calloc(69, sizeof(double));
    X_OLD = (double*)calloc(69, sizeof(double));

    for (i = 0; i < 69; i++) {
        if (i == 4) {
            matrix[i][0] = -1 * k1 / h1;
            matrix[i][1] = (k1 / h1 + k2 / h2);
            matrix[i][2] = -1 * k2 / h2;
            B[i] = (q1 * h1 + q2 * h2) / 2;
            continue;
        }
        if (i == 64) {
            matrix[i][0] = -1 * k2 / h2;
            matrix[i][1] = (k1 / h1 + k2 / h2);
            matrix[i][2] = -1 * k1 / h1;
            B[i] = (q1 * h1 + q2 * h2) / 2;
            continue;
        }
        if (i < 5 || i>63) {
            exp = k1;
            expq = q1;
            step = h1;
        }
        else {
            exp = k2;
            expq = q2;
            step = h2;
        }
        matrix[i][0] = -1 * exp / step;
        matrix[i][1] = 2 * exp / step;
        matrix[i][2] = -1 * exp / step;
        B[i] = expq * step;
    }
    matrix[0][0] = 0;
    matrix[68][2] = 0;
    B[0] += k1 / h1 * Tl;
    B[68] += k1 / h1 * Tr;

    for (i = 0; i < 69; i++) {
        for (j = 0; j < 3; j++) {
            printf("%.3f ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nB vector\n");
    for (i = 0; i < 69; i++) {
        printf("%.3f\n", B[i]);
    }

    i = 0;
    while(1) {
        flag = 0;
        jacobi_sequence(matrix, X, B, X_OLD);
        for (j = 0; j < 69; j++) {
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