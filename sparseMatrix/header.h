#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct matrixForm {
	double* aa;
	int* ja;
}matrixForm;

typedef struct vectorForm {
	double* val;
}vectorForm;

vectorForm* setVector(FILE*, int*, int);
matrixForm* setMatrix(FILE*, int*, int*, int*);
void mmult(matrixForm*, vectorForm*, vectorForm*, int, int*, int*, double*, double*);
double normEval(vectorForm*, int);
