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
	// Queue 생성 및 초기화
	Queue q;
	QueueInit(&q);

	// 데이터 넣기
	Enqueue(&q, 1);	Enqueue(&q, 2);
	Enqueue(&q, 3);	Enqueue(&q, 4);
	Enqueue(&q, 5);

	// 데이터 꺼내기
	while (!IsEmpty(&q))
		PRINTF("%d ", Dequeue(&q));

	return 0;
}

int NextPosIdx(int pos)
{
	if (pos == QUE_LEN - 1)
		return 0;	// 배열의 끝에 도달
	else
		return pos + 1;
}

void QueueInit(Queue* pq)
{
	// 텅 빈 경우 front와 rear는 동일한 위치
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
		// 큐가 꽉 찼다면
		printf("Queue Memory Error!\n");
		exit(-1);
	}

	pq->rear = NextPosIdx(pq->rear);	// rear 한 칸 이동
	pq->quearr[pq->rear] = data;		// rear이 가리키는 위치에 데이터 저장
}

Data Dequeue(Queue* pq)
{
	if (IsEmpty(pq))
	{
		printf("Queue Memory Error! \n");
		exit(-1);
	}

	pq->front = NextPosIdx(pq->front);	// front 한 칸 이동
	return pq->quearr[pq->front];		// front가 가리키는 데이터 반환
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