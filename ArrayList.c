#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define LIST_LEN 100

typedef int LData;
typedef struct __ArrayList
{
	LData arr[LIST_LEN];
	int numOfData;		// 저장된 데이터 수
	int curPosition;	// 데이터 참조위치 기록
} ArrayList;
typedef ArrayList List;

void ListInit(List* plist);				// 초기화
void LInsert(List* plist, LData data);	// 데이터 저장

int LFirst(List* plist, LData* pdata);	// 첫 데이터 참조
int LNext(List* plist, LData* pdata);	// 두 번째 데이터 이후 참조

LData LRemove(List* plist);				// 참조한 데이터 삭제
int LCount(List* plist);				// 저장된 데이터 수 반환

int main(void) 
{
	// ArrayList의 생성 및 초기화 
	List list;
	int data;
	LIstInit(&list);

	// 5개 데이터 저장
	LInsert(&list, 11);
	LInsert(&list, 11);
	LInsert(&list, 22);
	LInsert(&list, 22);
	LInsert(&list, 33);

	// 저장된 데이터 전체 출력
	printf("현재 데이터의 수: %d \n", LCount(&list));

	if (LFirst(&list, &data))	// 첫 번째 데이터 조회
	{
		printf("%d ", data);

		while (LNext(&list, &data))	// 두 번째 이후의 데이터 조회
			printf("%d ", data);
	}
	printf("\n\n");

	// 숫자 22를 탐색하여 모두 삭제
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

	// 삭제 후 남은 데이터 전체 출력
	printf("현재 데이터의 수: %d \n", LCount(&list));

	if (LFirst(&list, &data))
	{
		printf("%d ", data);

		while (LNext(&list, &data))
			printf("%d ", data);
	}
	printf("\n\n");
	return 0;
}

void ListInit(List* plist)
{
	(plist->numOfData) = 0;		// 리스트에 저장된 데이터 수는 0
	(plist->curPosition) = -1;	// 현재 아무 위치도 가리키지 않음
}

void LInsert(List* plist, LData data)
{
	if (plist->numOfData >= LIST_LEN)	// 더 이상 저장할 공간이 없다면
	{
		printf("저장이 불가능합니다.\n");
		return;
	}

	plist->arr[plist->numOfData] = data;	// 데이터 저장
	(plist->numOfData)++;	// 저장된 데이터 수 증가
}

int LFirst(List* plist, LData* pdata)
{
	if (plist->numOfData == 0)	// 저장된 데이터가 하나도 없다면
		return FALSE;

	(plist->curPosition) = 0;	// 첫 번째 데이터 참조
	*pdata = plist->arr[0];		// pdata가 가리키는 공간에 데이터 저장
	return TRUE;
}

int LNext(List* plist, LData* pdata)
{
	if (plist->curPosition >= (plist->numOfData) - 1)	// 더 이상 참조할 데이터가 없다면
		return FALSE;

	(plist->curPosition)++;
	*pdata = plist->arr[plist->curPosition];
	return TRUE;
}

LData LRemove(List* plist)
{
	int rpos = plist->curPosition;	// 삭제할 데이터의 인덱스 참조
	int num = plist->numOfData;
	int i;
	LData rdata = plist->arr[rpos];	// 삭제할 데이터 임시 저장

	// 삭제를 위한 데이터 이동을 진행하는 반복문
	for (i = rpos; i < num - 1; i++)
		plist->arr[i] = plist->arr[i + 1];

	(plist->numOfData)--;	// 데이터 수 감소
	(plist->curPosition)--;	// 참조위치를 하나 되돌림, 하나씩 앞 당겨졌기 때문
	return rdata;			// 삭제된 데이터 반환
}

int LCount(List* plist)
{
	return plist->numOfData;
}