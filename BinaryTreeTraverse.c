#include <stdio.h>

typedef int BTData;

typedef struct _bTreeNode
{
	BTData data;
	struct _bTreeNode* left;
	struct _bTreeNode* right;
} BTreeNode;

typedef void VisitFuncPtr(BTData data);

void PreorderTraverse(BTreeNode* bt, VisitFuncPtr action)
{
	if (bt == NULL)
		return;	// // ������ ���� ��� Ż��

	action(bt->data);					// 1�ܰ�. ��Ʈ ��� �湮
	PreorderTraverse(bt->left, action);	// 2�ܰ�. ���� ���� Ʈ�� ��ȸ
	PreorderTraverse(bt->right, action);// 3�ܰ�. ������ ���� Ʈ�� ��ȸ
}

void InorderTraverse(BTreeNode* bt, VisitFuncPtr action)
{
	if (bt == NULL)
		return;	// // ������ ���� ��� Ż��

	InorderTraverse(bt->left, action);	// 1�ܰ�. ���� ���� Ʈ�� ��ȸ
	action(bt->data);					// 2�ܰ�. ��Ʈ ��� �湮
	InorderTraverse(bt->right, action);	// 3�ܰ�. ������ ���� Ʈ�� ��ȸ
}

void PostorderTraverse(BTreeNode* bt, VisitFuncPtr action)
{
	if (bt == NULL)
		return;	// // ������ ���� ��� Ż��

	PostorderTraverse(bt->left, action);	// 1�ܰ�. ���� ���� Ʈ�� ��ȸ
	PostorderTraverse(bt->right, action);	// 2�ܰ�. ������ ���� Ʈ�� ��ȸ
	action(bt->data);						// 3�ܰ�. ��Ʈ ��� �湮
}