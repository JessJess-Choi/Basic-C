
#include<stdio.h>

#define N 7
#define INF 212345678
int d[N][N],tmp[N][N];
int min(int a, int b) { return a > b ? b : a; } // 둘중 작은 값을 리턴하는 함수

int main() {
	/*
		가중치를 저장하는 w 배열 초기화
	*/
	int w[N][N] = { {INF,4,INF,INF,INF,10,INF},{3,INF,INF,18,INF,INF,INF},{INF,6,INF,INF,INF,INF,INF},{INF,5,15,INF,2,19,5},{INF,INF,12,1,INF,INF,INF},{INF,INF,INF,INF,INF,INF,10}, {INF,INF,INF,8,INF,INF,INF} };
	
	/*
		d배열 초기화 및 임시로 저장해 사용 할 tmp 배열 초기화
	*/
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			d[i][j] = w[i][j];
			tmp[i][j] = w[i][j];
		}

	/*
		d 배열에 d[i][k] + w[k][j] 중 가장 작은 값 
	*/
	for (int m = 2; m < N; m++) {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				for (int k = 0; k < N; k++)
					d[i][j] = min(d[i][j], d[i][k] + w[k][j]);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				tmp[i][j] = d[i][j];
	}
	/*
		자기자신으로 가는 path는 없다
	*/
	for (int i = 0; i < N; i++)
		d[i][i] = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%d ", d[i][j]);
		printf("\n");
	}
	return 0;
}