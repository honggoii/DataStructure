#ifndef __AL_GRAPH__
#define __AL_GRAPH__

#include "DLinkedLish.h"

// 정점의 이름 상수화
enum {A,B,C,D,E,F,G,H,I,J};

typedef struct _ual
{
	int numV; // 정점 수
	int numE; // 간선 수
	List* adjList; // 간선 정보
} ALGraph;

// 그래프 초기화
void GraphInit(ALGraph* pg, int nv);

// 그래프 리소스 해제
void GraphDestroy(ALGraph* pg);

// 간선 추가
void AddEdge(ALGraph* pg, int fromV, int toV);

// 간선 정보 출력
void ShowGraphEdgeInfo(ALGraph* pg);

#endif