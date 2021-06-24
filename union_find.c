#pragma warning(disable : 4996)		//visual studio 에서 scanf함수를 error/warning 표시 없이 사용하기 위한 조치

#include<stdio.h>
#include<stdlib.h>

void init(int);
int find(int);
void unite(int, int);
int par[10], rnk[10];

int main() {

	/*
		(a)에 있는 두개의 트리를 합치고 출력
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
		par배열과 rnk배열을 재사용하기 위해 메모리 초기화한다
		(b)에 있는 두개의 트리를 합치고 결과를 출력한다
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
		par배열과 rnk배열을 재사용하기 위해 메모리 초기화한다
		(a), (b)를 수행한 후 남은 두개의 트리를 합치고 결과를 출력한다
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
	초기화를 위한 함수
	부모를 저장하는 배열인 par은 자기 자신으로,
	rank를 나타내는 rnk 배열은 1로 초기화한다
*/

void init(int n) {
	for (int i = 1; i <= n; i++) {
		par[i] = i;
		rnk[i] = 1;
	}
}

/*
	트리의 루트노드를 찾아주는 함수
	자기 자신이 루트일 경우는 자신을 리턴하고
	아닐 경우 재귀호출을 통해 루트노드를 찾아 리턴한다
*/

int find(int x) {
	if (x == par[x])return x;
	return par[x] = find(par[x]);
}

/*
	두 요소를 합쳐주는 함수
	입력받은 두 인자의 루트노드를 찾아 루트가 같으면 끝내고
	아닐 경우 rank를 비교해 rank가 높은 루트노드에 rank가 낮은 루트노드를 붙인다
	그리고 두 트리의 rank가 같을 경우 완성된 트리의 루트노드의 rank를 1증가시킨다
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