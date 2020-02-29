#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define LIST_LEN 100

typedef int LData;
typedef struct __ArrayList
{
	LData arr[LIST_LEN];
	int numOfData;		// ����� ������ ��
	int curPosition;	// ������ ������ġ ���
} ArrayList;
typedef ArrayList List;

void ListInit(List* plist);				// �ʱ�ȭ
void LInsert(List* plist, LData data);	// ������ ����

int LFirst(List* plist, LData* pdata);	// ù ������ ����
int LNext(List* plist, LData* pdata);	// �� ��° ������ ���� ����

LData LRemove(List* plist);				// ������ ������ ����
int LCount(List* plist);				// ����� ������ �� ��ȯ

int main(void) 
{
	// ArrayList�� ���� �� �ʱ�ȭ 
	List list;
	int data;
	LIstInit(&list);

	// 5�� ������ ����
	LInsert(&list, 11);
	LInsert(&list, 11);
	LInsert(&list, 22);
	LInsert(&list, 22);
	LInsert(&list, 33);

	// ����� ������ ��ü ���
	printf("���� �������� ��: %d \n", LCount(&list));

	if (LFirst(&list, &data))	// ù ��° ������ ��ȸ
	{
		printf("%d ", data);

		while (LNext(&list, &data))	// �� ��° ������ ������ ��ȸ
			printf("%d ", data);
	}
	printf("\n\n");

	// ���� 22�� Ž���Ͽ� ��� ����
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

	// ���� �� ���� ������ ��ü ���
	printf("���� �������� ��: %d \n", LCount(&list));

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
	(plist->numOfData) = 0;		// ����Ʈ�� ����� ������ ���� 0
	(plist->curPosition) = -1;	// ���� �ƹ� ��ġ�� ����Ű�� ����
}

void LInsert(List* plist, LData data)
{
	if (plist->numOfData >= LIST_LEN)	// �� �̻� ������ ������ ���ٸ�
	{
		printf("������ �Ұ����մϴ�.\n");
		return;
	}

	plist->arr[plist->numOfData] = data;	// ������ ����
	(plist->numOfData)++;	// ����� ������ �� ����
}

int LFirst(List* plist, LData* pdata)
{
	if (plist->numOfData == 0)	// ����� �����Ͱ� �ϳ��� ���ٸ�
		return FALSE;
	
	(plist->curPosition) = 0;	// ù ��° ������ ����
	*pdata = plist->arr[0];		// pdata�� ����Ű�� ������ ������ ����
	return TRUE;
}

int LNext(List* plist, LData* pdata)
{
	if (plist->curPosition >= (plist->numOfData) - 1)	// �� �̻� ������ �����Ͱ� ���ٸ�
		return FALSE;

	(plist->curPosition)++;
	*pdata = plist->arr[plist->curPosition];
	return TRUE;
}

LData LRemove(List* plist)
{
	int rpos = plist->curPosition;	// ������ �������� �ε��� ����
	int num = plist->numOfData;
	int i;
	LData rdata = plist->arr[rpos];	// ������ ������ �ӽ� ����

	// ������ ���� ������ �̵��� �����ϴ� �ݺ���
	for (i = rpos; i < num - 1; i++)
		plist->arr[i] = plist->arr[i + 1];

	(plist->numOfData)--;	// ������ �� ����
	(plist->curPosition)--;	// ������ġ�� �ϳ� �ǵ���, �ϳ��� �� ������� ����
	return rdata;			// ������ ������ ��ȯ
}

int LCount(List* plist);				// ����� ������ �� ��ȯ