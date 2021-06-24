#pragma warning(disable : 4996)
#include<stdio.h>
#define Vertex 8
#define Edge 14
#define INF 2123456789

typedef struct Weight {
	int start;
	int end;
	int weight;
}W;
W w[Edge];

int weight[Vertex][Vertex];
int parent[Vertex + 1];
int find(int);
void unite(int, int);
int sameParent(int, int);
void prim();
int minVertex();
int d[Vertex + 1], check[Vertex + 1];

int main() {

	/*
		�ʱ�ȭ
	*/

	for (int i = 0; i < Vertex; i++)
		for (int j = 0; j < Vertex; j++)
			weight[i][j] = INF;
	for (int i = 0; i < Edge; i++) {
		int start, end, wei;
		scanf("%d %d %d", &start, &end, &wei);
		w[i].start = start;
		w[i].end = end;
		w[i].weight = wei;
		weight[start - 1][end - 1] = wei;
	}
	for (int i = 0; i < Vertex; i++)weight[i][i] = 0;

	/*
		���� �˰��� �Լ� ȣ��
	*/

	printf("����\n");
	prim();
	printf("\n");

	/*
		ũ�罺Į �˰���
	*/
	printf("ũ�罺Į\n");
	/*
		����ġ������ ����
	*/
	for (int i = 0; i < Edge; i++) {
		for (int j = 0; j < i; j++) {
			if (w[i].weight < w[j].weight) {
				W tmp = w[i];
				w[i] = w[j];
				w[j] = tmp;
			}
		}
	}

	/*
		�θ� ��Ÿ���� �迭 �ʱ�ȭ
	*/

	for (int i = 1; i <= Vertex; i++)parent[i] = i;

	/*
		�� ��尡 ���� �θ� ���� ���� ��� ��ħ
	*/

	for (int i = 0; i < Edge; i++) {
		if (!sameParent(w[i].start, w[i].end)) {
			unite(w[i].start, w[i].end);
			printf("%d-%d\n", w[i].start,w[i].end);
		}
	}

	return 0;
}

void prim() {
	/*
		�ʱ�ȭ
	*/

	for (int i = 0; i < Vertex; i++) {
		d[i] = INF;
		check[i] = 0;
	}

	/*
		������ �Ÿ��� 0
	*/
	d[0] = 0;

	/*
		�ּҰŸ��� ���� ������ �����ϰ� �湮 ǥ�ø� �Ѵ�
		��ΰ� ������ �Լ� ����
		��θ� ����ϰ� ������ u�� ����Ǿ� �ִٸ� d�迭�� ���� ����
	*/

	for (int i = 0; i < Vertex; i++) {
		int u = minVertex();
		check[u] = 1;
		if (d[u] == INF)return;
		printf("%d ", u+1);
		for (int j = 0; j < Vertex; j++)
			if (weight[u][j] != INF)
				if (!check[j] && weight[u][j] < d[j]) {
					d[j] = weight[u][j];
				}
	}
}

int minVertex() {
	/*
		���� ���õ��� ���� �������� ������� �� ������
		�ּҰŸ��� ���� �ִ��� Ȯ���Ͽ� ����
	*/

	int ret;
	for (int i = 0; i < Vertex; i++) {
		if (!check[i]) {
			ret = i;
			break;
		}
	}
	for (int i = 0; i < Vertex; i++) 
		if (!check[i] && (d[i] < d[ret]))ret = i;
	return ret;
}

/*
	x�� �θ� ã�� �Լ�
*/

int find(int x) {

	if (parent[x] == x)return x;
	return parent[x] = find(parent[x]);
}

/*
	�ΰ��� ������ ��ġ�� �Լ�
*/

void unite(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y)parent[y] = x;
}

/*
	�ΰ��� ��Ұ� ���� �θ� ������ 1, �ƴϸ� 0 ����
*/

int sameParent(int x, int y) {
	x = find(x);
	y = find(y);
	if (x == y)return 1;
	return 0;
}