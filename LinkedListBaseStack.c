#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node* next;
} Node;

typedef struct _listStack
{
	Node* head;
} ListStack;

typedef ListStack Stack;

void StackInit(Stack* pstack);	// 스택 초기화
int IsEmpty(Stack* pstack);		// 스택이 비었는지 확인

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
	pstack->head = NULL;	// head를 NULL로 초기화
}

int IsEmpty(Stack* pstack)
{
	if (pstack->head == NULL)
		return TRUE;
	else
		return FALSE;
}

void Push(Stack* pstack, Data data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));	// 새 노드 생성

	newNode->data = data;			// 새 노드에 데이터 저장
	newNode->next = pstack->head;	// 새 노드가 최근에 추가된 노드를 가리킴

	pstack->head = newNode;			// 포인터 변수 head가 새 노드를 가리킴
}

Data Pop(Stack* pstack)
{
	Data rdata;
	Node* rnode;

	if (IsEmpty(pstack))
	{
		printf("Stack Memory Error!\n");
		exit(-1);
	}

	rdata = pstack->head->data;	// 삭제할 노드의 데이터를 저장
	rnode = pstack->head;		// 삭제할 노드의 주소 값 저장

	pstack->head = pstack->head->next;	// 삭제할 노드의 다음 노드를 head가 가리킴
	free(rnode);	// 노드 삭제
	return rdata;	// 삭제된 노드 데이터 반환
}

Data Peek(Stack* pstack)
{
	if (IsEmpty(pstack))
	{
		printf("Stack Memory Error!\n");
		exit(-1);
	}

	return pstack->head->data;	// head가 가리키는 노드에 저장된 데이터 반환
}