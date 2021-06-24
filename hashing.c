#include<stdio.h>
#include<stdlib.h>

#define INF 2123456789	//비어있음을 표시하기위한 표시

/*
	chain에서 링크드리스트를 표현하기위한 구조체
*/

typedef struct node {
	int value;
	struct node* next;
}node;

void linearHash(int);
void quadraticHash(int);
void chaining(int);
void printAll();
int arr[8] = { 10,20,30,40,33,46,50,60 };
int linear[13], quadratic[13];
node* chain[13];

int main() {
	
	/*
		입력받기 전 배열들 초기화
	*/

	for (int i = 0; i < 13; i++) {
		linear[i] = quadratic[i] = -INF;
	}
	
	/*
		선형조사방법
	*/

	for (int i = 0; i < 8; i++) {
		linearHash(i);
		if (i >= 4) {
			printf("%d추가한 이후\n", arr[i]);
			for (int j = 0; j < 13; j++) {
				printf("%d : %d", j, linear[j]);
				printf("\n");
			}
		}
	}
	printf("\n");

	/*
		이차원조사방법
	*/

	for (int i = 0; i < 8; i++) {
		quadraticHash(i);
		if (i >= 4) {
			printf("%d추가한 이후\n", arr[i]);
			for (int j = 0; j < 13; j++) {
				printf("%d : %d", j, quadratic[j]);
				printf("\n");
			}
		}
	}
	printf("\n");

	/*
		체이닝
	*/

	for (int i = 0; i < 8; i++) {
		chaining(i);
		if (i >= 4) {
			printf("%d추가한 이후\n", arr[i]);
			printAll();
		}
	}
	return 0;
}

/*
	선형조사방법의 정의대로 key값을 index로 하는 linear배열에
	value를 저장한다. linear배열의 key 인덱스에 값이 있을 경우
	key+1의 인덱스에 저장한다.
*/

void linearHash(int n) {
	int key = arr[n] % 13;
	while (1) {
		if (linear[key] == -INF)break;
		key++;
		if (key == 13)key = 0;
	}
	linear[key] = arr[n];
}

/*
	이차원조사방법의 정의대로 key값을 index로 하는 quadratic배열에
	value를 저장한다. linear배열의 key 인덱스에 값이 있을 경우
	key+i*I의 인덱스에 저장한다.
*/

void quadraticHash(int n) {
	int key = arr[n] % 13;
	int check = 0;
	int tmp = key;
	while (1) {
		key = tmp + check * check;
		if (quadratic[key] == -INF)break;
		check++;
		if (key >= 13)key -= 13;
	}
	quadratic[key] = arr[n];
}

/*
	체이닝의 정의대로 key값을 index로 하는 chain배열에 value를 저장한다.
	chain배열에 다른 value가 있을 경우 linkedlist를 이용하여 연결한다.
*/

void chaining(int n) {
	int key = arr[n] % 13;
	node* tmp = (node*)malloc(sizeof(node));
	tmp->value = arr[n];
	tmp->next = NULL;
	if (chain[key] == NULL)
		chain[key] = tmp;
	else {
		tmp->next = chain[key];
		chain[key] = tmp;
	}
}

/*
	chain배열에 있는 모든 value를 출력한다. 비어있을 경우 넘어가고,
	값이 있을 경우 linkedlist의 끝 까지 출력한다.
*/

void printAll() {
	for (int i = 0; i < 13; i++) {
		int tmp[13], cnt = 0;
		printf("index : %d\n", i);
		if (chain[i] != NULL) {
			node* temp = chain[i];
			while (temp->next) {
				tmp[cnt++] = temp->value;
				temp = temp->next;
			}
			tmp[cnt++] = temp->value;
		}
		for (int j = cnt-1; j >= 0; j--)
			printf("%d ", tmp[j]);
		printf("\n");
	}
	printf("\n");
}