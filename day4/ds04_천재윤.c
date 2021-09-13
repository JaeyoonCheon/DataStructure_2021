#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

int isPrime(int, int);

int main() {
	FILE* fp;
	int a, b;

	printf("ÄÄÇªÅÍÈøºÎ 2016115430 ÃµÀçÀ±\n");

	fp = fopen("in.txt", "r");

	while (!feof(fp)) {
		fscanf(fp, "%d %d", &a, &b);
		if (a <= 0 || b <= 0) {
			break;
		}
		printf("%d %d ", a, b);
		if (isPrime(a, b)) {
			printf("true\n");
		}
		else {
			printf("false\n");
		}
		
	}

	fclose(fp);
	return 0;
}

int isPrime(int a, int b) {
	if (a == 1 || b == 1) {
		return 1;
	}
	if (a != 1 && b != 1) {
		if (a == b) {
			return 0;
		}
		else if (a < b) {
			return isPrime(a, b - a);
		}
		else {
			return isPrime(a - b, b);
		}
	}

}