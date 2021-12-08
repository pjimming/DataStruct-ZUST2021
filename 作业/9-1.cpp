/*
	@author: 潘江明
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20

typedef int ElemType;
typedef struct {
	ElemType key;
	int count;
} Hash[MAX_SIZE];

typedef struct {
	Hash hash;
	int numkey, tablelength;
	ElemType Key[MAX_SIZE];
} HashTable;

void CreateHash(HashTable *h) {
	printf("请输入关键值的个数和表长：\n");
	scanf("%d%d", &h->numkey, &h->tablelength);

	printf("请输入每个关键值：\n");
	for (int i = 0; i < h->numkey; i++) {
		scanf("%d", &h->Key[i]);
	}

	for (int i = 0; i < h->tablelength; i++) {
		h->hash[i].count = 0;
	}
}

void DisPlayKey(HashTable h) {
	printf("表中有%d个key值;\n", h.numkey);
	for (int i = 0; i < h.numkey; i++)
		printf("%d ", h.Key[i]);
	printf("\n");
}

void HashKey(HashTable *h) {
	for (int i = 0; i < h->numkey; i++) {
		int tmp = h->Key[i] % 7, cnt = 1;
		if (h->hash[tmp].count == 0) {
			h->hash[tmp].count = cnt;
			h->hash[tmp].key = h->Key[i];
			continue;
		}

		while (h->hash[tmp].count) {
			tmp = (h->Key[i] % 7 + cnt * cnt) % h->tablelength;
			cnt++;
		}

		h->hash[tmp].count = cnt;
		h->hash[tmp].key = h->Key[i];
	}
}

void DisPlayHash(HashTable h) {
	for (int i = 0; i < h.tablelength; i++) {
		if (h.hash[i].count)
			printf("%d在表中第%d的位置上，查找次数为%d次\n", h.hash[i].key, i, h.hash[i].count);
	}
}

void FindKey(HashTable h, ElemType key) {
	printf("\n------------------------------------\n");
	for (int i = 0; i < h.tablelength; i++) {
		if (h.hash[i].key == key)
			printf("%d的查找次数为%d次", key, h.hash[i].count);
	}
	printf("\n------------------------------------\n");
}

int main() {
	HashTable h;

	CreateHash(&h);

	DisPlayKey(h);

	HashKey(&h);

	DisPlayHash(h);

	FindKey(h, 84);

	return 0;
}

/*
8 10
9 01 23 14 55 20 84 27
*/