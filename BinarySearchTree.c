#include <stdio.h>
#include <stdlib.h>

typedef BTData BSTData;

void BSTMakeAndInit(BTreeNode** pRoot); // BST 생성 및 초기화

BSTData BSTGetNodeData(BTreeNode* bst); // 노드에 저장된 데이터 반환

void BSTInsert(BTreeNode** pRoot, BSTData data); // BST를 대상으로 데이터 저장(노드 생성)

BTreeNode* BSTSearch(BTreeNode* bst, BSTData target); // BST를 대상으로 데이터 탐색

BTreeNode* BSTRemove(BTreeNode** pRoot, BSTData target); // 트리에서 노드를 제거하고 제거된 노드의 주소 값 반환

void BSTShowAll(BTreeNode* bst); // 이진 탐색 트리에 저장된 모든 노드의 데이터 출력

int main(void)
{
	BTreeNode* bstRoot; // bstRoo는 BST의 루트 노드
	BTreeNode* sNode; // search node

	BSTMakeAndInit(&bstRoot); // Binary Search Tree 생성 및 초기화

	BSTInsert(&bstRoot, 9); // bstRoot에 9 저장
	BSTInsert(&bstRoot, 1); // bstRoot에 1 저장
	BSTInsert(&bstRoot, 6); // bstRoot에 6 저장
	BSTInsert(&bstRoot, 2); // bstRoot에 2 저장
	BSTInsert(&bstRoot, 8); // bstRoot에 8 저장
	BSTInsert(&bstRoot, 3); // bstRoot에 3 저장
	BSTInsert(&bstRoot, 5); // bstRoot에 5 저장

	sNode = BSTSearch(bstRoot, 1); // 1 찾으러
	if (sNode == NULL)
		printf("탐색 실패\n");
	else
		printf("탐색에 성공한 키의 값: %d \n", BSTGetNodeData(sNode));

	sNode = BSTSearch(bstRoot, 4); // 4 찾으러
	if (sNode == NULL)
		printf("탐색 실패\n");
	else
		printf("탐색에 성공한 키의 값: %d \n", BSTGetNodeData(sNode));

	sNode = BSTSearch(bstRoot, 6); // 6 찾으러
	if (sNode == NULL)
		printf("탐색 실패\n");
	else
		printf("탐색에 성공한 키의 값: %d \n", BSTGetNodeData(sNode));

	sNode = BSTSearch(bstRoot, 7); // 7 찾으러
	if (sNode == NULL)
		printf("탐색 실패\n");
	else
		printf("탐색에 성공한 키의 값: %d \n", BSTGetNodeData(sNode));

	return 0;
}

void BSTMakeAndInit(BTreeNode** pRoot)
{
	*pRoot = NULL;
}

BSTData BSTGetNodeData(BTreeNode* bst)
{
	return GetData(bst);
}

void BSTInsert(BTreeNode** pRoot, BSTData data)
{
	BTreeNode* pNode = NULL; // parent node
	BTreeNode* cNode = *pRoot; // current node
	BTreeNode* nNode = NULL; // new node

	// 새로운 노드 위치 찾기
	while (cNode != NULL)
	{
		if (data == GetData(cNode))
			return; // 키 중복 방지

		pNode = cNode;

		if (GetData(cNode) > data)
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}

	// pNode의 자식 노드로 추가할 새 노드 생성
	nNode = MakeBTreeNode(); // 새 노드 생성
	SetData(nNode, data); // 새 노드에 데이터 저장

	// pNode의 자식 노드로 새 노드 추가
	if (pNode != NULL)
	{ // 새 노드가 루트 노드가 아니라면
		if (data < GetData(pNode))
			MakeLeftSubTree(pNode, nNode); 
		else
			MakeRightSubTree(pNode, nNode);
	}
	else
	{ // 새 노드가 루트 노드라면
		*pRoot = nNode;
	}
}

BTreeNode* BSTSearch(BTreeNode* bst, BSTData target)
{
	BTreeNode* cNode = bst; // current node
	BSTData cd; // current data

	while (cNode != NULL)
	{
		cd = GetData(cNode);

		if (target == cd)
			return cNode;
		else if (target < cd)
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}

	return NULL; // 탐색대상이 저장되어 있지 않음 
}

BTreeNode* BSTRemove(BTreeNode** pRoot, BSTData target)
{
	// 삭제 대상이 루트 노드인 경우를 별도로 고려
	BTreeNode* pVRoot = MakeBTreeNode(); // 가상 루트 노드
	BTreeNode* pNode = pVRoot; // parent node
	BTreeNode* cNode = *pRoot; // current node
	BTreeNode* dNode; // delete node
	
	// 루트 노드를 pVRoot가 가리키는 노드의 오른쪽 자식 노드가 되게 한다.
	ChangeRightSubTree(pVRoot, *pRoot);

	// 삭제 대상인 노드 탐색
	while (cNode != NULL && GetData(cNode) != target)
	{
		pNode = cNode; 

		if (target < GetData(cNode))
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}

	if (cNode == NULL) // 삭제 대상이 존재하지 않는다면
		return NULL;

	dNode = cNode; // 삭제 대상을 dNode에 저장

	// 경우 1 : 삭제 대상이 단말 노드인 경우
	if (GetLeftSubTree(dNode) == NULL && GetRightSubTree(dNode) == NULL)
	{
		if (GetLeftSubTree(pNode) == dNode) // 삭제 노드가 왼쪽 자식 노드라면
			RemoveLeftSubTree(pNode);       // 왼쪽 자식 노드 트리 제거
		else                                // 삭제 노드가 오른쪽 자식 노드라면
			RemoveRightSubTree(pNode);      // 오른쪽 자식 노드 트리 제거
	}

	// 경우 2 : 삭제 대상이 하나의 자식 노드를 갖는 경우
	else if (GetLeftSubTree(dNode) == NULL || GetRightSubTree(dNode) == NULL)
	{
		BTreeNode* dcNode; // 삭제 대상의 자식 노드를 가리킴

		// 삭제 대상의 자식 노드 찾기
		if (GetLeftSubTree(dNode) != NULL) // 자식 노드가 왼쪽에 있다면
			dcNode = GetLeftSubTree(dNode);
		else                               // 자식 노드가 오른쪽에 있다면
			dcNode = GetRightSubTree(dNode);

		// 삭제 대상의 부모 노드와 자식 노드 연결
		if (GetLeftSubTree(dNode) == dNode)    // 삭제 대상이 왼쪽 자식 노드이면
			ChangeLeftSubTree(pNode, dcNode);  // 왼쪽에 연결
		else                                   // 삭제 대상이 오른쪽 자식 노드이면
			ChangeRightSubTree(pNode, dcNode); // 오른쪽에 연결
	}

	// 경우 3 : 두 개의 자식 노드를 갖는 경우
	else
	{
		BTreeNode* mNode = GetRightSubTree(dNode); // 대체 노드
		BTreeNode* mpNode = dNode; // 대체 노드의 부모 노드
		int delData;

		// 삭제 대상의 대체 노드 찾기
		while (GetLeftSubTree(mNode) != NULL)
		{
			mpNode = mNode;
			mNode = GetLeftSubTree(mNode);
		}

		// 대체 노드에 저장된 값을 삭제할 노드에 대입
		delData = GetData(dNode); 
		SetData(dNode, GetData(mNode));

		// 대체 노드의 부모 노드와 자식 노드 연결
		// 대체 노드는 무조건 왼쪽 자식이므로 오른쪽 자식만 남음 
		if (GetLeftSubTree(mpNode) == mNode) // 대체할 노드가 왼쪽 자식 노드라면
			ChangeLeftSubTree(mpNode, GetRightSubTree(mNode)); // 대체할 노드의 자식 노드를 부모 노드 왼쪽에 연결
		else                                 // 대체할 노드가 오른쪽 자식 노드라면
			ChangeRightSubTree(mpNode, GetRightSubTree(mNode)); // 대체할 노드의 자식 노드를 부모 노드의 오른쪽에 연결
		
 
		dNode = mNode;
		SetData(dNode, delData);
	}

	// 삭제된 노드가 루트 노드인 경우에 대한 추가 처리
	if (GetRightSubTree(pVRoot) != *pRoot)
		*pRoot = GetRightSubTree(pVRoot); // 루트 노드 변경 반영

	free(pVRoot); // 가상 루트 노드 소멸
	return dNode; // 삭제 대상 반환
}

void ShowIntData(int data)
{
	printf("%d ", data);
}
void BSTShowAll(BTreeNode* bst)
{
	InorderTraverse(bst, ShowIntData);
}

int main(void)
{
	BTreeNode* bstRoot;
	BTreeNode* sNode;
	
	BSTMakeAndInit(&bstRoot);

	BSTInsert(&bstRoot, 5);	BSTInsert(&bstRoot, 8);
	BSTInsert(&bstRoot, 1);	BSTInsert(&bstRoot, 6);
	BSTInsert(&bstRoot, 4);	BSTInsert(&bstRoot, 9);
	BSTInsert(&bstRoot, 3);	BSTInsert(&bstRoot, 2);
	BSTInsert(&bstRoot, 7);

	BSTShowAll(bstRoot); printf("\n");
	sNode = BSTRemove(&bstRoot, 3);
	free(sNode);

	BSTShowAll(bstRoot); printf("\n");
	sNode = BSTRemove(&bstRoot, 8);
	free(sNode);

	BSTShowAll(bstRoot); printf("\n");
	sNode = BSTRemove(&bstRoot, 1);
	free(sNode);

	BSTShowAll(bstRoot); printf("\n");
	sNode = BSTRemove(&bstRoot, 6);
	free(sNode);

	BSTShowAll(bstRoot); printf("\n");
	free(sNode);
}