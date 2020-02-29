int LSearch(int ar[], int len, int target)
{
	int i;
	
	for (i = 0; i < len; i++)
	{
		if (ar[i] == target)
			return i;	// 찾은 대상의 인덱스 값 반환
	}
	
	return -1;			// 찾지 못했음을 의미하는 값 반환
}