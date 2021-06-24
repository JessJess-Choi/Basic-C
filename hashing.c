#include<stdio.h>
#include<stdlib.h>

#define INF 2123456789	//��������� ǥ���ϱ����� ǥ��

/*
	chain���� ��ũ�帮��Ʈ�� ǥ���ϱ����� ����ü
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
		�Է¹ޱ� �� �迭�� �ʱ�ȭ
	*/

	for (int i = 0; i < 13; i++) {
		linear[i] = quadratic[i] = -INF;
	}
	
	/*
		����������
	*/

	for (int i = 0; i < 8; i++) {
		linearHash(i);
		if (i >= 4) {
			printf("%d�߰��� ����\n", arr[i]);
			for (int j = 0; j < 13; j++) {
				printf("%d : %d", j, linear[j]);
				printf("\n");
			}
		}
	}
	printf("\n");

	/*
		������������
	*/

	for (int i = 0; i < 8; i++) {
		quadraticHash(i);
		if (i >= 4) {
			printf("%d�߰��� ����\n", arr[i]);
			for (int j = 0; j < 13; j++) {
				printf("%d : %d", j, quadratic[j]);
				printf("\n");
			}
		}
	}
	printf("\n");

	/*
		ü�̴�
	*/

	for (int i = 0; i < 8; i++) {
		chaining(i);
		if (i >= 4) {
			printf("%d�߰��� ����\n", arr[i]);
			printAll();
		}
	}
	return 0;
}

/*
	������������ ���Ǵ�� key���� index�� �ϴ� linear�迭��
	value�� �����Ѵ�. linear�迭�� key �ε����� ���� ���� ���
	key+1�� �ε����� �����Ѵ�.
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
	�������������� ���Ǵ�� key���� index�� �ϴ� quadratic�迭��
	value�� �����Ѵ�. linear�迭�� key �ε����� ���� ���� ���
	key+i*I�� �ε����� �����Ѵ�.
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
	ü�̴��� ���Ǵ�� key���� index�� �ϴ� chain�迭�� value�� �����Ѵ�.
	chain�迭�� �ٸ� value�� ���� ��� linkedlist�� �̿��Ͽ� �����Ѵ�.
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
	chain�迭�� �ִ� ��� value�� ����Ѵ�. ������� ��� �Ѿ��,
	���� ���� ��� linkedlist�� �� ���� ����Ѵ�.
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