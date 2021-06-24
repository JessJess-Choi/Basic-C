
#include<stdio.h>

#define N 7
#define INF 212345678
int d[N][N],tmp[N][N];
int min(int a, int b) { return a > b ? b : a; } // ���� ���� ���� �����ϴ� �Լ�

int main() {
	/*
		����ġ�� �����ϴ� w �迭 �ʱ�ȭ
	*/
	int w[N][N] = { {INF,4,INF,INF,INF,10,INF},{3,INF,INF,18,INF,INF,INF},{INF,6,INF,INF,INF,INF,INF},{INF,5,15,INF,2,19,5},{INF,INF,12,1,INF,INF,INF},{INF,INF,INF,INF,INF,INF,10}, {INF,INF,INF,8,INF,INF,INF} };
	
	/*
		d�迭 �ʱ�ȭ �� �ӽ÷� ������ ��� �� tmp �迭 �ʱ�ȭ
	*/
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			d[i][j] = w[i][j];
			tmp[i][j] = w[i][j];
		}

	/*
		d �迭�� d[i][k] + w[k][j] �� ���� ���� �� 
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
		�ڱ��ڽ����� ���� path�� ����
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