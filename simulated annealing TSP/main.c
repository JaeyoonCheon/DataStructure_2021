#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PATH 100
#define MAX_LEN 100

double cost[MAX_PATH][MAX_PATH];
int originPath[MAX_PATH], revisedPath[MAX_PATH], swapped[MAX_PATH];
int num = 12, swap, minDist = 999999;

double evalCost(int path[]) {
	double distance = 0;
	int i, j;

	for (i = 0; i < num; i++) {
		distance += cost[path[i]][path[i + 1]];
	}

	return distance;
}

void initSeq(int path[], int starting) {
	int i, j;

	for (i = 0; i < num+1; i++) {
		if (i == starting) {
			path[i] = 0;
		}
		else {
			path[i] = i;
		}
	}
	path[0] = starting;
	path[num] = starting;
}

void swapLocation(int path[], int from, int to) {
	int i, temp, idx1 = 0, idx2 = 0;

	for (i = 0; i < num; i++) {
		if (path[i] == from) {
			idx1 = i;
			continue;
		}
		if (path[i] == to) {
			idx2 = i;
			continue;
		}
	}

	temp = path[idx1];
	path[idx1] = path[idx2];
	path[idx2] = temp;
}

void revise(int path[]) {
	int i, j, size = -1;
	int idx1, idx2, flag = 0;;

	for (i = 0; i < swap; i++) {
		size++;
		while (flag == 0) {
			idx1 = rand() % 11 + 1;
			flag = 1;
			swapped[size] = idx1;
			for (j = 0; j < size; j++) {
				if (swapped[j] == idx1) {
					flag = 0;
					break;
				}
			}
		}
		size++;
		flag = 0;
		while (flag == 0) {
			idx2 = rand() % 11 + 1;
			flag = 1;
			swapped[size] = idx2;
			for (j = 0; j < size; j++) {
				if (swapped[j] == idx2) {
					flag = 0;
					break;
				}
			}
		}

		swapLocation(path, idx1, idx2);
	}

	
}

int compare() {
	int i;
	double currSum = 0, revisedSum = 0;

	currSum = evalCost(originPath);
	revise(revisedPath);
	revisedSum = evalCost(revisedPath);

	if (currSum > revisedSum) {
		minDist = revisedSum;
		for (i = 1; i < num-1; i++) {
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

	swap = ((num / 2) - 2) / 2;

	initSeq(originPath, 0);
	initSeq(revisedPath, 0);

	while (count < 100) {
		if (compare() == 1) {
			count = 0;
		}
		else {
			count++;
		}
		repeat++;
	}

	printf("!");
}