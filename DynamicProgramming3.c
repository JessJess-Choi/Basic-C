
#include<stdio.h>
#include<string.h>

#define N 7
#define INF 2123456789
int d[N + 1][N + 1], p[N + 1][N + 1];
int min(int a, int b) { return a > b ? b : a; } // 둘중 작은 값을 리턴하는 함수
void path(int q, int r) {
	if (p[q][r] != 0) {
		path(q, p[q][r]);
		printf("%d->", p[q][r]);
		path(p[q][r], r);
	}
} //p배열의 값을 추적하며 최단경로를 출력해주는 함수
int main() {
	/*
		가중치를 저장하는 w 배열 초기화
		vertex 변경 후 가중치를 저장하는 w1배열 초기화
	*/
	int w[N][N] = { {0,4,0,0,0,10,0},{3,0,0,18,0,0,0},{0,6,0,0,0,0,0},{0,5,15,0,2,19,5},{0,0,12,1,0,0,0},{0,0,0,0,0,0,10}, {0,0,0,8,0,0,0} };
	int w1[N][N] = { {0,0,0,8,0,0,0},{10,0,0,0,0,0,0},{0,0,0,1,12,0,0},{5,19,2,0,15,5,0},{0,0,0,0,0,6,0},{0,0,0,18,0,0,4},{10,0,0,0,0,3,0} };
	memset(d, INF, sizeof(d));

	/*
		d배열 초기화 및 p배열 초기화
	*/
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++) {
			if (w[i - 1][j - 1])
				d[i][j] = w[i - 1][j - 1];
			p[i][j] = 0;
		}

	/*
		d 배열에 d[i][k] + w[k][j] 중 가장 작은 값
	*/
	for (int k = 1; k <= N; k++)
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++) {
				if (d[i][j] > d[i][k] + d[k][j]) {
					d[i][j] = d[i][k] + d[k][j];
					p[i][j] = k;
				}
				if (i == j)d[i][j] = 0; //자기자신으로 가는 path는 없다
			}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			printf("%d ", d[i][j]);
		printf("\n");
	}
	printf("5->");
	path(5, 2);
	printf("2");
	printf("\nSortest path : %d\n", p[5][2]);

	/*
		w1을 이용해 다시 한번 플로이드 알고리즘 사용
	*/
	printf("\nAfter Change\n");

	memset(d, INF, sizeof(d));

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++) {
			if (w1[i - 1][j - 1])
				d[i][j] = w1[i - 1][j - 1];
			p[i][j] = 0;
		}

	for (int k = 1; k <= N; k++)
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++) {
				if (d[i][j] > d[i][k] + d[k][j]) {
					d[i][j] = d[i][k] + d[k][j];
					p[i][j] = k;
				}
				if (i == j)d[i][j] = 0;
			}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			printf("%d ", d[i][j]);
		printf("\n");
	}
	printf("5->");
	path(5, 2);
	printf("2");
	printf("\nSortest path : %d\n", p[5][2]);
	return 0;
}