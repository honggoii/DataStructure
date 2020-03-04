#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define HEAP_LEN 100

typedef char HData;
typedef int Priority;

typedef int PriorityComp(HData d1, HData d2);

typedef struct _heap
{
	PriorityComp* comp; // 프로그래머가 우선순위 판단 기준 설정
	int numOfData;
	HData heapArr[HEAP_LEN];
} Heap;

void HeapInit(Heap* ph, PriorityComp pc);
int IsEmpty(Heap* ph);

void Insert(Heap* ph, HData data);
HData Delete(Heap* ph);

int DataPriorityComp(char ch1, char ch2) // 우선순위 비교함수
{
	return ch2 - ch1;
}

int main(void)
{
	Heap heap;
	HeapInit(&heap, DataPriorityComp);

	Insert(&heap, 'A', 1);
	Insert(&heap, 'B', 2);
	Insert(&heap, 'C', 3);
	pirntf("%c \n", Delete(&heap));

	Insert(&heap, 'A', 1);
	Insert(&heap, 'B', 2);
	Insert(&heap, 'C', 3);
	printf("%c \n", Delete(&heap));

	while (!IsEmpty(&heap))
		printf("%c \n", Delete(&heap));

	return 0;
}

void HeapInit(Heap* ph, PriorityComp pc)
{
	ph->numOfData = 0;
	ph->comp = pc; // 우선순위 비교에 사용되는 함수
}

int IsEmpty(Heap* ph)
{
	if (ph->numOfData == 0)
		return TRUE;
	else
		return FALSE;
}

int GetParentIDX(int idx)
{
	return idx / 2;
}

int GetLChildIDX(int idx)
{
	return idx * 2;
}

int GetRChildIDX(int idx)
{
	return GetLChildIDX(idx) + 1;
}

int GetHiPriChildIDX(Heap* ph, int idx)
{
	if (GetLChildIDX(idx) > ph->numOfData) 
		// 자식 노드가 존재하지 않으면
		// 왼쪽 자식 노드의 인덱스 값이 노드 수를 넘어서면
		return 0;
	else if (GetLChildIDX(idx) == ph->numOfData)
		// 왼쪽 자식 노드 하나만 존재한다면
		// 자식이 하나라면 마지막 노드이고 왼쪽 자식 노드
		return GetLChildIDX(idx);
	else
	{   // 자식 노드가 둘 다 존재 한다면
		if (ph->comp(ph->heapArr[GetLChildIDX(idx)],
			ph->heapArr[GetRChildIDX(idx)]) < 0)
			// 오른쪽 자식 노드의 우선순위가 높다면
			return GetRChildIDX(idx); // 오른쪽 자식 노드 인덱스 반환
		else
			// 왼쪽 자식 노드의 우선순위가 높다면
			return GetLChildIDX(idx); // 왼쪽 자식 노드 인덱스 반환
	}
}

void Insert(Heap* ph, HData data)
{
	int idx = ph->numOfData + 1; // 새 노드가 저장될 인덱스 값 저장

	// 새 노드가 저장될 위치가 루트 노드의 위치가 아니라면 while문 반복
	while (idx != 1)
	{
		// 새 노드와 부모 노드의 우선순위 비교
		if (ph->comp(data, ph->heapArr[GetParentIDX(idx)]) > 0)
		{// 새 노드의 우선순위가 높다면

			ph->heapArr[idx] = ph->heapArr[GetParentIDX(idx)];
			// 부모 노드를 한 레벨 "실제로" 내림
			idx = GetParentIDX(idx);
			// 새 노드를 "인덱스 값만" 한 레벨 올림
		}
		else
			// 새 노드의 우선순위가 낮다면
			break; 
	}
	
	ph->heapArr[idx] = data; // 새 노드를 배열에 저장
	ph->numOfData += 1;
}

HData Delete(Heap* ph)
{
	HData rData = ph->heapArr[1]; // 삭제할 데이터 저장(루트 노드)
	HData lastElem = ph->heapArr[ph->numOfData]; // 마지막 노드 저장

	int parentIdx = 1; // 마지막 노드가 저장될 위치정보
	int childIdx;

	// 루트 노드의 우선순위가 높은 자식 노드를 시작으로 반복문 시작
	while (childIdx = GetHiPriChildIDX(ph, parentIdx))
	{
		if (ph->comp(lastElem, ph->heapArr[childIdx]) >= 0) // 마지막 노드와 우선순위 비교
			break; // 마지막 노드의 우선순위가 높으면 반복문 탈출

		// 마지막 노드보다 우선순위가 높으니
		ph->heapArr[parentIdx] = ph->heapArr[childIdx];
		// 자식 노드를 부모 노드 위치로 "실제로" 올림
		parentIdx = childIdx; // 마지막 노드가 저장될 "위치정보"를 한 레벨 내림
	}
	// 반복문을 탈출하면 parentIdx에는 마지막 노드의 위치정보가 저장


	ph->heapArr[parentIdx] = lastElem; // 마지막 노드 저장
	ph->numOfData -= 1; // 개수 하나 감소
	return rData; // 삭제 데이터 반환
}