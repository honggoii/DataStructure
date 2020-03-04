#include <stdio.h>
#include <stdlib.h>

void MergeTwoArea(int arr[], int left, int mid, int right)
{
	int fIdx = left; // �� �迭 ù ��° �ε���
	int rIdx = mid + 1; // �� �迭 ù ��° �ε���
	int i;

	int* sortArr = (int*)malloc(sizeof(int) * (right + 1)); // ���� ����� ���� �迭 ���� �Ҵ�
	int sIdx = left;

	while (fIdx <= mid && rIdx == right)
	{
		if (arr[fIdx] <= arr[rIdx])
			sortArr[sIdx] = arr[fIdx++];
		else
			sortArr[sIdx] = arr[rIdx++];

		sIdx++;
	}

	if (fIdx > mid)
	{ // �迭�� �պκ��� ��� sortArr�� �Ű����ٸ�
		for (i = rIdx; i <= right; i++, sIdx++)
			sortArr[sIdx] = arr[i]; // �迭 �޺κ��� �״�� sortArr�� �ű��.
	}
	else
	{ // �迭�� �޺κ��� ��� sortArr�� �Ű����ٸ�
		for (i = fIdx; i <= mid; i++, sIdx++)
			sortArr[sIdx] = arr[i]; // �迭 �պκ��� �״�� sortArr�� �ű��.
	}

	for (i = left; i <= right; i++)
		arr[i] = sortArr[i];

	free(sortArr);
}

void MergeSort(int arr[], int left, int right)
{
	int mid;

	if (left < right)
	{
		// �� ���� �� ������

		// �߰����� ���
		mid = (left + right) / 2;

		// �ѷ� ������ ���� ����
		MergeSort(arr, left, mid);	// left ~ mid ����
		MergeSort(arr, mid + 1, right); // mid+1 ~ right����

		// ���ĵ� �� �迭 ����
		MergeTwoArea(arr, left, mid, right);
	}
}

int main(void)
{
	int arr[7] = { 3,2,4,1,7,6,5 };
	int i;

	// �迭 arr�� ��ü ���� ����
	MergeSort(arr, 0, sizeof(arr) / sizeof(int) - 1);

	for (i = 0; i < 7; i++)
		printf("%d ", arr[i]);

	printf("\n");
	return 0;
}