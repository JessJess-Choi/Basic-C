#pragma warning(disable : 4996)	//visual studio���� scanf�Լ��� error�� warning ���� ����ϱ� ����

#include<stdio.h>

#define N 5

const int INF = 2123456789;
int dp[N][1 << N];
int cost[N][N];

int TSP(int now, int visit) {	
	//now:���� ��ġ�� ������ index 
	//visit:�ٷ� ���� �湮�� ������ index
	
	printf("���� ��ġ : %d ���� �湮�Ѱ� : %d ", now, visit);
	int res;
	int ret = dp[now][visit];
	if (ret != 0) {
		//dp�迭�� �̹� ���� �� ������ ����
		printf("dp�迭�� ����ִ� ���� ��� : %d\n", ret);
		return ret;
	}
	if (visit == (1 << N) - 1) {
		//��� ������ �湮���� ���
		if (cost[now][0] != 0) {
			//������ 0��° ������ ���ư��� vertex�� �ִ� ���
			printf("ù��° ������ ���� ����ġ : %d\n", cost[now][0]);
			return cost[now][0];
		}
		return INF;
	}
	ret = INF;

	for (int i = 0; i < N; i++) {
		if ((visit & 1 << i) || (cost[now][i] == 0))continue;	//i��° visit�� Ȯ���ϱ� ���� ��Ʈ����
		res = TSP(i, (visit | 1 << i)) + cost[now][i];
		if (res < ret)
			ret = res;
	}
	dp[now][visit] = ret;
	printf("dp[%d][%d]�迭�� ���� ����ġ : %d\n", now, visit, ret);
	return ret;
}

int main() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &cost[i][j]);
	int tmp = TSP(0, 1);
	printf("����ġ���� �ּ� : %d", tmp);
	return 0;
}