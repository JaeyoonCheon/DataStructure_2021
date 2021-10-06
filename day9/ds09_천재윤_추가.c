#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
};

void printList(listPointer* first) {
	listPointer tail;
	tail = (*first);

	while (tail->link != NULL) {
		printf("%d ", tail->data);
		tail = tail->link;
	}
	printf("%d", tail->data);
}

void insertFirst(listPointer* first, int _data) {
	listPointer	temp;

	//temp = createNode();
	temp = (listPointer)malloc(sizeof(listPointer));

	temp->data = _data;
	temp->link = NULL;

	if (*first) {
		temp->link = (*first);
		(*first) = temp;
	}
	else {
		(*first) = temp;
	}
}

void insertLast(listPointer* first, int _data) {
	listPointer	temp;
	listPointer tail;

	//temp = createNode();
	temp = (listPointer)malloc(sizeof(listPointer));
	temp->data = _data;
	temp->link = NULL;

	tail = (*first);

	if (*first) {
		while (tail->link != NULL && tail->link->data <= _data) {
			tail = tail->link;
		}

		temp->link = tail->link;
		tail->link = temp;
	}
	else {
		(*first) = temp;
	}
}

void insert(listPointer* first, int _data) {
	listPointer	temp;
	listPointer tail;

	//temp = createNode();
	temp = (listPointer)malloc(sizeof(listPointer));
	temp->data = _data;
	temp->link = NULL;

	tail = (*first);

	if (*first) {
		while (tail->link != NULL) {
			tail = tail->link;
		}

		temp->link = tail->link;
		tail->link = temp;
	}
	else {
		(*first) = temp;
	}
}

void P1() {
	FILE* fp;
	listPointer list = NULL;
	int data;
	int x;

	//list = createNode();

	fp = fopen("in.txt", "r");

	while (!feof(fp)) {
		fscanf(fp, "%d", &data);

		if (list) {
			if (list->data <= data) {
				insertLast(&list, data);
			}
			else {
				insertFirst(&list, data);
			}
		}
		else {
			insertLast(&list, data);
		}
	}

	while (1) {
		scanf("%d", &x);
		if (x < 0) {
			return;
		}
		else {
			if (list->data <= x) {
				insertLast(&list, x);
			}
			else {
				insertFirst(&list, x);
			}
		}
		printList(&list);
		printf("\n");
	}

}

int main() {
	printf("컴퓨터학부 2016115430 천재윤\n");
	P1();
}