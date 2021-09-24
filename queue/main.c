#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 3

int* createQueue();
void add(int);
int delete();
void queueFull();
void queueEmpty();
void showQueue();

//global variable

int* queue;
int front = 0, rear = 0;
int capacity;

//¿øÇü Å¥da
int main() {
	char keyword[10];
	int data;

	queue = createQueue();

	capacity = MAX_QUEUE_SIZE;

	while (1) {
		scanf("%s", keyword);
		if (!strcmp(keyword, "add")) {
			scanf("%d", &data);
			add(data);
			showQueue();
		}
		else if (!strcmp(keyword, "del")) {
			printf("stack pop! : %d\n", delete());
			showQueue();
		}
		else {
			printf("buffer\n");
		}
	}
}

int* createQueue() {
	int* stack = (int*)calloc(capacity, sizeof(int));

	return stack;
}

void add(int data) {
	if ((rear + 1) % (capacity + 1) == front) {
		printf("front: %d, rear: %d\n", front, rear);
		queueFull();

		rear = (rear + 1) % (capacity + 1);
	}

	rear = (rear + 1) % (capacity + 1);
	queue[rear] = data;
}

int delete() {
	if (rear == front) {
		queueEmpty();
	}
	front = (front + 1) % capacity;
	return queue[front];
}

void copy(int front, int rear, int* newQueue) {
	int i;
	for (i = front; i < rear; i++) {
		newQueue[i] = queue[i];
	}
}

void queueFull() {
	int* newQueue;

	printf("queue doubling!!\n");

	newQueue = (int*)malloc(sizeof(int) * capacity * 2);

	printf("queueFull.. front: %d rear: %d\n", front, rear);
	
	int start = (front + 1) % capacity;
	if (start < 2) {
		copy(start, start + capacity - 1, newQueue);
	}
	else {
		copy(start, capacity, newQueue);
		copy(rear + 1, capacity - start, newQueue);
	}
	showQueue();
}

void queueEmpty() {
	fprintf(stderr, "queue is empty!\n");
	exit(EXIT_FAILURE);
}

void showQueue() {
	int i;

	printf("Current front-rear : %d %d\n", front, rear);
	printf("Current queue : ");

	i = (front + 1) % (capacity + 1);
	while (1) {
		if (front == rear) {
			queueEmpty();
		}
		if (i > rear) {
			break;
		}
		printf("%d ", queue[i++ % (capacity + 1)]);
	}
	printf("\n");
}