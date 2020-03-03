#include <stdio.h>

BTreeNode* MakeExpTree(char exp[]);	// ���� Ʈ�� ����
int EvaluateExpTree(BTreeNode* bt);	// ���� Ʈ�� ���

void ShowPrefixTypeExp(BTreeNode* bt);	// ���� ǥ��� ��� ��� (���� ��ȸ)
void ShowInfixTypeExp(BTreeNode* bt);	// ���� ǥ��� ��� ��� (���� ��ȸ)
void ShowPostfixTypeExp(BTreeNode* bt);	// ���� ǥ��� ��� ��� (���� ��ȸ)

int main(void)
{
	char exp[] = "12+7*";
	BTreeNode* eTree = MakeExpTree(exp);

	printf("���� ǥ����� ����: ");
	ShowPrefixTypeExp(eTree);
	printf("\n");

	printf("���� ǥ����� ����: ");
	ShowInfixTypeExp(eTree);
	printf("\n");

	printf("���� ǥ����� ����: ");
	ShowPostfixTypeExp(eTree);
	printf("\n");

	printf("������ ���: %d\n", EvaluateExpTree(eTree));

	return 0;
}

BTreeNode* MakeExpTree(char exp[])
{
	Stack stack;
	BTreeNode* pnode;

	int expLen = strlen(exp);
	int i;

	StackIni(&stack);	// ���� �ʱ�ȭ

	for (i = 0; i < expLen; i++)
	{
		pnode = MakeBTreeNode();	// ��� ����

		if (isdigit(exp[i]))
		{	// �ǿ����ڶ��
			SetData(pnode, exp[i] - '0');	// ���ڸ� ������ �ٲ㼭 ����
		}
		else
		{
			// �����ڶ��
			MakeRightSubTree(pnode, Pop(&stack));	 // ���ÿ��� pop�Ͽ� ������ �ڽĳ���
			MakeLeftSubTree(pnode, Pop(&stack));	 // ���ÿ��� pop�Ͽ� ���� �ڽĳ���
			SetData(pnode, exp[i]);
		}

		Push(&stack, pnode);	// ���ÿ� ��� push
	}

	return Pop(&stack);
}

int EvaluateExpTree(BTreeNode* bt)
{
	int op1, op2;

	if (GetLeftSubTree(bt) == NULL && GetRightSubTree(bt) == NULL)
		// �ܸ� ����� ��� Ż�� ������ ��
		return GetData(bt);

	op1 = EvaluateExpTree(GetLeftSubTree(bt));	// ���� ���� Ʈ�� ���
	op2 = EvaluateExpTree(GetRightSubTree(bt));	// ������ ���� Ʈ�� ���

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