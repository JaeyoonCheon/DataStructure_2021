#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

#define MAX_ARR_SIZE 100

typedef struct line {
	int v1;
	int v2;
	int weight;
}line;

typedef struct edge* edgePointer;
typedef struct edge {
	int key;
	int weight;
	edgePointer link;
}edge;

edgePointer* adjList;

int n, count = 1;
int* visited;
int** adjMatrix;

int dfs(int prev, int v, int origin) {
	edgePointer w;
	int flag = 0;

	visited[v] = visited[prev];
	visited[v]++;

	for (w = adjList[v]; w; w = w->link) {
		if (w->key != prev) {
			if (w->key == origin && visited[w->key] < visited[v]) {
				flag = 1;
				return flag;
			}
			if (!visited[w->key]) {
				flag = dfs(v, w->key, origin);
				if (flag)
					return;
			}
		}
	}

	return flag;
}

void printWeight(line* edgeArr) {
	int i, j;
	line key;
	
	for (i = 1; i < count; i++) {
		key = edgeArr[i];

		for (j = i - 1; j >= 0 && edgeArr[j].weight > key.weight; j--) {
			edgeArr[j + 1] = edgeArr[j];
		}
		edgeArr[j+1] = key;
	}

	for (i = 1; i < count; i++) {
		if(edgeArr[i].v1 > edgeArr[i].v2)
			printf("%d (%d, %d)\n", edgeArr[i].weight, edgeArr[i].v2, edgeArr[i].v1);
		else
			printf("%d (%d, %d)\n", edgeArr[i].weight, edgeArr[i].v1, edgeArr[i].v2);
	}
}

int main() {
	FILE* fp;
	int i, j, data, starting;
	edgePointer pointer, temp;
	line* edgeArr;

	printf("컴퓨터학부 2016115430 천재윤\n");

	fp = fopen("in.txt", "r");

	fscanf(fp, "%d", &n);

	adjMatrix = (int**)malloc(sizeof(int*) * n);
	for (i = 0; i < n; i++) {
		adjMatrix[i] = (int*)calloc(n, sizeof(int));
	}

	edgeArr = (line*)calloc(MAX_ARR_SIZE, sizeof(line));

	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			fscanf(fp, "%d", &data);
			adjMatrix[i][j] = data;
			adjMatrix[j][i] = data;
			if (data != 0) {
				edgeArr[count].v1 = i+1;
				edgeArr[count].v2 = j+1;
				edgeArr[count].weight = data;
				count++;
			}
		}
	}

	adjList = (edgePointer*)calloc(n, sizeof(edge));

	for (i = 0; i < n; i++) {
		pointer = &adjList[i];
		for (j = 0; j < n; j++) {
			if (adjMatrix[i][j] != 0) {
				temp = (edgePointer)malloc(sizeof(edge));
				temp->key = j + 1;
				temp->weight = adjMatrix[i][j];
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

	printf("문제 1\n");
	printWeight(edgeArr);


	printf("\n문제 2\n");
	while (1) {
		visited = (int*)calloc(n + 1, sizeof(int));
		scanf("%d", &starting);

		if (starting == -1)
			break;

		if (dfs(starting, starting, starting))
			printf("Yes\n");
		else
			printf("No\n");
	}


}