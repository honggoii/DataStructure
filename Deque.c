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
	// Deque 생성 및 초기화
	Deque deq;
	DequeInit(&deq);

	// 데이터 넣기
	AddFirst(&deq, 3);
	AddFirst(&deq, 2);
	AddFirst(&deq, 1);

	AddLast(&deq, 4);
	AddLast(&deq, 5);
	AddLast(&deq, 6);

	// 데이터 머리에서 꺼내기
	while (!IsEmpty(&deq))
		printf("%d ", RemoveFirst(&deq));

	printf("\n");

	// 데이터 넣기
	AddFirst(&deq, 3);
	AddFirst(&deq, 2);
	AddFirst(&deq, 1);

	AddLast(&deq, 4);
	AddLast(&deq, 5);
	AddLast(&deq, 6);

	// 데이터 꼬리에서 꺼내기
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
	if (pdeq->head == NULL) // head가 NULL이면 비어있음
		return TRUE;
	else
		return FALSE;
}

void AddFirst(Deque* pdeq, Data data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;		// 새 노드에 데이터 넣기

	newNode->next = pdeq->head;	// 새 노드를 덱의 head와 연결 

	if (IsEmpty(pdeq))			// 첫 노드이면
		pdeq->tail = newNode;	// 꼬리가 새 노드를 가리키게 함
	else
		pdeq->head->prev = newNode;	// 헤드의 이전이 새 노드를 가리키게 함

	newNode->prev = NULL;	// 새 노드의 이전을 NULL로 
	pdeq->head = newNode;	// head가 새 노드를 가리키게 함
}

void AddLast(Deque* pdeq, Data data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;			// 새 노드에 데이터 넣기
	newNode->prev = pdeq->tail;		// 덱의 꼬리와 새 노드의 이전 연결

	if (IsEmpty(pdeq))				// 첫 노드이면
		pdeq->head = newNode;		// head가 새 노드를 가리킴
	else
		pdeq->tail->next = newNode;	// 꼬리의 다음이 새 노드를 가리킴

	newNode->next = NULL;	// 새 노드의 다음은 NULL
	pdeq->tail = newNode;	// 꼬리가 새 노드를 가리킴
}

Data RemoveFirst(Deque* pdeq)
{
	Node* rnode = pdeq->head;	// head 주소 저장
	Data rdata;
	if (IsEmpty(pdeq))
	{
		printf("Deque Memory Error! \n");
		exit(-1);
	}
	rdata = pdeq->head->data;	// head의 값 저장

	pdeq->head = pdeq->head->next;	// head는 다음의 노드를 가리킴
	free(rnode);	// rnode 삭제

	if (pdeq->head == NULL)	// 덱이 비어있으면
		pdeq->tail = NULL;	// tail이 NULL을 가리킴
	else
		pdeq->head->prev = NULL;	// head의 이전은 NULL을 가리킴

	return rdata;	// 삭제한 값 반환
}

Data RemoveLast(Deque* pdeq)
{
	Node* rnode = pdeq->tail;	// tail 주소 저장
	Data rdata;
	if (IsEmpty(pdeq))
	{
		printf("Deque Memory Error! \n");
		exit(-1);
	}
	rdata = pdeq->tail->data;	// tail의 값 저장

	pdeq->tail = pdeq->tail->prev;	// tail은 이전의 노드를 가리킴
	free(rnode);	// rnode 삭제

	if (pdeq->tail == NULL)	// 덱이 비어있으면
		pdeq->head = NULL;	// head가 NULL을 가리킴
	else
		pdeq->tail->next = NULL;	// tail의 다음은 NULL을 가리킴

	return rdata;	// 삭제한 값 반환
}

Data GetFirst(Deque* pdeq)
{
	if (IsEmpty(pdeq))
	{
		printf("Deque Memory Error! \n");
		exit(-1);
	}
	return pdeq->head->data;	// head의 값 반환
}

Data GetLast(Deque* pdeq)
{
	if (IsEmpty(pdeq))
	{
		printf("Deque Memory Error! \n");
		exit(-1);
	}
	return pdeq->tail->data;	// tail의 값 반환
}
