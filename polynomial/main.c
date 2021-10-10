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

	// A polynomial�� �� ���� = finishA = start + n - 1
	// ������ term �迭�� A, B�� ������ ���̹Ƿ� �� ���� avail�� ����
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

	// B polynomial�� term �迭������ ���� ��ġ startB = finishA + 1
	// B polynomial�� �� ���� = finishB = startB + n - 1
	// ������ term �迭�� A, B�� ������ ���̹Ƿ� �� ���� avail�� ����
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

	// �� ���׽��� ���ϱ� ���� �� ���׽� ���� ����/�� ��ġ�� �����ϰ� ��� ����� ������ ���ο� ���׽��� �� ����/�� ��ġ�� �����ͷ� ����
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
	// ������ ���ο� ���׽��� ������ġ�� avail��
	*startD = avail;

	// �� ���׽� �� ��ġ���� ��� �˻����� �ʾ��� ��� ��� �˻�
	while (startA <= finishA && startB <= finishB) {
		switch (COMPARE(terms[startA].exp, terms[startB].exp)) {
		case -1:
			// A�� < B��
			attach(terms[startB].coef, terms[startB].exp);
			startB++;
			break;
		case 0:
			// A�� = B��
			// �� ���, �� ���� coefficient�� ���ؼ� attach
			coef = terms[startA].coef + terms[startB].coef;
			if (coef)
				attach(coef, terms[startA].exp);
			startA++;
			startB++;
			break;
		case 1:
			// A�� > B��
			attach(terms[startA].coef, terms[startA].exp);
			startA++;
		}
	}

	// �� ���׽��� ��� attach���� ��, ���� �ٸ� ���׽��� ��� �ڿ� attach 
	for (; startA <= finishA; startA++) {
		attach(terms[startA].coef, terms[startA].exp);
	}
	for (; startB <= finishB; startB++) {
		attach(terms[startB].coef, terms[startB].exp);
	}
	// ���ο� ���׽��� ���� �� ����
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