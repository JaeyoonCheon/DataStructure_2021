#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

int** transpose(int**, int, int);
int** mMult(int**, int**, int, int);

int main() {
	FILE* M1, * M2;
	int m1x, m1y, m2x, m2y;
	int i, j;
	int** arr1, ** arr2, **newarr;

	printf("컴퓨터학부 2016115430 천재윤\n");

	M1 = fopen("m1.txt", "r");
	M2 = fopen("m2.txt", "r");

	fscanf(M1, "%d %d", &m1x, &m1y);
	fscanf(M2, "%d %d", &m2x, &m2y);

	arr1 = (int**)malloc(sizeof(int*) * m1x);
	for (i = 0; i < m1x; i++) {
		arr1[i] = (int*)malloc(sizeof(int) * m1y);
	}
	arr2 = (int**)malloc(sizeof(int*) * m2x);
	for (i = 0; i < m2x; i++) {
		arr2[i] = (int*)malloc(sizeof(int) * m2y);
	}

	for (i = 0; i < m1x; i++) {
		for (j = 0; j < m1y; j++) {
			fscanf(M1, "%d", &arr1[i][j]);
		}
	}
	for (i = 0; i < m2x; i++) {
		for (j = 0; j < m2y; j++) {
			fscanf(M2, "%d", &arr2[i][j]);
		}
	}

	newarr = mMult(arr1, arr2, m1x, m1y, m2x, m2y);

	for (i = 0; i < m1x; i++) {
		free(arr1[i]);
	}
	free(arr1);

	for (i = 0; i < m2x; i++) {
		free(arr2[i]);
	}
	free(arr2);
}

int** transpose(int** arr, int x, int y) {
	int i, j;
	int** newMatrix;

	newMatrix = (int**)malloc(sizeof(int*) * y);
	for (i = 0; i < y; i++) {
		newMatrix[i] = (int*)malloc(sizeof(int) * x);
	}

	for (i = 0; i < x; i++) {
		for (j = 0; j < y; j++) {
			newMatrix[i][j] = arr[j][i];
		}
	}

	return newMatrix;
}

int** mMult(int** arr1, int** arr2, int m1x, int m1y, int m2x, int m2y) {
	int i, j, k, sum = 0;
	int** newMatrix;

	newMatrix = (int**)malloc(sizeof(int*) * m1x);
	for (i = 0; i < m1x; i++) {
		newMatrix[i] = (int*)malloc(sizeof(int) * m2y);
	}

	printf("%d %d\n", m1x, m2y);

	for (i = 0; i < m1x; i++) {
		for (j = 0; j < m2y; j++) {
			for (k = 0; k < m2x; k++) {
				sum += arr1[i][k] * arr2[k][j];
				// sum += arr1[i][k] * arr2[j][k]; transpose했을 경우
			}
			newMatrix[i][j] = sum;
			sum = 0;
			printf("%d ", newMatrix[i][j]);
		}
		printf("\n");
	}
}