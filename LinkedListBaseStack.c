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

void StackInit(Stack* pstack);	// ���� �ʱ�ȭ
int IsEmpty(Stack* pstack);		// ������ ������� Ȯ��

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
	pstack->head = NULL;	// head�� NULL�� �ʱ�ȭ
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
	Node* newNode = (Node*)malloc(sizeof(Node));	// �� ��� ����

	newNode->data = data;			// �� ��忡 ������ ����
	newNode->next = pstack->head;	// �� ��尡 �ֱٿ� �߰��� ��带 ����Ŵ

	pstack->head = newNode;			// ������ ���� head�� �� ��带 ����Ŵ
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

	rdata = pstack->head->data;	// ������ ����� �����͸� ����
	rnode = pstack->head;		// ������ ����� �ּ� �� ����

	pstack->head = pstack->head->next;	// ������ ����� ���� ��带 head�� ����Ŵ
	free(rnode);	// ��� ����
	return rdata;	// ������ ��� ������ ��ȯ
}

Data Peek(Stack* pstack)
{
	if (IsEmpty(pstack))
	{
		printf("Stack Memory Error!\n");
		exit(-1);
	}

	return pstack->head->data;	// head�� ����Ű�� ��忡 ����� ������ ��ȯ
}