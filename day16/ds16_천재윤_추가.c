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

	// key가 root인 트리 curr과 curr의 부모인 트리 parent를 가져옴
	parentSearch(&curr, k, &parent);

	/*curr에서 최솟값을 더 이상 찾아낼 수 없는 상태
	즉, leaf까지 교환 완료한 경우 재귀 반환*/
	if (curr == NULL)
		return;

	/*1. curr의 자식 node가 하나도 없는 경우:
	parent의 curr과 연결된 link를 끊고 curr을 삭제*/
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
	/*2. curr의 자식 node가 2개인 경우:
	* 조건이 오른쪽 subtree에서 가장 작은 값을 root value로 하도록 설정
	해당 값을 찾고, 그 값이 현재 curr의 root value가 될 것이기 때문에
	아래쪽에 동일한 해당 값이 존재할 것.
	따라서 해당 값을 트리에서 동일한 삭제 과정을 거쳐줌으로써
	해당 값을 가진 노드를 삭제하는 연산과정을 재귀호출 해준다.
	이후, subtree 상에 해당 값을 가진 node가 없으므로,
	현재 curr의 root value에 해당 값을 삽입한다.*/
	else if (curr->rightChild && curr->leftChild) {
		tempVal = minSearch(curr->rightChild);
		minVal = tempVal->key;

		delete(&(*node), tempVal->key);

		curr->key = minVal;
	}
	/*3. curr의 자식 node가 1개인 경우:
	1개인 자식 tree를 가지고 와서
	curr이 root 트리인 경우(삭제하려는 key가 root이면서 자식이 1개)
	root 트리를 자식 트리로 교체
	curr이 root 트리가 아닌 경우에는 parent의 curr과 연결된 link가
	child를 가리키도록 하고 curr을 삭제한다.*/
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