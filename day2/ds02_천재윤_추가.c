#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int binPresentation(int N) {
	if (N == 0) {
		return 0;
	}
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
		while (1) {
			scanf_s("%d", &N);
			if (N < 0 || N >128)
				return 0;
			else
				break;
		}

		printf("%d\n", binPresentation(N));
	}
}