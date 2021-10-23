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

	// AA, JA 배열 구성
	matrixSet = setMatrix(fa, &rowSize, &colSize, &nonZero);

	// X 배열 구성
	X = setVector(fx, &vSize, colSize);

	// 행렬 곱 결과를 담을 벡터 배열 생성(X와 동일한 A 행렬 column 길이 + 1)
	if (!(result = (vectorForm*)malloc(sizeof(vectorForm)))) {
		fprintf(stderr, "allocation error\n");
		exit(1);
	}
	// colSize+1 크기의 X 배열 동적할당(+1 -> 0 index 사용 x)
	if (!(result->val = (double*)calloc(colSize + 1, sizeof(double)))) {
		fprintf(stderr, "allocation error\n");
		exit(1);
	}

	mmult(matrixSet, result, X, rowSize, &minIdx, &maxIdx, &min, &min);

	// index 1부터 결과를 파일에 출력
	for (i = 1; i <= colSize; i++) {
		fprintf(output1, "%e\n", result->val[i]);
	}

	// norm 연산
	norm = normEval(result, colSize);

	printf("norm : %e\n", norm);

	// index 1부터 정규화된 결과를 파일에 출력
	for (i = 1; i <= colSize; i++) {
		fprintf(output2, "%e\n", result->val[i] / norm);
	}

	if (max > -1 * min) {
		printf("정규화 절대값 최대 : %e\n", result->val[maxIdx] / norm);
	}
	else {
		printf("정규화 절대값 최소 : %e\n", result->val[minIdx] / norm);
	}

	return 0;
}