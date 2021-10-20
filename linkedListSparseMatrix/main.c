#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50

typedef enum { head, entry } tagfield;
typedef struct matrixNode* matrixPointer;
typedef struct entryNode {
	int row;
	int col;
	int value;
}entryNode;
typedef struct matrixNode {
	matrixPointer down;
	matrixPointer right;
	tagfield tag;
	union {
		matrixPointer next;
		entryNode entry;
	} u;
}matrixNode;

matrixPointer hdnode[MAX_SIZE];

matrixPointer mread() {
	int numRows, numCols, numTerms, numHeads, i;
	int row, col, value, currentRow;
	matrixPointer temp, last, node;

	printf("Enter the number of rows, columns and number of nonzero terms: ");
	scanf("%d%d%d", &numRows, &numCols, &numTerms);

	numHeads = (numCols > numRows) ? numCols : numRows;
	node = newNode();
	node->tag = entry;
	node->u.entry.row = numRows;
	node->u.entry.col = numCols;

	if (!numHeads) {
		node->right = node;
	}
	else {
		if (i = 0; i < numHeads; i++) {
			temp = newNode;
			hdnode[i] = temp;
			hdnode[i]->tag = head;
		}
	}
}