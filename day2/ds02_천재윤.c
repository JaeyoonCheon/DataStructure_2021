#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//int sum(int n) {
//	int i;
//	int sum = 0;
//
//	for (i = 1; i <= n; i++) {
//		sum += i;
//	}
//
//	return sum;
//}
//
//int rsum(int n) {
//	if (n == 1)
//		return 1;
//	return rsum(n - 1) + n;
//}
//
//int constSum(int n) {
//	return (n * (n + 1)) / 2;
//}

int rfib(int n) {
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return rfib(n - 1) + rfib(n - 2);
}

int ifib(int n) {
	int i, *arr, result;

	// step 2
	arr = (int*)malloc(sizeof(int) * (n+1));

	if (n == 0) {
		result = 0;
		free(arr);
		return result;
	}

	arr[0] = 0, arr[1] = 1;

	for (i = 2; i <= n; i++) {
		arr[i] = arr[i - 1] + arr[i - 2];
	}

	result = arr[n];

	// step 5
	free(arr);

	return result;
}

int main() {
	int N;
	clock_t start, finish;
	double elapsed;

	//step 8
	while (1) {
		// step 1
		
		while (1) {
			scanf_s("%d", &N);
			if (N < 0 || N >50)
				return 0;
			else
				break;
		}

		start = clock();
		// step 3
		printf("Iteration F(n) : %d\n", ifib(N));
		finish = clock();
		elapsed = ((double)(finish)-(double)(start)) / CLOCKS_PER_SEC;
		// step 4
		printf("Iteration time: %f\n", elapsed * 1000.0);

		start = clock();
		// step 6
		printf("Recursive F(n) : %d\n", rfib(N));
		finish = clock();
		elapsed = ((double)(finish)-(double)(start)) / CLOCKS_PER_SEC;
		// step 7
		printf("Recursive time: %f\n", elapsed * 1000.0);
	}
}