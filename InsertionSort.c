#include <stdio.h>

void InserSort(int arr[], int n)
{
	int i, j;
	int insData;

	for (i = 1; i < n; i++)
	{
		insData = arr[i]; // 정렬대상 저장
		
		for (j = i - 1; j >= 0; j--)
		{
			// 앞으로 한 칸씩 이동
			if (arr[j] > insData)
				arr[j + 1] = arr[j]; // 한 칸씩 뒤로 이동
			else
				break; // 삽입위치 찾음
		}

		arr[j + 1] = insData; // 찾은 위치에 데이터 삽입
	}
}

int main(void)
{
	int arr[5] = { 5,3,2,4,1 };
	int i;

	InserSort(arr, sizeof(arr) / sizeof(int));

	for (i = 0; i < 5; i++)
		printf("%d ", arr[i]);

	printf("\n");
	return 0;
}