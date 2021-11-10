#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

typedef struct vertex* vertexPointer;
typedef struct vertex {
	int key;
	vertexPointer link;
}vertex;

vertexPointer* adjList;

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
				temp->key = j+1;
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

	for (i = 1; i < n+1; i++) {
		printf("Vertex %d: ", i);
		pointer = adjList[i];
		for (; pointer; pointer = pointer->link) {
			printf("%d ", pointer->key);
		}
		printf("\n");
	}
}