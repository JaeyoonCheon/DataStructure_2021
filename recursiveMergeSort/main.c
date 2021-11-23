#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

#define MAX_ARR_SIZE 100

typedef struct element {
	int x;
	int y;
	int z;
}element;

int listMerge(element a[], int link[], int start1, int start2) {
	int last1, last2, lastResult = 0;

	for (last1 = start1, last2 = start2; last1 && last2;) {
		if (a[last1].x <= a[last2].x) {
			link[lastResult] = last1;
			last1 = link[last1];
		}
		else {
			link[lastResult] = last2;
			lastResult = last2;
			last2 = link[last2];
		}
	}

	if (last1 == 0) {
		link[lastResult] = last2;
	}
	else {
		link[lastResult] = last1;
	}
	return link[0];
}

int rmergeSort(element a[], int link[], int left, int right) {
	int mid;

	if (left >= right) {
		return left;
	}
	mid = (left + right) / 2;
	return listMerge(a, link, rmergeSort(a, link, left, mid), rmergeSort(a, link, mid + 1, right));
}

int main() {
	element a[MAX_ARR_SIZE];
	int link[MAX_ARR_SIZE];


}