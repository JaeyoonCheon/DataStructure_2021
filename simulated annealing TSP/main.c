#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PATH 200
#define MAX_LEN 200

double cost[MAX_PATH][MAX_PATH];
int originPath[MAX_PATH], revisedPath[MAX_PATH], swapped[MAX_PATH];
int num = 12, swap, minDist = 999999, starting = 0;

double evalCost(int path[]) {
	double distance = 0;
	int i, j;

	for (i = 0; i < num + 1; i++) {
		distance += cost[path[i]][path[i + 1]];
	}

	return distance;
}

void initSeq(int path[], int starting) {
	int i, j;

	//for (i = 0; i < num+1; i++) {
	//	if (i == starting) {
	//		path[i] = 0;
	//	}
	//	else {
	//		path[i] = i;
	//	}
	//}
	//path[0] = starting;
	//path[num] = starting;

	path[0] = 0;
	path[1] = 2;
	path[2] = 9;
	path[3] = 4;
	path[4] = 7;
	path[5] = 5;
	path[6] = 3;
	path[7] = 10;
	path[8] = 1;
	path[9] = 8;
	path[10] = 6;
	path[11] = 11;
	path[12] = 0;

	// minimum path
	//path[0] = 0;
	//path[1] = 1;
	//path[2] = 2;
	//path[3] = 3;
	//path[4] = 4;
	//path[5] = 5;
	//path[6] = 6;
	//path[7] = 7;
	//path[8] = 8;
	//path[9] = 9;
	//path[10] = 10;
	//path[11] = 11;
	//path[12] = 0;
}

void swapLocation(int path[], int from, int to) {
	int i, temp, idx1 = 0, idx2 = 0;

	temp = path[from];
	path[from] = path[to];
	path[to] = temp;
}

void revise(int path[], int start) {
	int i, j, size = -1;
	int idx1, idx2, flag = 0;;

	for (i = 0; i < swap; i++) {
		idx1 = rand() % 11 + 1;
		if (idx1 == start)
			continue;

		idx2 = rand() % 11 + 1;
		if (idx2 == start || idx2 == idx1)
			continue;

		swapLocation(path, idx1, idx2);
	}


}

int compare(int start) {
	int i;
	double currSum = 0, revisedSum = 0;

	currSum = evalCost(originPath);
	if (minDist == 999999)
		minDist = currSum;
	revise(revisedPath, start);
	revisedSum = evalCost(revisedPath);

	if (currSum > revisedSum) {
		minDist = revisedSum;
		for (i = 1; i < num; i++) {
			originPath[i] = revisedPath[i];
		}
		return 1;
	}
	return 0;
}

int main() {
	/*
	1. cost 입력 배열 구성
	2. TSP 순열 초기값 설정
	3. 랜덤 index 2k개 뽑아서 교환
	4. 근접 해와 비교해서 작으면 해로 대체
	5. 반복 하면서 교환 변수 k 감소
	*/

	FILE* fin;
	char* line;
	char token;
	int i, j, count = 0, repeat = 0;
	double data;

	fin = fopen("tsp.txt", "r");

	srand(time(NULL));

	i = 0;
	while (!feof(fin)) {
		for (j = 0; j < num; j++) {
			fscanf(fin, "%lf", &data);
			cost[i][j] = data;
		}
		i++;
	}


	initSeq(originPath, 0);
	initSeq(revisedPath, 0);

	while (repeat < 100000) {
		if (compare(starting) == 1) {
			repeat = 0;
		}
		else {
			repeat++;
		}
		swap = rand() % num + 1;
	}

	printf("%d", minDist);
}