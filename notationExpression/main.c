#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_EXP_SIZE 100

//infix -> postfix
//1. ����� string char�迭�� �Է¹���
//2. string�� ��ȣ�� ���Ե� ���� �� Ȯ��
//3. 0 index���� �ܾ� �̻�
//4. (->���ÿ� ����
//5. ���� �ٷ� ���(���ӵ� �������� Ȯ�� �ʿ�)
//6. �����ڸ� ������ ���ÿ� ����
//7. ���ÿ� �����ڰ� top�ε� �����ڸ� ������ ����� �����ڸ� pop�Ͽ� ���
//8.)->stack top��(pop�Ͽ� ����

char stack[MAX_STACK_SIZE];
top = -1;

void push(char exp) {
	if (top >= MAX_STACK_SIZE - 1) {
		printf("stack full\n");
		exit(EXIT_FAILURE);
	}

	stack[++top] = exp;
}

char pop() {
	if (top < 0) {
		printf("stack empty\n");
		exit(1);
	}
	
	return stack[top--];
}

int main() {
	int i;
	char exp[MAX_EXP_SIZE];

	createStack();

	if (!scanf("%s", exp)) {
		fprintf(stderr, "Can't read expresstion\n");
		exit(1);
	}

	do {

	} while (top > -1);
}