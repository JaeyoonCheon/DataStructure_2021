#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#include "header.h"

int main() {
	FILE* fa, * fx, *fw, * output1, * output2;
	int i, j, n;
	int rowSize = NULL, colSize = NULL, nonZero = NULL, vSize = NULL, minIdx = NULL, maxIdx = NULL;
	double temp1, temp2, temp3 = 1, min = INT_MAX, max = INT_MIN, lambda = 1.0, lambda_old, norm = 0.0;
	matrixForm* matrixSet = NULL;
	vectorForm* X = NULL, *W = NULL, *X_OLD = NULL, * result = NULL;

	//fa = fopen("8x8A.txt", "r+");
	//fx = fopen("8X.txt", "r+");
	//fw = fopen("8W.txt", "r+");
	fa = fopen("MatrixA.txt", "r+");
	fx = fopen("VectorX.txt", "r+");
	fw = fopen("VectorW.txt", "r+");
	output1 = fopen("out.txt", "w+");
	output2 = fopen("out_norm.txt", "w+");

	// AA, JA 배열 구성
	matrixSet = setMatrix(fa, &rowSize, &colSize, &nonZero);

	// X 배열 구성
	X = setVector(fx, &vSize, colSize);
	W = setVector(fw, &vSize, colSize);

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

	if (!(X_OLD = (vectorForm*)malloc(sizeof(vectorForm)))) {
		fprintf(stderr, "allocation error\n");
		exit(1);
	}
	if (!(X_OLD->val = (double*)calloc(colSize + 1, sizeof(double)))) {
		fprintf(stderr, "allocation error\n");
		exit(1);
	}

	for (i = 0; i <= vSize; i++) {
		X_OLD->val[i] = X->val[i];
	}

	printf("iteration n : ");
	if (!scanf("%d", &n)) {
		fprintf(stderr, "reading error\n");
		exit(1);
	}

	for (i = 0; i < n; i++) {
		mmult(matrixSet, result, X, rowSize, &minIdx, &maxIdx, &min, &min);
		temp1 = 0.0;
		temp2 = 0.0;

		for (j = 1; j <= vSize; j++) {
			X_OLD->val[j] = X->val[j];

			X->val[j] = 1 / lambda * result->val[j];
			temp1 += W->val[j] * X->val[j];
			temp2 += W->val[j] * X_OLD->val[j];
		}
		lambda = lambda * temp1 / temp2;
	}

	//for (i = 0; temp3 > powf(10, -3); i++) {
	//	mmult(matrixSet, result, X, rowSize, &minIdx, &maxIdx, &min, &min);
	//	norm = normEval(X, vSize);
	//	
	//	
	//	temp1 = 0.0;
	//	temp3 = 0.0;
	//	lambda = 0.0;

	//	for (j = 1; j <= vSize; j++) {
	//		//temp1 = W->val[j] * X->val[j];
	//		//temp2 = W->val[j] * X_OLD->val[j];
	//		//lambda = lambda * temp1 / temp2;
	//		temp1 = result->val[j];
	//		if (lambda < temp1) {
	//			lambda = temp1;
	//		}
	//	}
	//	for (j = 1; j <= vSize; j++) {
	//		result->val[j] = result->val[j] / lambda;
	//		if (temp3 < fabs(result->val[j] - X->val[j])) {
	//			temp3 = fabs(result->val[j] - X->val[j]);
	//		}
	//	}
	//	for (j = 0; j <= vSize; j++) {
	//		X->val[j] = result->val[j];
	//	}
	//}

	printf("iteration %d, lambda : %e\n", i, lambda);

	return 0;
}