#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101
#define MAX_EXP 100

#define COMPARE(x,y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

void padd(int, int, int, int, int*, int*);
void attach(float, int);

typedef struct poly {
	float coef;
	int exp;
}poly;

poly terms[MAX_TERMS];
int avail = 0;
int startA, startB, finishA, finishB;
int startD = 0, finishD = 0;

int main() {
	FILE* A, * B, * C;
	int i, n;

	A = fopen("a.txt", "r");
	B = fopen("b.txt", "r");
	C = fopen("c.txt", "w+");

	for (i = 0; i < MAX_TERMS; i++) {
		terms[i].coef = 0;
		terms[i].exp = 0;
	}

	// A polynomial의 항 갯수 = finishA = start + n - 1
	// 동일한 term 배열에 A, B를 저장할 것이므로 총 길이 avail을 저장
	startA = 0;
	fscanf(A, "%d", &n);
	finishA = startA + n - 1;
	for (i = 0; i < n; i++) {
		fscanf(A, "%f %d", &terms[i].coef, &terms[i].exp);
		if (terms[i].exp < 0 || terms[i].exp > MAX_EXP) {
			return 0;
		}
		avail++;
	}

	// B polynomial의 term 배열에서의 시작 위치 startB = finishA + 1
	// B polynomial의 항 갯수 = finishB = startB + n - 1
	// 동일한 term 배열에 A, B를 저장할 것이므로 총 길이 avail을 저장
	startB = finishA + 1;
	fscanf(B, "%d", &n);
	finishB = startB + n - 1;
	for (i = startB; i < startB + n; i++) {
		fscanf(B, "%f %d", &terms[i].coef, &terms[i].exp);
		if (terms[i].exp < 0 || terms[i].exp > MAX_EXP) {
			return 0;
		}
		avail++;
	}

	// 두 다항식을 더하기 위해 각 다항식 항의 시작/끝 위치를 전달하고 계산 결과를 저장할 새로운 다항식의 항 시작/끝 위치를 포인터로 전달
	padd(startA, finishA, startB, finishB, &startD, &finishD);

	fprintf(C, "%d ", finishD - startD + 1);
	for (i = startD; i < finishD + 1; i++) {
		fprintf(C, "%f %d ", terms[i].coef, terms[i].exp);
	}

	fclose(A);
	fclose(B);
	fclose(C);
}

void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD) {
	float coef;
	// 더해진 새로운 다항식의 시작위치는 avail임
	*startD = avail;

	// 두 다항식 끝 위치까지 모두 검사하지 않았을 경우 계속 검사
	while (startA <= finishA && startB <= finishB) {
		switch (COMPARE(terms[startA].exp, terms[startB].exp)) {
		case -1:
			// A항 < B항
			attach(terms[startB].coef, terms[startB].exp);
			startB++;
			break;
		case 0:
			// A항 = B항
			// 이 경우, 두 항의 coefficient를 더해서 attach
			coef = terms[startA].coef + terms[startB].coef;
			if (coef)
				attach(coef, terms[startA].exp);
			startA++;
			startB++;
			break;
		case 1:
			// A항 > B항
			attach(terms[startA].coef, terms[startA].exp);
			startA++;
		}
	}

	// 한 다항식을 모두 attach했을 떄, 남은 다른 다항식을 모두 뒤에 attach 
	for (; startA <= finishA; startA++) {
		attach(terms[startA].coef, terms[startA].exp);
	}
	for (; startB <= finishB; startB++) {
		attach(terms[startB].coef, terms[startB].exp);
	}
	// 새로운 다항식의 최종 끝 길이
	*finishD = avail - 1;
}

void attach(float coef, int exp) {
	if (avail >= MAX_TERMS) {
		fprintf(stderr, "too many terms in the polynomial\n");
		exit(EXIT_FAILURE);
	}
	terms[avail].coef = coef;
	terms[avail].exp = exp;
	avail++;
}