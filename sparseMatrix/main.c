#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>


#define MAX_SIZE 100

int rowSize, colSize, vSize, nonZero;
double min = INT_MAX, max = INT_MIN;
int minIdx, maxIdx;

int* createMatrix();
void initMatrix(double*, int*);
void setX(FILE*, double*);
void setMatrix(FILE*, double*, int*);
void mmult(double*, double*, int*, double*);

int main() {
	FILE* fa, * fx, * output1, * output2;
	int* ja;
	double* aa, * x, * result;
	int i;
	double norm = 0.0;

	fa = fopen("MatrixA.txt", "r+");
	fx = fopen("VectorX.txt", "r+");
	output1 = fopen("out.txt", "w+");
	output2 = fopen("out_norm.txt", "w+");

	// A 행렬의 row, column, nonZero 갯수 입력
	fscanf(fa, "%d %d %d", &rowSize, &colSize, &nonZero);

	// nonZero+1 크기의 AA, JA 배열 동적할당(+1 -> 0 index 사용 x)
	aa = (double*)calloc(nonZero + 1, sizeof(double));
	ja = (int*)calloc(nonZero + 1, sizeof(int));

	// AA, JA 배열 구성
	setMatrix(fa, aa, ja);

	// X 벡터의 크기 입력 = A 행렬의 column 길이와 동일
	fscanf(fx, "%d", &vSize);
	// colSize+1 크기의 X 배열 동적할당(+1 -> 0 index 사용 x)
	x = (double*)calloc(colSize + 1, sizeof(double));

	// X 배열 구성
	setX(fx, x);

	printf("input finished\n");

	// 행렬 곱 결과를 담을 벡터 배열 생성(X와 동일한 A 행렬 column 길이 + 1)
	result = (double*)calloc(colSize + 1, sizeof(double));

	mmult(result, aa, ja, x);
	
	printf("multiplication finished\n");

	// index 1부터 파일에 출력
	for (i = 1; i < colSize; i++) {
		fprintf(output1, "%e\n", result[i]);
	}

	// element 제곱의 합 연산
	for (i = 1; i < colSize; i++) {
		norm += powf(result[i], 2);
	}

	// norm 계산
	norm = sqrtf(norm);

	printf("norm : %e\n", norm);

	for (i = 1; i < colSize; i++) {
		fprintf(output2, "%e\n", result[i] / norm);
	}

	if (max > -1 * min) {
		printf("절대값 최대 : %e\n", result[maxIdx] / norm);
	}
	else {
		printf("절대값 최대 : %e\n", result[minIdx] / norm);
	}

	printf("finished\n");

	return 0;
}

int* createMatrix() {
	int i, j;
	int* temp;
	int matSIze = nonZero + 1;

	temp = (int*)calloc(matSIze, sizeof(int));

	return temp;
}

void initMatrix(double* AA, int* JA) {
	//대각행렬 갯수 자리에 *
	AA[rowSize + 1] = 0;
	//* 아래자리 위치 정보가 행렬 크기 index
	JA[rowSize + 1] = nonZero + 2;
}

void setX(FILE* fx, double* X) {
	int i;
	int row, col;
	double val;

	for (i = 0; i < vSize; i++) {
		fscanf(fx, "%d %d %lf", &row, &col, &val);

		X[row] = val;
	}
}

void setMatrix(FILE* fa, double* AA, int* JA) {
	int i;
	// t : 대각성분 저장 시작점, s : 나머지 희소성분 저장 시작점
	int t = 1, s = colSize + 2;
	int row, col;
	double val;
	int size = nonZero + 1;


	initMatrix(AA, JA);

	for (i = 0; i < nonZero; i++) {
		fscanf(fa, "%d %d %lf", &row, &col, &val);

		// row == col일 경우 대각성분을 먼저 1부터 저장
		if (row == col) {
			AA[t] = val;
			t++;
		}
		// row != col일 경우 성분을 colSize + 2부터 저장
		else {
			// 행 자리의 index에 처음 접근했을 경우 한번만 시작점을 기록
			if (JA[row] == 0)
				JA[row] = s;
			// s index에 column 정보 기록
			JA[s] = col;
			// AA 배열 동일 위치에 값 기록
			AA[s] = val;
			s++;
		}
	}
}

void mmult(double* Y, double* AA, int* JA, double* X) {
	int i, j, k;
	long double temp;

	for (i = 1; i < rowSize + 1; i++) {
		// 대각성분과 X 벡터의 i index 곱
		temp = AA[i] * X[i];
		
		// 나머지 성분과 X 벡터의 곱의 합
		for (k = JA[i]; k < JA[i + 1]; k++) {
			// j : A 행렬의 해당 원소 column 정보
			j = JA[k];
			temp += AA[k] * X[j];
		}
		Y[i] = temp;

		// min, max값과 index를 기록하여 최대 절대값 정보 구할 때 사용
		if (Y[i] < min) {
			min = Y[i];
			minIdx = i;
		}
		if (Y[i] > max) {
			max = Y[i];
			maxIdx = i;
		}
	}
}