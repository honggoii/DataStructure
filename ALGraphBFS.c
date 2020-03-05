#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ALGraphBFS.h"
#include "DLinkedList.h"
#include "CircularQueue.h"

int WhoIsPrecede(int data1, int data2);

void GraphInit(ALGraph* pg, int nv) // 그래프 초기화
{
	int i;

	// 정점의 수에 해당하는 길이의 리스트 배열 생성
	pg->adjList = (List*)malloc(sizeof(List) * nv); // 간선정보를 저장할 리스트 생성

	pg->numV = nv; // 정점의 수는 nv에 저장된 값으로 결정
	pg->numE = 0; // 간선의 수는 초기 0개

	// 정점의 수만큼 생성된 리스트 초기화
	for (i = 0; i < nv; i++)
	{
		ListInit(&(pg->adList[i]));
		SetSortRule(&(pg->adList[i]), WhoIsPrecede); // 리스트의 정렬기준 설정
	}

	pg->visitInfo = (int*)malloc(sizeof(int) * pg->numV);
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
}

void GraphDestroy(ALGraph* pg) // 그래프 리소스 해제
{
	if (pg->adjList != NULL)
		fre(pg->adjList); // 동적으로 할당된 연결 리스트 소멸

	if (pg->visitInfo != NULL)
		free(pg->visitInfo);
}

void AddEdge(ALGraph* pg, int fromV, int toV) // 간선 추가
{
	// 정점 fromV의 연결 리스트에 정점 toV 정보 추가
	LInsert(&(pg->adjList[fromV]), toV);

	// 정점 toV의 연결 리스트에 정점 fromV 정보 추가
	LInsert(&(pg->adjList[toV]), fromV);
	pg->numE += 1;
}

void ShowGraphEdgeInfo(ALGraph* pg) // 간선 정보 출력
{
	int i;
	int vx;

	for (i = 0; i < pg->numV; i++)
	{
		printf("%c와 연결된 정점: ", i + 65);

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

int VisitVertex(ALGraph* pg, int visitV) // 두 번째 매개변수로 전달된 이름의 정점에 방문
{
	if (pg->visitInfo[visitV] == 0) // visitV에 처음 방문
	{
		pg->visitInfo[visitV] = 1; // visitV에 방문 기록
		printf("%c ", visitV + 65); // 방문 정점 이름 출력
		return TRUE; // 방문 성공
	}
	return FALSE; // 방문 실패
}

void BFShowGraphVertex(ALGraph* pg, int startV) // BFS(Breadth First Search 기반) 정점 정보 출력
{
	Queue queue;
	int visitV = startV;
	int nextV;

	QueueInit(&queue); // BFS를 위한 큐 초기화
	VisitVertex(pg, visitV); // 시작 정점 방문

	// visitV에 담긴 정점과 연결된 정점의 방문 시도
	while (LFirst(&(pg->adjList[visitV]), &nextV) == TRUE)
	{
		if (VisitVertex(pg, nextV) == TRUE) // 방문 성공
			Enqueue(&queue, nextV); // 큐에 저장

		while (LNext(&(pg->adjList[visitV]), &nextV) == TRUE)
		{
			if (VisitVertex(pg, nextV) == TRUE)
				Enqueue(&queue, nextV); // 큐에 저장
		}
		
		// 큐가 비면 BFS 종료
		if (QIsEmpty(&queue) == TRUE)
			break;
		else
			visitV = Dequeue(&queue); // 큐에서 하나 꺼내 while문 다시 시작
	}

	// 이후 탐색을 위해 탐색 정보 초기화
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
}