#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

int* createStack();
void push(int*, int, int*);
int pop(int*, int*);
void stackFull();
void stackEmpty();
void showStack(int*, int*);

int main() {
	int* stack;
	int top = -1;
	int i, data;
	char keyword[10];

	stack = createStack();

	while (1) {
		scanf("%s", keyword);
		if (!strcmp(keyword, "push")) {
			scanf("%d", &data);
			push(stack, data, &top);
			showStack(stack, &top);
		}
		else if (!strcmp(keyword, "pop")) {
			printf("stack pop! : %d\n", pop(stack, &top));
			showStack(stack, &top);
		}
		else {
			printf("buffer\n");
		}
	}
}

int* createStack() {
	int* stack = (int*)calloc(MAX_STACK_SIZE, sizeof(int));

	return stack;
}

void push(int* stack, int data, int *top) {
	if (*top >= MAX_STACK_SIZE) {
		stackFull();
	}
	stack[++(*top)] = data;
}

int pop(int* stack, int *top) {
	if (*top < 0) {
		stackEmpty();
	}
	return stack[(*top)--];
}

void stackFull() {
	fprintf(stderr, "stack is full!\n");
	exit(EXIT_FAILURE);
}

void stackEmpty() {
	fprintf(stderr, "stack is empty!\n");
	exit(EXIT_FAILURE);
}

void showStack(int* stack, int *top) {
	int i;
	
	printf("Current top : %d\n", *top);
	printf("Current stack : ");
	for (i = 0; i <= *top; i++) {
		printf("%d ", stack[i]);
	}
	printf("\n");
}