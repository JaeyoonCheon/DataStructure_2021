#include <stdio.h>
#include <stdlib.h>

void hanoi(int, char, char, char);
void move(int, char, char);

int main() {
	int N;

	scanf_s("%d", &N);

	hanoi(N, 'A', 'B', 'C');
}

void hanoi(int num, char from, char to, char via) {
	if (num == 1) {
		move(1, from, to);
	}
	else {
		hanoi(num - 1, from, via, to);
		move(num, from, to);
		hanoi(num - 1, via, from, to);
	}
}

void move(int num, char from, char to) {
	printf("plate %d moved from %c to %c\n", num, from, to);
	return;
}