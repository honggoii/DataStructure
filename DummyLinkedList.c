#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int LData;
typedef struct _node
{
	LData data;
	struct _node* next;
} Node;
typedef struct _linkedList
{
	Node* head;	// 더미 노드를 가리키는 멤버
	Node* cur;	// 조회 및 삭제를 돕는 멤버
	Node* before;	// 삭제를 돕는 멤버
	int numOfData;	// 저장된 데이터 수 기록
	int (*comp)(LData d1, LData d2);	// 정렬의 기준을 등록하기 위한 멤버
} LinkedList;
typedef LinkedList List;

void ListInit(List* plist);
void LInsert(List* plist, LData data);

int LFirst(List* plist, LData* pdata);
int LNext(List* plist, LData* pdata);

LData LRemove(List* plist);
int LCount(List* plist);

void SetSortRule(List* plist, int (*comp)(LData d1, LData d2));

int WhoIsPrecede(int d1, int d2)
{
	if (d1 < d2)
		return 0;	// d1이 정렬 순서상 앞
	else
		return 1;	// d2가 정렬 순서상 앞
}

int main(void)
{
	// 리스트 생성 및 초기화
	List list;
	int data;
	ListInit(&list);

	// 5개의 데이터 저장
	LInsert(&list, 11);
	LInsert(&list, 11);
	LInsert(&list, 22);
	LInsert(&list, 22);
	LInsert(&list, 33);

	// 저장된 데이터 출력
	printf("현재 데이터의 수 : %d \n", LCount(&list));

	if (LFirst(&list, &data))
	{
		print("%d ", data);

		while (LNext(&list, &data))
			printf("%d ", data);
	}
	printf("\n\n");

	// 숫자 22을 검색하여 모두 삭제
	if (LFirst(&list, &data))
	{
		if (data == 22)
			LRemove(&list);

		while (LNext(&list, &data))
		{
			if (data == 22)
				LRemove(&list);
		}
	}

	// 삭제 후 남은 데이터 출력
	printf("현재 데이터의 수 : %d \n", LCount(&list));

	if (LFirst(&list, &data))
	{
		pirntf("%d ", data);

		while (LNext(&list, &data))
			printf("%d ", data);
	}
	printf("\n\n");
	return 0;
}

void ListInit(List* plist)
{
	plist->head = (Node*)malloc(sizeof(Node));
	plist->head->next = NULL;
	plist->comp = NULL;
	plist->numOfData = 0;
}

void FInsert(List* plist, LData data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));	// 새 노드 생성
	newNode->data = data;	// 새 노드에 데이터 저장
		
	newNode->next = plist->head->next;	// 새 노드가 다른 노드를 가리키게 함
	plist->head->next = newNode;		// 더미 노드가 새 노드를 가리키게 함

	(plist->numOfData)++;	// 저장된 노드 수 증가
}

void SInsert(List* plist, LData data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));	// 새 노드 생성
	Node* pred = plist->head;	// pred는 더미 노드를 가리킴
	newNode->data = data;	// 새 노드에 데이터 저장

	// 새 노드가 들어갈 위치를 찾기 위한 반복문
	while (pred->next != NULL && plist->comp(data, pred->next->data) != 0)
	{
		pred = pred->next;	// 다음 노드로 이동
	}

	newNode->next = pred->next;	// 새 노드의 오른쪽 연결
	pred->next = newNode;	// 새 노드의 왼쪽 연결

	(plist->numOfData)++;	// 저장된 데이터 수 증가
}

void LInsert(List* plist, LData data)
{
	if (plist->comp == NULL)	// 정렬 기준이 마련되지 않았으면
		FInsert(plist, data);	// 머리에 노드 추가
	else
		SInsert(plist, data);	// 정렬 기준으로 노드 추가
}

int LFirst(List* plist, LData* pdata)
{
	if (plist->head->next == NULL)	// 더미 노드가 NULL을 가리키면
		return FALSE;	// 반환할 데이터가 없다
	
	plist->before = plist->head;	// before는 더미 노드를 가리키게 함
	plist->cur = plist->head->next;	// cur은 첫 번째 노드를 가리키게 함

	*pdata = plist->cur->data;	// 첫 번째 노드의 데이터 전달
	return TRUE;				// 데이터 반환 성공
}

int LNext(List* plist, LData* pdata)
{
	if (plist->cur->next == NULL)	// cur이 NULL을 가리키면
		return FALSE;	// 반환할 데이터가 없다

	plist->before = plist->cur;		// cur이 가리키던 것을 before가 가리킴
	plist->cur = plist->cur->next;	// cur은 그 다음 노드를 가리킴

	*pdata = plist->cur->data;	// cur이 가리키는 노드의 데이터 전달
	return TRUE;	// 데이터 반환 성공
}

LData LRemove(List* plist)
{
	Node* rpos = plist->cur;	// 소멸 대상의 주소 값을 rpos에 저장
	LData rdata = rpos->data;	// 소멸 대상의 데이터를 rdata에 저장

	plist->before->next = plist->cur->next;	// 소멸 대상을 리스트에서 제거
	plist->cur = plist->before;				// cur이 가리키는 위치 재조정

	free(rpos);				// 제거된 노드 소멸
	(plist->numOfData)--;	// 저장된 데이터 수 감소
	return rdata;			// 제거된 노드 반환
}

int LCount(List* plist)
{
	return plist->numOfData;
}

void SetSortRule(List* plist, int (*comp)(LData d1, LData d2))
{
	plist->comp = comp;
}