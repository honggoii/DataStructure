#include <stdio.h>
#include <stdlib.h>

typedef int BTData;

typedef struct _bTreeNode
{
	BTData data;
	struct _bTreeNode* left;
	struct _bTreeNode* right;
} BTreeNode;

BTreeNode* MakeBTreeNode(void);	// ��� ����
BTData GetData(BTreeNode* bt);	// ��忡 ����� ������ ��ȯ
void SetData(BTreeNode* bt, BTData data);	// ��忡 ������ ����

BTreeNode* GetLeftSubTree(BTreeNode* bt);	// ���� ���� Ʈ�� �ּ� �� ��ȯ
BTreeNode* GetRightSubTree(BTreeNode* bt);	// ������ ���� Ʈ�� �ּ� �� ��ȯ

void MakeLeftSubTree(BTreeNode* main, BTreeNode* sub);	// main�� ���� ����Ʈ���� sub ����
void MakeRightSubTree(BTreeNode* main, BTreeNode* sub);	// main�� ������ ����Ʈ���� sub ����

int main(void)
{
	BTreeNode* bt1 = MakeBTreeNode();	// ��� bt1 ����
	BTreeNode* bt2 = MakeBTreeNode();	// ��� bt2 ����
	BTreeNode* bt3 = MakeBTreeNode();	// ��� bt3 ����
	BTreeNode* bt4 = MakeBTreeNode();	// ��� bt4 ����

	SetData(bt1, 1);	// bt1�� 1 ����
	SetData(bt2, 2);	// bt2�� 2 ����
	SetData(bt3, 3);	// bt3�� 3 ����
	SetData(bt4, 4);	// bt4�� 4 ����

	MakeLeftSubTree(bt1, bt2);	// bt2�� bt1�� ���� �ڽ� ����
	MakeRightSubTree(bt1, bt3);	// bt3�� bt1�� ������ �ڽ� ����
	MakeLeftSubTree(bt2, bt4);	// bt4�� bt2�� ���� �ڽ� ����

	// bt1�� ���� �ڽ� ��� ������ ���
	printf("%d \n", GetData(GetLeftSubTree(bt1)));

	// bt1�� ���� �ڽ� ����� ���� �ڽ� ��� ������ ���
	printf("%d \n", GetData(GetLeftSubTree(GetLeftSubTree(bt1))));

	return 0;
}

BTreeNode* MakeBTreeNode(void)
{
	BTreeNode* nd = (BTreeNode*)malloc(sizeof(BTreeNode));
	nd->left = NULL;	// ���� NULL�� �ʱ�ȭ
	nd->right = NULL;	// ������ NULL�� �ʱ�ȭ
	return nd;	// ��� ��ȯ
}

BTData GetData(BTreeNode* bt)
{
	return bt->data;
}

void SetData(BTreeNode* bt, BTData data)
{
	bt->data = data;
}

BTreeNode* GetLeftSubTree(BTreeNode* bt)
{
	return bt->left;
}

BTreeNode* GetRightSubTree(BTreeNode* bt)
{
	return bt->right;
}

void MakeLeftSubTree(BTreeNode* main, BTreeNode* sub)
{
	if (main->left != NULL)	// ������ ������ NULL�� �ƴϸ�
		free(main->left);	// �ش� Ʈ�� ����

	main->left = sub;	// ���� ���ʿ� sub����
}

void MakeRightSubTree(BTreeNode* main, BTreeNode* sub)
{
	if (main->right != NULL)// ������ �������� NULL�� �ƴϸ�
		free(main->right);	// �ش� Ʈ�� ����

	main->right = sub;	// ���� �����ʿ� sub����
}