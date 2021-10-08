#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 10

typedef struct stack* stackPointer;
typedef struct element {
	int key;
}element;
typedef struct stack {
	element data;
	stackPointer link;
};
stackPointer top[MAX_STACK_SIZE];