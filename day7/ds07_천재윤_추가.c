#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

int* stack;
int top = -1;
int capacity = 1;

int* createStack(int);
void push(int);
int pop();
void copy(int*);
void stackFull();
void stackEmpty();
void showStack();

int main() {
	FILE* fp;
	int i, count = 0;
	char keyword;
	int value;
	
	printf("컴퓨터학부 2016115430 천재윤\n");

	fp = fopen("in.txt", "r");

	stack = createStack(capacity);

	while (1) {
		if (count == 100)
			break;
		if (!feof(fp)) {
			fscanf(fp, "%c", &keyword);
			fgetc(fp);
			if (keyword == 'a') {
				fscanf(fp, "%d", &value);
				push(value);
				fgetc(fp);
			}
			if (keyword == 'd') {
				pop();
			}
		}
		else
		{
			showStack();
			break;
		}
		count++;
	}
}

int* createStack(int newCapacity) {
	int* temp;

	temp = (int*)malloc(sizeof(int) * newCapacity);

	return temp;
}

void push(int data) {
	if (top >= capacity-1) {
		stackFull();
	}
	stack[++top] = data;
}

int pop() {
	if (top < 0) {
		stackEmpty();
		return 0;
	}
	return stack[top--];
}

void copy(int* newStack) {
	int i;

	for (i = 0; i <= top; i++) {
		newStack[i] = stack[i];
	}
}

void stackFull() {
	int* newStack;
	int newCapacity;

	newCapacity = capacity * 2;

	newStack = createStack(newCapacity);

	copy(newStack);

	stack = newStack;
}

void stackEmpty() {
	int* newStack;
	int newCapacity;

	if (capacity > 1) {
		newCapacity = capacity / 2;
	}
	else {
		return;
	}

	newStack = createStack(newCapacity);

	copy(newStack);

	free(stack);
	stack = newStack;
}

void showStack() {
	int i;

	for (i = 0; i <= top; i++) {
		printf("%d ", stack[i]);
	}
}