#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
#define MAX_ARR_SIZE 100

typedef struct element {
	int x;
	int y;
	int z;
}element;

void adjust(element a[], int root, int n, char keyword) {
	int child, rootkey;
	element temp;

	switch (keyword)
	{
	case 'X':
		temp = a[root];
		rootkey = a[root].x;
		child = 2 * root;
		while (child <= n) {
			if ((child < n) && (a[child].x > a[child + 1].x)) {
				child++;
			}
			if (rootkey < a[child].x) {
				break;
			}
			else {
				a[child / 2] = a[child];
				child *= 2;
			}
		}
		a[child / 2] = temp;
		break;
	case 'Y':
		temp = a[root];
		rootkey = a[root].y;
		child = 2 * root;
		while (child <= n) {
			if ((child < n) && (a[child].y > a[child + 1].y)) {
				child++;
			}
			if (rootkey < a[child].y) {
				break;
			}
			else {
				a[child / 2] = a[child];
				child *= 2;
			}
		}
		a[child / 2] = temp;
		break;
	case 'Z':
		temp = a[root];
		rootkey = a[root].z;
		child = 2 * root;
		while (child <= n) {
			if ((child < n) && (a[child].z > a[child + 1].z)) {
				child++;
			}
			if (rootkey < a[child].z) {
				break;
			}
			else {
				a[child / 2] = a[child];
				child *= 2;
			}
		}
		a[child / 2] = temp;
		break;
	default:
		break;
	}

}

void heapSort(element a[], int n, char keyword) {
	int i, j;
	element temp;

	for (i = n / 2; i > 0; i--) {
		adjust(a, i, n, keyword);
	}
	for (i = n - 1; i > 0; i--) {
		SWAP(a[1], a[i + 1], temp);
		adjust(a, 1, i, keyword);
	}
}

int main() {
	FILE* fin, * fout, * eval;
	element a[MAX_ARR_SIZE];
	element evaluation[MAX_ARR_SIZE];
	int X, Y, Z, i, j, size = 1, starting, flag = 0, evalSize = 0;;
	char keyword;
	char evalCrit;

	printf("컴퓨터학부 2016115430 천재윤\n");

	fin = fopen("in.txt", "r");

	while (!feof(fin)) {
		fscanf(fin, "%d %d %d", &X, &Y, &Z);
		a[size].x = X;
		a[size].y = Y;
		a[size].z = Z;
		size++;
	}

	scanf("%c", &keyword);

	heapSort(a, size - 1, keyword);

	fclose(fin);

	fout = fopen("out.txt", "w");

	fprintf(fout, "%c\n", keyword);
	for (i = 1; i < size; i++) {
		fprintf(fout, "%d %d %d\n", a[i].x, a[i].y, a[i].z);
	}

	fclose(fout);

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
			if (evaluation[i].x < evaluation[i + 1].x) {
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
			if (evaluation[i].y < evaluation[i + 1].y) {
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
			if (evaluation[i].z < evaluation[i + 1].z) {
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