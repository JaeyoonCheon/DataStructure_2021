#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_EXP_SIZE 100
#define MAX_STR_SIZE 255

typedef enum precedence {
	lparen,
	rparen,
	plus,
	minus,
	times,
	divide,
	mod,
	eos,
	operand,
} precedence;

int stack[MAX_STACK_SIZE];
char expr[MAX_STR_SIZE];
char postfixExpr[MAX_STR_SIZE];
int top = -1;
int first = 0;

int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

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

precedence getToken(char* symbol, int* n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}

//postfix 표현식의 결과 계산
//stack을 이용하여 
int eval() {
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0;
	top = -1;
	
	token = getToken(&symbol, &n);

	while (token != eos) {
		if (token == operand) {
			push(symbol - '0');
		}
		else {
			op2 = pop();
			op1 = pop();
			switch (token) {
			case plus:
				push(op1 + op2);
				break;
			case minus:
				push(op1 - op2);
				break;
			case times:
				push(op1 * op2);
				break;
			case divide:
				push(op1 / op2);
				break;
			case mod:
				push(op1 % op2);
				break;
			}
		}
		token = getToken(&symbol, &n);
	}
	return pop();
}

void printToken(precedence token)
{/* print out the character equivalent of the token */
	switch (token) {
	case  plus:   
		printf("+");
		postfixExpr[first++] = '+';
		break;
	case  minus:  
		printf("-");
		postfixExpr[first++] = '-';
		break;
	case  divide: 
		printf("/");
		postfixExpr[first++] = '/';
		break;
	case  times:  
		printf("*");
		postfixExpr[first++] = '*';
		break;
	case  mod:    
		printf("%");
		postfixExpr[first++] = '%';
	}
}

//infix -> postfix
//1. 연산식 string char배열로 입력받음
//2. string이 괄호가 포함된 식인 지 확인
//3. 0 index부터 단어 겁사
//4. (->스택에 저장
//5. 숫자 바로 출력(연속된 숫자인지 확인 필요)
//6. 연산자를 만나면 스택에 저장
//7. 스택에 연산자가 top인데 연산자를 만나면 저장된 연산자를 pop하여 출력
//8.)->stack top의(pop하여 제거

void postfix() {
	char symbol;
	precedence token;
	int n = 0;

	top = 0;
	stack[0] = eos;

	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		if (token == operand) {
			printf("%c", symbol);
			postfixExpr[first++] = symbol;
		}
		else if (token == rparen) {
			while (stack[top] != lparen) {
				printToken(pop());
			}
			pop();
		}
		else {
			while (isp[stack[top]] >= icp[token]) {
				printToken(pop());
			}
			push(token);
		}
	}
	while ((token = pop()) != eos) {
		printToken(token);
	}
	postfixExpr[first++] = '\0';
	printf("\n");
}

int main() {
	int i;

	printf("input INFIX expression : ");
	if (!scanf("%s", expr)) {
		fprintf(stderr, "Can't read expresstion\n");
		exit(1);
	}
	
	printf("POSTFIX expression : ");
	postfix();

	strcpy(expr, postfixExpr);

	printf("result : %d\n", eval());
}