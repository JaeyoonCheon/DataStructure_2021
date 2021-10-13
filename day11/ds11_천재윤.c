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

listPointer sortedList(FILE* fp) {
	listPointer list = NULL;
	int data;
	int x;

	while (!feof(fp)) {
		fscanf(fp, "%d", &data);

		insert(&list, data);
	}

	return list;
}

listPointer intersection(listPointer *A, listPointer *B) {
	listPointer result = NULL;
	listPointer pA, pB;
	int data;
	int x;

	pA = *A;
	pB = *B;

	while(pB && pA) {
		if (pA->data == pB->data) {
			insert(&result, pA->data);
			pA = pA->link;
			pB = pB->link;
		}
		else if (pA->data < pB->data) {
			pA = pA->link;
		}
		else {
			pB = pB->link;
		}
	}

	return result;
}

int main() {
	int i;
	FILE* in1, * in2;
	listPointer A, B, intersectionList, unionList;

	printf("컴퓨터학부 2016115430 천재윤\n");

	in1 = fopen("in1.txt", "r");
	in2 = fopen("in2.txt", "r");

	A = sortedList(in1);
	B = sortedList(in2);
	
	printf("A: ");
	printList(&A);
	printf("B: ");
	printList(&B);

	intersectionList = intersection(&A, &B);
	printf("교집합: ");
	printList(&intersectionList);
}