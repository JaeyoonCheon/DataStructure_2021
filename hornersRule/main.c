#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR 99
#define MAX_EXP 99

int main() {
	// 2x^3+4x+1 = ((2x^2+4)x +1)
	char* poly = (char*)malloc(sizeof(char)*MAX_STR);
	int x, i=0;
	int* coef, * exp;
	char temp[10] = "";

	printf("put polynomial 'ax^n+bx^n-1+...+z' format\n");
	scanf("%s", poly);

	printf("put point x\n");
	scanf("%d", &x);

	coef = (int*)malloc(sizeof(int) * MAX_EXP);
	exp = (int*)malloc(sizeof(int) * MAX_EXP);

	while (1) {
		if (poly[i] == '\0')
			break;
		if (poly[i] != 'x') {
			strcat(temp, poly[i]);

		}
	}
}