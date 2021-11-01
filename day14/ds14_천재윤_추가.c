#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef struct treeNode* treePointer;
typedef struct treeNode {
	int data;
	treePointer leftChild, rightChild;
}treeNode;

treePointer* stack;
int top = -1;
int x, y;
treePointer root;

treePointer* createStack() {
	int* stack = (treePointer*)calloc(MAX_STACK_SIZE, sizeof(treeNode));

	return stack;
}

void push(treePointer ptr) {
	//if (top >= MAX_STACK_SIZE) {
	//	stackFull();
	//}
	stack[++top] = ptr;
}

treePointer pop() {
	if (top < 0) {
		return NULL;
	}
	return stack[top--];
}

void inOrder(treePointer node) {
	while (1) {
		for (; node; node = node->leftChild)
			push(node);
		node = pop();
		if (!node)
			break;
		printf("%d ", node->data);
		node = node->rightChild;
	}
}

void insertData(treePointer* node, int n) {
	treePointer temp;

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

	stack = createStack();

	inOrder(temp);

	printf("\n");
}