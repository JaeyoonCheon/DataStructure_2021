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

//postfix ǥ������ ��� ���
//stack�� �̿��Ͽ� postfix�� ���
int eval() {
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0;
	top = -1;
	
	//ǥ������ ���� �տ��� ������ ���ڸ� �ϳ� �� �޾� ��
	token = getToken(&symbol, &n);

	while (token != eos) {
		// �ǿ������� ���, '0'�� ���� �����Ͽ� ���� ���ڰ� ����ǵ��� ���ÿ� push
		if (token == operand) {
			push(symbol - '0');
		}
		// �����ڸ� �����ٸ�, ���ÿ��� �ǿ����� 2���� �̾� �ش� �����ڷ� �� �ǿ����ڸ� ��� �� ���ÿ� push
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
	//������ ���ÿ� ���� top�� ��� postfix���� ���� �����
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
//1. ����� string char�迭�� �Է¹���
//2. string�� ��ȣ�� ���Ե� ���� �� Ȯ��
//3. 0 index���� �ܾ� �̻�
//4. (->���ÿ� ����
//5. ���� �ٷ� ���(���ӵ� �������� Ȯ�� �ʿ�)
//6. �����ڸ� ������ ���ÿ� ����
//7. ���ÿ� �����ڰ� top�ε� �����ڸ� ������ ����� �����ڸ� pop�Ͽ� ���
//8.)->stack top��(pop�Ͽ� ����

void postfix() {
	char symbol;
	precedence token;
	int n = 0;

	//���� ó�� ���ÿ� eos�� �־���´�.
	top = 0;
	stack[0] = eos;

	//�տ������� �� ĭ�� �̾Ƽ� postfix ������ ������ �� ���� �� ó��
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		// �ǿ������� ��� �״�� ���
		if (token == operand) {
			printf("%c", symbol);
			postfixExpr[first++] = symbol;
		}
		// ������ ��ȣ�� ��� ���ÿ� ����� ���ҵ��� ���� ��ȣ�� ���Ë� ���� pop
		else if (token == rparen) {
			while (stack[top] != lparen) {
				printToken(pop());
			}
			//���� ��ȣ�� �̾� ����
			pop();
		}
		//�������� ���, ���� ������ top�� �ִ� �����ڿ� ���Ͽ� �켱������ ����
		//������ �켱������ ���� ��ū���� ������ �� ���� pop�Ͽ� ���
		else {
			while (isp[stack[top]] >= icp[token]) {
				printToken(pop());
			}
			//���� ��ū�� push
			push(token);
		}
	}
	//������ ������ �������� �� ���ÿ� ����� ���ҵ��� pop�Ͽ� ��� ���
	while ((token = pop()) != eos) {
		printToken(token);
	}
	//������ \0 ���� �߰�
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