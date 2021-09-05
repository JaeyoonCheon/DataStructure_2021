#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

int fib(int);

int main() {
	int N;

	scanf_s("%d", &N);

	printf("%dth fib number is %d", N, fib(N));
}

int fib(int N) {
	if (N == 0)
		return 0;
	else if (N == 1)
		return 1;
	else
		return fib(N - 1) + fib(N - 2);
}