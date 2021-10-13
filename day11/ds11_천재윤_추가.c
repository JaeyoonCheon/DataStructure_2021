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

	while (pointer != NULL) {
		printf("%d ", pointer->data);
		pointer = pointer->link;
	}
	//printf("%d", pointer->data);
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
		//�߰��ϴ� �����Ͱ� first�� data���� ���� �� �տ� �߰�
		if (pointer->data > _data) {
			temp->link = (*first);
			(*first) = temp;
		}
		//�̿��� ���� ������� ������ ���鼭 �ٴ��� ���� _data���� ū ��� ���� �� �ڿ� �߰�
		else {
			while (pointer->link != NULL && pointer->link->data <= _data) {
				pointer = pointer->link;
			}

			temp->link = pointer->link;
			pointer->link = temp;
		}
	}
	else {
		//linked list�� �ƹ� node�� ���� ���
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

listPointer unionLists(listPointer* A, listPointer* B) {
	listPointer result = NULL;
	listPointer pA, pB;
	int data;
	int x;

	pA = *A;
	pB = *B;

	while (pB && pA) {
		if (pA->data == pB->data) {
			insert(&result, pA->data);
			pA = pA->link;
			pB = pB->link;
		}
		else if (pA->data < pB->data) {
			insert(&result, pA->data);
			pA = pA->link;
		}
		else {
			insert(&result, pB->data);
			pB = pB->link;
		}
	}
	while (pA) {
		insert(&result, pA->data);
		pA = pA->link;
	}
	while (pB) {
		insert(&result, pB->data);
		pB = pB->link;
	}

	return result;
}

int main() {
	int i;
	FILE* in1, * in2;
	listPointer A, B, unionList;

	printf("��ǻ���к� 2016115430 õ����\n");

	in1 = fopen("in1.txt", "r");
	in2 = fopen("in2.txt", "r");

	A = sortedList(in1);
	B = sortedList(in2);

	printf("A: ");
	printList(&A);
	printf("B: ");
	printList(&B);

	unionList = unionLists(&A, &B);
	printf("������: ");
	printList(&unionList);
}