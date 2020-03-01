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

typedef struct _CLL
{
	Node* tail;
	Node* cur;
	Node* before;
	int numOfData;
} CList;

typedef CList List;

void ListInit(List* plist);	
void LInsert(List* plist, Data data);	// 꼬리에 노드 추가
void LInsertFront(List* plist, Data data);	// 머리에 노드 추가

int LFirst(List* plist, Data* pdata);
int LNext(List* plist, Data* pdata);
Data LRemove(List* plist);
int LCount(List* plist);

int main(void)
{
	// 원형 연결 리스트 생성 및 초기화
	List list;
	int data, i, nodeNum;
	ListInit(&list);

	// 리스트에 5개의 데이터 저장
	LInsert(&list, 3);
	LInsert(&list, 4);
	LInsert(&list, 5);
	LInsertFront(&list, 2);
	LInsertFront(&list, 1);

	// 리스트에 저장된 데이터를 연속 3회 출력
	if (LFirst(&list, &data))
	{
		printf("%d ", data);

		for (i = 0; i < LCount(&list) * 3 - 1; i++)
		{
			if (LNext(&list, &data))
				printf("%d ", data);
		}
	}
	printf("\n");

	// 2의 배수 삭제
	nodeNum = LCount(&list);

	if (nodeNum != 0)
	{
		LFirst(&list, &data);
		if (data % 2 == 0)
			LRemove(&list);

		for (i = 0; i < nodeNum - 1; i++)
		{
			LNext(&list, &data);
			if (data % 2 == 0)
				LRemove(&list);
		}
	}

	// 전체 데이터 1회 출력
	if (LFirst(&list, &data))
	{
		printf("%d ", data);

		for (i = 0; i < LCount(&list) - 1; i++)
		{
			if (LNext(&list, &data))
				printf("%d ", data);
		}
	}
	
	return 0;
}

void ListInit(List* plist)
{
	plist->tail = NULL;
	plist->cur = NULL;
	plist->before = NULL;
	plist->numOfData = 0;
}

void LInsert(List* plist, Data data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));	// 새 노드 생성
	newNode->data = data;			// 새 노드에 데이터 저장

	if (plist->tail == NULL)		// 첫 번째 노드라면
	{
		plist->tail = newNode;		// tail이 새 노드를 가리키게 함
		newNode->next = newNode;	// 새 노드인 자신을 가리키게 함
	}
	else
	{
		newNode->next = plist->tail->next;	// 새 노드가 머리에 연결
		plist->tail->next = newNode;		// 꼬리와 새 노드 연결
		plist->tail = newNode;
	}

	(plist->numOfData)++;
}

void LInsertFront(List* plist, Data data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));	// 새 노드 생성
	newNode->data = data;			// 새 노드에 데이터 저장

	if (plist->tail == NULL)		// 첫 번째 노드라면
	{
		plist->tail = newNode;		// tail이 새 노드를 가리키게 함
		newNode->next = newNode;	// 새 노드인 자신을 가리키게 함
	}
	else
	{
		newNode->next = plist->tail->next;	// 새 노드가 머리에 연결
		plist->tail->next = newNode;		// 꼬리와 새 노드 연결
	}

	(plist->numOfData)++;
}


int LFirst(List* plist, Data* pdata)
{
	if (plist->tail == NULL)	// 저장된 노드가 없다면
		return FALSE;

	plist->before = plist->tail;	// before가 꼬리를 가리키게 함
	plist->cur = plist->tail->next;	// cur이 머리를 가리키게 함

	*pdata = plist->cur->data;		// cur이 가리키는 노드의 데이터 반환
	return TRUE;
}

int LNext(List* plist, Data* pdata)
{
	if (plist->tail == NULL)	// 저장된 노드가 없다면
		return FALSE;	

	plist->before = plist->cur;		// before 한 칸 이동
	plist->cur = plist->cur->next;	// cur 한 칸 이동

	*pdata = plist->cur->data;		// cur이 가라키는 노드의 데이터 반환
	return TRUE;
}

Data LRemove(List* plist)
{
	Node* rpos = plist->cur;
	Data rdata = rpos->data;

	if (rpos == plist->tail)	// 삭제 대상이 tail이 가리키는 것이라면
	{
		if (plist->tail == plist->tail->next)	// 유일한 노드라면
			plist->tail = NULL;
		else
			plist->tail = plist->before;
	}

	plist->before->next = plist->cur->next;
	plist->cur = plist->before;

	free(rpos);
	(plist->numOfData)--;
	return rdata;
}

int LCount(List* plist)
{
	return plist->numOfData;
}