#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
typedef struct node {
	int data;
	treePointer leftChild, rightChild;
}node;

int x, y;
treePointer root;

void leafLevel(treePointer ptr, int level) {
	if (ptr) {
		leafLevel(ptr->leftChild, level + 1);
		leafLevel(ptr->rightChild, level + 1);
		if(ptr->leftChild == NULL && ptr->rightChild == NULL) {
			printf("%d ", level);
		}
	}
}

void insertData(treePointer* node, int n) {
	treePointer temp;

	temp = (treePointer)malloc(sizeof(node));
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

	leafLevel(temp, 1);

	printf("\n");
}