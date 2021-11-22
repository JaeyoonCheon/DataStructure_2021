#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

#define MAX_ARR_SIZE 100

#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

typedef struct element {
	int x;
	int y;
	int z;
}element;

element values[MAX_ARR_SIZE];
element evaluation[MAX_ARR_SIZE];
int size = 1;
int evalSize = 0;
char crit, evalCrit;

void mergeX(element initList[], element mergedList[], int i, int m, int n) {
	int j, k, t;

	j = m + 1;
	k = i;

	while (i <= m && j <= n) {
		if (initList[i].x <= initList[j].x)
			mergedList[k++] = initList[i++];
		else
			mergedList[k++] = initList[j++];
	}
	if (i > m)
		for (t = j; t <= n; t++)
			mergedList[t] = initList[t];
	else
		for (t = i; t <= m; t++)
			mergedList[k + t - i] = initList[t];
}

void mergeY(element initList[], element mergedList[], int i, int m, int n) {
	int j, k, t;

	j = m + 1;
	k = i;

	while (i <= m && j <= n) {
		if (initList[i].y <= initList[j].y)
			mergedList[k++] = initList[i++];
		else
			mergedList[k++] = initList[j++];
	}
	if (i > m)
		for (t = j; t <= n; t++)
			mergedList[t] = initList[t];
	else
		for (t = i; t <= m; t++)
			mergedList[k + t - i] = initList[t];
}

void mergeZ(element initList[], element mergedList[], int i, int m, int n) {
	int j, k, t;

	j = m + 1;
	k = i;

	while (i <= m && j <= n) {
		if (initList[i].z <= initList[j].z)
			mergedList[k++] = initList[i++];
		else
			mergedList[k++] = initList[j++];
	}
	if (i > m)
		for (t = j; t <= n; t++)
			mergedList[t] = initList[t];
	else
		for (t = i; t <= m; t++)
			mergedList[k + t - i] = initList[t];
}

void mergePass(element initList[], element mergedList[], int n, int s) {
	int i, j;
	for (i = 1; i <= n - 2 * s + 1; i += 2 * s) {
		switch (crit)
		{
		case 'X':
			mergeX(initList, mergedList, i, i + s - 1, i + 2 * s - 1);
			break;
		case 'Y':
			mergeY(initList, mergedList, i, i + s - 1, i + 2 * s - 1);
			break;
		case 'Z':
			mergeZ(initList, mergedList, i, i + s - 1, i + 2 * s - 1);
			break;
		default:
			break;
		}
	}
	if (i + s - 1 < n) {
		switch (crit)
		{
		case 'X':
			mergeX(initList, mergedList, i, i + s - 1, n);
			break;
		case 'Y':
			mergeY(initList, mergedList, i, i + s - 1, n);
			break;
		case 'Z':
			mergeZ(initList, mergedList, i, i + s - 1, n);
			break;
		default:
			break;
		}
	}
	else {
		for (j = i; j <= n; j++) {
			mergedList[j] = initList[j];
		}
	}
}

void mergeSort(element a[], int n) {
	int s = 1;
	element extra[MAX_ARR_SIZE];
	
	while (s < n) {
		mergePass(a, extra, n, s);
		s *= 2;
		mergePass(extra, a, n, s);
		s *= 2;
	}
}

int main() {
	FILE* fp, * output, * eval;
	int i, flag = 0;
	int X, Y, Z;

	printf("컴퓨터학부 2016115430 천재윤\n");

	fp = fopen("in.txt", "r");
	output = fopen("out.txt", "w");

	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &X, &Y, &Z);
		values[size].x = X;
		values[size].y = Y;
		values[size].z = Z;
		size++;
	}

	values[size].x = INT_MAX;
	values[size].y = INT_MAX;
	values[size].z = INT_MAX;

	scanf("%c", &crit);

	switch (crit)
	{
	case 'X':
		fprintf(output, "X\n");
		mergeSort(values, size - 1);
		break;
	case 'Y':
		fprintf(output, "Y\n");
		mergeSort(values, size - 1);
		break;
	case 'Z':
		fprintf(output, "Z\n");
		mergeSort(values, size - 1);
		break;
	default:
		break;
	}

	for (i = 1; i < size; i++) {
		fprintf(output, "%d %d %d", values[i].x, values[i].y, values[i].z);
		if (i < size - 1)
			fprintf(output, "\n");
	}

	fclose(output);

	eval = fopen("out.txt", "r");

	fscanf(eval, "%c", &evalCrit);

	while (!feof(eval)) {
		fscanf(eval, "%d %d %d", &X, &Y, &Z);
		evaluation[evalSize].x = X;
		evaluation[evalSize].y = Y;
		evaluation[evalSize].z = Z;
		evalSize++;
	}
	evalSize--;

	i = 0;

	switch (evalCrit)
	{
	case 'X':
		while (i < evalSize) {
			if (evaluation[i].x > evaluation[i + 1].x) {
				printf("fail\n");
				flag = 1;
				break;
			}
			i++;
		}
		if(!flag)
			printf("success\n");
		break;
	case 'Y':
		while (i < evalSize) {
			if (evaluation[i].y > evaluation[i + 1].y) {
				printf("fail\n");
				break;
			}
			i++;
		}
		if (!flag)
			printf("success\n");
		break;
	case 'Z':
		while (i < evalSize) {
			if (evaluation[i].z > evaluation[i + 1].z) {
				printf("fail\n");
				break;
			}
			i++;
		}
		if (!flag)
			printf("success\n");
		break;
	default:
		break;
	}
}