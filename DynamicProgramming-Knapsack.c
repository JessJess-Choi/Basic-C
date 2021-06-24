#include<stdio.h>
#define W 9		//목표하는 가중치
#define N 5		//node의 갯수

typedef struct node {
	int level;
	int profit;
	int weight;
}node;

typedef struct node2 {
	int level;
	int profit;
	int weight;
	float bound;
}node2;

void knapsack(int, int, int);
int promising(int, int, int);
void knapsack2();
float bound(node);
int isEmpty();
void enQueue(node);
node deQueue();
void knapsack3();
float bound2(node2);
int isEmpty2();
void enQueue2(node2);
node2 deQueue2();
int p[N + 1] = { 0,20,30,35,12,3 }, w[N + 1] = { 0,2,5,7,3,1 }, way[N + 1], maxprofit, bestset[N + 1];
int queueFront, queueRear, priorityQueueFront, priorityQueueRear;
node queue[N];
node2 priorityQueue[N];

int main() {
	knapsack(0, p[0], w[0]);
	printf("DFS\n%d\n", maxprofit);
	for (int i = 0; i < 6; i++)
		if (bestset[i])
			if (bestset[i] == w[i])
				printf("%d : %d\n", i, p[i]);

	knapsack2();
	printf("BFS\n%d\n", maxprofit);

	knapsack3();
	printf("Best First Search\n%d\n", maxprofit);

	return 0;
}

/*
	dfs를 이용한 탐색(백트래킹)
*/

void knapsack(int i, int profit, int weight) {
	if (weight <= W && profit > maxprofit) {
		maxprofit = profit;
		for (int j = 0; j < 6; j++)
			bestset[j] = way[j];
	}
	if (promising(i, profit, weight)) {
			way[i + 1] = w[i + 1];
			knapsack(i + 1, profit + p[i + 1], weight + w[i + 1]);
			way[i + 1] = 0;
			knapsack(i + 1, profit, weight);

	}
}

/*
	가지치기를 위한 함수
	없으면 전체를 탐색한다
*/

int promising(int i, int profit, int weight) {
	if (i > N)return 0;
	int j, k, totweight, maxprofit = 0;
	float bound;
	if (weight >= W)return 0;
	else {
		j = i + 1;
		bound = profit;
		totweight = weight;
		while ((j <= N) && (totweight + w[j] <= W)) {
			totweight += w[j];
			bound += p[j];
			j++;
		}
		k = j;
		if (k <= N) {
			bound += (W - totweight) * p[k] / w[k];
			return bound > maxprofit;
		}
	}
}

/*
	bfs를 이용한 탐색
	큐를 구현 하고 큐에 값을 넣었다 빼면서 탐색
*/

void knapsack2() {
	node u, v;
	maxprofit = 0;
	v.level = 0; v.profit = 0; v.weight = 0;
	enQueue(v);
	while (!isEmpty()) {
		v = deQueue(); u.level = v.level + 1;
		u.profit = v.profit + p[u.level];
		u.weight = v.weight + w[u.level];
		if ((u.weight <= W) && (u.profit > maxprofit))maxprofit = u.profit;
		if (bound(u) > maxprofit) enQueue(u);
		u.weight = v.weight;
		u.profit = v.profit;
		if (bound(u) > maxprofit) enQueue(u);
	}
}

/*
	인자로 넘겨 받은 노드를 가지고 목표한 W값이 되는지
	확인한다 조건을 모두 만족할 경우 노드의 bound값을 리턴
*/

float bound(node n) {
	int j, k, totweight;
	float result;
	if (n.weight >= W)return 0;
	else {
		result = n.profit; j = n.level + 1; totweight = n.weight;
		while ((j <= N) && (totweight + w[j] <= W)) {
			totweight += w[j];
			result += p[j];
			j++;
		}
		k = j;
		if (k <= N)result += (W - totweight) * (p[k] / w[k]);
		return result;
	}
}

/*
	큐의 isEmpty()함수 구현
*/

int isEmpty() {
	return (queueFront == queueRear);
}

/*
	큐의 enqueue 구현
	원형 큐로 구현하였다
*/

void enQueue(node n) {
	queueRear++;
	queueRear %= N;
	queue[queueRear] = n;
}

/*
	큐의 dequeue 구현
*/

node deQueue() {
	queueFront++;
	queueFront %= N;
	return queue[queueFront - 1];
}

/*
	best frist search 구현
	priority queue를 사용한다
	구현은 bfs와 비슷하나, node2 구조체에 bound가 추가된다
*/

void knapsack3() {
	node2 u, v;
	maxprofit = 0;
	v.level = 0; v.profit = 0; v.weight = 0; v.bound = bound2(v);
	enQueue2(v);
	while (!isEmpty2()) {
		v = deQueue2();
		if (v.bound > maxprofit) {
			u.level = v.level + 1;
			u.weight = v.weight + w[u.level];
			u.profit = v.profit + p[u.level];
			if ((u.weight <= W) && (u.profit > maxprofit))maxprofit = u.profit;
			u.bound = bound2(u);
			if (u.bound > maxprofit)enQueue2(u);
			u.weight = v.weight;
			u.profit = v.profit;
			u.bound = bound2(u);
			if (u.bound > maxprofit)enQueue2(u);
		}
	}
}

/*
	bfs에서 사용된 bound()함수와 같다
	다른점은 인자로 받는 구조체 node2에 멤버로
	bound가 있다는 것 뿐이다
*/

float bound2(node2 n) {
	int j, k, totweight;
	float ret;
	if (n.weight > W)return 0;
	else {
		ret = n.profit; j = n.level + 1; totweight = n.weight;
		while ((j <= N) && (totweight + w[j] <= W)) {
			totweight += w[j];
			ret += p[j];
			j++;
		}
		k = j;
		if (k <= N)
			ret += (W - totweight) * (p[k] / w[k]);
		return ret;
	}
}

/*
	priorityqueue가 비어있는지 확인하는 함수
*/

int isEmpty2() {
	return (priorityQueueFront == priorityQueueRear);
}

/*
	priorityqueue에 값을 추가하는 함수
*/
void enQueue2(node2 n) {
	priorityQueue[priorityQueueRear++] = n;
	for(int i=priorityQueueFront;i<priorityQueueRear;i++)
		for(int j= priorityQueueFront;j<i;j++)
			if (priorityQueue[j].bound > priorityQueue[i].bound) {
				node2 tmp = priorityQueue[i];
				priorityQueue[i] = priorityQueue[j];
				priorityQueue[j] = tmp;
			}
}

/*
	priorityqueue에서 노드를 제거하는 함수
*/

node2 deQueue2() {
	return priorityQueue[priorityQueueFront++];
}
