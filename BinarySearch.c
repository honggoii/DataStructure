int BSearch(int ar[], int len, int target)
{
	int first = 0;		// 배열 시작 인덱스 값
	int last = len - 1;	// 배열 마지막 인덱스 값
	int mid;			// 중앙 인덱스 값

	while (first <= last)	// first == last는 탐색 대상이 하나 남았다는 의미
	{
		mid = (first + last) / 2;	// 중앙을 찾는다.

		if (target == ar[mid])
			return mid;
		else
		{
			if (target < ar[mid])	// target보다 중앙값이 크면
				last = mid - 1;		// last를 줄인다
			else
				first = mid + 1;	// first를 늘린다.
		}
	}

	return -1;	// 찾지 못했을 때 반환
} 