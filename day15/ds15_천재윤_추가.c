#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

typedef struct element {
	int key;
}element;
typedef struct treeNode* treePointer;
typedef struct treeNode {
	element data;
	treePointer leftChild, rightChild;
}treeNode;

treePointer root;
int count = 0;

void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		count++;
		inorder(ptr->rightChild);
	}
}

element* search(treePointer root, int key) {
	if (!root)
		return NULL;
	if (key == root->data.key)
		return &(root->data);
	if (key < root->data.key)
		return search(root->leftChild, key);
	return search(root->rightChild, key);
}

treePointer modifiedSearch(treePointer root, int key) {
	if (!root)
		return NULL;
	if (key < root->data.key)
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
		ptr->data.key = k;
		ptr->leftChild = ptr->rightChild = NULL;

		if (*node) {
			if (k < temp->data.key)
				temp->leftChild = ptr;
			else
				temp->rightChild = ptr;
		}
		else
			*node = ptr;
	}
}

int main() {
	int n;
	int i, j;
	FILE* fp1, * fp2;
	treePointer temp;

	printf("컴퓨터학부 2016115430 천재윤\n");

	fp1 = fopen("in.txt", "r");
	fp2 = fopen("search.txt", "r");

	while (!feof(fp1)) {
		fscanf(fp1, "%d", &n);
		insert(&root, n);
	}

	while (!feof(fp2)) {
		fscanf(fp2, "%d", &n);
		if (search(root, n)) {
			temp = search(root, n);
			inorder(temp);
			printf("%d ", count);
			count = 0;
		}
		else
			printf("E ");
	}

	printf("\n");
}