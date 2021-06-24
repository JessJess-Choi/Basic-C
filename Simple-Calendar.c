#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

int main() {
	int array[31], * p, year, x = 0;
	scanf("%d", &year);
	year--;
	x = (year * 365 + year / 4 - year / 100 + year / 400 + 1) % 7;
	p = array;
	for (int i = 0; i < 31; i++) {
		*p = x++;
		p++;
	}
	p = array;
	for (int i = 0; i < 31; i++) {
		char day[10];
		switch (*p % 7) {
		case 0:
			strcpy(day, "일");
			break;
		case 1:
			strcpy(day, "월");
			break;
		case 2:
			strcpy(day, "화");
			break;
		case 3:
			strcpy(day, "수");
			break;
		case 4:
			strcpy(day, "목");
			break;
		case 5:
			strcpy(day, "금");
			break;
		case 6:
			strcpy(day, "토");
			break;
		}
		printf("%d 1/%d : %s\n", year+1, i + 1, day);
		p++;
	}
	return 0;
}