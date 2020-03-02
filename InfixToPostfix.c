#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int GetOpPec(char op)	// �������� �켱���� ���� ��ȯ
{
	switch (op)
	{
	case '*':
	case '/':
		return 5;
	case '+':
	case '-':
		return 3;
	case '(':
		return 1;
	}

	return -1;	// ��ϵ��� ���� ��������
}

int WhoPrecOp(char op1, char op2)
{
	int op1Prec = GetOpPec(op1);
	int op2Prec = GetOpPec(op2);

	if (op1Prec > op2Prec)	
		return 1;	// op1�� �켱������ �� ���ٸ�
	else if (op1Prec < op2Prec)
		return -1;	// op2�� �켱������ �� ���ٸ�
	else
		return 0;	// �켱������ ���ٸ�
}

void ConvToRPNExp(char exp[])
{
	Stack stack;
	int expLen = strlen(exp);
	char* convExp = (char*)malloc(expLen + 1);	// ��ȯ�� ���� ����

	int i, idx = 0;
	char tok, popOp;

	memset(convExp, 0, sizeof(char) * expLen + 1);	// 0���� �ʱ�ȭ
	StackInit(&stack);

	for (i = 0; i < expLen; i++)
	{
		tok = exp[i];	

		if (isdigit(tok))
		{
			convExp[idx++] = tok;	// �ǿ����ڴ� �׳� �ű�
		}
		else
		{
			switch (tok)
			{
			case '(':				// ���� �Ұ�ȣ��
				Push(&stack, tok);	// push
				break;
			case ')':				// �ݴ� �Ұ�ȣ��
				while (1)
				{
					popOp = Pop(&stack);// pop�ϰ� ����
					if (popOp == '(')	// ���� �Ұ�ȣ�� ������
						break;			// �ݺ��� Ż��
					convExp[idx++] = popOp;
				}
				break;
			case '+': case '-':
			case '*': case '/':
				while (!IsEmpty(&stack) && WhoPrecOp(Peek(&stack), tok) >= 0)
					// ������ ��������ʰ� ������ ����Ⱑ ���� �����ں��� �켱������ ������
					convExp[idx++] = Pop(&stack);	// pop
				Push(&stack, tok);
				break;
			}
		}
	}

	while (IsEmpty(&stack))				// ���ÿ� ���� �����ڸ�
		convExp[idx++] = Pop(&stack);	// ��� �ű�

	strcpy(exp, convExp);	// ��ȯ�� ������ exp�� ����
	free(convExp);			// convExp �Ҹ�
}