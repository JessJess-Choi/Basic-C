#include<stdio.h>
#include<string.h>
int map[100][100];
int visited[100];
int stack[100];
int top = 0;
int num;
int start;
void printLoad() {
	for(int i=1; i<=num; i++)
	{
		printf("%d>", stack[i]);
	}
	printf("%d \n", start);
}
void DFS(int i)
{
	for(int j=1; j<=num; j++)
	{
		if(visited[j] == 0 && map[i][j] == 1)
		{
			stack[++top] = j;
			visited[j] = 1;
			DFS(j);
		}
		else if(map[i][j] == 1 && visited[j] == 1 && j == start && top == num)
		{
			printLoad();
			break;
		}
		else
			;
	}
	stack[top] = 0;
	top--;
	visited[i] = 0;
}

int main(void)
{
	memset(map,0,sizeof(int) * 20 * 20);
	memset(visited,0,sizeof(int)*20);
	printf("input num N :");
	scanf("%d", &num);
	
	for(int i=1; i<=num; i++)
	{
		for(int j=1; j<=num; j++)
		{
			scanf("%d", &map[i][j]);
		}
	}

	for(int i=1; i<=num; i++)
	{
		start = i;
		top = 0;
		memset(stack, 0, sizeof(int)*20);
		memset(visited, 0, sizeof(int)*20);
		
		stack[++top] = i;
		visited[i] = 1;
		DFS(i);
	}
}
