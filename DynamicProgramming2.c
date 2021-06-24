
#include<stdio.h>
#include<string.h>

#define N 7
#define INF 2123456789
int d[N + 1][N + 1], p[N + 1][N + 1];
int min(int a, int b) { return a > b ? b : a; } // 둘중 작은 값을 리턴하는 함수
void path(int q, int r) {
	if (p[q][r] != 0) {
		path(q, p[q][r]);
		printf("V%d->", p[q][r]);
		path(p[q][r], r);
	}
} //p배열의 값을 추적하며 최단경로를 출력해주는 함수
int main() {
	/*
		가중치를 저장하는 w 배열 초기화
	*/
	int w[N][N] = { {0,4,0,0,0,10,0},{3,0,0,18,0,0,0},{0,6,0,0,0,0,0},{0,5,15,0,2,19,5},{0,0,12,1,0,0,0},{0,0,0,0,0,0,10}, {0,0,0,8,0,0,0} };

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
	printf("D\n");
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			printf("%d ", d[i][j]);
		printf("\n");
	}
	printf("P\n");
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			printf("%d ", p[i][j]);
		printf("\n");
	}
	printf("V3 to V6 : %d\n", d[3][6]);
	printf("V3->");
	path(3, 6);
	printf("V6");
	return 0;
}