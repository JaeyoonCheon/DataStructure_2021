#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 10

typedef struct stack* stackPointer;
typedef struct stack {
	int data;
	stackPointer link;
}stack;
stackPointer top;

void push(int item) {
	stackPointer temp;

	temp = (stackPointer)malloc(sizeof(stack));
	temp->data = item;
	temp->link = top;
	top = temp;
}

int stackEmpty() {
	if (!top) {
		return 1;
	}
	return 0;
}

int pop() {
	stackPointer temp = top;
	int item;

	if (stackEmpty()) {
		fprintf(stderr, "stack empty!\n");
		exit(EXIT_FAILURE);
	}
	item = temp->data;
	top = temp->link;
	free(temp);
	return item;
}

void printList() {
	stackPointer temp;
	if (!stackEmpty()) {
		temp = top;
		while (temp) {
			printf("%d ", temp->data);
			temp = temp->link;
		}
		printf("\n");
	}
}

int main() {
	int i, data, err;
	char keyword[20];

	while (1) {
		if ((err = scanf("%s", keyword)) == NULL) {
			fprintf(stderr, "input data error!\n");
			exit(EXIT_FAILURE);
		}

		if (!strcmp(keyword, "exit")) {
			break;
		}
		else if (!strcmp(keyword, "push")) {
			scanf("%d", &data);
			push(data);
			printf("pushed data into stack!\n");
			printList();
		}
		else if (!strcmp(keyword, "pop")) {
			data = pop();
			printf("pop data %d from stack!\n", data);
			printList();
		}
		else if (!strcmp(keyword, "print")) {
			printList();
		}
		else {
			continue;
		}
	}
}