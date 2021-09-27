#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int front = 0, rear = 0;
int capacity;

//원형 큐da
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
	rear = (rear + 1) % capacity;

	// is next cell front? -> mod rear for capacity + 1
	if (rear == front) {
		//queue full. alert and doubling queue
		queueFull();
	}

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
	int i;

	printf("size : %d\n", sizeof(newQueue));
	
	for (i = 0; i < capacity * 2; i++) {
		printf("%d %d address : %x\n",i, newQueue[i], &newQueue[i]);
	}
	printf("\n");

	printf("front %x %d: rear %x %d\n", front, *front, rear, *rear);
	
	for (i = 0; i < sizeof(newQueue); i++) {
		*(front + i) = *(rear + i);
	}
	printf("\n");
}

void queueFull() {
	int* newQueue;
	printf("queue doubling!!\n");

	// make new queue for copy old queue
	newQueue = (int*)malloc(sizeof(int) * capacity * 2);

	printf("queueFull.. front: %d rear: %d\n", front, rear);

	int start = (front + 1) % capacity;

	// 환형 큐에서 add/del을 통해 front가 움직인 경우를 검사(front가 초기 위치가 아니면 rear가 capacity를 넘어감)
	if (start < 2) {
		printf("one block!\n");
		// front ~ capacity 복사
		printf("%d %d\n", *(queue + front), *(queue + capacity + 1));
		copy(queue + front, queue + capacity + 1, newQueue);
	}
	else {
		printf("two block!\n");
		// front ~ capacity 복사
		copy(queue + start, queue + capacity, newQueue);
		// rear + 1 ~ 
		copy(queue, queue + rear + 1, newQueue + capacity - start);
	}

	front = 2 * capacity - 1;
	rear = capacity - 2;
	capacity *= 2;
	free(queue);
	queue = newQueue;
	showQueue();
}

void queueEmpty() {
	fprintf(stderr, "queue is empty!\n");
	exit(EXIT_FAILURE);
}

void showQueue() {
	int i;

	for (i = 0; i < capacity; i++) {
		printf("%d ", queue[i]);
	}
	printf("\n");

	i = (front + 1) % capacity;
	printf("i : %d, rear : %d\n", i, rear);
	do {
		i = i % capacity;
		printf("%d ", queue[i% capacity]);
		if (i == rear)
			break;
		i++;
	} while (1);
	printf("\n");
}