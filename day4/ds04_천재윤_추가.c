#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* A, * B;
	int i = 0, j, nA, nB, tmpA, tmpB, iA = 0, iB = 0, size = 0;
	int* arrA, * arrB, * arr;

	printf("컴퓨터학부 2016115430 천재윤\n");

	A = fopen("a.txt", "r");
	B = fopen("b.txt", "r");

	fscanf(A, "%d", &nA);
	fscanf(B, "%d", &nB);

	arrA = (int*)malloc(sizeof(int) * (nA + 1));
	arrB = (int*)malloc(sizeof(int) * (nB + 1));

	for (j = 0; j < nA; j++) {
		fscanf(A, "%d", &arrA[j]);
	}

	for (j = 0; j < nB; j++) {
		fscanf(B, "%d", &arrB[j]);
	}

	arr = (int*)malloc(sizeof(int) * (nA + nB));

	while (1) {
		/*printf("%d %d %d %d %d\n", i, iA, iB, arrA[iA], arrB[iB]);*/
		if (iA == nA && iB == nB) {
			break;
		}
		size++;
		if (iA == nA) {
			arr[i] = arrB[iB];
			i++;
			iB++;
			continue;
		}
		if (iB == nB) {
			arr[i] = arrA[iA];
			i++;
			iA++;
			continue;
		}
		if (arrA[iA] == arrB[iB]) {
			arr[i] = arrA[iA];
			i++;
			iA++;
			iB++;
		}
		else if (arrA[iA] < arrB[iB]) {
			arr[i] = arrA[iA];
			i++;
			iA++;
		}
		else {
			arr[i] = arrB[iB];
			i++;
			iB++;
		}
	}

	for (i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
}