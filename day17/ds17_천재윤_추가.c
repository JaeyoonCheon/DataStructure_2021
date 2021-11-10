#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

typedef struct vertex* vertexPointer;
typedef struct vertex {
	int key;
	vertexPointer link;
}vertex;

vertexPointer* adjList;
int maxPath, minPath, count, found;
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

	printf("컴퓨터학부 2016115430 천재윤\n");

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

		queue = (int*)calloc(n, sizeof(int));
		visited = (int*)calloc(n, sizeof(int));
		count = 0;
		found = 0;

		//방문 확인
		visited[s] = 1;

		// 길이 1 증가
		count++;

		add(s);
		// 큐에서 계속 뽑아서 검사
		while (front != rear) {
			s = delete();

			// 갈 수 있는 경로 모두 큐에 저장
			pointer = adjList[s];
			for (; pointer; pointer = pointer->link) {
				if (pointer->key == e) {
					found = 1;
					printf("Shortest path length: %d\n", count);
					break;
				}
				if (!visited[pointer->key]) {
					visited[pointer->key] = 1;
					add(pointer->key);
				}
			}
			if (found)
				break;

			// 길이 1 증가
			count++;
		}
		if (!found) {
			printf("No Path!\n");
		}
		front = -1;
		rear = -1;
	}
}