#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX_STACK_SIZE 100

//maze�� ������ �Էµ� x, y ��ǥ�� �� �ڵ忡�� �� ���� ������� �ùٸ��� ���ȴ�.
//maze���� �ÿ��� x�� ����, y�� ���θ� ����ϰ�, ���⿡�� row�� ����, col�� ���θ� ����ϹǷ�
//���� ���� �� maze[col][row] ���·� ����ؾ� �ùٸ� ��ġ ������ ����ȴ�.

typedef struct dir {
	int row;
	int col;
}dir;
dir offset[8];

dir stack[MAX_STACK_SIZE];
int top = -1;

int** maze, **cache;
int x, y;

//x, y�� ���� ���� ����
int** createMaze() {
	int i;
	int** temp = (int**)calloc(y, sizeof(int*));

	for (i = 0; i < y; i++) {
		temp[i] = (int*)calloc(x, sizeof(int));
	}

	return temp;
}

//1ĭ �̵����� �̵� ������ �̸� ����Ͽ� offset�� ����
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

//������ ��ġ�� ������ ���ÿ� ����
void push(dir pos, dir step) {
	if (top <= MAX_STACK_SIZE) {
		top++;
	}
	else {
		printf("stack full!\n");
		exit(EXIT_FAILURE);
	}
	stack[top].row = pos.row + step.row;
	stack[top].col = pos.col + step.col;
}

//����� ������ pop
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

//maze�� ������ ����� �� �˻�
int isScope(dir pos, int i) {
	if (pos.row + offset[i].row < 0 || pos.row + offset[i].row >= y || pos.col + offset[i].col < 0 || pos.col + offset[i].col >= x)
		return 0;
	return 1;
}

//�̹� �湮�� ��ġ���� Ȯ��
//�̹� �湮�Ͽ� cache[col][rpw]==1�̶�� �ش� ��ġ���� ��� �������� ������µ� ���� �����ִٴ� �ǹ�
int isVisited(dir pos, int i) {
	int row, col;

	row = pos.row + offset[i].row;
	col = pos.col + offset[i].col;

	if (cache[col][row] != 1) {
		return 0;
	}
	else {
		return 1;
	}
}

//������ ������ ��ġ�� �� �� �ִ� ������ maze[col][row]==1���� Ȯ��
int isPath(dir pos, int i) {
	int row, col;

	row = pos.row + offset[i].row;
	col = pos.col + offset[i].col;

	if (maze[col][row] != 1) {
		return 0;
	}
	else {
		return 1;
	}
}

int isGoal(dir pos, int i) {
	int row, col;

	row = pos.row + offset[i].row;
	col = pos.col + offset[i].col;

	if (row == y-1 && col == x-1) {
		return 1;
	}
	else {
		return 0;
	}
}

//iterative�� stack dfs maze
void findPath() {
	int i;
	dir pos;

	//ó�� ������ġ = (0, 0)
	top++;
	stack[top].row = 0;
	stack[top].col = 0;
	pos.row = 0;
	pos.col = 0;

	while (1) {
		//�湮�� ��� cache�� ���
		cache[pos.col][pos.row] = 1;
		//8���� ������ ���� ����/�湮����/���Ⱑ�ɿ��� ����
		for (i = 0; i < 8; i++) {
			if (isScope(pos, i)) {
				//�ش� ������ �������� ��� ����
				if (isGoal(pos, i)) {
					printf("Goal!\n");
					return;
				}
				if (!isVisited(pos, i) && !isPath(pos, i)) {
					//�� �� �ִ� ��ġ�� ��� ���ÿ� ����
					push(pos, offset[i]);
				}
			}
		}
		if (isEmpty()) {
			printf("Can't find any way\n");
			return;
		}
		//pop�Ͽ� ��� ������ �̵������� ��ġ�� �ϳ��� �̾Ƽ� �ٽ� 8���� ����
		//���� ���ٸ� ����� for�� ������ push�� �����Ƿ� stack���� ��� pop�Ǿ� ���� �������� ���� �̵� ���� ��ġ�� ���ö� ���� pop
		pos = pop();
		printf("current x : %d, y : %d\n", pos.row, pos.col);
	}
}

int main() {
	FILE* fp;

	fp = fopen("maze_debug.txt", "r");

	fscanf(fp, "%d %d", &x, &y);

	maze = createMaze();
	cache = createMaze();

	makeOffset();

	readMaze(fp);
	printMaze();

	findPath();
}