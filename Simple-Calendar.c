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
			strcpy(day, "��");
			break;
		case 1:
			strcpy(day, "��");
			break;
		case 2:
			strcpy(day, "ȭ");
			break;
		case 3:
			strcpy(day, "��");
			break;
		case 4:
			strcpy(day, "��");
			break;
		case 5:
			strcpy(day, "��");
			break;
		case 6:
			strcpy(day, "��");
			break;
		}
		printf("%d 1/%d : %s\n", year+1, i + 1, day);
		p++;
	}
	return 0;
}