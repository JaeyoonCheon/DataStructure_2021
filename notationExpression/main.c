#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_EXP_SIZE 100

//infix -> postfix
//1. 연산식 string char배열로 입력받음
//2. string이 괄호가 포함된 식인 지 확인
//3. 0 index부터 단어 겁사
//4. (->스택에 저장
//5. 숫자 바로 출력(연속된 숫자인지 확인 필요)
//6. 연산자를 만나면 스택에 저장
//7. 스택에 연산자가 top인데 연산자를 만나면 저장된 연산자를 pop하여 출력
//8.)->stack top의(pop하여 제거

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