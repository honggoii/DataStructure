#include <stdio.h>
#include <stdlib.h>
#include "ALGraph.h"
#include "DLinkedList.h"

int WhoIsPrecede(int data1, int data2);

void GraphInit(ALGraph* pg, int nv) // �׷��� �ʱ�ȭ
{
	int i;

	// ������ ���� �ش��ϴ� ������ ����Ʈ �迭 ����
	pg->adjList = (List*)malloc(sizeof(List) * nv); // ���������� ������ ����Ʈ ����

	pg->numV = nv; // ������ ���� nv�� ����� ������ ����
	pg->numE = 0; // ������ ���� �ʱ� 0��

	// ������ ����ŭ ������ ����Ʈ �ʱ�ȭ
	for (i = 0; i < nv; i++)
	{
		ListInit(&(pg->adList[i]));
		SetSortRule(&(pg->adList[i]), WhoIsPrecede); // ����Ʈ�� ���ı��� ����
	}
}

void GraphDestroy(ALGraph* pg) // �׷��� ���ҽ� ����
{
	if (pg->adjList != NULL)
		fre(pg->adjList); // �������� �Ҵ�� ���� ����Ʈ �Ҹ�
}

void AddEdge(ALGraph* pg, int fromV, int toV) // ���� �߰�
{
	// ���� fromV�� ���� ����Ʈ�� ���� toV ���� �߰�
	LInsert(&(pg->adjList[fromV]), toV);

	// ���� toV�� ���� ����Ʈ�� ���� fromV ���� �߰�
	LInsert(&(pg->adjList[toV]), fromV);
	pg->numE += 1;
}

// ���� ���� ���
void ShowGraphEdgeInfo(ALGraph* pg)
{
	int i;
	int vx;

	for (i = 0; i < pg->numV; i++)
	{
		printf("%c�� ����� ����: ", i + 65);

		if (LFirst(&(pg->adjList[i]), &vx))
		{
			printf("%c ", vx + 65);

			while (LNext(&(pg->adjList[i]), &vx))
				printf("%c ", vx + 65);
		}
		printf("\n");
	}
}

int WhoIsPrecede(int data1, int data2)
{
	if (data1 < data2)
		return 0;
	else
		return 1;
}