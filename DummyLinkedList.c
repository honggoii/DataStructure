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
	Node* head;	// ���� ��带 ����Ű�� ���
	Node* cur;	// ��ȸ �� ������ ���� ���
	Node* before;	// ������ ���� ���
	int numOfData;	// ����� ������ �� ���
	int (*comp)(LData d1, LData d2);	// ������ ������ ����ϱ� ���� ���
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
		return 0;	// d1�� ���� ������ ��
	else
		return 1;	// d2�� ���� ������ ��
}

int main(void)
{
	// ����Ʈ ���� �� �ʱ�ȭ
	List list;
	int data;
	ListInit(&list);

	// 5���� ������ ����
	LInsert(&list, 11);
	LInsert(&list, 11);
	LInsert(&list, 22);
	LInsert(&list, 22);
	LInsert(&list, 33);

	// ����� ������ ���
	printf("���� �������� �� : %d \n", LCount(&list));

	if (LFirst(&list, &data))
	{
		print("%d ", data);

		while (LNext(&list, &data))
			printf("%d ", data);
	}
	printf("\n\n");

	// ���� 22�� �˻��Ͽ� ��� ����
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

	// ���� �� ���� ������ ���
	printf("���� �������� �� : %d \n", LCount(&list));

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
	Node* newNode = (Node*)malloc(sizeof(Node));	// �� ��� ����
	newNode->data = data;	// �� ��忡 ������ ����
		
	newNode->next = plist->head->next;	// �� ��尡 �ٸ� ��带 ����Ű�� ��
	plist->head->next = newNode;		// ���� ��尡 �� ��带 ����Ű�� ��

	(plist->numOfData)++;	// ����� ��� �� ����
}

void SInsert(List* plist, LData data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));	// �� ��� ����
	Node* pred = plist->head;	// pred�� ���� ��带 ����Ŵ
	newNode->data = data;	// �� ��忡 ������ ����

	// �� ��尡 �� ��ġ�� ã�� ���� �ݺ���
	while (pred->next != NULL && plist->comp(data, pred->next->data) != 0)
	{
		pred = pred->next;	// ���� ���� �̵�
	}

	newNode->next = pred->next;	// �� ����� ������ ����
	pred->next = newNode;	// �� ����� ���� ����

	(plist->numOfData)++;	// ����� ������ �� ����
}

void LInsert(List* plist, LData data)
{
	if (plist->comp == NULL)	// ���� ������ ���õ��� �ʾ�����
		FInsert(plist, data);	// �Ӹ��� ��� �߰�
	else
		SInsert(plist, data);	// ���� �������� ��� �߰�
}

int LFirst(List* plist, LData* pdata)
{
	if (plist->head->next == NULL)	// ���� ��尡 NULL�� ����Ű��
		return FALSE;	// ��ȯ�� �����Ͱ� ����
	
	plist->before = plist->head;	// before�� ���� ��带 ����Ű�� ��
	plist->cur = plist->head->next;	// cur�� ù ��° ��带 ����Ű�� ��

	*pdata = plist->cur->data;	// ù ��° ����� ������ ����
	return TRUE;				// ������ ��ȯ ����
}

int LNext(List* plist, LData* pdata)
{
	if (plist->cur->next == NULL)	// cur�� NULL�� ����Ű��
		return FALSE;	// ��ȯ�� �����Ͱ� ����

	plist->before = plist->cur;		// cur�� ����Ű�� ���� before�� ����Ŵ
	plist->cur = plist->cur->next;	// cur�� �� ���� ��带 ����Ŵ

	*pdata = plist->cur->data;	// cur�� ����Ű�� ����� ������ ����
	return TRUE;	// ������ ��ȯ ����
}

LData LRemove(List* plist)
{
	Node* rpos = plist->cur;	// �Ҹ� ����� �ּ� ���� rpos�� ����
	LData rdata = rpos->data;	// �Ҹ� ����� �����͸� rdata�� ����

	plist->before->next = plist->cur->next;	// �Ҹ� ����� ����Ʈ���� ����
	plist->cur = plist->before;				// cur�� ����Ű�� ��ġ ������

	free(rpos);				// ���ŵ� ��� �Ҹ�
	(plist->numOfData)--;	// ����� ������ �� ����
	return rdata;			// ���ŵ� ��� ��ȯ
}

int LCount(List* plist)
{
	return plist->numOfData;
}

void SetSortRule(List* plist, int (*comp)(LData d1, LData d2))
{
	plist->comp = comp;
}