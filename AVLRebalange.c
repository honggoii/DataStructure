int GetHeight(BTreeNode* bst) // 트리 높이 계산하여 반환
{
	int leftH; // left height
	int rightH; // right height

	if (bst == NULL)
		return 0;

	leftH = GetHeight(GetLeftSubTree(bst)); // 왼쪽 서브 트리 높이 계산
	rightH = GetHeight(GetRightSubTree(bst)); // 오른쪽 서브 트리 높이 계산

	// 큰 값의 높이 반환
	if (leftH > rightH)
		return leftH + 1;
	else
		return rightH + 1;
}

int GetHeightDiff(BTreeNode* bst) // 균형 인수 반환
{
	int lsh; // left sub tree height
	int rsh; // right sub tree height

	if (bst == NULL)
		return 0;

	lsh = GetHeight(GetLeftSubTree(bst)); // 왼쪽 서브 트리 높이
	rsh = GetHeight(GetRightSubTree(bst)); // 오른쪽 서브 트리 높이
	
	return lsh - rsh; // 균형인수 공식
}

BTreeNode* RotateLL(BTreeNode* bst) // LL회전
{
	BTreeNode* pNode; // parent node
	BTreeNode* cNode; // child node

	pNode = bst;
	cNode = GetLeftSubTree(pNode);

	// 실제 회전
	ChangeLeftSubTree(pNode, GetRightSubTree(cNode));
	ChangeRightSubTree(cNode, pNode);

	return cNode; // 변경된 루트 주소 값 반환
}

BTreeNode* RotateRR(BTreeNode* bst) // RR회전
{
	BTreeNode* pNode; // parent node
	BTreeNode* cNode; // child node

	pNode = bst;
	cNode = GetRightSubTree(pNode);

	// 실제 회전
	ChangeRightSubTree(pNode, GetLeftSubTree(cNode));
	ChangeLeftSubTree(cNode, pNode);

	return cNode; // 변경된 루트 주소 값 반환
}

BTreeNode* RotateLR(BTreeNode* bst) // LR회전
{
	BTreeNode* pNode; // parent node
	BTreeNode* cNode; // child node

	pNode = bst;
	cNode = GetLeftSubTree(pNode);

	ChangeLeftSubTree(pNode, RotateRR(cNode)); // 부분 RR회전

	return RotateLL(pNode); // LL회전
}

BTreeNode* RotateRL(BTreeNode* bst) // RL회전
{
	BTreeNode* pNode; // parent node
	BTreeNode* cNode; // child node

	pNode = bst;
	cNode = GetRightSubTree(pNode);

	ChangeRightSubTree(pNode, RotateLL(cNode)); // 부분 LL회전

	return RotateRR(pNode); // RR회전
}

BTreeNode* Rebalance(BTreeNode** pRoot)
{
	int hDiff = GetHeightDiff(*pRoot); // 균형 인수 계산

	// 균형 인수가 +2이상이면 LL상태 또는 LR상태
	if (hDiff > 1)
	{
		if (GetHeightDiff(GetLeftSubTree(*pRoot)) > 0) // LL상태라면
			*pRoot = RotateLL(*pRoot);                 // LL회전
		else                                           // LR상태라면
			*pRoot = RotateLR(*pRoot);                 // LR회전
	}

	// 균형 인수가 -2이하이면 RR상태 또는 RL상태
	if (hDiff < -1)
	{
		if (GetHeightDiff(GetRightSubTree(*pRoot)) < 0) // RR상태라면
			*pRoot = RotateRR(*pRoot);                  // RR회전
		else                                            // LL상태라면
			* pRoot = RotateRL(*pRoot);                 // LL회전
	}

	return *pRoot;
}