#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define maxNumber 30

typedef struct stack {
	int index;
	char arr[maxNumber];
}stack;

stack st;
char sentence[maxNumber];
char postfix[maxNumber];
int value[maxNumber];
void getLine();
void print();
void replace();
int changePostfix(int);
int calculate();
void push(char);
void pop();
char top();
void erase();

int main() {
	while (1) {
		getLine();
	}
	return 0;
}

void getLine() {
	gets(sentence);
	for (int i = 0; i < strlen(sentence); i++) {
		if (sentence[i] == '=') {
			replace();
			return;
		}
	}
	if (strstr(sentence, "print ")) {
		print();
		return;
	}
	if (!strcmp(sentence, "exit"))exit(0);
	printf("Systax Error\n");
}

void print() {
	int tmp = changePostfix(6);
	if (tmp == -1) {
		printf("Syntax Error\n");
		return;
	}

	tmp = calculate();
	if (tmp == -1) {
		printf("Syntax Error\n");
		return;
	}
	printf("%d\n", tmp - '0');
}

void replace() {
	int tmp = changePostfix(2);
	if (tmp == -1) {
		printf("Syntax Error\n");
		return;
	}

	tmp = calculate();
	if (tmp == -1) {
		printf("Syntax Error\n");
		return;
	}
	value[sentence[0] - 'a'] = tmp - '0';
}

int changePostfix(int startIndex) {
	erase();
	char result[maxNumber];
	int tmpInt = 0, resultIndex = 0;
	for (int i = startIndex; i < strlen(sentence); i++) {
		if (sentence[i] == '(')push('(');
		else if (sentence[i] >= '0' && sentence[i] <= '9') {
			tmpInt *= 10;
			tmpInt += (sentence[i] - '0');
			if (i == strlen(sentence) - 1) {
				result[resultIndex++] = tmpInt + '0';
			}
		}
		else if (sentence[i] == '+') {
			if ((sentence[i - 1] < '0' || sentence[i - 1] > '9') && (i != startIndex))
				if (sentence[i - 1] < 'a' || sentence[i]>'z')
					return -1;
			if (tmpInt!=0) {
				result[resultIndex++] = tmpInt + '0';
				tmpInt = 0;
			}
			while (1) {
				if (top() == '+' || top() == '*') {
					result[resultIndex++] = top();
					pop();
				}
				else
					break;
			}
			push(sentence[i]);
		}
		else if (sentence[i] == '*') {
			if ((sentence[i - 1] < '0' || sentence[i - 1] > '9') && (i != startIndex))
				if (sentence[i - 1] < 'a' && sentence[i]>'z')
					return -1;
			if (tmpInt!=0) {
				result[resultIndex++] = tmpInt + '0';
				tmpInt = 0;
			}
			while (1) {
				if (top() == '*') {
					result[resultIndex++] = top();
					pop();
				}
				else
					break;
			}
			push(sentence[i]);
		}
		else if (sentence[i] == ')') {
			if ((sentence[i - 1] < '0' || sentence[i - 1] > '9') && (i != startIndex))
				if (sentence[i - 1] < 'a' && sentence[i]>'z')
					return -1;
			if (tmpInt!=0) {
				result[resultIndex++] = tmpInt + '0';
				tmpInt = 0;
			}
			while (1) {
				if (top() == '(') {
					pop();
					break;
				}
				result[resultIndex++] = top();
				pop();
			}
		}
		else if (sentence[i] >= 'a' && sentence[i] <= 'z') {
			result[resultIndex++] = value[sentence[i]-'a']+'0';
		}
		else
			return -1;
	}
	while (!isEmpty()) {
		char tmp = top();
		if (tmp == '(')
			return -1;
		result[resultIndex++] = top();
		pop();
	}
	result[resultIndex++] = '\0';
	strcpy(postfix, result);
}

int calculate() {
	erase();
	for (int i = 0; i < strlen(postfix); i++) {
		if (postfix[i] == '+') {
			int x, y;
			x = top(); pop();
			y = top(); pop();
			if (x == -1 || y == -1)return -1;
			push(x + y - '0');
		}
		else if (postfix[i] == '*') {
			int x, y;
			x = top(); pop();
			y = top(); pop();
			if (x == -1 || y == -1)return -1;
			push((x - '0') * (y - '0') + '0');
		}
		else 
			push(postfix[i]);
	}
	if (st.index != 1)return -1;
	else return top();
}

void push(char n) {
	st.arr[st.index++] = n;
}

void pop() {
	if(!isEmpty())
		st.index--;
}

char top() {
	if (!isEmpty())
		return st.arr[st.index - 1];
	else
		return -1;
}

void erase() {
	st.index = 0;
}

int isEmpty() {
	return !st.index;
}