int EvalRPNExp(char exp[])
{
	Stack stack;
	int expLen = strlen(exp);
	int i;
	char tok, op1, op2;

	StackInit(&stack);

	for (i = 0; i < expLen; i++)
	{
		tok = exp[i];
		if(isdigit(tok))
		{
			Push(&stack, tok - '0');	// �ǿ����ڴ� push , tok�� char�� ����Ǿ��ֱ� ������ ���ڷ� �ٲ���
		}
		else
		{
			op2 = Pop(&stack);	// ���� ���� �ǿ����ڴ� ������ �ǿ�����
			op1 = Pop(&stack);	// ���߿� ���� �ǿ����ڴ� ���� �ǿ�����

			switch (tok)
			{
			case '+':
				Push(&stack, op1 + op2);
				break;
			case '-':
				Push(&stack, op1 - op2);
				break;
			case '*':
				Push(&stack, op1 * op2);
				break;
			case '/':
				Push(&stack, op1 / op2);
				break;
			}
		}
	}
	return Pop(&stack);	// ���ÿ� ���� ������ ��ȯ
}