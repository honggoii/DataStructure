int WhoIsPrecede(int data1, int data2);

int PQWeightComp(Edge d1, Edge d2)
{
	return d1.weight - d2.weight;
}

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

	// 우선순위 큐 초기화
	PQueueInit(&(pg->pqueue), PQWeightComp);
}

void GraphDestroy(ALGraph* pg) // 그래프 리소스 해제
{
	if (pg->adjList != NULL)
		fre(pg->adjList); // 동적으로 할당된 연결 리스트 소멸

	if (pg->visitInfo != NULL)
		free(pg->visitInfo);
}

void AddEdge(ALGraph* pg, int fromV, int toV, int weight) // 간선 추가
{
	Edge edge = { fromV,toV,weight }; // 간선의 가중치 정보 담음

	// 정점 fromV의 연결 리스트에 정점 toV 정보 추가
	LInsert(&(pg->adjList[fromV]), toV);

	// 정점 toV의 연결 리스트에 정점 fromV 정보 추가
	LInsert(&(pg->adjList[toV]), fromV);
	pg->numE += 1;

	// 간선의 가중치 정보를 우선순위 큐에 저장
	PEnqueue(&(pg->pqueue), edge);
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

void DFShowGraphVertex(ALGraph* pg, int startV) // DFS(Depth First Search 기반) 정점 정보 출력
{
	Stack stack;
	int visitV = startV;
	int nextV;

	StackInit(&stack); // DFS를 위한 스택 초기화
	VisitVertex(pg, visitV); // 시작 정점 방문
	SPush(&stack, visitV); // 시작 정점의 정보를 스택으로

	// visitV에 담긴 정점과 연결된 정점의 방문 시도
	while (LFirst(&(pg->adjList[visitV]), &nextV) == TRUE)
	{
		// visitV와연결된 정점의 정보가 nextV에 담긴 상태에서 진행
		int visitFlag = FALSE;

		if (VisitVertex(pg, nextV) == TRUE) // 방문 성공
		{
			SPush(&stack, visitV); // visitV에 담긴 정점의 정보 push
			visitV = nextV;
			visitFlag = TRUE;
		}
		else // 방문에 성공하지 못하면, 연결된 다른 정점을 찾음
		{
			while (LNext(&(pg->adjList[visitV]), &nextV) == TRUE)
			{
				if (VisitVertex(pg, nextV) == TRUE)
				{
					SPush(&stack, visitV);
					visitV = nextV;
					visitFlag = TRUE;
					break;
				}
			}
		}
		if (visitFlag == FALSE) // 추가로 방문한 정점이 없었다면
		{
			// 스택이 비면 탐색의 시작점으로 되돌아 온 것
			if (SIsEmpty(&stack) == TRUE)
				break;
			else
				visitV = Spop(&stack); // 길을 되돌아 감
		}
	}

	// 이후 탐색을 위해 탐색 정보 초기화
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
}

void ConKruskalMST(ALGraph* pg)// 최소 비용 신장 트리 구성
{
	Edge recvEdge[20]; // 복원할 간선 정보 저장
	Edge edge;
	int eidx = 0;
	int i;

	// MST를 형성할 때까지 반복
	while (pg->numE + 1 > pg->numV) // MST 간선의 수 + 1 == 정점의 수
	{
		edge = PDequeue(&(pg->pqueue)); // 우선순위 큐에서 가중치가 제일 높은 간선 꺼냄
		RemoveEdge(pg, edge.v1, edge.v2); // 우선순위 큐에서 꺼낸 간선을 그래프에서 삭제

		// 간선 삭제 후 두 정점을 연결하는 경로가 있는지 확인
		if (!IsConnVertex(pg, edge.v1, edge.v2))
		{
			RecoverEdge(pg, edge.v1, edge.v2, edge.weight); // 경로가 없으면 삭제한 간선 복원
			recvEdge[eidx++] = edge; // 복원한 간선 정보 별도 저장
		}
	}

	// 우선순위 큐에서 삭제된 간선 정보 회복
	for (i = 0; i < eidx; i++)
		PEnqueue(&(pg->pqueue), recvEdge[i]);
}

void ShowGraphEdgeWeightInfo(ALGraph* pg)// 가중치 정보 출력
{
	PQueue copyPQ = pg->pqueue;
	Edge edge;

	while (!PQIsEmpty(&copyPQ))
	{
		edge = PDequeue(&copyPQ);
		printf("(%c-%c), w:%d \n", edge.v1 + 65, edge.v2 + 65, edge.weight);
	}
}

void RemoveEdge(ALGraph* pg, int fromV, int toV) // 간선 소멸
{
	RemoveWayEdge(pg, fromV, toV);
	RemoveWayEdge(pg, toV, fromV);
	(pg->numE)--;
}

void RemoveWayEdge(ALGraph* pg, int fromV, int toV) // 한쪽 방향 간선 소멸
{
	int edge;

	if (LFirst(&(pg->adjList[fromV]), &edge))
	{
		if (edge == toV)
		{
			LRemove(&(pg->adjList[fromV]));
				return;
		}

		while (LNext(&(pg->adjList[fromV]), &edge))
		{
			if (edge == toV)
			{
				LRemove(&(pg->adjList[fromV]));
				return;
			}
		}
	}
}

void RecoverEdge(ALGraph* pg, int fromV, int toV, int weight)
{
	LInsert(&(pg->adjList[fromV]), toV);
	LInsert(&(pg->adjList[toV]), fromV);
	(pg->numE)++;
}

int IsConnVertex(ALGraph* pg, int v1, int v2) // 인자로 전달된 두 정점이 연결되면 TRUE, 그렇지 않으면 FALSE 반환
{
	Stack stack;
	int visitV = v1;
	int nextV;

	StackInit(&stack); // 스택 초기화
	VisitVertex(pg, visitV); // 시작 정점 방문
	SPush(&stack, visitV); // 시작 정점의 정보를 스택으로

	// visitV에 담긴 정점과 연결된 정점의 방문 시도
	while (LFirst(&(pg->adjList[visitV]), &nextV) == TRUE)
	{
		// visitV와연결된 정점의 정보가 nextV에 담긴 상태에서 진행
		int visitFlag = FALSE;

		// 정점을 돌아다니는 도중에 목표 찾으면 TRUE 반환
		if (nextV == v2)
		{
			// 함수가 반환하기 전에 초기화 
			memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
			return TRUE;
		}

		if (VisitVertex(pg, nextV) == TRUE) // 방문 성공
		{
			SPush(&stack, visitV); // visitV에 담긴 정점의 정보 push
			visitV = nextV;
			visitFlag = TRUE;
		}
		else // 방문에 성공하지 못하면, 연결된 다른 정점을 찾음
		{
			while (LNext(&(pg->adjList[visitV]), &nextV) == TRUE)
			{
				// 정점을 돌아다니는 도중에 목표 찾으면 TRUE 반환
				if (nextV == v2)
				{
					// 함수가 반환하기 전에 초기화 
					memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
					return TRUE;
				}

				if (VisitVertex(pg, nextV) == TRUE)
				{
					SPush(&stack, visitV);
					visitV = nextV;
					visitFlag = TRUE;
					break;
				}
			}
		}
		if (visitFlag == FALSE) // 추가로 방문한 정점이 없었다면
		{
			// 스택이 비면 탐색의 시작점으로 되돌아 온 것
			if (SIsEmpty(&stack) == TRUE)
				break;
			else
				visitV = Spop(&stack); // 길을 되돌아 감
		}
	}

	// 이후 탐색을 위해 탐색 정보 초기화
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
	return FALSE; // 목표 찾지 못함
}