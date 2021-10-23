#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#include "header.h"

vectorForm* setVector(FILE* fp, int *vSize, int colSize) {
	int i;
	int row;
	double val;
	vectorForm* vector;

	// X ������ ũ�� �Է� = A ����� column ���̿� ����
	if (!fscanf(fp, "%d", &vSize)) {
		fprintf(stderr, "reading error\n");
		exit(1);
	}

	if (!(vector = (vectorForm*)malloc(sizeof(vectorForm)))) {
		fprintf(stderr, "allocation error\n");
		exit(1);
	}

	// colSize+1 ũ���� X �迭 �����Ҵ�(+1 -> 0 index ��� x)
	if (!(vector->val = (double*)calloc(colSize + 1, sizeof(double)))) {
		fprintf(stderr, "allocation error\n");
		exit(1);
	}

	for (i = 0; i < vSize; i++) {
		if (!fscanf(fp, "%d %lf", &row, &val)) {
			fprintf(stderr, "read error!\n");
			exit(1);
		}
		if (row < i) {
			fseek(fp, -13, SEEK_CUR);
			continue;
		}
		vector->val[row] = val;
	}
	return vector;
}

matrixForm* setMatrix(FILE* fp, int *rowSize, int *colSize, int *nonZero) {
	// t : �밢���� ���� ������, s : ������ ��Ҽ��� ���� ������
	int i;
	int row, col;
	double val;
	int t = 1, s = *colSize + 2;
	int size = *nonZero + 1;
	matrixForm* matrixSet;

	// A ����� row, column, nonZero ���� �Է�
	if (!fscanf(fp, "%d %d %d", rowSize, colSize, nonZero)) {
		fprintf(stderr, "reading error\n");
		exit(1);
	}

	if (!(matrixSet = (matrixForm*)malloc(sizeof(matrixForm)))) {
		fprintf(stderr, "allocation error\n");
		exit(1);
	}

	// nonZero+1 ũ���� AA, JA �迭 �����Ҵ�(+1 -> 0 index ��� x)
	if (!(matrixSet->aa = (double*)calloc(*nonZero + 1, sizeof(double)))) {
		fprintf(stderr, "allocation error\n");
		exit(1);
	}
	if (!(matrixSet->ja = (double*)calloc(*nonZero + 1, sizeof(double)))) {
		fprintf(stderr, "allocation error\n");
		exit(1);
	}

	//�밢��� ���� �ڸ��� *
	matrixSet->aa[*rowSize + 1] = 0;
	//* �Ʒ��ڸ� ��ġ ������ ��� ũ�� index
	matrixSet->ja[*rowSize + 1] = *nonZero + 2;

	for (i = 0; i < *nonZero; i++) {
		if (!fscanf(fp, "%d %d %lf", &row, &col, &val)) {
			fprintf(stderr, "read error!\n");
			exit(1);
		}

		// row == col�� ��� �밢������ ���� 1���� ����
		if (row == col) {
			matrixSet->aa[t] = val;
			t++;
		}
		// row != col�� ��� ������ colSize + 2���� ����
		else {
			// �� �ڸ��� index�� ó�� �������� ��� �ѹ��� �������� ���
			if (matrixSet->ja[row] == 0)
				matrixSet->ja[row] = s;
			// s index�� column ���� ���
			matrixSet->ja[s] = col;
			// AA �迭 ���� ��ġ�� �� ���
			matrixSet->aa[s] = val;
			s++;
		}
	}
	return matrixSet;
}

void mmult(matrixForm *matrixSet, vectorForm* Y, vectorForm* X, int rowSize, int* minIdx, int* maxIdx, int* min, int* max) {
	int i, j, k;
	double temp;

	for (i = 1; i < rowSize + 1; i++) {
		// �밢���а� X ������ i index ��
		temp = matrixSet->aa[i] * X->val[i];

		// ������ ���а� X ������ ���� ��
		for (k = matrixSet->ja[i]; k < matrixSet->ja[i + 1]; k++) {
			// j : A ����� �ش� ���� column ����
			j = matrixSet->ja[k];
			temp += matrixSet->aa[k] * X->val[j];
		}
		Y->val[i] = temp;

		// min, max���� index�� ����Ͽ� �ִ� ���밪 ���� ���� �� ���
		if (Y->val[i] < *min) {
			*min = Y->val[i];
			*minIdx = i;
		}
		if (Y->val[i] > *max) {
			*max = Y->val[i];
			*maxIdx = i;
		}
	}
}

int normEval(vectorForm* vector, int colSize) {
	int i, norm = 0;
	for (i = 1; i <= colSize; i++) {
		norm += powf(vector->val[i], 2);
	}

	// norm ���
	norm = sqrtf(norm);
}