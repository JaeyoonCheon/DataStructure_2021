#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

typedef struct polyNode* polyPointer;
typedef struct polyNode {
	float coef;
	int exp;
	polyPointer link;
}polyNode;

void add(polyPointer *poly, float _coef, int _exp) {
	polyPointer temp, tail;

	temp = (polyPointer)malloc(sizeof(polyNode));
	tail = *poly;

	temp->coef = _coef;
	temp->exp = _exp;
	temp->link = NULL;

	if (tail) {
		while (tail->link) {
			tail = tail->link;
		}
		tail->link = temp;
	}
	else {
		*poly = temp;
	}
}

polyPointer padd(polyPointer *a, polyPointer *b) {
	polyPointer c;
	float sum;
	c = NULL;

	while ((*a) && (*b)) {
		switch (COMPARE((*a)->exp, (*b)->exp)) {
		case -1:
			add(&c, (*b)->coef, (*b)->exp);
			(*b) = (*b)->link;
			break;
		case 0:
			sum = (*a)->coef + (*b)->coef;
			if (sum) {
				add(&c, sum, (*a)->exp);
			}
			(*a) = (*a)->link;
			(*b) = (*b)->link;
			break;
		case 1:
			add(&c, (*a)->coef, (*a)->exp);
			(*a) = (*a)->link;
		}
	}
	while((*a)) {
		add(&c, (*a)->coef, (*a)->exp);
		(*a) = (*a)->link;
	}
	while ((*b)) {
		add(&c, (*b)->coef, (*b)->exp);
		(*b) = (*b)->link;
	}
	return c;
}

void setPoly(polyPointer *poly, FILE* fp) {
	float _coef;
	int _exp;
	while (!feof(fp)) {
		fscanf(fp, "%f %d", &_coef, &_exp);
		add(poly, _coef, _exp);
	}
}

int main() {
	FILE* fa, * fb;
	float _coef;
	int _exp;
	polyPointer A = NULL, B = NULL, C;

	fa = fopen("a.txt", "r");
	fb = fopen("b.txt", "r");

	setPoly(&A, fa);
	setPoly(&B, fb);

	C = padd(&A, &B);
}