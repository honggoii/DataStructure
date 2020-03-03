#include <stdio.h>

BTreeNode* MakeExpTree(char exp[]);	// 수식 트리 구성
int EvaluateExpTree(BTreeNode* bt);	// 수식 트리 계산

void ShowPrefixTypeExp(BTreeNode* bt);	// 전위 표기법 기반 출력 (전위 순회)
void ShowInfixTypeExp(BTreeNode* bt);	// 중위 표기법 기반 출력 (중위 순회)
void ShowPostfixTypeExp(BTreeNode* bt);	// 후위 표기법 기반 출력 (후위 순회)

int main(void)
{
	char exp[] = "12+7*";
	BTreeNode* eTree = MakeExpTree(exp);

	printf("전위 표기법의 수식: ");
	ShowPrefixTypeExp(eTree);
	printf("\n");

	printf("중위 표기법의 수식: ");
	ShowInfixTypeExp(eTree);
	printf("\n");

	printf("후위 표기법의 수식: ");
	ShowPostfixTypeExp(eTree);
	printf("\n");

	printf("연산의 결과: %d\n", EvaluateExpTree(eTree));

	return 0;
}

BTreeNode* MakeExpTree(char exp[])
{
	Stack stack;
	BTreeNode* pnode;

	int expLen = strlen(exp);
	int i;

	StackIni(&stack);	// 스택 초기화

	for (i = 0; i < expLen; i++)
	{
		pnode = MakeBTreeNode();	// 노드 생성

		if (isdigit(exp[i]))
		{	// 피연산자라면
			SetData(pnode, exp[i] - '0');	// 문자를 정수로 바꿔서 저장
		}
		else
		{
			// 연산자라면
			MakeRightSubTree(pnode, Pop(&stack));	 // 스택에서 pop하여 오른쪽 자식노드로
			MakeLeftSubTree(pnode, Pop(&stack));	 // 스택에서 pop하여 왼쪽 자식노드로
			SetData(pnode, exp[i]);
		}

		Push(&stack, pnode);	// 스택에 결과 push
	}

	return Pop(&stack);
}

int EvaluateExpTree(BTreeNode* bt)
{
	int op1, op2;

	if (GetLeftSubTree(bt) == NULL && GetRightSubTree(bt) == NULL)
		// 단말 노드라면 재귀 탈출 조건이 됨
		return GetData(bt);

	op1 = EvaluateExpTree(GetLeftSubTree(bt));	// 왼쪽 서브 트리 계산
	op2 = EvaluateExpTree(GetRightSubTree(bt));	// 오른쪽 서브 트리 계산

	switch (GetData(bt))
	{
	case '+':
		return op1 + op2;
	case '-':
		return op1 - op2;
	case '*':
		return op1 * op2;
	case '/':
		return op1 / op2;
	}

	return 0;
}

void ShowPrefixTypeExp(BTreeNode* bt)
{
	PreorderTraverse(bt, ShowNodeData);
}

void ShowInfixTypeExp(BTreeNode* bt)
{
	InorderTraverse(bt, ShowNodeData);
}

void ShowPostfixTypeExp(BTreeNode* bt)
{
	PostorderTraverse(bt, ShowNodeData);
}