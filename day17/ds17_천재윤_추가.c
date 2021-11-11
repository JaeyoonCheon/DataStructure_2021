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
int max = 0, min = 0, count, found;
int s, e;

int* queue;
int front = -1, rear = -1;
int* visited;

void add(int data) {
	queue[++rear] = data;
}

int delete() {
	return queue[++front];
}

int main() {
	FILE* fp;
	int n, i, j;
	int** adjMatrix;
	vertexPointer pointer, temp;

	printf("��ǻ���к� 2016115430 õ����\n");

	fp = fopen("in.txt", "r");

	fscanf(fp, "%d", &n);

	adjMatrix = (int**)malloc(sizeof(int*) * n);
	for (i = 0; i < n; i++) {
		adjMatrix[i] = (int*)malloc(sizeof(int) * n);
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fscanf(fp, "%d", &adjMatrix[i][j]);
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
		scanf("%d %d", &s, &e);

		if (s == 0 && e == 0)
			break;
		if (s == e)
			continue;

		queue = (int*)calloc(MAX_QUEUE_SIZE, sizeof(int));
		visited = (int*)calloc(n + 1, sizeof(int));
		count = 0;
		found = 0;

		//�湮 Ȯ��
		visited[s] = 1;

		// ���� 1 ����
		count++;

		add(s);
		// ť���� ��� �̾Ƽ� �˻�
		while (front != rear) {
			s = delete();

			// �� �� �ִ� ��� ��� ť�� ����
			pointer = adjList[s];
			for (; pointer; pointer = pointer->link) {
				if (pointer->key == e) {
					found = 1;
					break;
				}
				if (!visited[pointer->key]) {
					visited[pointer->key] = 1;
					add(pointer->key);
					max++;
				}
			}

			// ���� 1 ����
			max--;
			if(max == 0)
				count++;
		}
		if (!found) {
			printf("No Path!\n");
		}
		else {
			printf("Shortest path length: %d\n", count);
		}
		front = -1;
		rear = -1;
		max = 0;
	}
}