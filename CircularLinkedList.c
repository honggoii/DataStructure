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
void LInsert(List* plist, Data data);	// ������ ��� �߰�
void LInsertFront(List* plist, Data data);	// �Ӹ��� ��� �߰�

int LFirst(List* plist, Data* pdata);
int LNext(List* plist, Data* pdata);
Data LRemove(List* plist);
int LCount(List* plist);

int main(void)
{
	// ���� ���� ����Ʈ ���� �� �ʱ�ȭ
	List list;
	int data, i, nodeNum;
	ListInit(&list);

	// ����Ʈ�� 5���� ������ ����
	LInsert(&list, 3);
	LInsert(&list, 4);
	LInsert(&list, 5);
	LInsertFront(&list, 2);
	LInsertFront(&list, 1);

	// ����Ʈ�� ����� �����͸� ���� 3ȸ ���
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

	// 2�� ��� ����
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

	// ��ü ������ 1ȸ ���
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
	Node* newNode = (Node*)malloc(sizeof(Node));	// �� ��� ����
	newNode->data = data;			// �� ��忡 ������ ����

	if (plist->tail == NULL)		// ù ��° �����
	{
		plist->tail = newNode;		// tail�� �� ��带 ����Ű�� ��
		newNode->next = newNode;	// �� ����� �ڽ��� ����Ű�� ��
	}
	else
	{
		newNode->next = plist->tail->next;	// �� ��尡 �Ӹ��� ����
		plist->tail->next = newNode;		// ������ �� ��� ����
		plist->tail = newNode;
	}

	(plist->numOfData)++;
}

void LInsertFront(List* plist, Data data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));	// �� ��� ����
	newNode->data = data;			// �� ��忡 ������ ����

	if (plist->tail == NULL)		// ù ��° �����
	{
		plist->tail = newNode;		// tail�� �� ��带 ����Ű�� ��
		newNode->next = newNode;	// �� ����� �ڽ��� ����Ű�� ��
	}
	else
	{
		newNode->next = plist->tail->next;	// �� ��尡 �Ӹ��� ����
		plist->tail->next = newNode;		// ������ �� ��� ����
	}

	(plist->numOfData)++;
}


int LFirst(List* plist, Data* pdata)
{
	if (plist->tail == NULL)	// ����� ��尡 ���ٸ�
		return FALSE;

	plist->before = plist->tail;	// before�� ������ ����Ű�� ��
	plist->cur = plist->tail->next;	// cur�� �Ӹ��� ����Ű�� ��

	*pdata = plist->cur->data;		// cur�� ����Ű�� ����� ������ ��ȯ
	return TRUE;
}

int LNext(List* plist, Data* pdata)
{
	if (plist->tail == NULL)	// ����� ��尡 ���ٸ�
		return FALSE;	

	plist->before = plist->cur;		// before �� ĭ �̵�
	plist->cur = plist->cur->next;	// cur �� ĭ �̵�

	*pdata = plist->cur->data;		// cur�� ����Ű�� ����� ������ ��ȯ
	return TRUE;
}

Data LRemove(List* plist)
{
	Node* rpos = plist->cur;
	Data rdata = rpos->data;

	if (rpos == plist->tail)	// ���� ����� tail�� ����Ű�� ���̶��
	{
		if (plist->tail == plist->tail->next)	// ������ �����
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