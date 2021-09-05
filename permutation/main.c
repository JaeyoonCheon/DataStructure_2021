#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

#define SWAP(A, B, type) do{ \
	type temp; \
	temp = A; \
	A = B; \
	B = temp; \
}while(0); \

void perm(int*, int, int);

int main() {
	FILE* in;
	int i, n;
	int* arr;

	if (!(in = fopen("in.txt", "r")))
		perror("read file error");
	if (!(fscanf(in, "%d", &n)))
		perror("read count number error");

	if (!(arr = (int*)malloc(sizeof(int) * n)))
		perror("alloction error");

	for (i = 0; i < n; i++) {
		if (!(fscanf(in, "%d", &arr[i])))
			perror("read element error");
	}

	perm(arr, 0, n);
}

void perm(int* arr, int i, int n) {
	int j;

	if (i == n) {
		for (j = 0; j < n; j++) {
			printf("%d", arr[j]);
		}
		printf("\n");
	}
	else {
		for (j = i; j < n; j++) {
			SWAP(arr[i], arr[j], int);
			perm(arr, i + 1, n);
			SWAP(arr[i], arr[j], int);
		}
	}
}