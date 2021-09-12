#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 255
#define MAX_ARR_SIZE 100

void strnins(char*, char*, int);
int nfind(char*, char*);
void kmpfind(char*, char*);
int* getPartialMatch(char*);

int main() {
	int result = 0, i = 1, stack = 0;
	char str1[MAX_SIZE] = "abababaaawabababaaasswwdaabababaaaaawqwdabababaa", str2[MAX_SIZE] = "abababaa", tempStr[MAX_SIZE];
	char* s = str1;
	char* t = str2;
	char* temp = tempStr;

	//kmp �˰����� ������ O(n+m) �ð����⵵�� Ž�� �ڵ�
	kmpfind(s, t);
	return 0;

	// nfind�� �̿��� ���� ��ü ���� ��Ī �ڵ�. O(N*M) �ð����⵵
	while (1) {
		printf("%s\n", s + stack);
		result = nfind(s + stack, t);
		if (result == -1)
			break;

		stack += result;
		printf("%dst pattern matching at %d\n", i, stack);
		stack += strlen(t);
		_sleep(1000);
	}
}

void strnins(char* s, char* t, int i) {
	char string[MAX_SIZE], * temp = string;

	printf("2 %s %s\n", s, t);

	if (i < 0 && i > strlen(s)) {
		fprintf(stderr, "out of bound\n");
		exit(EXIT_FAILURE);
	}

	if (!strlen(s)) {
		strcpy(s, t);
	}
	else if (strlen(t)) {
		strncpy(temp, s, i);
		//strncpy�� ���� s ���ڿ����� i��ŭ�� ����Ǵµ� �� �� ������ NULL���ڴ� ������� �����Ƿ� ���� �߰� �ؾ� ��
		temp[i] = '\0';
		strcat(temp, t);
		strcat(temp, (s + i));
		strcpy(s, temp);
	}
}

int nfind(char* string, char* pat) {
	int i, j = 0, start = 0;
	//s�� ����
	int lasts = strlen(string) - 1;
	//p�� ����
	int lastp = strlen(pat) - 1;
	int endmatch = lastp;

	//
	for (i = 0; endmatch <= lasts; endmatch++, start++) {
		if (string[endmatch] == pat[lastp]) {
			for (j = 0, i = start; j < lastp && string[i] == pat[j]; i++, j++);
		}
		if (j == lastp) {
			return start;
		}
	}
	return -1;
}

//Ž������ ó�� ���ں��� �������� ����/���̻簡 ��ġ�ϴ� ���̸� �̸� ���س���
void kmpfind(char* string, char* search) {
	int i = 1, j;
	int n = strlen(string) - 1, m = strlen(search) - 1;
	//begin���� �� ���ھ� ���ϸ� ���ڰ� ��ġ�� �� matched ����.
	int begin = 0, matched = 0;

	printf("%s %s\n", string, search);
	int* pi;

	//Ž������ ����/���� ����
	pi = getPartialMatch(search);

	while (begin <= n - m) {
		//���� Ž�� ��ġ���� ���ڰ� ��ġ�ϴ� ���
		if (matched < m && string[begin + matched] == search[matched]) {
			++matched;
			//begin���� ���� Ž�� ��ġ���� ��� ��ġ�� ��� ��ġ�ϴ� �ܾ ã�� �����
			if (matched == m) {
				printf("%dst matched at %d\n", i, begin);
				i++;
			}
		}
		//���� Ž�� ��ġ���� ���ڰ� ����ġ�ϴ� ���
		else {
			//���� Ž�� ��ġ���� ��� ���ڵ� ����ġ �� ��� ���� ��ġ ����
			if (matched == 0) {
				//printf("jump\n");
				++begin;
			}
			//begin���� ���� Ž�� ��ġ���� �� ���ڰ� ��ġ�� ��� ���̻� ������ �̿��� �ǳʶٱ�
			else {
				//printf("jump to suffix\n");
				//���̻� ������ġ - ���̻� ����
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}

		}

	}
}

//kmp �˰����� �����ϰ� �̿��Ͽ� Ž��� ���� ����/���̰� ��ġ�ϴ� ���� ������ �����Ͽ� ��ȯ
int* getPartialMatch(char* search) {
	int i = 1, j;
	int m = strlen(search) - 1;
	int begin = 1, matched = 0;

	int* pi = (int*)calloc(m, sizeof(int));

	while (begin + matched < m) {
		//���� ��ġ�� ���ڰ� ��ġ�ϴ� ���
		if (search[begin + matched] == search[matched]) {
			matched++;
			pi[begin + matched - 1] = matched;
		}
		//���� ��ġ�� ���ڰ� ����ġ�ϴ� ���
		else {
			//�ռ� ���ڰ� ��� ����ġ�� ���
			if (matched == 0) {
				begin++;
			}
			//�ռ��� ���ڰ� �κ������� ��ġ�� ��� ����� pi������ �̿��� ���̻� ��ġ�� �̵�
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}

	}

	return pi;
}


