#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* M1, * M2;
	int m1x, m1y, m2x, m2y;
	int i, j;
	int** arr1, ** arr2;
	
	printf("ÄÄÇªÅÍÇÐºÎ 2016115430 ÃµÀçÀ±\n");

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
			fscanf(M2, "%d", &arr2[i][j]);
			arr1[i][j] += arr2[i][j];
			printf("%d ", arr1[i][j]);
		}
		printf("\n");
	}

	for (i = 0; i < m1x; i++) {
		free(arr1[i]);
	}
	free(arr1);
	
	for (i = 0; i < m2x; i++) {
		free(arr2[i]);
	}
	free(arr2);
}