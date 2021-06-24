
/*	
	scanf�Լ��� error�� warning���� ����ϱ� ���� ��ġ
*/

#pragma warning(disable:4996)

#include<stdio.h>
#include<stdlib.h>

/*	
	������ �ִ� _TreeNode ����ü ����
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
		�Է¹��� �θ��� ������ �θ��带 ���� ã��,
		ã�� �θ����� �����Ϳ� �Է¹��� ����,������ �ڽ���
		���ڷ� �Ѱܼ� �ڽĳ�带 �����.
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
	�Լ� �����Ҷ� ��Ʈ��带 ����Ű�� start�����͸� �ʱ�ȭ���ش�
*/

void initTree() {
	TreeNode* tmp = (TreeNode*)malloc(sizeof(TreeNode));
	start = tmp;
	start->value = 'A';
	tmp->left = NULL;
	tmp->right = NULL;
}

/*	
	�Է¹��� ���� �ڽİ� ������ �ڽ��� '.' �� ��� NULL,
	�ƴ� ��� �� ���� �Ҵ��ϰ� ���� ���� ������ �ڽĿ� NULL�� �Ҵ��Ѵ�.
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
	ã�ƾ� �� ���� ���ڷ� �޾� ����Ž������ ã�� ��
	�´� ���� ã���� �� TreeNode�����͸� �����Ѵ�.
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
	����Ž������ Ž���� �ϸ� ���� ����Ѵ�.
*/

void treeInOrder(TreeNode* node) {
	if (node != NULL) {
		treeInOrder(node->left);
		printf("%c ", node->value);
		treeInOrder(node->right);
	}
}