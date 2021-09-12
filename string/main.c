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

	//kmp 알고리즘을 응용한 O(n+m) 시간복잡도의 탐색 코드
	kmpfind(s, t);
	return 0;

	// nfind를 이용한 문장 전체 패턴 매칭 코드. O(N*M) 시간복잡도
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
		//strncpy에 의해 s 문자열에서 i만큼만 복사되는데 이 떄 마지막 NULL문자는 복사되지 않으므로 임의 추가 해야 함
		temp[i] = '\0';
		strcat(temp, t);
		strcat(temp, (s + i));
		strcpy(s, temp);
	}
}

int nfind(char* string, char* pat) {
	int i, j = 0, start = 0;
	//s의 길이
	int lasts = strlen(string) - 1;
	//p의 길이
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

//탐색어의 처음 글자부터 끝까지의 접두/접미사가 일치하는 길이를 미리 구해놓음
void kmpfind(char* string, char* search) {
	int i = 1, j;
	int n = strlen(string) - 1, m = strlen(search) - 1;
	//begin부터 한 글자씩 비교하며 글자가 일치할 때 matched 증가.
	int begin = 0, matched = 0;

	printf("%s %s\n", string, search);
	int* pi;

	//탐색어의 접두/접미 정보
	pi = getPartialMatch(search);

	while (begin <= n - m) {
		//현재 탐색 위치에서 글자가 일치하는 경우
		if (matched < m && string[begin + matched] == search[matched]) {
			++matched;
			//begin부터 현재 탐색 위치까지 모두 일치한 경우 일치하는 단어를 찾은 경우임
			if (matched == m) {
				printf("%dst matched at %d\n", i, begin);
				i++;
			}
		}
		//현재 탐색 위치에서 글자가 불일치하는 경우
		else {
			//현재 탐색 위치에서 어떠한 글자도 불일치 한 경우 시작 위치 증가
			if (matched == 0) {
				//printf("jump\n");
				++begin;
			}
			//begin부터 현재 탐색 위치까지 몇 글자가 일치한 경우 접미사 정보를 이용해 건너뛰기
			else {
				//printf("jump to suffix\n");
				//접미사 시작위치 - 접미사 길이
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}

		}

	}
}

//kmp 알고리즘을 동일하게 이용하여 탐색어에 대한 접두/접미가 일치하는 길이 정보를 저장하여 반환
int* getPartialMatch(char* search) {
	int i = 1, j;
	int m = strlen(search) - 1;
	int begin = 1, matched = 0;

	int* pi = (int*)calloc(m, sizeof(int));

	while (begin + matched < m) {
		//현재 위치의 글자가 일치하는 경우
		if (search[begin + matched] == search[matched]) {
			matched++;
			pi[begin + matched - 1] = matched;
		}
		//현재 위치의 글자가 불일치하는 경우
		else {
			//앞서 글자가 모두 불일치한 경우
			if (matched == 0) {
				begin++;
			}
			//앞서의 글자가 부분적으로 일치한 경우 저장된 pi정보를 이용해 접미사 위치로 이동
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}

	}

	return pi;
}


