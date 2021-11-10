#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT 200
#define HEAP_FULL(n) (n==MAX_ELEMENT-1)
#define HEAP_EMPTY(n) (!n)

typedef struct element {
	int key;
}element;

element* heap;

void push(element item, int* n) {
	int i;

	if (HEAP_FULL(*n)) {
		fprintf(stderr, "The heap is full.\n");
		exit(EXIT_FAILURE);
	}
	i = ++(*n);
	/*
	1. 처음 삽입이 아닌 경우
	2. 삽입 값이 현 빈자리의 부모의 값보다 큰 경우
	부모의 값을 현재 빈자리에 넣고 빈 자리의 인덱스를 부모 위치로 지정
	*/
	while ((i != 1) && (item.key > heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

element pop(int* n) {
	int parent, child;
	element item, temp;

	if (HEAP_EMPTY(*n)) {
		fprintf(stderr, "The heap is empty.\n");
		exit(EXIT_FAILURE);
	}
	item = heap[1];
	temp = heap[(*n)--];
	parent = 1;
	child = 2;
	while (child <= *n) {
		if ((child < *n) && (heap[child].key < heap[child + 1].key)) {
			child++;
		}
		if (temp.key >= heap[child].key) {
			break;
		}
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}

element* create() {
	element* temp;

	temp = (element*)malloc(sizeof(element) * MAX_ELEMENT);

	return temp;
}

int main() {
	FILE* fp;
	int n = 0;

	fp = fopen("in.txt", "r");


}