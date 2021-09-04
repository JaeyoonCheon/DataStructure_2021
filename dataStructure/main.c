#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

#define SWAP(A, B, type) do{ \
	type temp = A; \
	A = B; \
	B = temp; \
}while(0); \

int main() {
	FILE* in;
	int i, j, n, min;
	int* arr;

	if (!(in = fopen("in.txt", "w")))
		perror("read file error");
	if (!(fscanf(in, "%d", &n)))
		perror("read count number error");

	for (i = 0; i < n; i++) {
		fscanf(in, "%d", &arr[i]);
	}

	for (i = 0; i < n; i++) {
		min = i;
		for (j = i + 1; j < n; j++) {
			if (min > j)
				min = j;
		}
		SWAP(arr[i], arr[min], int);
	}

	for (i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	
}