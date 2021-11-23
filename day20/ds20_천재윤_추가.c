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

void merge(element initList[], element mergedList[], int i, int m, int n, char keyword) {
	int j, k, t;

	j = m + 1;
	k = i;

	while (i <= m && j <= n) {
		switch (keyword)
		{
		case 'X':
			if (initList[i].x <= initList[j].x)
				mergedList[k++] = initList[i++];
			else
				mergedList[k++] = initList[j++];
		case 'Y':
			if (initList[i].y <= initList[j].y)
				mergedList[k++] = initList[i++];
			else
				mergedList[k++] = initList[j++];
		case 'Z':
			if (initList[i].z <= initList[j].z)
				mergedList[k++] = initList[i++];
			else
				mergedList[k++] = initList[j++];
		default:
			break;
		}

	}
	if (i > m)
		for (t = j; t <= n; t++)
			mergedList[t] = initList[t];
	else
		for (t = i; t <= m; t++)
			mergedList[k + t - i] = initList[t];
}

void mergePass(element initList[], element mergedList[], int n, int s, char keyword) {
	int i, j;
	for (i = 1; i <= n - 2 * s + 1; i += 2 * s) {
		merge(initList, mergedList, i, i + s - 1, i + 2 * s - 1, keyword);
	}
	if (i + s - 1 < n) {
		merge(initList, mergedList, i, i + s - 1, n, keyword);
	}
	else {
		for (j = i; j <= n; j++) {
			mergedList[j] = initList[j];
		}
	}
}

void mergeSort(element a[], int n, char keyword) {
	int s = 1;
	element extra[MAX_ARR_SIZE];
	
	while (s < n) {
		mergePass(a, extra, n, s, keyword);
		s *= 2;
		mergePass(extra, a, n, s, keyword);
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

	fprintf(output, "%c\n", crit);
	mergeSort(values, size - 1, crit);

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