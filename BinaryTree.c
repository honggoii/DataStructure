#include <stdio.h>
#include <stdlib.h>

typedef int BTData;

typedef struct _bTreeNode
{
	BTData data;
	struct _bTreeNode* left;
	struct _bTreeNode* right;
} BTreeNode;

BTreeNode* MakeBTreeNode(void);	// 노드 생성
BTData GetData(BTreeNode* bt);	// 노드에 저장된 데이터 반환
void SetData(BTreeNode* bt, BTData data);	// 노드에 데이터 저장

BTreeNode* GetLeftSubTree(BTreeNode* bt);	// 왼쪽 서브 트리 주소 값 반환
BTreeNode* GetRightSubTree(BTreeNode* bt);	// 오른쪽 서브 트리 주소 값 반환

void MakeLeftSubTree(BTreeNode* main, BTreeNode* sub);	// main의 왼쪽 서브트리에 sub 연결
void MakeRightSubTree(BTreeNode* main, BTreeNode* sub);	// main의 오른쪽 서브트리에 sub 연결

int main(void)
{
	BTreeNode* bt1 = MakeBTreeNode();	// 노드 bt1 생성
	BTreeNode* bt2 = MakeBTreeNode();	// 노드 bt2 생성
	BTreeNode* bt3 = MakeBTreeNode();	// 노드 bt3 생성
	BTreeNode* bt4 = MakeBTreeNode();	// 노드 bt4 생성

	SetData(bt1, 1);	// bt1에 1 저장
	SetData(bt2, 2);	// bt2에 2 저장
	SetData(bt3, 3);	// bt3에 3 저장
	SetData(bt4, 4);	// bt4에 4 저장

	MakeLeftSubTree(bt1, bt2);	// bt2를 bt1의 왼쪽 자식 노드로
	MakeRightSubTree(bt1, bt3);	// bt3를 bt1의 오른쪽 자식 노드로
	MakeLeftSubTree(bt2, bt4);	// bt4를 bt2의 왼쪽 자식 노드로

	// bt1의 왼쪽 자식 노드 데이터 출력
	printf("%d \n", GetData(GetLeftSubTree(bt1)));

	// bt1의 왼쪽 자식 노드의 왼쪽 자식 노드 데이터 출력
	printf("%d \n", GetData(GetLeftSubTree(GetLeftSubTree(bt1))));

	return 0;
}

BTreeNode* MakeBTreeNode(void)
{
	BTreeNode* nd = (BTreeNode*)malloc(sizeof(BTreeNode));
	nd->left = NULL;	// 왼쪽 NULL로 초기화
	nd->right = NULL;	// 오른쪽 NULL로 초기화
	return nd;	// 노드 반환
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
	if (main->left != NULL)	// 메인의 왼쪽이 NULL이 아니면
		free(main->left);	// 해당 트리 삭제

	main->left = sub;	// 메인 왼쪽에 sub연결
}

void MakeRightSubTree(BTreeNode* main, BTreeNode* sub)
{
	if (main->right != NULL)// 메인의 오른쪽이 NULL이 아니면
		free(main->right);	// 해당 트리 삭제

	main->right = sub;	// 메인 오른쪽에 sub연결
}