#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

#define MAX_ARR_SIZE 100
#define MAX_QUEUE_SIZE 100

typedef struct treeNode* treePointer;
typedef struct treeNode {
	int key;
	treePointer leftChild, rightChild;
}treeNode;

treePointer root;
int count = 0;
int* tempArr;

treePointer* queue;
int front = 0, rear = 0;

treePointer* createQueue() {
	treePointer* q = (treePointer*)calloc(MAX_QUEUE_SIZE, sizeof(treeNode));

	return q;
}

void addq(treePointer ptr) {
	rear = rear + 1;
	queue[rear] = ptr;
}

treePointer deleteq() {
	front = front + 1;
	return queue[front];
}

void levelOrder(treePointer ptr) {
	if (!ptr)
		return;
	addq(ptr);
	while (1) {
		ptr = deleteq();
		if (ptr) {
			printf("%d ", ptr->key);
			if (ptr->leftChild)
				addq(ptr->leftChild);
			if (ptr->rightChild)
				addq(ptr->rightChild);
		}
		else
			break;
	}
}

treePointer* search(treePointer root, int key) {
	if (!root)
		return NULL;
	if (key == root->key)
		return root;
	if (key < root->key)
		return search(root->leftChild, key);
	return search(root->rightChild, key);
}

treePointer minSearch(treePointer root) {
	treePointer trail;

	trail = root;

	while (trail->leftChild) {
		trail = trail->leftChild;
	}
	return trail;
}

treePointer modifiedSearch(treePointer root, int key) {
	if (!root)
		return NULL;
	if (key < root->key)
	{
		if (!root->leftChild)
		{
			return root;
		}
		return modifiedSearch(root->leftChild, key);
	}
	else {
		if (!root->rightChild)
		{
			return root;
		}
		return modifiedSearch(root->rightChild, key);
	}
}

void insert(treePointer* node, int k) {
	treePointer ptr, temp = modifiedSearch(*node, k);

	if (temp || !(*node)) {
		ptr = (treePointer)malloc(sizeof(treeNode));
		ptr->key = k;
		ptr->leftChild = ptr->rightChild = NULL;

		if (*node) {
			if (k < temp->key)
				temp->leftChild = ptr;
			else
				temp->rightChild = ptr;
		}
		else
			*node = ptr;
	}
}

void parentSearch(treePointer* root, int key, treePointer* parent) {
	while ((*root) && (*root)->key != key) {
		*parent = *root;

		if (key < (*root)->key)
			(*root) = (*root)->leftChild;
		else
			(*root) = (*root)->rightChild;
	}
}

void delete(treePointer* node, int k) {
	int minVal;
	treePointer parent, curr, child, tempVal;

	parent = NULL;
	curr = *node;

	parentSearch(&curr, k, &parent);

	if (curr == NULL)
		return;

	// no child
	if (!curr->leftChild && !curr->rightChild) {
		if (curr != (*node)) {
			if (parent->leftChild == curr)
				parent->leftChild = NULL;
			else
				parent->rightChild = NULL;
		}
		else {
			(*node) = NULL;
		}
		free(curr);
	}
	// 2 child
	else if (curr->rightChild && curr->leftChild) {
		tempVal = minSearch(curr->rightChild);
		minVal = tempVal->key;

		delete(&(*node), tempVal->key);

		curr->key = minVal;
	}
	//1 child
	else {
		if (curr->leftChild)
			child = curr->leftChild;
		else {
			child = curr->rightChild;
		}
		
		if (curr != (*node)) {
			if (curr == parent->leftChild)
				parent->leftChild = child;
			else
				parent->rightChild = child;
		}
		else {
			(*node) = child;
		}

		free(curr);
	}
}

int main() {
	int n, min;
	int i, j;
	FILE* fp1;
	treePointer temp;

	tempArr = (int*)malloc(sizeof(int) * MAX_ARR_SIZE);
	queue = createQueue();

	printf("컴퓨터학부 2016115430 천재윤\n");

	fp1 = fopen("in.txt", "r");

	while (!feof(fp1)) {
		fscanf(fp1, "%d", &n);
		insert(&root, n);
	}

	scanf("%d", &n);

	temp = search(root, n);

	delete(&root, temp->key);
			
	levelOrder(root);

	printf("\n");
}