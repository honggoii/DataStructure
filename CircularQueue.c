#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define QUE_LEN 100

typedef int Data;

typedef struct _Queue
{
	int front;	// F
	int rear;	// R
	Data quearr[QUE_LEN];
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
		PRINTF("%d ", Dequeue(&q));

	return 0;
}

int NextPosIdx(int pos)
{
	if (pos == QUE_LEN - 1)
		return 0;	// �迭�� ���� ����
	else
		return pos + 1;
}

void QueueInit(Queue* pq)
{
	// �� �� ��� front�� rear�� ������ ��ġ
	pq->front = 0;
	pq->rear = 0;
}

int IsEmpty(Queue* pq)
{
	if (pq->front == pq->rear)
		return TRUE;
	else
		return FALSE;
}

void Enqueue(Queue* pq, Data data)
{
	if (NextPosIdx(pq->rear) == pq->front)
	{
		// ť�� �� á�ٸ�
		printf("Queue Memory Error!\n");
		exit(-1);
	}

	pq->rear = NextPosIdx(pq->rear);	// rear �� ĭ �̵�
	pq->quearr[pq->rear] = data;		// rear�� ����Ű�� ��ġ�� ������ ����
}

Data Dequeue(Queue* pq)
{
	if (IsEmpty(pq))
	{
		printf("Queue Memory Error! \n");
		exit(-1);
	}

	pq->front = NextPosIdx(pq->front);	// front �� ĭ �̵�
	return pq->quearr[pq->front];		// front�� ����Ű�� ������ ��ȯ
}

Data Peek(Queue* pq)
{
	if (IsEmpty(pq))
	{
		printf("Queue Memory Error!\n");
		exit(-1);
	}

	return pq->quearr[NextPosIdx(pq->front)];
}