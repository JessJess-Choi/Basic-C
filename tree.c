
/*	
	scanf함수를 error나 warning없이 사용하기 위한 조치
*/

#pragma warning(disable:4996)

#include<stdio.h>
#include<stdlib.h>

/*	
	명세서에 있는 _TreeNode 구조체 구현
*/

typedef struct _TreeNode{
	char value;
	struct _TreeNode* left;
	struct _TreeNode* right;
} TreeNode;

void makeChild(TreeNode*, char, char);
void treeInOrder(TreeNode*);
void initTree();
TreeNode* searchNode(TreeNode*, char);
TreeNode* start = NULL,* find = NULL;

int main() {
	int n;
	scanf("%d", &n);
	getchar();
	initTree();

	/*
		입력받은 부모의 값으로 부모노드를 먼저 찾고,
		찾은 부모노드의 포인터와 입력받은 왼쪽,오른쪽 자식을
		인자로 넘겨서 자식노드를 만든다.
	*/

	for (int i = 0; i < n; i++) {
		find = start;
		char parent, leftChild, rightChild;
		scanf("%c %c %c", &parent, &leftChild, &rightChild);
		getchar();
		makeChild(searchNode(find,parent), leftChild, rightChild);
	}

	treeInOrder(start);
	printf("\n");
	return 0;
}

/*
	함수 시작할때 루트노드를 가리키는 start포인터를 초기화해준다
*/

void initTree() {
	TreeNode* tmp = (TreeNode*)malloc(sizeof(TreeNode));
	start = tmp;
	start->value = 'A';
	tmp->left = NULL;
	tmp->right = NULL;
}

/*	
	입력받은 왼쪽 자식과 오른쪽 자식이 '.' 인 경우 NULL,
	아닌 경우 그 값을 할당하고 다음 왼쪽 오른쪽 자식에 NULL을 할당한다.
*/

void makeChild(TreeNode* node, char leftChild, char rightChild) {
	if (leftChild != '.') {
		node->left = (TreeNode*)malloc(sizeof(TreeNode));
		node->left->value = leftChild;
		node->left->left = node->left->right = NULL;
	}
	else
		node->left = NULL;
	if (rightChild != '.') {
		node->right = (TreeNode*)malloc(sizeof(TreeNode));
		node->right->value = rightChild;
		node->right->left = node->right->right = NULL;
	}
	else
		node->right = NULL;
}

/*	
	찾아야 할 값을 인자로 받아 중위탐색으로 찾은 후
	맞는 값을 찾으면 그 TreeNode포인터를 리턴한다.
*/

TreeNode* searchNode(TreeNode* node,char ch) {
	TreeNode* tmp = NULL;
	if (node == NULL || node->value == ch)return node;
	tmp = searchNode(node->left, ch);
	if (tmp != NULL)return tmp;
	tmp = searchNode(node->right, ch);
	return tmp;
}

/*	
	중위탐색으로 탐색을 하며 값을 출력한다.
*/

void treeInOrder(TreeNode* node) {
	if (node != NULL) {
		treeInOrder(node->left);
		printf("%c ", node->value);
		treeInOrder(node->right);
	}
}