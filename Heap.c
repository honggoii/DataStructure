#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define HEAP_LEN 100

typedef char HData;
typedef int Priority;

typedef int PriorityComp(HData d1, HData d2);

typedef struct _heap
{
	PriorityComp* comp; // ���α׷��Ӱ� �켱���� �Ǵ� ���� ����
	int numOfData;
	HData heapArr[HEAP_LEN];
} Heap;

void HeapInit(Heap* ph, PriorityComp pc);
int IsEmpty(Heap* ph);

void Insert(Heap* ph, HData data);
HData Delete(Heap* ph);

int DataPriorityComp(char ch1, char ch2) // �켱���� ���Լ�
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
	ph->comp = pc; // �켱���� �񱳿� ���Ǵ� �Լ�
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
		// �ڽ� ��尡 �������� ������
		// ���� �ڽ� ����� �ε��� ���� ��� ���� �Ѿ��
		return 0;
	else if (GetLChildIDX(idx) == ph->numOfData)
		// ���� �ڽ� ��� �ϳ��� �����Ѵٸ�
		// �ڽ��� �ϳ���� ������ ����̰� ���� �ڽ� ���
		return GetLChildIDX(idx);
	else
	{   // �ڽ� ��尡 �� �� ���� �Ѵٸ�
		if (ph->comp(ph->heapArr[GetLChildIDX(idx)],
			ph->heapArr[GetRChildIDX(idx)]) < 0)
			// ������ �ڽ� ����� �켱������ ���ٸ�
			return GetRChildIDX(idx); // ������ �ڽ� ��� �ε��� ��ȯ
		else
			// ���� �ڽ� ����� �켱������ ���ٸ�
			return GetLChildIDX(idx); // ���� �ڽ� ��� �ε��� ��ȯ
	}
}

void Insert(Heap* ph, HData data)
{
	int idx = ph->numOfData + 1; // �� ��尡 ����� �ε��� �� ����

	// �� ��尡 ����� ��ġ�� ��Ʈ ����� ��ġ�� �ƴ϶�� while�� �ݺ�
	while (idx != 1)
	{
		// �� ���� �θ� ����� �켱���� ��
		if (ph->comp(data, ph->heapArr[GetParentIDX(idx)]) > 0)
		{// �� ����� �켱������ ���ٸ�

			ph->heapArr[idx] = ph->heapArr[GetParentIDX(idx)];
			// �θ� ��带 �� ���� "������" ����
			idx = GetParentIDX(idx);
			// �� ��带 "�ε��� ����" �� ���� �ø�
		}
		else
			// �� ����� �켱������ ���ٸ�
			break; 
	}
	
	ph->heapArr[idx] = data; // �� ��带 �迭�� ����
	ph->numOfData += 1;
}

HData Delete(Heap* ph)
{
	HData rData = ph->heapArr[1]; // ������ ������ ����(��Ʈ ���)
	HData lastElem = ph->heapArr[ph->numOfData]; // ������ ��� ����

	int parentIdx = 1; // ������ ��尡 ����� ��ġ����
	int childIdx;

	// ��Ʈ ����� �켱������ ���� �ڽ� ��带 �������� �ݺ��� ����
	while (childIdx = GetHiPriChildIDX(ph, parentIdx))
	{
		if (ph->comp(lastElem, ph->heapArr[childIdx]) >= 0) // ������ ���� �켱���� ��
			break; // ������ ����� �켱������ ������ �ݺ��� Ż��

		// ������ ��庸�� �켱������ ������
		ph->heapArr[parentIdx] = ph->heapArr[childIdx];
		// �ڽ� ��带 �θ� ��� ��ġ�� "������" �ø�
		parentIdx = childIdx; // ������ ��尡 ����� "��ġ����"�� �� ���� ����
	}
	// �ݺ����� Ż���ϸ� parentIdx���� ������ ����� ��ġ������ ����


	ph->heapArr[parentIdx] = lastElem; // ������ ��� ����
	ph->numOfData -= 1; // ���� �ϳ� ����
	return rData; // ���� ������ ��ȯ
}