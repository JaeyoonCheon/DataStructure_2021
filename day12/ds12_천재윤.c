#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1
#define MALLOC(p,s) \
if ((p = malloc(s)) == NULL) {	\
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
}

typedef struct node* nodePointer;
typedef struct node {
	int data;
	nodePointer link;
}node;

int main() {
	FILE* in;
	short int out[MAX_SIZE];
	nodePointer seq[MAX_SIZE];
	nodePointer x, y, top;
	int i, j, n;

	printf("컴퓨터학부 2016115430 천재윤\n");

	in = fopen("in.txt", "r");

	fscanf(in, "%d", &n);

	for (i = 0; i < n; i++) {
		out[i] = TRUE;
		seq[i] = NULL;
	}

	while (!feof(in)) {
		fscanf(in, "%d %d", &i, &j);
		
		MALLOC(x, sizeof(*x));
		x->data = j;
		x->link = seq[i];
		seq[i] = x;
		
		MALLOC(x, sizeof(*x));
		x->data = i;
		x->link = seq[j];
		seq[j] = x;
	}

	for (i = 0; i < n; i++) {
		if (out[i]) {
			printf("%d ", i);
			out[i] = FALSE;
			x = seq[i];
			top = NULL;

			while (1) {
				while (x) {
					j = x->data;
					if (out[j]) {
						printf("%d ", j);
						out[j] = FALSE;
						y = x->link;
						x->link = top;
						top = x;
						x = y;
					}
					else {
						x = x->link;
					}
				}
				if (!top) {
					printf("\n");
					break;
				}
				x = seq[top->data];
				top = top->link;
			}
		}
	}
}