#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

enum{ERR,PLUS,STAR,NUMBER,LP,RP,ID,PRINT,EQL,RET} token;

void get_token();
int expr();
int term();
int factor();
void error();
void statement();
int num;
int array[26];
char sentence[50];
int index;

int main() {
	while (1) {
		index = -1;
		memset(sentence, 0, 50);
		fgets(sentence, 50, stdin);
		if (!strcmp(sentence, "exit\n"))break;
		get_token();
		statement();
	}
}

void get_token() {
	index++;
	if (sentence[index] == '+')token = PLUS;
	else if (sentence[index] == '*')token = STAR;
	else if (sentence[index] == '(')token = LP;
	else if (sentence[index] == ')')token = RP;
	else if (sentence[index] == '\n')token = RET;
	else if (index == 0 && sentence[index + 1] == '=' && sentence[index] >= 'a' && sentence[index] <= 'z')token = EQL, index++;
	else if (sentence[index] >= '0' && sentence[index] <= '9')token = NUMBER, num = sentence[index] - '0';
	else if (index > 1 && sentence[index] >= 'a' && sentence[index] <= 'z')token = ID, num = sentence[index] - 'a';
	else if (index == 0 && sentence[index] == 'p' && sentence[1]=='r' && sentence[2]=='i' && sentence[3] == 'n' && sentence[4] == 't' && sentence[5] == ' ')token = PRINT, index = 5;
	else token = ERR;
}

void statement() {
	while (1) {
		if (token == PRINT) {
			get_token();
			if (token == NUMBER)
				if (strstr(sentence, "print "))
					printf("%d\nCorrect Expression\n", expr());
				else if (sentence[1] == '=' && sentence[0] >= 'a' && sentence[0] <= 'z')
					array[sentence[0] - 'a'] = expr();
				else
					token = ERR;

			if (token == ID)
				if (strstr(sentence, "print "))
					printf("%d\nCorrect Expression\n", expr());
				else if (sentence[1] == '=' && sentence[0] >= 'a' && sentence[0] <= 'z')
					array[sentence[0] - 'a'] = expr();
				else
					token = ERR;
		}
		else if (token == EQL) {
			printf("Correct Expression\n");
			get_token();
			if (token == NUMBER)
				if (strstr(sentence, "print "))
					printf("%d\nCorrect Expression\n", expr());
				else if (sentence[1] == '=' && sentence[0] >= 'a' && sentence[0] <= 'z')
					array[sentence[0] - 'a'] = expr();
				else
					token = ERR;

			if (token == ID)
				if (strstr(sentence, "print "))
					printf("%d\nCorrect Expression\n", expr());
				else if (sentence[1] == '=' && sentence[0] >= 'a' && sentence[0] <= 'z')
					array[sentence[0] - 'a'] = expr();
				else
					token = ERR;
		}
		if (token == ERR) {
			error();
			return;
		}
		if (token == RET)break;
		get_token();
	}
}

int expr() {
	int r;
	r = term();
	while (token == PLUS) {
		get_token();
		r = r + term();
	}
	return r;
}

int term() {
	int r;
	r = factor();
	while (token == STAR) {
		get_token();
		r = r * factor();
	}
	return r;
}

int factor() {
	int r;
	if (token == NUMBER) {
		r = num;
		get_token();
	}
	else if (token == ID) {
		r = array[num];
		get_token();
	}
	else if (token == LP) {
		get_token();
		r = expr();
		if (token == RP)
			get_token();
		else
			error();
	}
	else
		error();
	return r;
}

void error() {
	printf("Syntax Error\n");
}