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
	// Queue 생성 및 초기화
	Queue q;
	QueueInit(&q);

	// 데이터 넣기
	Enqueue(&q, 1);	Enqueue(&q, 2);
	Enqueue(&q, 3);	Enqueue(&q, 4);
	Enqueue(&q, 5);

	// 데이터 꺼내기
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
	if (pq->front == NULL)	// F가 NULL이면
		return TRUE;		// 텅 빈 큐
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
		// 첫 번째 노드 추가
		pq->front = newNode;	// front가 새 노드를 가리킴
		pq->rear = newNode;		// rear가 새 노드를 가리킴
	}
	else 
	{
		// 두 번째 이후 노드 추가
		pq->rear->next = newNode;	// 마지막 노드가 새 노드를 가리킴
		pq->rear = newNode;		// rear가 새 노드를 가리킴 
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

	delNode = pq->front;	// 삭제할 노드의 주소 값
	rData = delNode->data;	// 삭제할 노드에 저장된 값
	pq->front = pq->front->next;	// front가 삭제할 노드 다음 노드를 가리킴

	free(delNode);	// 소멸
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