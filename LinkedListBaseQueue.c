#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node* next;
} Node;

typedef struct _Queue
{
	Node* front;	// F
	Node* rear;		// R
} Queue;

typedef Queue Queue;

void QueueInit(Queue* pq);
int IsEmpty(Queue* pq);

void Enqueue(Queue* pq, Data data);
Data Dequeue(Queue* pq);
Data Peek(Queue* pq);

int main(void)
{
	// Queue ���� �� �ʱ�ȭ
	Queue q;
	QueueInit(&q);

	// ������ �ֱ�
	Enqueue(&q, 1);	Enqueue(&q, 2);
	Enqueue(&q, 3);	Enqueue(&q, 4);
	Enqueue(&q, 5);

	// ������ ������
	while (!IsEmpty(&q))
		printf("%d ", Dequeue(&q));

	return 0;
}

void QueueInit(Queue* pq)
{
	pq->front = NULL;	
	pq->rear = NULL;
}

int IsEmpty(Queue* pq)
{
	if (pq->front == NULL)	// F�� NULL�̸�
		return TRUE;		// �� �� ť
	else
		return FALSE;
}

void Enqueue(Queue* pq, Data data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->data = data;

	if (IsEmpty(pq))
	{
		// ù ��° ��� �߰�
		pq->front = newNode;	// front�� �� ��带 ����Ŵ
		pq->rear = newNode;		// rear�� �� ��带 ����Ŵ
	}
	else 
	{
		// �� ��° ���� ��� �߰�
		pq->rear->next = newNode;	// ������ ��尡 �� ��带 ����Ŵ
		pq->rear = newNode;		// rear�� �� ��带 ����Ŵ 
	}
}

Data Dequeue(Queue* pq)
{
	Node* delNode;
	Data rData;

	if (IsEmpty(pq))
	{
		printf("Queue Memory Error!\n");
		exit(-1);
	}

	delNode = pq->front;	// ������ ����� �ּ� ��
	rData = delNode->data;	// ������ ��忡 ����� ��
	pq->front = pq->front->next;	// front�� ������ ��� ���� ��带 ����Ŵ

	free(delNode);	// �Ҹ�
	return rData;
}

Data Peek(Queue* pq)
{
	if (IsEmpty(pq))
	{
		printf("Queue Memory Error!\n");
		exit(-1);
	}

	return pq->front->data;
}