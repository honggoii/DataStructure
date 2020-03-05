#ifndef __AL_GRAPH_BFS__
#define __AL_GRAPH_BFS__

#include "DLinkedList.h"

// 정점 이름 상수화
enum { A, B, C, D, E, F, G, H, I, J };

typedef struct _ual
{
	int numV; // 정점 수
	int numE; // 간선 수
	List* adjList; // 간선 정보
	int* visitInfo;
} ALGraph;

// 그래프 초기화
void GraphInit(ALGraph* pg, int nv);

// 그래프 리소스 해제
void GraphDestroy(ALGraph* pg);

// 간선 추가
void AddEdge(ALGraph* pg, int fromV, int toV);

// 간선 정보 출력
void ShowGraphEdgeInfo(ALGraph* pg);

// BFS(Breadth First Search 기반) 정점 정보 출력
void BFShowGraphVertex(ALGraph* pg, int startV);

#endif