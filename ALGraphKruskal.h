#ifndef __AL_GRAPH_KRUSCAL__
#define __AL_GRAPH_KRUSCAL__

#include "DLinkedList.h"
#include "PriorityQueue.h"
#include <ALEdge.h>

// 정점 이름 상수화
enum { A, B, C, D, E, F, G, H, I, J };

typedef struct _ual
{
	int numV; // 정점 수
	int numE; // 간선 수
	List* adjList; // 간선 정보
	int* visitInfo;
	PQueue pqueue; // 간선의 가중치 정보 저장
} ALGraph;

// 그래프 초기화
void GraphInit(ALGraph* pg, int nv);

// 그래프 리소스 해제
void GraphDestroy(ALGraph* pg);

// 간선 추가
void AddEdge(ALGraph* pg, int fromV, int toV, int weight);

// 간선 정보 출력
void ShowGraphEdgeInfo(ALGraph* pg);

// DFS(Depth First Search 기반) 정점 정보 출력
void DFShowGraphVertex(ALGraph* pg, int startV);

// 최소 비용 신장 트리 구성
void ConKruskalMST(ALGraph* pg); 

// 가중치 정보 출력
void ShowGraphEdgeWeightInfo(ALGraph* pg); 

#endif