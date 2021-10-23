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

	// X 벡터의 크기 입력 = A 행렬의 column 길이와 동일
	if (!fscanf(fp, "%d", &vSize)) {
		fprintf(stderr, "reading error\n");
		exit(1);
	}

	if (!(vector = (vectorForm*)malloc(sizeof(vectorForm)))) {
		fprintf(stderr, "allocation error\n");
		exit(1);
	}

	// colSize+1 크기의 X 배열 동적할당(+1 -> 0 index 사용 x)
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
	// t : 대각성분 저장 시작점, s : 나머지 희소성분 저장 시작점
	int i;
	int row, col;
	double val;
	int t = 1, s = *colSize + 2;
	int size = *nonZero + 1;
	matrixForm* matrixSet;

	// A 행렬의 row, column, nonZero 갯수 입력
	if (!fscanf(fp, "%d %d %d", rowSize, colSize, nonZero)) {
		fprintf(stderr, "reading error\n");
		exit(1);
	}

	if (!(matrixSet = (matrixForm*)malloc(sizeof(matrixForm)))) {
		fprintf(stderr, "allocation error\n");
		exit(1);
	}

	// nonZero+1 크기의 AA, JA 배열 동적할당(+1 -> 0 index 사용 x)
	if (!(matrixSet->aa = (double*)calloc(*nonZero + 1, sizeof(double)))) {
		fprintf(stderr, "allocation error\n");
		exit(1);
	}
	if (!(matrixSet->ja = (double*)calloc(*nonZero + 1, sizeof(double)))) {
		fprintf(stderr, "allocation error\n");
		exit(1);
	}

	//대각행렬 갯수 자리에 *
	matrixSet->aa[*rowSize + 1] = 0;
	//* 아래자리 위치 정보가 행렬 크기 index
	matrixSet->ja[*rowSize + 1] = *nonZero + 2;

	for (i = 0; i < *nonZero; i++) {
		if (!fscanf(fp, "%d %d %lf", &row, &col, &val)) {
			fprintf(stderr, "read error!\n");
			exit(1);
		}

		// row == col일 경우 대각성분을 먼저 1부터 저장
		if (row == col) {
			matrixSet->aa[t] = val;
			t++;
		}
		// row != col일 경우 성분을 colSize + 2부터 저장
		else {
			// 행 자리의 index에 처음 접근했을 경우 한번만 시작점을 기록
			if (matrixSet->ja[row] == 0)
				matrixSet->ja[row] = s;
			// s index에 column 정보 기록
			matrixSet->ja[s] = col;
			// AA 배열 동일 위치에 값 기록
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
		// 대각성분과 X 벡터의 i index 곱
		temp = matrixSet->aa[i] * X->val[i];

		// 나머지 성분과 X 벡터의 곱의 합
		for (k = matrixSet->ja[i]; k < matrixSet->ja[i + 1]; k++) {
			// j : A 행렬의 해당 원소 column 정보
			j = matrixSet->ja[k];
			temp += matrixSet->aa[k] * X->val[j];
		}
		Y->val[i] = temp;

		// min, max값과 index를 기록하여 최대 절대값 정보 구할 때 사용
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

	// norm 계산
	norm = sqrtf(norm);
}