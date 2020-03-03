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
		return;	// // 공집합 노드면 재귀 탈출

	action(bt->data);					// 1단계. 루트 노드 방문
	PreorderTraverse(bt->left, action);	// 2단계. 왼쪽 서브 트리 순회
	PreorderTraverse(bt->right, action);// 3단계. 오른쪽 서브 트리 순회
}

void InorderTraverse(BTreeNode* bt, VisitFuncPtr action)
{
	if (bt == NULL)
		return;	// // 공집합 노드면 재귀 탈출

	InorderTraverse(bt->left, action);	// 1단계. 왼쪽 서브 트리 순회
	action(bt->data);					// 2단계. 루트 노드 방문
	InorderTraverse(bt->right, action);	// 3단계. 오른쪽 서브 트리 순회
}

void PostorderTraverse(BTreeNode* bt, VisitFuncPtr action)
{
	if (bt == NULL)
		return;	// // 공집합 노드면 재귀 탈출

	PostorderTraverse(bt->left, action);	// 1단계. 왼쪽 서브 트리 순회
	PostorderTraverse(bt->right, action);	// 2단계. 오른쪽 서브 트리 순회
	action(bt->data);						// 3단계. 루트 노드 방문
}