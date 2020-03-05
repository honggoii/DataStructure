#include <stdio.h>
#include "ALGraph.h"

int main(void)
{
	ALGraph graph; // 그래프 생성
	GraphInit(&graph, 5); // 그래프 초기화, 5개의 정점 생성

	AddEdge(&graph, A, B); // 정점 A와 B 연결
	AddEdge(&graph, A, D); // 정점 A와 D 연결
	AddEdge(&graph, B, C); // 정점 B와 C 연결
	AddEdge(&graph, C, D); // 정점 C와 D 연결
	AddEdge(&graph, D, E); // 정점 D와 E 연결
	AddEdge(&graph, E, A); // 정점 E와 A 연결

	ShowGraphEdgeInfo(&graph); // 그래프 간선정보 출력
	GraphDestroy(&graph); // 그래프 리소스 소멸

	return 0;
}