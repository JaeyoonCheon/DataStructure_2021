#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int binPresentation(int N) {
	if (N == 1) {
		return 1;
	}
	if (N % 2 == 1) {
		return binPresentation(N / 2) + 1;
	}
	else {
		return binPresentation(N / 2);
	}
}

int main() {
	int N;
	
	while (1) {
		do {
			scanf_s("%d", &N);
		} while (N < 0 || N>128);

		printf("%d\n", binPresentation(N));
	}
}