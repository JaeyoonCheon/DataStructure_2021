#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define MAX_QUEUE_SIZE 3

int* createQueue();
void add(int);
int delete();
void copy(int*, int*, int*);
void queueFull();
void queueEmpty();
void showQueue();

//global variable

int* queue;
int front = -1, rear = -1;
int capacity;

//원형 큐da
int main() {
	char keyword[10];
	int data;
	int* test;


	capacity = MAX_QUEUE_SIZE;
	queue = createQueue();

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
	printf("front : %d, rear : %d\n", front % capacity, rear % capacity);
	// is next cell front? -> mod rear for capacity + 1
	if (front % capacity < 0) {
		if ((rear + 1) % capacity == capacity + front % capacity) {
			//queue full. alert and doubling queue
			queueFull();
		}
	}
	else {
		if ((rear + 1) % capacity == front % capacity) {
			//queue full. alert and doubling queue
			queueFull();
		}
	}
	rear = (rear + 1) % capacity;

	queue[rear] = data;
}

int delete() {
	if (rear == front) {
		queueEmpty();
	}
	front = (front + 1) % capacity;
	return queue[front];
}

void copy(int* front, int* rear, int* newQueue) {
	int i, j;
	int* temp;

	i = 0;
	temp = front;
	while (1) {
		if (temp == rear) {
			newQueue[i++] = *(temp++);
			break;
		}
		newQueue[i] = *(temp);
		i++;
		temp++;
	}
}

void queueFull() {
	int* newQueue;
	printf("queue doubling!!\n");

	// make new queue for copy old queue
	newQueue = (int*)malloc(sizeof(int) * capacity * 2);

	int start = (front + 1) % capacity;

	// 환형 큐에서 add/del을 통해 front가 움직인 경우를 검사(front가 초기 위치가 아니면 rear가 capacity를 넘어감)
	if (start < 2) {
		// front ~ capacity 복사
		copy(queue + start, queue + start + capacity - 1, newQueue);
	}
	else {
		// front ~ capacity 복사
		copy(queue + start, queue + capacity, newQueue);
		// rear + 1 ~ 
		copy(queue, queue + rear + 1, newQueue + capacity - start);
	}

	front = 2 * capacity - 1;
	rear = capacity - 2;
	capacity *= 2;
	printf("queue size is : %d, double to %d\n", (int)(_msize(queue)/sizeof(int)), (int)(_msize(queue) / sizeof(int)) * 2);
	queue = newQueue;
}

void queueEmpty() {
	fprintf(stderr, "queue is empty!\n");
	exit(EXIT_FAILURE);
}

void showQueue() {
	int i;

	i = (front + 1) % capacity;
	do {
		i = i % capacity;
		printf("%d ", queue[i]);
		if (i == rear)
			break;
		i++;
	} while (1);
	printf("\n");
}