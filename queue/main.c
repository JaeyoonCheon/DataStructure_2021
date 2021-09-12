#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 10

int* createQueue();
void add(int*, int, int*, int*);
int delete(int*, int*, int*);
void queueFull();
void queueEmpty();
void showQueue(int*, int*, int*);

//¿øÇü Å¥
int main() {
	int* queue;
	int front = 0, rear = 0;
	int i, data;
	char keyword[10];

	queue = createQueue();

	while (1) {
		scanf("%s", keyword);
		if (!strcmp(keyword, "add")) {
			scanf("%d", &data);
			add(queue, data, &front, &rear);
			showQueue(queue, &front, &rear);
		}
		else if (!strcmp(keyword, "del")) {
			printf("stack pop! : %d\n", delete(queue, &front, &rear));
			showQueue(queue, &front, &rear);
		}
		else {
			printf("buffer\n");
		}
	}
}

int* createQueue() {
	int* stack = (int*)calloc(MAX_QUEUE_SIZE, sizeof(int));

	return stack;
}

void add(int* queue, int data, int* front, int* rear) {
	if ((*rear) + 1 == *front) {
		queueFull();
	}
	*rear = ((*rear) + 1) % (MAX_QUEUE_SIZE + 1);
	queue[(*rear)] = data;
}

int delete(int* queue, int* front, int* rear) {
	if (*rear == *front) {
		queueEmpty();
	}
	*front = ((*front) + 1) % (MAX_QUEUE_SIZE + 1);
	return queue[*front];
}

void queueFull() {
	fprintf(stderr, "queue is full!\n");
	exit(EXIT_FAILURE);
}

void queueEmpty() {
	fprintf(stderr, "queue is empty!\n");
	exit(EXIT_FAILURE);
}

void showQueue(int* queue, int* front, int* rear) {
	int i;

	printf("Current front-rear : %d %d\n", *front, *rear);
	printf("Current queue : ");

	i = ((*front) + 1) % (MAX_QUEUE_SIZE + 1);
	while (1) {
		if (*front == *rear) {
			printf("Empty Queue\n");
			break;
		}
		if (i > *rear) {
			break;
		}
		printf("%d ", queue[i++ % (MAX_QUEUE_SIZE + 1)]);
	}
	printf("\n");
}