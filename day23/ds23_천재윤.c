#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

int hashing(int key, int bucket) {
	return key % bucket;
}

void push(int** cache, int hashedKey, int key, int slot) {
	/*cache[hashedKey][0]++;

	cache[hashedKey][cache[hashedKey][0]] = key;*/
	int i, j;

	for (i = 0; i < slot; i++) {
		if (cache[hashedKey][i] == -1) {
			cache[hashedKey][i] = key;
			break;
		}
	}
}

int searching(int** cache, int key, int bucket, int slot) {
	int i, j;
	int hashedKey = hashing(key, bucket);

	for (i = 0; i < bucket; i++) {
		for (j = 0; j < slot; j++) {
			if (cache[hashedKey][j] == key) {
				printf("%d\n", hashedKey);
				return hashedKey;
			}
		}
		hashedKey = (hashedKey + 1) % bucket;
	}

	return -1;
}

void printBucket(int** cache, int bucket, int slot) {
	int i, j;

	printf("Hash table :\n");

	for (i = 0; i < bucket; i++) {
		printf("%d: ", i);
		for (j = 0; j < slot; j++) {
			if (cache[i][j] == -1)
				break;
			printf("%d ", cache[i][j]);
		}
		printf("\n");
	}
}

int main() {
	FILE* fin;
	int bucket, slot, key, hashedKey, searchingKey, result;
	int i, j, flag;
	int** cache;

	fin = fopen("in.txt", "r");

	fscanf(fin, "%d %d", &bucket, &slot);

	cache = (int**)malloc(sizeof(int) * bucket);
	for (i = 0; i < bucket; i++) {
		cache[i] = (int*)malloc(sizeof(int) * slot);
	}

	for (i = 0; i < bucket; i++) {
		for (j = 0; j < slot; j++) {
			cache[i][j] = -1;
		}
	}
	
	while (!feof(fin)) {
		fscanf(fin, "%d", &key);

		hashedKey = hashing(key, bucket);

		flag = 0;
		while (1) {

			for (i = 0; i < slot; i++) {
				if (cache[hashedKey][i] == -1) {
					flag = 1;
					break;
				}
			}

			if (flag == 1) {
				push(cache, hashedKey, key, slot);
				break;
			}
			else {
				hashedKey = (hashedKey + 1) % bucket;
			}
		}
	}

	printBucket(cache, bucket, slot);

	while (1) {
		scanf("%d", &searchingKey);
		if (searchingKey == -999) {
			break;
		}
		
		result = searching(cache, searchingKey, bucket, slot);
		if (result == -1) {
			printf("%d\n", result);
		}
	}

	return 0;
}