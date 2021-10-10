#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 10

typedef struct queue* queuePointer;
typedef struct queue {
	int data;
	queuePointer link;
}queue;
queuePointer front, rear;

void add(int item) {
	queuePointer temp;

	temp = (queuePointer)malloc(sizeof(queue));
	temp->data = item;
	temp->link = NULL;
	if (front) {
		rear->link = temp;
	}
	else {
		front = temp;
	}
	rear = temp;
}

int queueEmpty() {
	if (!front) {
		return 1;
	}
	return 0;
}

int delete() {
	queuePointer temp = front;
	int item;

	if (queueEmpty()) {
		fprintf(stderr, "queue empty!\n");
		exit(EXIT_FAILURE);
	}
	item = temp->data;
	front = temp->link;
	free(temp);
	return item;
}

void printList() {
	queuePointer temp;
	if (!queueEmpty()) {
		temp = front;
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
		else if (!strcmp(keyword, "add")) {
			scanf("%d", &data);
			add(data);
			printf("added data into queue!\n");
			printList();
		}
		else if (!strcmp(keyword, "del")) {
			data = delete();
			printf("delete data %d from queue!\n", data);
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