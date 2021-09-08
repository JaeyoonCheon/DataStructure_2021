#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sequentialSearch(int*, int, int);
int bsIterative(int*, int, int, int);
int bsRecursive(int*, int, int, int);

int main() {
	FILE* in;
	int i, n, key, result;
	int hi, lo, mid;
	int* arr;
	clock_t start, finish;
	double elapsed;

	if (!(in = fopen("in.txt", "r")))
		perror("read file error");


	while (1) {
		if (!(fscanf(in, "%d", &n)))
			perror("read count number error");

		if (!(arr = (int*)malloc(sizeof(int) * n)))
			perror("alloction error");

		for (i = 0; i < n; i++) {
			if (!(fscanf(in, "%d", &arr[i])))
				perror("read element error");
		}

		while (1) {
			scanf_s("%d", &key);
			if (key <= 0) {
				return 0;
			}
			else
				break;
		}

		lo = 0, hi = n - 1;

		//selection search
		start = clock();
		printf("Sequential: ");
		if ((result = sequentialSearch(arr, n, key)) == -1)
			printf("Fail ");
		else
			printf("%d ", result);
		finish = clock();
		elapsed = ((double)(finish)-(double)(start)) / CLOCKS_PER_SEC;
		printf("<%fms>\n", elapsed * 1000.0);

		//iterative binary search
		start = clock();
		printf("Iterative: ");
		if ((result = bsIterative(arr, key, lo, hi)) == -1)
			printf("Fail ");
		else
			printf("%d ", result);
		finish = clock();
		elapsed = ((double)(finish)-(double)(start)) / CLOCKS_PER_SEC;
		printf("<%fms>\n", elapsed * 1000.0);

		//recursive binary search
		start = clock();
		printf("Recursive: ");
		if ((result = bsRecusive(arr, key, lo, hi)) == -1)
			printf("Fail ");
		else
			printf("%d ", result);
		finish = clock();
		elapsed = ((double)(finish)-(double)(start)) / CLOCKS_PER_SEC;
		printf("<%fms>\n", elapsed * 1000.0);

		free(arr);
		rewind(in);
	}

	return 0;
}

//sequential search
int sequentialSearch(int* arr, int N, int key) {
	int i = 0;

	for (i = 0; i < N; i++) {
		if (arr[i] == key)
			return i;
	}
	return -1;
}

//iterative binary search
int bsIterative(int* arr, int key, int lo, int hi) {
	int mid;
	while (1) {
		mid = (lo + hi) / 2;
		if (arr[mid] == key) {
			return mid;
		}
		if (lo > hi) {
			return -1;
		}
		if (arr[mid] > key) {
			hi = mid - 1;
		}
		if (arr[mid] < key) {
			lo = mid + 1;
		}
	}
}

//recursive binary search
int bsRecusive(int* arr, int key, int lo, int hi) {
	int mid = (lo + hi) / 2;

	if (arr[mid] == key) {
		return mid;
	}
	if (lo > hi) {
		return -1;
	}
	if (arr[mid] > key) {
		return bsRecusive(arr, key, lo, mid - 1);
	}
	if (arr[mid] < key) {
		return bsRecusive(arr, key, mid + 1, hi);
	}
}