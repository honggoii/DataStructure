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
			Push(&stack, tok - '0');	// 피연산자는 push , tok는 char로 선언되어있기 때문에 숫자로 바꿔줌
		}
		else
		{
			op2 = Pop(&stack);	// 먼저 꺼낸 피연산자는 오른쪽 피연산자
			op1 = Pop(&stack);	// 나중에 꺼낸 피연산자는 왼쪽 피연산자

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
	return Pop(&stack);	// 스택에 남은 연산결과 반환
}