#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1

int** dataSet;
int stack[MAX_SIZE];
int top = -1;

void stackFull() {
	fprintf(stderr, "stack is full!\n");
	exit(EXIT_FAILURE);
}

void stackEmpty() {
	fprintf(stderr, "stack is empty!\n");
	exit(EXIT_FAILURE);
}

void push(int data) {
	if (top >= MAX_SIZE) {
		stackFull();
	}
	stack[++top] = data;
}

int pop() {
	if (top < 0) {
		stackEmpty();
	}
	return stack[top--];
}

int main() {
	FILE* in;
	short int out[MAX_SIZE];
	int temp;
	int i, j, n;

	printf("컴퓨터학부 2016115430 천재윤\n");

	in = fopen("in.txt", "r");

	fscanf(in, "%d", &n);

	for (i = 0; i < n; i++) {
		out[i] = TRUE;
	}

	dataSet = (int**)calloc(n, sizeof(int*));
	for (i = 0; i < n; i++) {
		dataSet[i] = (int*)calloc(n, sizeof(int));
	}

	while (!feof(in)) {
		fscanf(in, "%d %d", &i, &j);

		dataSet[i][j] = TRUE;
		dataSet[j][i] = TRUE;
	}

	for (i = 0; i < n; i++) {
		if (out[i]) {
			printf("%d ", i);
			out[i] = FALSE;
			top = -1;
			temp = i;

			while (1) {
				for (j = 0; j < n; j++) {
					if (dataSet[temp][j] != 1) {
						continue;
					}
					else {
						if (out[j]) {
							printf("%d ", j);
							out[j] = FALSE;
							push(j);
						}
						else {
							continue;
						}
					}
				}
				if (top == -1) {
					printf("\n");
					break;
				}
				temp = pop();
			}
		}
	}
}