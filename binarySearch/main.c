#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* in;
	int i, n;
	int hi, lo, mid;
	int* arr;
	int key;

	if (!(in = fopen("in.txt", "r")))
		perror("read file error");
	if (!(fscanf(in, "%d", &n)))
		perror("read count number error");

	if(!(arr = (int*)malloc(sizeof(int) * n)))
		perror("alloction error");

	for (i = 0; i < n; i++) {
		if (!(fscanf(in, "%d", &arr[i])))
			perror("read element error");
	}

	scanf("%d", &key);

	lo = 0, hi = n-1;

	while (1) {
		mid = (lo + hi) / 2;
		if (arr[mid] == key) {
			printf("found!");
			return 0;
		}
		if (lo > hi) {
			printf("not found!");
			return 0;
		}
		if (arr[mid] > key) {
			hi = mid-1;
		}
		if (arr[mid] < key) {
			lo = mid+1;
		}
	}
}