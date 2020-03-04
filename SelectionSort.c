#include <stdio.h>

void SelSort(int arr[], int n)
{
	int i, j;
	int maxIdx;
	int temp;

	for (i = 0; i < n - 1; i++) 
	{
		maxIdx = i; // 왼쪽 자리 인덱스 저장

		for (j = i + 1; j < n; j++) 
		{
			if (arr[j] < arr[maxIdx])
				maxIdx = j;
		}

		// 교환
		temp = arr[i];
		arr[i] = arr[maxIdx];
		arr[maxIdx] = temp;
	}
}

int main(void)
{
	int arr[4] = { 3,4,2,1 };
	int i;

	SelSort(arr, sizeof(arr) / sizeof(int));

	for (i = 0; i < 4; i++)
		printf("%d ", arr[i]);

	printf("\n");
	return 0;
}