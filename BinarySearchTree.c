#include <stdio.h>
#include <stdlib.h>

typedef BTData BSTData;

void BSTMakeAndInit(BTreeNode** pRoot); // BST ���� �� �ʱ�ȭ

BSTData BSTGetNodeData(BTreeNode* bst); // ��忡 ����� ������ ��ȯ

void BSTInsert(BTreeNode** pRoot, BSTData data); // BST�� ������� ������ ����(��� ����)

BTreeNode* BSTSearch(BTreeNode* bst, BSTData target); // BST�� ������� ������ Ž��

BTreeNode* BSTRemove(BTreeNode** pRoot, BSTData target); // Ʈ������ ��带 �����ϰ� ���ŵ� ����� �ּ� �� ��ȯ

void BSTShowAll(BTreeNode* bst); // ���� Ž�� Ʈ���� ����� ��� ����� ������ ���

int main(void)
{
	BTreeNode* bstRoot; // bstRoo�� BST�� ��Ʈ ���
	BTreeNode* sNode; // search node

	BSTMakeAndInit(&bstRoot); // Binary Search Tree ���� �� �ʱ�ȭ

	BSTInsert(&bstRoot, 9); // bstRoot�� 9 ����
	BSTInsert(&bstRoot, 1); // bstRoot�� 1 ����
	BSTInsert(&bstRoot, 6); // bstRoot�� 6 ����
	BSTInsert(&bstRoot, 2); // bstRoot�� 2 ����
	BSTInsert(&bstRoot, 8); // bstRoot�� 8 ����
	BSTInsert(&bstRoot, 3); // bstRoot�� 3 ����
	BSTInsert(&bstRoot, 5); // bstRoot�� 5 ����

	sNode = BSTSearch(bstRoot, 1); // 1 ã����
	if (sNode == NULL)
		printf("Ž�� ����\n");
	else
		printf("Ž���� ������ Ű�� ��: %d \n", BSTGetNodeData(sNode));

	sNode = BSTSearch(bstRoot, 4); // 4 ã����
	if (sNode == NULL)
		printf("Ž�� ����\n");
	else
		printf("Ž���� ������ Ű�� ��: %d \n", BSTGetNodeData(sNode));

	sNode = BSTSearch(bstRoot, 6); // 6 ã����
	if (sNode == NULL)
		printf("Ž�� ����\n");
	else
		printf("Ž���� ������ Ű�� ��: %d \n", BSTGetNodeData(sNode));

	sNode = BSTSearch(bstRoot, 7); // 7 ã����
	if (sNode == NULL)
		printf("Ž�� ����\n");
	else
		printf("Ž���� ������ Ű�� ��: %d \n", BSTGetNodeData(sNode));

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

	// ���ο� ��� ��ġ ã��
	while (cNode != NULL)
	{
		if (data == GetData(cNode))
			return; // Ű �ߺ� ����

		pNode = cNode;

		if (GetData(cNode) > data)
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}

	// pNode�� �ڽ� ���� �߰��� �� ��� ����
	nNode = MakeBTreeNode(); // �� ��� ����
	SetData(nNode, data); // �� ��忡 ������ ����

	// pNode�� �ڽ� ���� �� ��� �߰�
	if (pNode != NULL)
	{ // �� ��尡 ��Ʈ ��尡 �ƴ϶��
		if (data < GetData(pNode))
			MakeLeftSubTree(pNode, nNode); 
		else
			MakeRightSubTree(pNode, nNode);
	}
	else
	{ // �� ��尡 ��Ʈ �����
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

	return NULL; // Ž������� ����Ǿ� ���� ���� 
}

BTreeNode* BSTRemove(BTreeNode** pRoot, BSTData target)
{
	// ���� ����� ��Ʈ ����� ��츦 ������ ���
	BTreeNode* pVRoot = MakeBTreeNode(); // ���� ��Ʈ ���
	BTreeNode* pNode = pVRoot; // parent node
	BTreeNode* cNode = *pRoot; // current node
	BTreeNode* dNode; // delete node
	
	// ��Ʈ ��带 pVRoot�� ����Ű�� ����� ������ �ڽ� ��尡 �ǰ� �Ѵ�.
	ChangeRightSubTree(pVRoot, *pRoot);

	// ���� ����� ��� Ž��
	while (cNode != NULL && GetData(cNode) != target)
	{
		pNode = cNode; 

		if (target < GetData(cNode))
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}

	if (cNode == NULL) // ���� ����� �������� �ʴ´ٸ�
		return NULL;

	dNode = cNode; // ���� ����� dNode�� ����

	// ��� 1 : ���� ����� �ܸ� ����� ���
	if (GetLeftSubTree(dNode) == NULL && GetRightSubTree(dNode) == NULL)
	{
		if (GetLeftSubTree(pNode) == dNode) // ���� ��尡 ���� �ڽ� �����
			RemoveLeftSubTree(pNode);       // ���� �ڽ� ��� Ʈ�� ����
		else                                // ���� ��尡 ������ �ڽ� �����
			RemoveRightSubTree(pNode);      // ������ �ڽ� ��� Ʈ�� ����
	}

	// ��� 2 : ���� ����� �ϳ��� �ڽ� ��带 ���� ���
	else if (GetLeftSubTree(dNode) == NULL || GetRightSubTree(dNode) == NULL)
	{
		BTreeNode* dcNode; // ���� ����� �ڽ� ��带 ����Ŵ

		// ���� ����� �ڽ� ��� ã��
		if (GetLeftSubTree(dNode) != NULL) // �ڽ� ��尡 ���ʿ� �ִٸ�
			dcNode = GetLeftSubTree(dNode);
		else                               // �ڽ� ��尡 �����ʿ� �ִٸ�
			dcNode = GetRightSubTree(dNode);

		// ���� ����� �θ� ���� �ڽ� ��� ����
		if (GetLeftSubTree(dNode) == dNode)    // ���� ����� ���� �ڽ� ����̸�
			ChangeLeftSubTree(pNode, dcNode);  // ���ʿ� ����
		else                                   // ���� ����� ������ �ڽ� ����̸�
			ChangeRightSubTree(pNode, dcNode); // �����ʿ� ����
	}

	// ��� 3 : �� ���� �ڽ� ��带 ���� ���
	else
	{
		BTreeNode* mNode = GetRightSubTree(dNode); // ��ü ���
		BTreeNode* mpNode = dNode; // ��ü ����� �θ� ���
		int delData;

		// ���� ����� ��ü ��� ã��
		while (GetLeftSubTree(mNode) != NULL)
		{
			mpNode = mNode;
			mNode = GetLeftSubTree(mNode);
		}

		// ��ü ��忡 ����� ���� ������ ��忡 ����
		delData = GetData(dNode); 
		SetData(dNode, GetData(mNode));

		// ��ü ����� �θ� ���� �ڽ� ��� ����
		// ��ü ���� ������ ���� �ڽ��̹Ƿ� ������ �ڽĸ� ���� 
		if (GetLeftSubTree(mpNode) == mNode) // ��ü�� ��尡 ���� �ڽ� �����
			ChangeLeftSubTree(mpNode, GetRightSubTree(mNode)); // ��ü�� ����� �ڽ� ��带 �θ� ��� ���ʿ� ����
		else                                 // ��ü�� ��尡 ������ �ڽ� �����
			ChangeRightSubTree(mpNode, GetRightSubTree(mNode)); // ��ü�� ����� �ڽ� ��带 �θ� ����� �����ʿ� ����
		
 
		dNode = mNode;
		SetData(dNode, delData);
	}

	// ������ ��尡 ��Ʈ ����� ��쿡 ���� �߰� ó��
	if (GetRightSubTree(pVRoot) != *pRoot)
		*pRoot = GetRightSubTree(pVRoot); // ��Ʈ ��� ���� �ݿ�

	free(pVRoot); // ���� ��Ʈ ��� �Ҹ�
	return dNode; // ���� ��� ��ȯ
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