#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node* next;	// 오른쪽 노드를 가리키는 포인터 변수
	struct _node* prev;	// 왼쪽 노드를 가리키는 포인터 변수
} Node;

typedef struct _DBLinkedList
{
	Node* head;
	Node* cur;
	int numOfData;
} DBLinkedList;

typedef DBLinkedList List;

void ListInit(List* plist);
void LInsert(List* plist, Data data);

int LFirst(List* plist, Data* pdata);	// 첫 번째 노드 데이터 조회
int LNext(List* plist, Data* pdata);	// 두 번째 이후 노드 데이터 조회
int LPrevious(List* plist, Data* pdata);	// LNext 반대 방향으로 데이터 조회
int LCount(List* plist);

int main(void)
{
	// 양방향 연결 리스트 생성 및 초기화
	List list;
	int data;
	ListInit(&list);

	// 8개 데이터 저장
	LInsert(&list, 1);	LInsert(&list, 2);
	LInsert(&list, 3);	LInsert(&list, 4);
	LInsert(&list, 5);	LInsert(&list, 6);
	LInsert(&list, 7);	LInsert(&list, 8);

	// 저장된 데이터 조회
	if (LFirst(&list, &data))
	{
		printf("%d ", data);

		// 오른쪽 노드로 이동하며 데이터 조회
		while (LNext(&list, &data))
			printf("%d ", data);

		// 왼쪽 노드로 이동하며 데이터 조회
		while (LPrevious(&list, &data))
			printf("%d ", data);

		printf("\n\n");
	}

	return 0;
}

void ListInit(List* plist)
{
	plist->head = NULL;
	plist->numOfData = 0;
}

void LInsert(List* plist, Data data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	newNode->next = plist->head;	// 새 노드의 next를 NULL로 초기화
	if (plist->head != NULL)
		plist->head->prev = newNode;	// 두 번째 이후 노드 추가할 때만 실행

	newNode->prev = NULL;			// 새 노드의 prev를 NULL로 초기화
	plist->head = newNode;			// 포인터 변수 head가 새 노드를 가리키게 함

	(plist->numOfData)++;
}

int LFirst(List* plist, Data* pdata)
{
	if (plist->head == NULL)
		return FALSE;

	plist->cur = plist->head;	// cur이 첫 번째 노드를 가리키게 함
	*pdata = plist->cur->data;	// cur이 가리키는 노드의 데이터 반환
	return TRUE;
}

int LNext(List* plist, Data* pdata)
{
	if (plist->cur->next = NULL)
		return FALSE;

	plist->cur = plist->cur->next;	// cur을 오른쪽으로 이동
	*pdata = plist->cur->data;		// cur이 가리키는 노드의 데이터 반환
	return TRUE;
}

int LPrevious(List* plist, Data* pdata)
{
	if (plist->cur->prev == NULL)
		return FALSE;

	plist->cur = plist->cur->prev;	// cur을 왼쪽으로 이동
	*pdata = plist->cur->data;		// cur이 가리키는 노드의 데이터 반환
	return TRUE;
}

int LCount(List* plist)
{
	return plist->numOfData;
}