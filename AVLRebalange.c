int GetHeight(BTreeNode* bst) // Ʈ�� ���� ����Ͽ� ��ȯ
{
	int leftH; // left height
	int rightH; // right height

	if (bst == NULL)
		return 0;

	leftH = GetHeight(GetLeftSubTree(bst)); // ���� ���� Ʈ�� ���� ���
	rightH = GetHeight(GetRightSubTree(bst)); // ������ ���� Ʈ�� ���� ���

	// ū ���� ���� ��ȯ
	if (leftH > rightH)
		return leftH + 1;
	else
		return rightH + 1;
}

int GetHeightDiff(BTreeNode* bst) // ���� �μ� ��ȯ
{
	int lsh; // left sub tree height
	int rsh; // right sub tree height

	if (bst == NULL)
		return 0;

	lsh = GetHeight(GetLeftSubTree(bst)); // ���� ���� Ʈ�� ����
	rsh = GetHeight(GetRightSubTree(bst)); // ������ ���� Ʈ�� ����
	
	return lsh - rsh; // �����μ� ����
}

BTreeNode* RotateLL(BTreeNode* bst) // LLȸ��
{
	BTreeNode* pNode; // parent node
	BTreeNode* cNode; // child node

	pNode = bst;
	cNode = GetLeftSubTree(pNode);

	// ���� ȸ��
	ChangeLeftSubTree(pNode, GetRightSubTree(cNode));
	ChangeRightSubTree(cNode, pNode);

	return cNode; // ����� ��Ʈ �ּ� �� ��ȯ
}

BTreeNode* RotateRR(BTreeNode* bst) // RRȸ��
{
	BTreeNode* pNode; // parent node
	BTreeNode* cNode; // child node

	pNode = bst;
	cNode = GetRightSubTree(pNode);

	// ���� ȸ��
	ChangeRightSubTree(pNode, GetLeftSubTree(cNode));
	ChangeLeftSubTree(cNode, pNode);

	return cNode; // ����� ��Ʈ �ּ� �� ��ȯ
}

BTreeNode* RotateLR(BTreeNode* bst) // LRȸ��
{
	BTreeNode* pNode; // parent node
	BTreeNode* cNode; // child node

	pNode = bst;
	cNode = GetLeftSubTree(pNode);

	ChangeLeftSubTree(pNode, RotateRR(cNode)); // �κ� RRȸ��

	return RotateLL(pNode); // LLȸ��
}

BTreeNode* RotateRL(BTreeNode* bst) // RLȸ��
{
	BTreeNode* pNode; // parent node
	BTreeNode* cNode; // child node

	pNode = bst;
	cNode = GetRightSubTree(pNode);

	ChangeRightSubTree(pNode, RotateLL(cNode)); // �κ� LLȸ��

	return RotateRR(pNode); // RRȸ��
}

BTreeNode* Rebalance(BTreeNode** pRoot)
{
	int hDiff = GetHeightDiff(*pRoot); // ���� �μ� ���

	// ���� �μ��� +2�̻��̸� LL���� �Ǵ� LR����
	if (hDiff > 1)
	{
		if (GetHeightDiff(GetLeftSubTree(*pRoot)) > 0) // LL���¶��
			*pRoot = RotateLL(*pRoot);                 // LLȸ��
		else                                           // LR���¶��
			*pRoot = RotateLR(*pRoot);                 // LRȸ��
	}

	// ���� �μ��� -2�����̸� RR���� �Ǵ� RL����
	if (hDiff < -1)
	{
		if (GetHeightDiff(GetRightSubTree(*pRoot)) < 0) // RR���¶��
			*pRoot = RotateRR(*pRoot);                  // RRȸ��
		else                                            // LL���¶��
			* pRoot = RotateRL(*pRoot);                 // LLȸ��
	}

	return *pRoot;
}