#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define STACK_LEN 100

typedef int Data;

typedef struct _arrayStack
{
	Data stackArr[STACK_LEN];
	int topIndex;
} ArrayStack;

typedef ArrayStack Stack;

void StackInit(Stack* pstack);	// ���� �ʱ�ȭ
int IsEmpty(Stack* pstack);		// ������ ����ִ��� Ȯ��

void Push(Stack* pstack, Data data);	// push
Data Pop(Stack* pstack);				// pop
Data Peek(Stack* pstack);				// peek

int main(void)
{
	// Stack ���� �� �ʱ�ȭ
	Stack stack;
	StackInit(&stack);

	// ������ ����
	Push(&stack, 1);	Push(&stack, 2);
	Push(&stack, 3);	Push(&stack, 4);
	Push(&stack, 5);

	// ������ ������
	while (!IsEmpty(&stack))
		printf("%d ", Pop(&stack));

	return 0;
}

void StackInit(Stack* pstack)
{
	pstack->topIndex = -1;	// -1�� �� ���¸� �ǹ���
}

int IsEmpty(Stack* pstack)
{
	if (pstack->topIndex == -1)	// ������ ���������
		return TRUE;
	else
		return FALSE;
}

void Push(Stack* pstack, Data data)
{
	pstack->topIndex += 1;	// Top�� �� ĭ �ø���
	pstack->stackArr[pstack->topIndex] = data;	// ������ ����
}

Data Pop(Stack* pstack)
{
	int idx;

	if (IsEmpty(pstack))
	{
		printf("Stack Memry Error!\n");
		exit(-1);
	}

	idx = pstack->topIndex;	// ������ �����Ͱ� ����� �ε��� �� ����
	pstack->topIndex -= 1;	// Top �Ʒ��� �� ĭ ����

	return pstack->stackArr[idx];	// �����Ǵ� ������ ��ȯ
}

Data Peek(Stack* pstack)
{
	if (IsEmpty(pstack))
	{
		printf("Stack Memory Error!\n");
		exit(-1);
	}

	return pstack->stackArr[pstack->topIndex];	// �� ���� ����� ������ ��ȯ
}