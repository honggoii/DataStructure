int BSearchRecur(int arr[], int first, int last, int target) {
	int mid;

	if (first > last)
		return -1;	// Å½»ö ½ÇÆĞ
	
	mid = (first + last) / 2;

	if (arr[mid] == target)
		return mid;
	else if (target < arr[mid])
		return BSearchRecur(arr, first, mid - 1, target);
	else
		return BSearchRecur(arr, mid + 1, last, target);
}