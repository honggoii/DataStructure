#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ALGraphBFS.h"
#include "DLinkedList.h"
#include "CircularQueue.h"

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

	pg->visitInfo = (int*)malloc(sizeof(int) * pg->numV);
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
}

void GraphDestroy(ALGraph* pg) // �׷��� ���ҽ� ����
{
	if (pg->adjList != NULL)
		fre(pg->adjList); // �������� �Ҵ�� ���� ����Ʈ �Ҹ�

	if (pg->visitInfo != NULL)
		free(pg->visitInfo);
}

void AddEdge(ALGraph* pg, int fromV, int toV) // ���� �߰�
{
	// ���� fromV�� ���� ����Ʈ�� ���� toV ���� �߰�
	LInsert(&(pg->adjList[fromV]), toV);

	// ���� toV�� ���� ����Ʈ�� ���� fromV ���� �߰�
	LInsert(&(pg->adjList[toV]), fromV);
	pg->numE += 1;
}

void ShowGraphEdgeInfo(ALGraph* pg) // ���� ���� ���
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

int VisitVertex(ALGraph* pg, int visitV) // �� ��° �Ű������� ���޵� �̸��� ������ �湮
{
	if (pg->visitInfo[visitV] == 0) // visitV�� ó�� �湮
	{
		pg->visitInfo[visitV] = 1; // visitV�� �湮 ���
		printf("%c ", visitV + 65); // �湮 ���� �̸� ���
		return TRUE; // �湮 ����
	}
	return FALSE; // �湮 ����
}

void BFShowGraphVertex(ALGraph* pg, int startV) // BFS(Breadth First Search ���) ���� ���� ���
{
	Queue queue;
	int visitV = startV;
	int nextV;

	QueueInit(&queue); // BFS�� ���� ť �ʱ�ȭ
	VisitVertex(pg, visitV); // ���� ���� �湮

	// visitV�� ��� ������ ����� ������ �湮 �õ�
	while (LFirst(&(pg->adjList[visitV]), &nextV) == TRUE)
	{
		if (VisitVertex(pg, nextV) == TRUE) // �湮 ����
			Enqueue(&queue, nextV); // ť�� ����

		while (LNext(&(pg->adjList[visitV]), &nextV) == TRUE)
		{
			if (VisitVertex(pg, nextV) == TRUE)
				Enqueue(&queue, nextV); // ť�� ����
		}
		
		// ť�� ��� BFS ����
		if (QIsEmpty(&queue) == TRUE)
			break;
		else
			visitV = Dequeue(&queue); // ť���� �ϳ� ���� while�� �ٽ� ����
	}

	// ���� Ž���� ���� Ž�� ���� �ʱ�ȭ
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
}