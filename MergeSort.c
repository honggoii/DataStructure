#include <stdio.h>
#include <stdlib.h>

void MergeTwoArea(int arr[], int left, int mid, int right)
{
	int fIdx = left; // 앞 배열 첫 번째 인덱스
	int rIdx = mid + 1; // 뒤 배열 첫 번째 인덱스
	int i;

	int* sortArr = (int*)malloc(sizeof(int) * (right + 1)); // 병합 결과를 담을 배열 동적 할당
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
	{ // 배열의 앞부분이 모두 sortArr에 옮겨졌다면
		for (i = rIdx; i <= right; i++, sIdx++)
			sortArr[sIdx] = arr[i]; // 배열 뒷부분을 그대로 sortArr에 옮긴다.
	}
	else
	{ // 배열의 뒷부분이 모두 sortArr에 옮겨졌다면
		for (i = fIdx; i <= mid; i++, sIdx++)
			sortArr[sIdx] = arr[i]; // 배열 앞부분을 그대로 sortArr에 옮긴다.
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
		// 더 나눌 수 있으면

		// 중간지점 계산
		mid = (left + right) / 2;

		// 둘로 나눠서 각각 정렬
		MergeSort(arr, left, mid);	// left ~ mid 정렬
		MergeSort(arr, mid + 1, right); // mid+1 ~ right정렬

		// 정렬된 두 배열 병합
		MergeTwoArea(arr, left, mid, right);
	}
}

int main(void)
{
	int arr[7] = { 3,2,4,1,7,6,5 };
	int i;

	// 배열 arr의 전체 영역 정렬
	MergeSort(arr, 0, sizeof(arr) / sizeof(int) - 1);

	for (i = 0; i < 7; i++)
		printf("%d ", arr[i]);

	printf("\n");
	return 0;
}