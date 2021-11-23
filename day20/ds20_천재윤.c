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
int size = 0;
int evalSize = 0;
char crit, evalCrit;

void quickSortX(element list[], int left, int right) {
	int pivot;
	int i, j;
	element temp;

	if (left < right) {
		i = left;
		j = right + 1;
		pivot = list[left].x;

		do {
			do i++; while (list[i].x < pivot);
			do j--; while (list[j].x > pivot);
			if (i < j) SWAP(list[i], list[j], temp);
		} while (i < j);
		SWAP(list[left], list[j], temp);
		quickSortX(list, left, j - 1);
		quickSortX(list, j + 1, right);
	} 
}

void quickSortY(element list[], int left, int right) {
	int pivot;
	int i, j;
	element temp;

	if (left < right) {
		i = left;
		j = right + 1;
		pivot = list[left].y;

		do {
			do i++; while (list[i].y < pivot);
			do j--; while (list[j].y > pivot);
			if (i < j) SWAP(list[i], list[j], temp);
		} while (i < j);
		SWAP(list[left], list[j], temp);
		quickSortY(list, left, j - 1);
		quickSortY(list, j + 1, right);
	}
}

void quickSortZ(element list[], int left, int right) {
	int pivot;
	int i, j;
	element temp;

	if (left < right) {
		i = left;
		j = right + 1;
		pivot = list[left].z;

		do {
			do i++; while (list[i].z < pivot);
			do j--; while (list[j].z > pivot);
			if (i < j) SWAP(list[i], list[j], temp);
		} while (i < j);
		SWAP(list[left], list[j], temp);
		quickSortZ(list, left, j - 1);
		quickSortZ(list, j + 1, right);
	}
}

int main() {
	FILE* fp, *output, *eval;
	int i, flag = 0;
	int X, Y, Z;
	char crit;

	printf("컴퓨터학부 2016115430 천재윤\n");

	fp = fopen("in.txt", "r");
	output = fopen("out.txt", "w");
	eval = fopen("out.txt", "r");

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
		quickSortX(values, 0, size - 1);
		break;
	case 'Y':
		fprintf(output, "Y\n");
		quickSortY(values, 0, size - 1);
		break;
	case 'Z':
		fprintf(output, "Z\n");
		quickSortZ(values, 0, size - 1);
		break;
	default:
		break;
	}


	for (i = 0; i < size; i++) {
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
		if (!flag)
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