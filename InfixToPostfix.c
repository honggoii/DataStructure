#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int GetOpPec(char op)	// 연산자의 우선순위 정보 반환
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

	return -1;	// 등록되지 않은 연사자임
}

int WhoPrecOp(char op1, char op2)
{
	int op1Prec = GetOpPec(op1);
	int op2Prec = GetOpPec(op2);

	if (op1Prec > op2Prec)	
		return 1;	// op1의 우선순위가 더 높다면
	else if (op1Prec < op2Prec)
		return -1;	// op2의 우선순위가 더 높다면
	else
		return 0;	// 우선순위가 같다면
}

void ConvToRPNExp(char exp[])
{
	Stack stack;
	int expLen = strlen(exp);
	char* convExp = (char*)malloc(expLen + 1);	// 변환된 수식 저장

	int i, idx = 0;
	char tok, popOp;

	memset(convExp, 0, sizeof(char) * expLen + 1);	// 0으로 초기화
	StackInit(&stack);

	for (i = 0; i < expLen; i++)
	{
		tok = exp[i];	

		if (isdigit(tok))
		{
			convExp[idx++] = tok;	// 피연산자는 그냥 옮김
		}
		else
		{
			switch (tok)
			{
			case '(':				// 여는 소괄호는
				Push(&stack, tok);	// push
				break;
			case ')':				// 닫는 소괄호는
				while (1)
				{
					popOp = Pop(&stack);// pop하고 저장
					if (popOp == '(')	// 여는 소괄호를 만나면
						break;			// 반복문 탈출
					convExp[idx++] = popOp;
				}
				break;
			case '+': case '-':
			case '*': case '/':
				while (!IsEmpty(&stack) && WhoPrecOp(Peek(&stack), tok) >= 0)
					// 스택이 비어있지않고 스택의 꼭대기가 비교할 연산자보다 우선순위가 높으면
					convExp[idx++] = Pop(&stack);	// pop
				Push(&stack, tok);
				break;
			}
		}
	}

	while (IsEmpty(&stack))				// 스택에 남은 연산자를
		convExp[idx++] = Pop(&stack);	// 모두 옮김

	strcpy(exp, convExp);	// 변환된 수식을 exp에 복사
	free(convExp);			// convExp 소멸
}