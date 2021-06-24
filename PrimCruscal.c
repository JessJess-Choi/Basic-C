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
		초기화
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
		프림 알고리즘 함수 호출
	*/

	printf("프림\n");
	prim();
	printf("\n");

	/*
		크루스칼 알고리즘
	*/
	printf("크루스칼\n");
	/*
		가중치순으로 정렬
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
		부모 나타내는 배열 초기화
	*/

	for (int i = 1; i <= Vertex; i++)parent[i] = i;

	/*
		두 노드가 같은 부모를 갖지 않을 경우 합침
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
		초기화
	*/

	for (int i = 0; i < Vertex; i++) {
		d[i] = INF;
		check[i] = 0;
	}

	/*
		시작은 거리가 0
	*/
	d[0] = 0;

	/*
		최소거리를 갖는 정점을 저장하고 방문 표시를 한다
		경로가 없으면 함수 종료
		경로를 출력하고 정점이 u와 연결되어 있다면 d배열의 값을 갱신
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
		아직 선택되지 않은 정점들을 대상으로 그 정점이
		최소거리를 갖고 있는지 확인하여 리턴
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
	x의 부모를 찾는 함수
*/

int find(int x) {

	if (parent[x] == x)return x;
	return parent[x] = find(parent[x]);
}

/*
	두개의 집합을 합치는 함수
*/

void unite(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y)parent[y] = x;
}

/*
	두개의 요소가 같은 부모를 가지면 1, 아니면 0 리턴
*/

int sameParent(int x, int y) {
	x = find(x);
	y = find(y);
	if (x == y)return 1;
	return 0;
}