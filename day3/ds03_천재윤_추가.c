#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sequentialSearch(char*, int, char);
int bsIterative(char*, char, int, int);
int bsRecursive(char*, char, int, int);

int main() {
	FILE* in;
	int i, n, result;
	int hi, lo, mid;
	char* arr;
	char key;
	clock_t start, finish;
	double elapsed;

	printf("컴퓨터학부 2016115430 천재윤\n");

	if (!(in = fopen("in.txt", "r")))
		perror("read file error");


	while (1) {
		if (!(fscanf(in, "%d", &n)))
			perror("read count number error");

		if (!(arr = (char*)malloc(sizeof(char) * n)))
			perror("alloction error");

		for (i = 0; i < n; i++) {
			if (!(fscanf(in, "%c", &arr[i])))
				perror("read element error");
			if (arr[i] == ' ')
			{
				fscanf(in, "%c", &arr[i]);
			}
		}

		while (1) {
			scanf_s("%c", &key);
			if (key == '\n')
				continue;
			if (key < 97 || key > 122) {
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
		if ((result = bsRecursive(arr, key, lo, hi)) == -1)
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
int sequentialSearch(char* arr, int N, char key) {
	int i = 0;

	for (i = 0; i < N; i++) {
		if (arr[i] == key)
			return i;
	}
	return -1;
}

//iterative binary search
int bsIterative(char* arr, char key, int lo, int hi) {
	int mid;
	while (1) {
		mid = (lo + hi) / 2;
		//printf("%c %d %d\n", arr[mid], (int)arr[mid], (int)key);
		if (arr[mid] == key) {
			return mid;
		}
		if (lo > hi) {
			return -1;
		}
		if ((int)arr[mid] > (int)key) {
			hi = mid - 1;
		}
		if ((int)arr[mid] < (int)key) {
			lo = mid + 1;
		}
	}
}

//recursive binary search
int bsRecursive(char* arr, char key, int lo, int hi) {
	int mid = (lo + hi) / 2;
	//printf("%c %d %d\n", arr[mid], (int)arr[mid], (int)key);
	if (arr[mid] == key) {
		return mid;
	}
	if (lo > hi) {
		return -1;
	}
	if ((int)arr[mid] > (int)key) {
		return bsRecursive(arr, key, lo, mid - 1);
	}
	if ((int)arr[mid] < (int)key) {
		return bsRecursive(arr, key, mid + 1, hi);
	}
}