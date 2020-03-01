#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node* next;	// ������ ��带 ����Ű�� ������ ����
	struct _node* prev;	// ���� ��带 ����Ű�� ������ ����
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

int LFirst(List* plist, Data* pdata);	// ù ��° ��� ������ ��ȸ
int LNext(List* plist, Data* pdata);	// �� ��° ���� ��� ������ ��ȸ
int LPrevious(List* plist, Data* pdata);	// LNext �ݴ� �������� ������ ��ȸ
int LCount(List* plist);

int main(void)
{
	// ����� ���� ����Ʈ ���� �� �ʱ�ȭ
	List list;
	int data;
	ListInit(&list);

	// 8�� ������ ����
	LInsert(&list, 1);	LInsert(&list, 2);
	LInsert(&list, 3);	LInsert(&list, 4);
	LInsert(&list, 5);	LInsert(&list, 6);
	LInsert(&list, 7);	LInsert(&list, 8);

	// ����� ������ ��ȸ
	if (LFirst(&list, &data))
	{
		printf("%d ", data);

		// ������ ���� �̵��ϸ� ������ ��ȸ
		while (LNext(&list, &data))
			printf("%d ", data);

		// ���� ���� �̵��ϸ� ������ ��ȸ
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

	newNode->next = plist->head;	// �� ����� next�� NULL�� �ʱ�ȭ
	if (plist->head != NULL)
		plist->head->prev = newNode;	// �� ��° ���� ��� �߰��� ���� ����

	newNode->prev = NULL;			// �� ����� prev�� NULL�� �ʱ�ȭ
	plist->head = newNode;			// ������ ���� head�� �� ��带 ����Ű�� ��

	(plist->numOfData)++;
}

int LFirst(List* plist, Data* pdata)
{
	if (plist->head == NULL)
		return FALSE;

	plist->cur = plist->head;	// cur�� ù ��° ��带 ����Ű�� ��
	*pdata = plist->cur->data;	// cur�� ����Ű�� ����� ������ ��ȯ
	return TRUE;
}

int LNext(List* plist, Data* pdata)
{
	if (plist->cur->next = NULL)
		return FALSE;

	plist->cur = plist->cur->next;	// cur�� ���������� �̵�
	*pdata = plist->cur->data;		// cur�� ����Ű�� ����� ������ ��ȯ
	return TRUE;
}

int LPrevious(List* plist, Data* pdata)
{
	if (plist->cur->prev == NULL)
		return FALSE;

	plist->cur = plist->cur->prev;	// cur�� �������� �̵�
	*pdata = plist->cur->data;		// cur�� ����Ű�� ����� ������ ��ȯ
	return TRUE;
}

int LCount(List* plist)
{
	return plist->numOfData;
}