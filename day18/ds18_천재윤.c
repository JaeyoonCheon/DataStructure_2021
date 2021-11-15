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

int main() {
	FILE* fp;
	int i, j, data, starting;
	vertexPointer pointer, temp;

	printf("컴퓨터학부 2016115430 천재윤\n");

	fp = fopen("in.txt", "r");

	fscanf(fp, "%d", &n);

	adjMatrix = (int**)malloc(sizeof(int*) * n);
	for (i = 0; i < n; i++) {
		adjMatrix[i] = (int*)calloc(n, sizeof(int));
	}

	for (i = 0; i < n-1; i++) {
		for (j = i+1; j < n; j++) {
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

	while (1) {
		visited = (int*)calloc(n+1, sizeof(int));
		scanf("%d", &starting);
		if (starting == -1) {
			break;
		}
		dfs(starting);
		printf("\n");
	}
}