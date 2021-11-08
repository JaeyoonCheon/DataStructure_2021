#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* parent;

void weightedUnion(int i, int j) {
	int temp = parent[i] + parent[j];

	if (parent[i] >= parent[j]) {
		parent[i] = j;
		parent[j] = temp;
	}
	else {
		parent[j] = i;
		parent[i] = temp;
	}
}

int collapsingFind(int i) {
	int root, trail, lead;

	for (root = i; parent[root] >= 0; root = parent[root]) {}
	
	for (trail = i; trail != root; trail = lead) {
		lead = parent[trail];
		parent[trail] = root;
	}
	return root;
}

void printSet(int n) {
	int i;

	for (i = 0; i < n + 1; i++) {
		printf("%d ", parent[i]);
	}
	printf("\n");
}

int main() {
	FILE* fp;
	int n, first, last;
	char command;
	int i, result;

	printf("컴퓨터학부 2016115430 천재윤\n");

	fp = fopen("in.txt", "r");

	fscanf(fp, "%d", &n);

	parent = (int*)malloc(sizeof(int) * (n + 1));

	for (i = 0; i < n + 1; i++) {
		parent[i] = -1;
	}

	while (!feof(fp)) {
		fscanf(fp, "%c ", &command);

		switch (command) {
		case 'U':
			fscanf(fp, "%d %d", &first, &last);
			printf("U %d %d: ", first, last);
			printf("\t");
			weightedUnion(first, last);
			printSet(n);
			break;
		case 'F':
			fscanf(fp, "%d", &first);
			printf("F %d: ", first);
			printf("\t");
			result = collapsingFind(first);
			printSet(n);
			printf("%d\n", result);
			break;
		}
	}

}