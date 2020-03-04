#include <stdio.h>

typedef int Key; // Ž�� Ű

typedef double Data; // Ž�� ������

typedef struct item
{
	Key searchKey; // Ž�� Ű
	Data searchData; // Ž�� ������
} Item;

int ISearch(int ar[], int first, int last, int target)
{
	int s; 

	if (ar[first] > target || ar[last] < target)
		// target�� ����� ���� first���� �۰ų� last���� ũ��
		// ��� Ż�� ����
		return -1; // Ž�� ����

	// ���� Ž������ ����
	s = ((double)(target-ar[first]) / (ar[last]-ar[first])*
		(last - first)) + first;

	if (ar[s] == target)
		return s; // Ž���� Ÿ�� �ε��� ��ȯ
	else if (target < ar[s])
		return ISearch(ar, first, s - 1, target);
	else 
		return ISearch(ar, s + 1, last, target);
}

int main(void)
{
	int arr[] = { 1,3,5,7,9 };
	int idx;

	idx = ISearch(arr, 0, sizeof(arr) / sizeof(int) - 1, 7);

	if (idx == -1)
		printf("Ž�� ����\n");
	else
		printf("Ÿ�� ���� �ε���: %d \n", idx);

	idx = ISearch(arr, 0, sizeof(arr) / sizeof(int) - 1, 10);
	if (idx == -1)
		printf("Ž�� ����\n");
	else
		printf("Ÿ�� ���� �ε���: %d \n", idx);

	return 0;
}