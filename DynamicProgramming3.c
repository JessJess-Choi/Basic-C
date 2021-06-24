
#include<stdio.h>
#include<string.h>

#define N 7
#define INF 2123456789
int d[N + 1][N + 1], p[N + 1][N + 1];
int min(int a, int b) { return a > b ? b : a; } // ���� ���� ���� �����ϴ� �Լ�
void path(int q, int r) {
	if (p[q][r] != 0) {
		path(q, p[q][r]);
		printf("%d->", p[q][r]);
		path(p[q][r], r);
	}
} //p�迭�� ���� �����ϸ� �ִܰ�θ� ������ִ� �Լ�
int main() {
	/*
		����ġ�� �����ϴ� w �迭 �ʱ�ȭ
		vertex ���� �� ����ġ�� �����ϴ� w1�迭 �ʱ�ȭ
	*/
	int w[N][N] = { {0,4,0,0,0,10,0},{3,0,0,18,0,0,0},{0,6,0,0,0,0,0},{0,5,15,0,2,19,5},{0,0,12,1,0,0,0},{0,0,0,0,0,0,10}, {0,0,0,8,0,0,0} };
	int w1[N][N] = { {0,0,0,8,0,0,0},{10,0,0,0,0,0,0},{0,0,0,1,12,0,0},{5,19,2,0,15,5,0},{0,0,0,0,0,6,0},{0,0,0,18,0,0,4},{10,0,0,0,0,3,0} };
	memset(d, INF, sizeof(d));

	/*
		d�迭 �ʱ�ȭ �� p�迭 �ʱ�ȭ
	*/
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++) {
			if (w[i - 1][j - 1])
				d[i][j] = w[i - 1][j - 1];
			p[i][j] = 0;
		}

	/*
		d �迭�� d[i][k] + w[k][j] �� ���� ���� ��
	*/
	for (int k = 1; k <= N; k++)
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++) {
				if (d[i][j] > d[i][k] + d[k][j]) {
					d[i][j] = d[i][k] + d[k][j];
					p[i][j] = k;
				}
				if (i == j)d[i][j] = 0; //�ڱ��ڽ����� ���� path�� ����
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
		w1�� �̿��� �ٽ� �ѹ� �÷��̵� �˰��� ���
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