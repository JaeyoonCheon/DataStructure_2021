#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ARR_SIZE 100

int digit(int a, int j, int r, int d) {
	int i;

	a = a % (int)pow(r, (d - j));
	a = a / (int)pow(r, (d - j - 1));

	return a;
}

int radixSort(int a[], int link[], int d, int r, int n) {
	int* front, * rear;
	int i, bin, current, first, last;

	front = (int*)malloc(sizeof(int) * r);
	rear = (int*)malloc(sizeof(int) * r);

	first = 1;

	for (i = 1; i < n; i++) {
		link[i] = i + 1;
	}

	link[n] = 0;

	for (i = d - 1; i >= 0; i--) {
		for (bin = 0; bin < r; bin++) {
			front[bin] = 0;
		}

		for (current = first; current; current = link[current]) {
			bin = digit(a[current], i, r, d);
			if (front[bin] == 0) {
				front[bin] = current;
			}
			else {
				link[rear[bin]] = current;
			}
			rear[bin] = current;
		}

		for (bin = 0; !front[bin]; bin++);

		first = front[bin];
		last = rear[bin];

		for (bin++; bin < r; bin++) {
			if (front[bin]) {
				link[last] = front[bin];
				last = rear[bin];
			}
		}
		link[last] = 0;
	}

	return first;
}

int main() {
	FILE* fin;
	int i, count = 1, starting;
	char* str;

	int a[MAX_ARR_SIZE], link[MAX_ARR_SIZE];

	printf("컴퓨터학부 2016115430 천재윤\n");

	fin = fopen("in.txt", "r");

	a[0] = 0;
	while (!feof(fin)) {
		fscanf(fin, "%x", &a[count]);
		count++;
	}

	for (i = 0; i < MAX_ARR_SIZE; i++) {
		link[i] = 0;
	}

	starting = radixSort(a, link, 4, 16, count - 1);

	printf("%.4X\n", a[starting]);
	for (i = starting; link[starting]; starting = link[starting]) {
		printf("%.4X\n", a[link[starting]]);
	}
}