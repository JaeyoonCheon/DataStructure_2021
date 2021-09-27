#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101

#define COMPARE(x,y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

void tadd(int, int, int, int, int*, int*);
void attach(int, char);

typedef struct tag {
	int num;
	char name;
}tag;

tag terms[MAX_TERMS];
int avail = 0;
int start1, start2, finish1, finish2;
int startD = 0, finishD = 0;

int main() {
	FILE* in1, * in2, * output;
	int i, n;

	printf("컴퓨터학부 2016115430 천재윤\n");

	in1 = fopen("in1.txt", "r");
	in2 = fopen("in2.txt", "r");
	output = fopen("out.txt", "w+");
	;
	for (i = 0; i < MAX_TERMS; i++) {
		terms[i].num = 0;
	}

	start1 = 0;
	finish1 = start1;
	i = start1;
	while(!feof(in1)) {
		fscanf(in1, "%d", &terms[i].num);
		while(1) {
			fscanf(in1, "%c", &terms[i].name);
			if (terms[i].name == ' ' || terms[i].name == '\n') {
				continue;
			}
			break;
		}
		i++;
		avail++;
		finish1++;
	}

	avail--;
	finish1 -= 2;

	start2 = finish1 + 1;
	finish2 = start2;
	i = start2;
	while (!feof(in2)) {
		fscanf(in2, "%d", &terms[i].num);
		while (1) {
			fscanf(in2, "%c", &terms[i].name);
			/*printf("!%c!", terms[i].name);*/
			if (terms[i].name == ' ' || terms[i].name == '\n') {
				continue;
			}
			break;
		}
		i++;
		avail++;
		finish2++;
	}

	avail--;
	finish2 -= 2;

	tadd(start1, finish1, start2, finish2, &startD, &finishD);

	for (i = startD; i < finishD + 1; i++) {
		fprintf(output, "%d %c\n", terms[i].num, terms[i].name);
	}

	fclose(in1);
	fclose(in2);
	fclose(output);
}

void tadd(int start1, int finish1, int start2, int finish2, int* startD, int* finishD) {
	
	*startD = avail;

	while (start1 <= finish1 && start2 <= finish2) {
		if(terms[start1].num < terms[start2].num) {
			attach(terms[start1].num, terms[start1].name);
			start1++;
		}
		else if(terms[start1].num > terms[start2].num) {
			attach(terms[start2].num, terms[start2].name);
			start2++;
		}
		else {
			attach(terms[start2].num, terms[start2].name);
			start1++;
			start2++;
		}
	}
	for (; start1 <= finish1; start1++) {
		attach(terms[start1].num, terms[start1].name);
	}
	for (; start2 <= finish2; start2++) {
		attach(terms[start2].num, terms[start2].name);
	}
	*finishD = avail - 1;
}

void attach(int num, char name) {
	if (avail >= MAX_TERMS) {
		fprintf(stderr, "too many terms in the polynomial\n");
		exit(EXIT_FAILURE);
	}
	terms[avail].num = num;
	terms[avail++].name = name;
}