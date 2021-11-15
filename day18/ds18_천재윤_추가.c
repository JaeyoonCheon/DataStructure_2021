#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct vertex* vertexPointer;
typedef struct vertex {
	int key;
	vertexPointer link;
}vertex;

vertexPointer* adjList;

int* queue;
int n, front = -1, rear = -1;
int* visited;
int** adjMatrix;

void add(int data) {
	queue[++rear] = data;
}

int delete() {
	return queue[++front];
}

void dfs(int v) {
	vertexPointer w;
	visited[v] = 1;
	printf("%d ", v);

	for (w = adjList[v]; w; w = w->link) {
		if (!visited[w->key]) {
			dfs(w->key);
		}
	}
}

void bfs(int v) {
	int data;
	vertexPointer w;

	//�湮 Ȯ��
	visited[v] = 1;

	add(v);
	// ť���� ��� �̾Ƽ� �˻�
	while (front != rear) {
		data = delete();

		printf("%d ", data);
		// �� �� �ִ� ��� ��� ť�� ����
		for (w=adjList[data]; w; w = w->link) {
			if (!visited[w->key]) {
				visited[w->key] = 1;
				add(w->key);
			}
		}
	}
	front = -1;
	rear = -1;
}

int main() {
	FILE* fp;
	int i, j, data, starting, count = 0;
	vertexPointer pointer, temp;

	printf("��ǻ���к� 2016115430 õ����\n");

	fp = fopen("in.txt", "r");

	fscanf(fp, "%d", &n);

	adjMatrix = (int**)malloc(sizeof(int*) * n);
	for (i = 0; i < n; i++) {
		adjMatrix[i] = (int*)calloc(n, sizeof(int));
	}

	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			fscanf(fp, "%d", &data);
			adjMatrix[i][j] = data;
			adjMatrix[j][i] = data;
		}
	}

	adjList = (vertexPointer*)calloc(n, sizeof(vertex));

	for (i = 0; i < n; i++) {
		pointer = &adjList[i];
		for (j = 0; j < n; j++) {
			if (adjMatrix[i][j] == 1) {
				temp = (vertexPointer)malloc(sizeof(vertex));
				temp->key = j + 1;
				temp->link = NULL;

				if (!pointer) {
					pointer = temp;
				}
				else
				{
					pointer->link = temp;
				}
				pointer = pointer->link;
			}
		}
	}

	queue = (int*)calloc(MAX_QUEUE_SIZE, sizeof(int));
	visited = (int*)calloc(n + 1, sizeof(int));
		
	for (i = 1; i < n + 1; i++) {
		if (!visited[i]) {
			bfs(i);
			count++;
			printf("\n");
		}
	}
	printf("Connect component ����: %d\n", count);
}