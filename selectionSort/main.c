#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

#define SWAP(A, B, type) do{ \
	int temp; \
	temp = A; \
	A = B; \
	B = temp; \
}while(0)

int main() {
	FILE* in;
	int i, j, k, n, min;
	int* arr;

	if (!(in = fopen("in.txt", "r")))
		perror("read file error");
	if (!(fscanf(in, "%d", &n)))
		perror("read count number error");
	if (!(arr = (int*)malloc(sizeof(int) * n)))
		perror("allocation error");

	for (i = 0; i < n; i++) {
		fscanf(in, "%d", &arr[i]);
	}

	for (k = 0; k < n; k++) {
		printf("%d ", arr[k]);
		if (k == n - 1)
			printf("\n");
	}

	for (i = 0; i < n; i++) {
		min = i;
		for (j = i; j < n; j++) {
			if (arr[min] > arr[j])
				min = j;
		}

		SWAP(arr[i], arr[min]);

		for (k = 0; k < n; k++) {
			printf("%d ", arr[k]);
			if (k == n - 1)
				printf("\n");
		}
	}
	for (k = 0; k < n; k++) {
		printf("%d ", arr[k]);
	}
}