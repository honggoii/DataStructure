int BSearch(int ar[], int len, int target)
{
	int first = 0;		// �迭 ���� �ε��� ��
	int last = len - 1;	// �迭 ������ �ε��� ��
	int mid;			// �߾� �ε��� ��

	while (first <= last)	// first == last�� Ž�� ����� �ϳ� ���Ҵٴ� �ǹ�
	{
		mid = (first + last) / 2;	// �߾��� ã�´�.

		if (target == ar[mid])
			return mid;
		else
		{
			if (target < ar[mid])	// target���� �߾Ӱ��� ũ��
				last = mid - 1;		// last�� ���δ�
			else
				first = mid + 1;	// first�� �ø���.
		}
	}

	return -1;	// ã�� ������ �� ��ȯ
}