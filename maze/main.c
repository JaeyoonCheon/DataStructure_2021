#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX_STACK_SIZE 100

//maze의 정보로 입력된 x, y 좌표는 이 코드에서 행 열을 뒤집어야 올바르게 계산된다.
//maze구성 시에는 x가 세로, y가 가로를 담당하고, 방향에서 row가 가로, col이 세로를 담당하므로
//스택 연산 시 maze[col][row] 형태로 계산해야 올바른 위치 정보가 저장된다.

typedef struct dir {
	int row;
	int col;
}dir;
dir offset[8];

dir stack[MAX_STACK_SIZE];
int top = -1;

int** maze, **cache;
int x, y;

//x, y의 구성 방향 주의
int** createMaze() {
	int i;
	int** temp = (int**)calloc(y, sizeof(int*));

	for (i = 0; i < y; i++) {
		temp[i] = (int*)calloc(x, sizeof(int));
	}

	return temp;
}

//1칸 이동시의 이동 변위를 미리 계산하여 offset에 저장
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

//움직인 위치의 정보를 스택에 저장
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

//저장된 정보를 pop
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

//maze의 범위를 벗어나는 지 검사
int isScope(dir pos, int i) {
	if (pos.row + offset[i].row < 0 || pos.row + offset[i].row >= y || pos.col + offset[i].col < 0 || pos.col + offset[i].col >= x)
		return 0;
	return 1;
}

//이미 방문한 위치인지 확인
//이미 방문하여 cache[col][rpw]==1이라면 해당 위치에서 모든 방향으로 뻗어나갔는데 길이 막혀있다는 의미
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

//움직일 방향의 위치가 갈 수 있는 길인지 maze[col][row]==1으로 확인
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

//iterative한 stack dfs maze
void findPath() {
	int i;
	dir pos;

	//처음 시작위치 = (0, 0)
	top++;
	stack[top].row = 0;
	stack[top].col = 0;
	pos.row = 0;
	pos.col = 0;

	while (1) {
		//방문한 경우 cache에 기록
		cache[pos.col][pos.row] = 1;
		//8방향 변위에 대해 범위/방문여부/진출가능여부 조사
		for (i = 0; i < 8; i++) {
			if (isScope(pos, i)) {
				//해당 변위가 도착지인 경우 종료
				if (isGoal(pos, i)) {
					printf("Goal!\n");
					return;
				}
				if (!isVisited(pos, i) && !isPath(pos, i)) {
					//갈 수 있는 위치인 경우 스택에 저장
					push(pos, offset[i]);
				}
			}
		}
		if (isEmpty()) {
			printf("Can't find any way\n");
			return;
		}
		//pop하여 방금 저장한 이동가능한 위치를 하나씩 뽑아서 다시 8방향 조사
		//갈수 없다면 상기의 for문 내에서 push가 없으므로 stack에서 계속 pop되어 아직 조사하지 않은 이동 가능 위치가 나올때 까지 pop
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