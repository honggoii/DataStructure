#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	int data;
	struct _node* next;
} Node;

int main(void)
{
	Node* head = NULL;	// ����Ʈ�� �Ӹ��� ����Ű�� ������ ����
	Node* tail = NULL;	// ����Ʈ�� ������ ����Ű�� ������ ����
	Node* cur = NULL;	// ����Ʈ ���θ� ���ƴٴϴ� ������ ����

	Node* newNode = NULL;
	int readData;

	// ������ �Է�
	while (1)
	{
		printf("�ڿ��� �Է�: ");
		scanf("%d", &readData);
		if (readData < 1)
			break;

		// ��� �߰�����
		newNode = (Node*)malloc(sizeof(Node));	// ��� ����
		newNode->data = readData;				// ��忡 ������ ����
		newNode->next = NULL;					// ����� next�� NULL�� �ʱ�ȭ

		if (head = NULL)	// ù ��° �����
			head = newNode;	// ù ��° ��尡 head�� ����Ű�� ��
		else
			tail->next = newNode;

		tail = newNode;		// ����� ���� tail�� ����Ű�� ��
	}
	printf("\n");

	// ������ ���
	printf("�Է� ���� ������ ��ü���! \n");
	if (head == NULL)
	{
		printf("����� �ڿ����� �������� �ʽ��ϴ�.\n");
	}
	else
	{
		cur = head;	// cur�� ����Ʈ�� ù ��° ��带 �⸮Ŵ
		printf("%d ", cur->data);	// ù ��° ������ ���

		while (cur->next != NULL)	// ����� ��尡 �����ϸ�
		{
			cur = cur->next;		// cur�� ���� ��带 ����Ű�� ��
			printf("%d ", cur->data);	// cur�� ����Ű�� ��� ���
		}
	}
	printf("\n\n");

	// ������ ����
	if (head == NULL)
	{
		return 0;	// ������ ��尡 ����
	}
	else
	{
		Node* delNode = head;
		Node* delNextNode = head->next;

		printf("%d��(��) �����մϴ�.\n", head->data);
		free(delNode);	// ù ��° ��� ����

		while (delNextNode != NULL)	// �� ��° ��� ���� ����
		{
			delNode = delNextNode;
			delNextNode = delNextNode->next;

			printf("%d��(��) �����մϴ�.\n", delNode->data);
			free(delNode);
		}
	}

	return 0;
}