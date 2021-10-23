#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#include "header.h"

int main() {
	FILE* fa, * fx, * output1, * output2;
	int i;
	int rowSize = NULL, colSize = NULL, nonZero = NULL, vSize = NULL, minIdx = NULL, maxIdx = NULL;
	double min = INT_MAX, max = INT_MIN, norm = 0.0;
	matrixForm* matrixSet = NULL;
	vectorForm* X = NULL, * result = NULL;

	fa = fopen("testA.txt", "r+");
	fx = fopen("testB.txt", "r+");
	output1 = fopen("out.txt", "w+");
	output2 = fopen("out_norm.txt", "w+");

	// AA, JA �迭 ����
	matrixSet = setMatrix(fa, &rowSize, &colSize, &nonZero);

	// X �迭 ����
	X = setVector(fx, &vSize, colSize);

	// ��� �� ����� ���� ���� �迭 ����(X�� ������ A ��� column ���� + 1)
	if (!(result = (vectorForm*)malloc(sizeof(vectorForm)))) {
		fprintf(stderr, "allocation error\n");
		exit(1);
	}
	// colSize+1 ũ���� X �迭 �����Ҵ�(+1 -> 0 index ��� x)
	if (!(result->val = (double*)calloc(colSize + 1, sizeof(double)))) {
		fprintf(stderr, "allocation error\n");
		exit(1);
	}

	mmult(matrixSet, result, X, rowSize, &minIdx, &maxIdx, &min, &min);

	// index 1���� ����� ���Ͽ� ���
	for (i = 1; i <= colSize; i++) {
		fprintf(output1, "%e\n", result->val[i]);
	}

	// norm ����
	norm = normEval(result, colSize);

	printf("norm : %e\n", norm);

	// index 1���� ����ȭ�� ����� ���Ͽ� ���
	for (i = 1; i <= colSize; i++) {
		fprintf(output2, "%e\n", result->val[i] / norm);
	}

	if (max > -1 * min) {
		printf("����ȭ ���밪 �ִ� : %e\n", result->val[maxIdx] / norm);
	}
	else {
		printf("����ȭ ���밪 �ּ� : %e\n", result->val[minIdx] / norm);
	}

	return 0;
}