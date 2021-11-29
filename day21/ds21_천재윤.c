//#pragma warning(disable: 4996)
//
//#include <stdio.h>
//#include <stdlib.h>
//
//#define MAX_ARR_SIZE 100
//
//typedef struct element {
//	int x;
//	int y;
//	int z;
//}element;
//
//int listMerge(element a[], int link[], int start1, int start2, char keyword) {
//	int last1, last2, lastResult = 0;
//
//	for (last1 = start1, last2 = start2; last1 && last2;) {
//		switch (keyword)
//		{
//		case 'X':
//			if (a[last1].x >= a[last2].x) {
//				link[lastResult] = last1;
//				lastResult = last1;
//				last1 = link[last1];
//			}
//			else {
//				link[lastResult] = last2;
//				lastResult = last2;
//				last2 = link[last2];
//			}
//			break;
//		case 'Y':
//			if (a[last1].y >= a[last2].y) {
//				link[lastResult] = last1;
//				lastResult = last1;
//				last1 = link[last1];
//			}
//			else {
//				link[lastResult] = last2;
//				lastResult = last2;
//				last2 = link[last2];
//			}
//			break;
//		case 'Z':
//			if (a[last1].z >= a[last2].z) {
//				link[lastResult] = last1;
//				lastResult = last1;
//				last1 = link[last1];
//			}
//			else {
//				link[lastResult] = last2;
//				lastResult = last2;
//				last2 = link[last2];
//			}
//			break;
//		default:
//			break;
//		}
//	}
//
//	if (last1 == 0) {
//		link[lastResult] = last2;
//	}
//	else {
//		link[lastResult] = last1;
//	}
//	return link[0];
//}
//
//int rmergeSort(element a[], int link[], int left, int right, char keyword) {
//	int mid;
//
//	if (left >= right) {
//		return left;
//	}
//	mid = (left + right) / 2;
//	return listMerge(a, link, rmergeSort(a, link, left, mid, keyword), rmergeSort(a, link, mid + 1, right, keyword), keyword);
//}
//
//int main() {
//	FILE* fin, * fout, *eval;
//	element a[MAX_ARR_SIZE];
//	element evaluation[MAX_ARR_SIZE];
//	int link[MAX_ARR_SIZE];
//	int X, Y, Z, i, j, size = 0, starting, evalSize = 0, flag = 0;
//	char keyword;
//	char evalCrit;
//
//	printf("컴퓨터학부 2016115430 천재윤\n");
//	
//	fin = fopen("in.txt", "r");
//
//	while (!feof(fin)) {
//		fscanf(fin, "%d %d %d", &X, &Y, &Z);
//		a[size].x = X;
//		a[size].y = Y;
//		a[size].z = Z;
//		size++;
//	}
//	//size == 4
//
//	for (i = 0; i < MAX_ARR_SIZE; i++) {
//		link[i] = 0;
//	}
//
//	scanf("%c", &keyword);
//
//	starting = rmergeSort(a, link, 0, size-1, keyword);
//
//	fclose(fin);
//
//	fout = fopen("out.txt", "w");
//
//	fprintf(fout, "%c\n", keyword);
//
//	starting = link[0];
//	for (i = 0; i < size; i++) {
//		fprintf(fout, "%d %d %d\n", a[starting].x, a[starting].y, a[starting].z);
//		starting = link[starting];
//	}
//
//	fclose(fout);
//
//	eval = fopen("out.txt", "r");
//
//	fscanf(eval, "%c", &evalCrit);
//
//	while (!feof(eval)) {
//		fscanf(eval, "%d %d %d", &X, &Y, &Z);
//		evaluation[evalSize].x = X;
//		evaluation[evalSize].y = Y;
//		evaluation[evalSize].z = Z;
//		evalSize++;
//	}
//	evalSize--;
//
//	i = 0;
//
//	switch (evalCrit)
//	{
//	case 'X':
//		while (i < evalSize) {
//			if (evaluation[i].x < evaluation[i + 1].x) {
//				printf("fail\n");
//				flag = 1;
//				break;
//			}
//			i++;
//		}
//		if (!flag)
//			printf("success\n");
//		break;
//	case 'Y':
//		while (i < evalSize) {
//			if (evaluation[i].y < evaluation[i + 1].y) {
//				printf("fail\n");
//				flag = 1;
//				break;
//			}
//			i++;
//		}
//		if (!flag)
//			printf("success\n");
//		break;
//	case 'Z':
//		while (i < evalSize) {
//			if (evaluation[i].z < evaluation[i + 1].z) {
//				printf("fail\n");
//				flag = 1;
//				break;
//			}
//			i++;
//		}
//		if (!flag)
//			printf("success\n");
//		break;
//	default:
//		break;
//	}
//}

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef struct element
{
    int key;
    int val1;
    int val2;
}element;

void merge(element* initList, element mergedList[], int i, int m, int n)
{
    int j, k, t;
    j = m + 1;
    k = i;
    while (i <= m && j <= n) {
        if (initList[i].key >= initList[j].key)
            mergedList[k++] = initList[i++];
        else
            mergedList[k++] = initList[j++];
    }
    if (i > m)
        for (t = j; t <= n; t++)
            mergedList[t] = initList[t];
    else
        for (t = i; t <= m; t++)
            mergedList[k + t - i] = initList[t];
}
void mergePass(element* initList, element mergedList[], int n, int s)
{
    int i, j;
    for (i = 1; i <= n - 2 * s + 1; i += 2 * s)
        merge(initList, mergedList, i, i + s - 1, i + 2 * s - 1);
    if (i + s - 1 < n)
        merge(initList, mergedList, i, i + s - 1, n);
    else
        for (j = i; j <= n; j++)
            mergedList[j] = initList[j];
}
void mergeSort(element* a, int n)
{
    int s = 1;
    element extra[MAX_SIZE];
    while (s < n)
    {
        mergePass(a, extra, n, s);
        s *= 2;
        mergePass(extra, a, n, s);
        s *= 2;
    }
}
void input(int k, element* R, int n)
{
    FILE* out;
    fopen_s(&out, "out.txt", "w");
    fprintf_s(out, "%c", k);
    fprintf(out, "\n");
    int i = 1;
    if (k == 'X')
        while (i < n + 1)
        {
            fprintf(out, "%d %d %d\n", R[i].key, R[i].val1, R[i].val2);
            i++;
        }
    else if (k == 'Y')
        while (i < n + 1)
        {
            fprintf(out, "%d %d %d\n", R[i].val1, R[i].key, R[i].val2);
            i++;
        }
    else if (k == 'Z')
        while (i < n + 1)
        {
            fprintf(out, "%d %d %d\n", R[i].val1, R[i].val2, R[i].key);
            i++;
        }
    fclose(out);
}
int main()
{
    printf("��ǻ���к� 2016115413 õ����\n");
    FILE* in, * out;
    errno_t err;
    err = fopen_s(&in, "in.txt", "r");
    int n;
    element* R = (element*)malloc(sizeof(R) * (MAX_SIZE));
    char k;
    scanf_s("%c", &k);
    int i = 1;
    if (k == 'X')
        while (!(feof(in) != 0))
        {
            fscanf_s(in, "%d %d %d", &R[i].key, &R[i].val1, &R[i].val2);
            i++;
        }
    else if (k == 'Y')
        while (!(feof(in) != 0))
        {
            fscanf_s(in, "%d %d %d", &R[i].val1, &R[i].key, &R[i].val2);
            i++;
        }
    else if (k == 'Z')
        while (!(feof(in) != 0))
        {
            fscanf_s(in, "%d %d %d", &R[i].val1, &R[i].val2, &R[i].key);
            i++;
        }
    mergeSort(R, i - 1);
    input(k, R, i - 1);
    int T = 1;
    int Q, W, E;
    char q;
    i = 1;
    fopen_s(&out, "out.txt", "r");
    fscanf_s(out, "%c", &q);
    if (q == k);
    else
    {
        printf("false");
        return 0;
    }
    if (k == 'X')
        while (i < n + 1)
        {
            fscanf_s(out, "%d %d %d", &Q, &W, &E);
            if (Q == R[i].key && W == R[i].val1 && E == R[i].val2);
            else
            {
                T = 0;
                printf("false\n");
                break;
            }

            i++;
        }
    else if (k == 'Y')
        while (i < n + 1)
        {
            fscanf_s(out, "%d %d %d", &W, &Q, &E);
            if (Q == R[i].key && W == R[i].val1 && E == R[i].val2);
            else
            {
                T = 0;
                printf("false\n");
                break;
            }
            i++;
        }
    else if (k == 'Z')
        while (i < n + 1)
        {
            fscanf_s(out, "%d %d %d", &W, &E, &Q);
            if (Q == R[i].key && W == R[i].val1 && E == R[i].val2);
            else
            {
                T = 0;
                printf("false\n");
                break;
            }
            i++;
        }
    if (T == 1)
        printf("true\n");
}