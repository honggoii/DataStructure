#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node* next;
	struct _node* prev;
} Node;

typedef struct _Deque
{
	Node* head;
	Node* tail;
} DLDeque;

typedef DLDeque Deque;

void DequeInit(Deque* pdeq);
int IsEmpty(Deque* pdeq);

void AddFirst(Deque* pdeq, Data data);
void AddLast(Deque* pdeq, Data data);

Data RemoveFirst(Deque* pdeq);
Data RemoveLast(Deque* pdeq);

Data GetFirst(Deque* pdeq);
Data GetLast(Deque* pdeq);

int main(void)
{
	// Deque ���� �� �ʱ�ȭ
	Deque deq;
	DequeInit(&deq);

	// ������ �ֱ�
	AddFirst(&deq, 3);
	AddFirst(&deq, 2);
	AddFirst(&deq, 1);

	AddLast(&deq, 4);
	AddLast(&deq, 5);
	AddLast(&deq, 6);

	// ������ �Ӹ����� ������
	while (!IsEmpty(&deq))
		printf("%d ", RemoveFirst(&deq));

	printf("\n");

	// ������ �ֱ�
	AddFirst(&deq, 3);
	AddFirst(&deq, 2);
	AddFirst(&deq, 1);

	AddLast(&deq, 4);
	AddLast(&deq, 5);
	AddLast(&deq, 6);

	// ������ �������� ������
	while (!IsEmpty(&deq))
		printf("%d ", RemoveLast(&deq));

	return 0;
}

void DequeInit(Deque* pdeq)
{
	pdeq->head = NULL;
	pdeq->tail = NULL;
}

int IsEmpty(Deque* pdeq)
{
	if (pdeq->head == NULL) // head�� NULL�̸� �������
		return TRUE;
	else
		return FALSE;
}

void AddFirst(Deque* pdeq, Data data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;		// �� ��忡 ������ �ֱ�

	newNode->next = pdeq->head;	// �� ��带 ���� head�� ���� 

	if (IsEmpty(pdeq))			// ù ����̸�
		pdeq->tail = newNode;	// ������ �� ��带 ����Ű�� ��
	else
		pdeq->head->prev = newNode;	// ����� ������ �� ��带 ����Ű�� ��

	newNode->prev = NULL;	// �� ����� ������ NULL�� 
	pdeq->head = newNode;	// head�� �� ��带 ����Ű�� ��
}

void AddLast(Deque* pdeq, Data data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;			// �� ��忡 ������ �ֱ�
	newNode->prev = pdeq->tail;		// ���� ������ �� ����� ���� ����

	if (IsEmpty(pdeq))				// ù ����̸�
		pdeq->head = newNode;		// head�� �� ��带 ����Ŵ
	else
		pdeq->tail->next = newNode;	// ������ ������ �� ��带 ����Ŵ

	newNode->next = NULL;	// �� ����� ������ NULL
	pdeq->tail = newNode;	// ������ �� ��带 ����Ŵ
}

Data RemoveFirst(Deque* pdeq)
{
	Node* rnode = pdeq->head;	// head �ּ� ����
	Data rdata;
	if (IsEmpty(pdeq))
	{
		printf("Deque Memory Error! \n");
		exit(-1);
	}
	rdata = pdeq->head->data;	// head�� �� ����

	pdeq->head = pdeq->head->next;	// head�� ������ ��带 ����Ŵ
	free(rnode);	// rnode ����

	if (pdeq->head == NULL)	// ���� ���������
		pdeq->tail = NULL;	// tail�� NULL�� ����Ŵ
	else
		pdeq->head->prev = NULL;	// head�� ������ NULL�� ����Ŵ

	return rdata;	// ������ �� ��ȯ
}

Data RemoveLast(Deque* pdeq)
{
	Node* rnode = pdeq->tail;	// tail �ּ� ����
	Data rdata;
	if (IsEmpty(pdeq))
	{
		printf("Deque Memory Error! \n");
		exit(-1);
	}
	rdata = pdeq->tail->data;	// tail�� �� ����

	pdeq->tail = pdeq->tail->prev;	// tail�� ������ ��带 ����Ŵ
	free(rnode);	// rnode ����

	if (pdeq->tail == NULL)	// ���� ���������
		pdeq->head = NULL;	// head�� NULL�� ����Ŵ
	else
		pdeq->tail->next = NULL;	// tail�� ������ NULL�� ����Ŵ

	return rdata;	// ������ �� ��ȯ
}

Data GetFirst(Deque* pdeq)
{
	if (IsEmpty(pdeq))
	{
		printf("Deque Memory Error! \n");
		exit(-1);
	}
	return pdeq->head->data;	// head�� �� ��ȯ
}

Data GetLast(Deque* pdeq)
{
	if (IsEmpty(pdeq))
	{
		printf("Deque Memory Error! \n");
		exit(-1);
	}
	return pdeq->tail->data;	// tail�� �� ��ȯ
}
