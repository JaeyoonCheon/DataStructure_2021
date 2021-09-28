#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef struct dir {
	int row;
	int col;
}dir;
dir offset[8];
dir stack[MAX_STACK_SIZE];
int top = -1;

int** maze, **cache;
int x, y;

int** createMaze() {
	int i;
	int** temp = (int**)calloc(x, sizeof(int*));

	for (i = 0; i < x; i++) {
		temp[i] = (int*)calloc(y, sizeof(int));
	}

	return temp;
}

void makeOffset() {
	int i, j, index = 0;
	for (i = -1; i < 2; i++) {
		for (j = -1; j < 2; j++) {
			if (i == 0 && j == 0)
				continue;
			offset[index].row = i;
			offset[index++].col = j;
		}
	}
}

void readMaze(FILE* fp) {
	int i, j;
	char partial;

	printf("%d %d\n", x, y);

	for (i = 0; i < x; i++) {
		for (j = 0; j < y; j++) {
			fscanf(fp, "%d", &maze[i][j]);
		}
	}
}

void printMaze() {
	int i, j;

	for (i = 0; i < x; i++) {
		for (j = 0; j < y; j++) {
			printf("%d ", maze[i][j]);
		}
		printf("\n");
	}
}

void push(dir step) {
	if (top <= MAX_STACK_SIZE) {
		top++;
	}
	else {
		printf("stack full!\n");
		exit(EXIT_FAILURE);
	}
	stack[top].row = step.row;
	stack[top].col = step.col;
}

dir pop() {
	dir temp;

	temp.row = stack[top].row;
	temp.col = stack[top].col;

	top--;

	return temp;
}

int isEmpty() {
	if (top == -1) {
		return 1;
	}
	else {
		return 0;
	}
}

int isScope(int i) {
	if (stack[top].row + offset[i].row < 0 && stack[top].row + offset[i].row >= y)
		return 0;
	if (stack[top].col + offset[i].col < 0 && stack[top].col + offset[i].col >= x)
		return 0;
	return 1;
}

int isVisited(int i) {
	int row, col;

	row = stack[top].row + offset[i].row;
	col = stack[top].col + offset[i].col;

	if (cache[row][col] != 1) {
		return 0;
	}
	else {
		return 1;
	}
}

int isGoal(int i) {
	int row, col;

	row = stack[top].row + offset[i].row;
	col = stack[top].col + offset[i].col;

	if (row == y && col == x) {
		return 1;
	}
	else {
		return 0;
	}
}

void findPath() {
	int i;

	top++;
	stack[top].row = 0;
	stack[top].col = 0;
	cache[0][0] = 1;

	while (1) {
		if (!isEmpty()) {
			printf("Can't find any way\n");
			return;
		}
		for (i = 0; i < 8; i++) {
			if (isScope(i)) {
				if (isGoal(i)) {
					printf("Goal!\n");
					return;
				}
				if (!isVisited(i)) {
					push(offset[i]);
				}
			}
		}
		pop();
	}
}

int main() {
	FILE* fp;

	fp = fopen("maze.txt", "r");

	fscanf(fp, "%d %d", &x, &y);

	maze = createMaze();
	cache = createMaze();

	makeOffset();

	readMaze(fp);
	printMaze();
}