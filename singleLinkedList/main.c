#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define MALLOC(p,s) \
if ((p = malloc(s)) == NULL) {	\
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
}

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
}listNode;

void printList(listPointer* first) {
	listPointer pointer;
	pointer = (*first);

	while (pointer->link != NULL) {
		printf("%d ", pointer->data);
		pointer = pointer->link;
	}
	printf("%d", pointer->data);
	printf("\n");
}

void delete(listPointer* first, int _data) {
	listPointer front = NULL;
	listPointer pointer;
	pointer = (*first);

	while (pointer->link != NULL && pointer->data != _data) {
		front = pointer;
		pointer = pointer->link;
	}
	if (pointer->link == NULL && pointer->data != _data) {
		printf("Not exist!\n");
		return;
	}
	printf("delete %d\n", pointer->data);
	if (front) {
		front->link = pointer->link;
	}
	else {
		(*first) = (*first)->link;
	}
}

void insert(listPointer* first, int _data) {
	listPointer	temp;
	listPointer pointer;

	MALLOC(temp, sizeof(listNode));
	//temp = (listPointer)malloc(sizeof(listNode));
	temp->data = _data;
	temp->link = NULL;

	pointer = (*first);

	if (pointer) {
		//추가하는 데이터가 first의 data보다 작을 때 앞에 추가
		if (pointer->data >= _data) {
			temp->link = (*first);
			(*first) = temp;
		}
		//이외의 값은 순서대로 조사해 가면서 다다음 값이 _data보다 큰 경우 다음 값 뒤에 추가
		else {
			while (pointer->link != NULL && pointer->link->data <= _data) {
				pointer = pointer->link;
			}

			temp->link = pointer->link;
			pointer->link = temp;
		}
	}
	else {
		//linked list에 아무 node가 없는 경우
		(*first) = temp;
	}
}

void insertFirst(listPointer* first, int _data) {
	listPointer	temp;

	MALLOC(temp, sizeof(listPointer));
	//temp = (listPointer)malloc(sizeof(listPointer));

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

	MALLOC(temp, sizeof(listPointer));
	//temp = (listPointer)malloc(sizeof(listPointer));
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

void sortedList() {
	FILE* fp;
	listPointer list = NULL;
	int data;
	int x;

	fp = fopen("in.txt", "r");

	while (!feof(fp)) {
		fscanf(fp, "%d", &data);

		insert(&list, data);
	}

	while (1) {
		scanf("%d", &x);
		insert(&list, x);
		printList(&list);
		printf("\n");
	}
}

void unSortedList() {
	FILE* fp;
	listPointer list = NULL;
	char dir[5];
	int data;
	int x;

	fp = fopen("in.txt", "r");

	printf("Input file data at head or tail? head/tail : ");
	scanf("%s", dir);
	printf("\n");
	getchar();

	while (!feof(fp)) {
		fscanf(fp, "%d", &data);

		if (!strcmp(dir, "head")) {
			insertFirst(&list, data);
		}
		else if (!strcmp(dir, "tail")) {
			insertLast(&list, data);
		}
		else {
			return;
		}
	}
	printList(&list);


	while (1) {
		printf("Input data at head or tail // Delete data? head/tail/del : ");
		scanf("%s", dir);
		getchar();
		scanf("%d", &x);

		if (!strcmp(dir, "head")) {
			insertFirst(&list, x);
		}
		else if (!strcmp(dir, "tail")) {
			insertLast(&list, x);
		}
		else if (!strcmp(dir, "del")) {
			delete(&list, x);
		}
		else {
			return;
		}

		printList(&list);
		printf("\n");
	}
}

int main() {
	char isSort;
	int i;

	while (1) {
		printf("Sorted linked list? Y/N : ");
		scanf("%c", &isSort);
		printf("\n");

		if (isSort == 'Y') {
			sortedList();
		}
		else if (isSort == 'N') {
			unSortedList();
		}
		else {
			continue;
		}
	}
}