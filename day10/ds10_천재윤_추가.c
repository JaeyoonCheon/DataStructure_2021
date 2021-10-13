#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_EXP_SIZE 100
#define MAX_STR_SIZE 255

#define TRUE 1
#define FALSE 0

typedef enum precedence {
	lparen,
	rparen,
	less,
	greater,
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

// 부등호 연산자 우선순위가 stack, incoming에서 더 낮음
int isp[] = { 0, 19, 8, 8, 12, 12, 13, 13, 13, 0 };
int icp[] = { 20, 19, 8, 8, 12, 12, 13, 13, 13, 0 };

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

// 부등호 연산자 우선순위 추가
precedence getToken(char* symbol, int* n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '<': return less;
	case '>': return greater;
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
//stack을 이용하여 postfix식 계산
int eval() {
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0;
	top = -1;

	//표현식의 가장 앞에서 부터의 글자를 하나 씩 받아 옴
	token = getToken(&symbol, &n);

	while (token != eos) {
		// 피연산자의 경우, '0'을 빼고 저장하여 실제 숫자가 저장되도록 스택에 push
		if (token == operand) {
			push(symbol - '0');
		}
		// 연산자를 만난다면, 스택에서 피연산자 2개를 뽑아 해당 연산자로 두 피연산자를 계산 후 스택에 push
		else {
			op2 = pop();
			op1 = pop();
			switch (token) {
			case less:
				if (op1 < op2)
					push(TRUE);
				else
					push(FALSE);
				break;
			case greater:
				if (op1 > op2)
					push(TRUE);
				else
					push(FALSE);
				break;
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
	//마지막 스택에 남은 top은 모든 postfix식이 계산된 경우임
	return pop();
}

void printToken(precedence token)
{/* print out the character equivalent of the token */
	switch (token) {
	case  less:
		printf("<");
		postfixExpr[first++] = '<';
		break;
	case  greater:
		printf(">");
		postfixExpr[first++] = '>';
		break;
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
		printf("%%");
		postfixExpr[first++] = '%';
		break;
	}
}

//infix -> postfix
//1. 연산식 string char배열로 입력받음
//2. string이 괄호가 포함된 식인 지 확인 (포함o 가정)
//3. 0 index부터 단어 겁사
//4. (->스택에 저장
//5. 숫자 바로 출력(연속된 숫자인지 확인 필요) (미구현)
//6. 연산자를 만나면 스택에 저장
//7. 스택에 연산자가 top인데 연산자를 만나면 저장된 연산자를 pop하여 출력
//8. )->stack top의 ( pop하여 제거

void postfix() {
	char symbol;
	precedence token;
	int n = 0;

	//가장 처음 스택에 eos를 넣어놓는다.
	top = 0;
	stack[0] = eos;

	//앞에서부터 한 칸씩 뽑아서 postfix 문장의 끝까지 한 글자 씩 처리
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		// 피연산자의 경우 그대로 출력
		if (token == operand) {
			printf("%c", symbol);
			postfixExpr[first++] = symbol;
		}
		// 오른쪽 괄호의 결우 스택에 저장된 원소들을 왼쪽 괄호가 나올떄 까지 pop
		else if (token == rparen) {
			while (stack[top] != lparen) {
				printToken(pop());
			}
			//왼쪽 괄호도 뽑아 제거
			pop();
		}
		//연산자의 경우, 현재 스택의 top에 있는 연산자와 비교하여 우선순위에 따라
		//스택의 우선순위가 현재 토큰보다 낮아질 때 까지 pop하여 출력
		else {
			while (isp[stack[top]] >= icp[token]) {
				printToken(pop());
			}
			//현재 토큰은 push
			push(token);
		}
	}
	//문장의 끝까지 도달했을 때 스택에 저장된 원소들을 pop하여 모두 출력
	while ((token = pop()) != eos) {
		printToken(token);
	}
	//마지막 \0 문자 추가
	postfixExpr[first++] = '\0';
	printf("\n");
}

int main() {
	FILE* in;
	int i;

	printf("컴퓨터학부 2016115430 천재윤\n");

	in = fopen("in.txt", "r");

	if (!fscanf(in, "%s", expr)) {
		fprintf(stderr, "Can't read expression\n");
		exit(1);
	}

	printf("postfix : ");
	postfix();

	strcpy(expr, postfixExpr);

	printf("Evaluation result : %d\n", eval());
}