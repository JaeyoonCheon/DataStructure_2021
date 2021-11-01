#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct treeNode* treePointer;
typedef struct treeNode {
	int data;
	treePointer leftChild, rightChild;
}treeNode;

treePointer* queue;
int front = 0, rear = 0;
int x, y;
treePointer root;

treePointer* createQueue() {
	treePointer* stack = (treePointer*)calloc(MAX_QUEUE_SIZE, sizeof(treeNode));

	return stack;
}

void queueEmpty() {
	fprintf(stderr, "queue is empty!\n");
	exit(EXIT_FAILURE);
}

void add(treePointer ptr) {
	rear = rear + 1;
	queue[rear] = ptr;
}

treePointer delete() {
	//if (rear == front) {
	//	queueEmpty();
	//}
	front = front + 1;
	return queue[front];
}

void levelOrder(treePointer ptr) {
	if (!ptr)
		return;
	add(ptr);
	while (1) {
		ptr = delete();
		if (ptr) {
			printf("%d ", ptr->data);
			if (ptr->leftChild)
				add(ptr->leftChild);
			if (ptr->rightChild)
				add(ptr->rightChild);
		}
		else
			break;
	}
}

void insertData(treePointer* node, int n) {
	treePointer temp;

	// 중요! 구조체 이름과 매개변수 이름이 겹치면 에러 발생 가능성
	temp = (treePointer)malloc(sizeof(treeNode));
	if (temp == NULL) {
		fprintf(stderr, "malloc error");
		exit(1);
	}
	temp->data = n;
	temp->leftChild = NULL;
	temp->rightChild = NULL;

	*node = temp;
	if ((*node)->data >= 10)
		return;
	insertData(&(*node)->leftChild, n * x);
	insertData(&(*node)->rightChild, n + y);
}

int main() {
	int n;
	int i, j;
	treePointer temp;

	printf("컴퓨터학부 2016115430 천재윤\n");

	printf("n: ");
	if (!scanf("%d", &n)) {
		fprintf(stderr, "scanf error\n");
		exit(1);
	}
	printf("x: ");
	if (!scanf("%d", &x)) {
		fprintf(stderr, "scanf error\n");
		exit(1);
	}
	printf("y: ");
	if (!scanf("%d", &y)) {
		fprintf(stderr, "scanf error\n");
		exit(1);
	}

	insertData(&root, n);

	temp = root;

	queue = createQueue();

	levelOrder(temp);

	printf("\n");
}