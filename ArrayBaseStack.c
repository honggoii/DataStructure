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

void StackInit(Stack* pstack);	// 스택 초기화
int IsEmpty(Stack* pstack);		// 스택이 비어있는지 확인

void Push(Stack* pstack, Data data);	// push
Data Pop(Stack* pstack);				// pop
Data Peek(Stack* pstack);				// peek

int main(void)
{
	// Stack 생성 및 초기화
	Stack stack;
	StackInit(&stack);

	// 데이터 삽입
	Push(&stack, 1);	Push(&stack, 2);
	Push(&stack, 3);	Push(&stack, 4);
	Push(&stack, 5);

	// 데이터 꺼내기
	while (!IsEmpty(&stack))
		printf("%d ", Pop(&stack));

	return 0;
}

void StackInit(Stack* pstack)
{
	pstack->topIndex = -1;	// -1은 빈 상태를 의미함
}

int IsEmpty(Stack* pstack)
{
	if (pstack->topIndex == -1)	// 스택이 비어있으면
		return TRUE;
	else
		return FALSE;
}

void Push(Stack* pstack, Data data)
{
	pstack->topIndex += 1;	// Top을 한 칸 올리고
	pstack->stackArr[pstack->topIndex] = data;	// 데이터 저장
}

Data Pop(Stack* pstack)
{
	int idx;

	if (IsEmpty(pstack))
	{
		printf("Stack Memry Error!\n");
		exit(-1);
	}

	idx = pstack->topIndex;	// 삭제할 데이터가 저장된 인덱스 값 저장
	pstack->topIndex -= 1;	// Top 아래로 한 칸 내림

	return pstack->stackArr[idx];	// 삭제되는 데이터 반환
}

Data Peek(Stack* pstack)
{
	if (IsEmpty(pstack))
	{
		printf("Stack Memory Error!\n");
		exit(-1);
	}

	return pstack->stackArr[pstack->topIndex];	// 맨 위에 저장된 데이터 반환
}