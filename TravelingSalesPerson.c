#pragma warning(disable : 4996)	//visual studio에서 scanf함수를 error나 warning 없이 사용하기 위함

#include<stdio.h>

#define N 5

const int INF = 2123456789;
int dp[N][1 << N];
int cost[N][N];

int TSP(int now, int visit) {	
	//now:현재 위치한 마을의 index 
	//visit:바로 전에 방문한 마을의 index
	
	printf("현재 위치 : %d 이전 방문한곳 : %d ", now, visit);
	int res;
	int ret = dp[now][visit];
	if (ret != 0) {
		//dp배열을 이미 구한 적 있으면 끝냄
		printf("dp배열에 들어있는 값을 사용 : %d\n", ret);
		return ret;
	}
	if (visit == (1 << N) - 1) {
		//모든 마을을 방문했을 경우
		if (cost[now][0] != 0) {
			//시작인 0번째 마을로 돌아가는 vertex가 있는 경우
			printf("첫번째 마을로 가는 가중치 : %d\n", cost[now][0]);
			return cost[now][0];
		}
		return INF;
	}
	ret = INF;

	for (int i = 0; i < N; i++) {
		if ((visit & 1 << i) || (cost[now][i] == 0))continue;	//i번째 visit을 확인하기 위한 비트연산
		res = TSP(i, (visit | 1 << i)) + cost[now][i];
		if (res < ret)
			ret = res;
	}
	dp[now][visit] = ret;
	printf("dp[%d][%d]배열에 들어가는 가중치 : %d\n", now, visit, ret);
	return ret;
}

int main() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &cost[i][j]);
	int tmp = TSP(0, 1);
	printf("가중치합의 최소 : %d", tmp);
	return 0;
}