#pragma warning(disable : 4996)		//visual studio ���� scanf�Լ��� error/warning ǥ�� ���� ����ϱ� ���� ��ġ

#include<stdio.h>
#include<stdlib.h>

void init(int);
int find(int);
void unite(int, int);
int par[10], rnk[10];

int main() {

	/*
		(a)�� �ִ� �ΰ��� Ʈ���� ��ġ�� ���
	*/

	printf("(a)\n");
	init(3);
	for (int i = 0; i < 2; i++) {
		int tmp1, tmp2;
		scanf("%d %d", &tmp1, &tmp2);
		unite(tmp1, tmp2);
	}
	for (int i = 1; i <= 3; i++) {
		if (i == par[i])
			printf("%c is root node\n", i - 1 + 'a');
		else
			printf("%c is parent of %c\n", par[i] - 1 + 'a', i - 1 + 'a');
	}

	/*
		par�迭�� rnk�迭�� �����ϱ� ���� �޸� �ʱ�ȭ�Ѵ�
		(b)�� �ִ� �ΰ��� Ʈ���� ��ġ�� ����� ����Ѵ�
	*/

	memset(par, 0, sizeof(par));
	memset(rnk, 0, sizeof(rnk));
	printf("(b)\n");
	init(6);
	for (int i = 0; i < 5; i++) {
		int tmp1, tmp2;
		scanf("%d %d", &tmp1, &tmp2);
		unite(tmp1, tmp2);
	}
	for (int i = 1; i <= 6; i++) {
		if (i == par[i])
			printf("%c is root node\n", i + 2 + 'a');
		else
			printf("%c is parent of %c\n", par[i] + 2 + 'a', i + 2 + 'a');
	}

	/*
		par�迭�� rnk�迭�� �����ϱ� ���� �޸� �ʱ�ȭ�Ѵ�
		(a), (b)�� ������ �� ���� �ΰ��� Ʈ���� ��ġ�� ����� ����Ѵ�
	*/

	memset(par, 0, sizeof(par));
	memset(rnk, 0, sizeof(rnk));
	printf("Print All\n");
	init(9);
	for (int i = 0; i < 8; i++) {
		int tmp1, tmp2;
		scanf("%d %d", &tmp1, &tmp2);
		unite(tmp1, tmp2);
	}
	for (int i = 1; i <= 9; i++) {
		if (i == par[i])
			printf("%c is root node\n", i - 1 + 'a');
		else
			printf("%c is parent of %c\n", par[i] - 1 + 'a', i - 1 + 'a');
	}
	return 0;
}

/*
	�ʱ�ȭ�� ���� �Լ�
	�θ� �����ϴ� �迭�� par�� �ڱ� �ڽ�����,
	rank�� ��Ÿ���� rnk �迭�� 1�� �ʱ�ȭ�Ѵ�
*/

void init(int n) {
	for (int i = 1; i <= n; i++) {
		par[i] = i;
		rnk[i] = 1;
	}
}

/*
	Ʈ���� ��Ʈ��带 ã���ִ� �Լ�
	�ڱ� �ڽ��� ��Ʈ�� ���� �ڽ��� �����ϰ�
	�ƴ� ��� ���ȣ���� ���� ��Ʈ��带 ã�� �����Ѵ�
*/

int find(int x) {
	if (x == par[x])return x;
	return par[x] = find(par[x]);
}

/*
	�� ��Ҹ� �����ִ� �Լ�
	�Է¹��� �� ������ ��Ʈ��带 ã�� ��Ʈ�� ������ ������
	�ƴ� ��� rank�� ���� rank�� ���� ��Ʈ��忡 rank�� ���� ��Ʈ��带 ���δ�
	�׸��� �� Ʈ���� rank�� ���� ��� �ϼ��� Ʈ���� ��Ʈ����� rank�� 1������Ų��
*/

void unite(int x, int y) {
	x = find(x);
	y = find(y);
	if (x == y)return;
	if (rnk[x] < rnk[y])par[x] = y;
	else par[y] = x;
	if (rnk[x] == rnk[y])
		rnk[x]++;
}