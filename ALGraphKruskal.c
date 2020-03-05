int WhoIsPrecede(int data1, int data2);

int PQWeightComp(Edge d1, Edge d2)
{
	return d1.weight - d2.weight;
}

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

	// �켱���� ť �ʱ�ȭ
	PQueueInit(&(pg->pqueue), PQWeightComp);
}

void GraphDestroy(ALGraph* pg) // �׷��� ���ҽ� ����
{
	if (pg->adjList != NULL)
		fre(pg->adjList); // �������� �Ҵ�� ���� ����Ʈ �Ҹ�

	if (pg->visitInfo != NULL)
		free(pg->visitInfo);
}

void AddEdge(ALGraph* pg, int fromV, int toV, int weight) // ���� �߰�
{
	Edge edge = { fromV,toV,weight }; // ������ ����ġ ���� ����

	// ���� fromV�� ���� ����Ʈ�� ���� toV ���� �߰�
	LInsert(&(pg->adjList[fromV]), toV);

	// ���� toV�� ���� ����Ʈ�� ���� fromV ���� �߰�
	LInsert(&(pg->adjList[toV]), fromV);
	pg->numE += 1;

	// ������ ����ġ ������ �켱���� ť�� ����
	PEnqueue(&(pg->pqueue), edge);
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

void DFShowGraphVertex(ALGraph* pg, int startV) // DFS(Depth First Search ���) ���� ���� ���
{
	Stack stack;
	int visitV = startV;
	int nextV;

	StackInit(&stack); // DFS�� ���� ���� �ʱ�ȭ
	VisitVertex(pg, visitV); // ���� ���� �湮
	SPush(&stack, visitV); // ���� ������ ������ ��������

	// visitV�� ��� ������ ����� ������ �湮 �õ�
	while (LFirst(&(pg->adjList[visitV]), &nextV) == TRUE)
	{
		// visitV�Ϳ���� ������ ������ nextV�� ��� ���¿��� ����
		int visitFlag = FALSE;

		if (VisitVertex(pg, nextV) == TRUE) // �湮 ����
		{
			SPush(&stack, visitV); // visitV�� ��� ������ ���� push
			visitV = nextV;
			visitFlag = TRUE;
		}
		else // �湮�� �������� ���ϸ�, ����� �ٸ� ������ ã��
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
		if (visitFlag == FALSE) // �߰��� �湮�� ������ �����ٸ�
		{
			// ������ ��� Ž���� ���������� �ǵ��� �� ��
			if (SIsEmpty(&stack) == TRUE)
				break;
			else
				visitV = Spop(&stack); // ���� �ǵ��� ��
		}
	}

	// ���� Ž���� ���� Ž�� ���� �ʱ�ȭ
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
}

void ConKruskalMST(ALGraph* pg)// �ּ� ��� ���� Ʈ�� ����
{
	Edge recvEdge[20]; // ������ ���� ���� ����
	Edge edge;
	int eidx = 0;
	int i;

	// MST�� ������ ������ �ݺ�
	while (pg->numE + 1 > pg->numV) // MST ������ �� + 1 == ������ ��
	{
		edge = PDequeue(&(pg->pqueue)); // �켱���� ť���� ����ġ�� ���� ���� ���� ����
		RemoveEdge(pg, edge.v1, edge.v2); // �켱���� ť���� ���� ������ �׷������� ����

		// ���� ���� �� �� ������ �����ϴ� ��ΰ� �ִ��� Ȯ��
		if (!IsConnVertex(pg, edge.v1, edge.v2))
		{
			RecoverEdge(pg, edge.v1, edge.v2, edge.weight); // ��ΰ� ������ ������ ���� ����
			recvEdge[eidx++] = edge; // ������ ���� ���� ���� ����
		}
	}

	// �켱���� ť���� ������ ���� ���� ȸ��
	for (i = 0; i < eidx; i++)
		PEnqueue(&(pg->pqueue), recvEdge[i]);
}

void ShowGraphEdgeWeightInfo(ALGraph* pg)// ����ġ ���� ���
{
	PQueue copyPQ = pg->pqueue;
	Edge edge;

	while (!PQIsEmpty(&copyPQ))
	{
		edge = PDequeue(&copyPQ);
		printf("(%c-%c), w:%d \n", edge.v1 + 65, edge.v2 + 65, edge.weight);
	}
}

void RemoveEdge(ALGraph* pg, int fromV, int toV) // ���� �Ҹ�
{
	RemoveWayEdge(pg, fromV, toV);
	RemoveWayEdge(pg, toV, fromV);
	(pg->numE)--;
}

void RemoveWayEdge(ALGraph* pg, int fromV, int toV) // ���� ���� ���� �Ҹ�
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

int IsConnVertex(ALGraph* pg, int v1, int v2) // ���ڷ� ���޵� �� ������ ����Ǹ� TRUE, �׷��� ������ FALSE ��ȯ
{
	Stack stack;
	int visitV = v1;
	int nextV;

	StackInit(&stack); // ���� �ʱ�ȭ
	VisitVertex(pg, visitV); // ���� ���� �湮
	SPush(&stack, visitV); // ���� ������ ������ ��������

	// visitV�� ��� ������ ����� ������ �湮 �õ�
	while (LFirst(&(pg->adjList[visitV]), &nextV) == TRUE)
	{
		// visitV�Ϳ���� ������ ������ nextV�� ��� ���¿��� ����
		int visitFlag = FALSE;

		// ������ ���ƴٴϴ� ���߿� ��ǥ ã���� TRUE ��ȯ
		if (nextV == v2)
		{
			// �Լ��� ��ȯ�ϱ� ���� �ʱ�ȭ 
			memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
			return TRUE;
		}

		if (VisitVertex(pg, nextV) == TRUE) // �湮 ����
		{
			SPush(&stack, visitV); // visitV�� ��� ������ ���� push
			visitV = nextV;
			visitFlag = TRUE;
		}
		else // �湮�� �������� ���ϸ�, ����� �ٸ� ������ ã��
		{
			while (LNext(&(pg->adjList[visitV]), &nextV) == TRUE)
			{
				// ������ ���ƴٴϴ� ���߿� ��ǥ ã���� TRUE ��ȯ
				if (nextV == v2)
				{
					// �Լ��� ��ȯ�ϱ� ���� �ʱ�ȭ 
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
		if (visitFlag == FALSE) // �߰��� �湮�� ������ �����ٸ�
		{
			// ������ ��� Ž���� ���������� �ǵ��� �� ��
			if (SIsEmpty(&stack) == TRUE)
				break;
			else
				visitV = Spop(&stack); // ���� �ǵ��� ��
		}
	}

	// ���� Ž���� ���� Ž�� ���� �ʱ�ȭ
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
	return FALSE; // ��ǥ ã�� ����
}