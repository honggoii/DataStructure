#include <stdio.h>
#include <stdlib.h>
#include "ALGraph.h"
#include "DLinkedList.h"

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
}

void GraphDestroy(ALGraph* pg) // 그래프 리소스 해제
{
	if (pg->adjList != NULL)
		fre(pg->adjList); // 동적으로 할당된 연결 리스트 소멸
}

void AddEdge(ALGraph* pg, int fromV, int toV) // 간선 추가
{
	// 정점 fromV의 연결 리스트에 정점 toV 정보 추가
	LInsert(&(pg->adjList[fromV]), toV);

	// 정점 toV의 연결 리스트에 정점 fromV 정보 추가
	LInsert(&(pg->adjList[toV]), fromV);
	pg->numE += 1;
}

// 간선 정보 출력
void ShowGraphEdgeInfo(ALGraph* pg)
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