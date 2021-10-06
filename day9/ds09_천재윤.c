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
	printf("%d ", tail->data);
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

	//list = createNode();

	fp = fopen("in1.txt", "r");

	printf("���� 1: ");

	while (!feof(fp)) {
		fscanf(fp, "%d", &data);

		insertLast(&list, data);
	}
	printList(&list);
}

void P2() {
	FILE* fp;
	listPointer list = NULL;
	int data;

	//list = createNode();

	fp = fopen("in2.txt", "r");

	printf("���� 2: ");

	while (!feof(fp)) {
		fscanf(fp, "%d", &data);

		insertFirst(&list, data);
	}
	printList(&list);
}

int main() {
	printf("��ǻ���к� 2016115430 õ����\n");
	P1();
	printf("\n");
	P2();
}