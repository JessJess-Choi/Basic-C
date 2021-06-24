#include<stdio.h>
void hanoi(char f,char s,char t,int n)    //f:첫번째 기둥, s:두번째기둥, t:세번째기둥, n:원판갯수
{
	if(n==1)
		printf("원판 첫번째를 %c 기둥에서 %c 기둥으로 옮긴다\n",f,t);

	else
	{
		hanoi(f,t,s,(n-1));
		printf("%d번째 원판을 %c기둥에서 %c 기둥으로 옮긴다\n",n,f,t);
		hanoi(s,f,t,(n-1));
	}
}
int main(void){
	int n;
	char f,s,t;
	printf("원판의 갯수를 입력하세요:");
	scanf("%d",&n);
	if(n<1)
		printf("잘못입력했습니다.1이상인 숫자를 입력하세요.");
	else
		hanoi('f','s','t',n);
	return 0;
}



	
