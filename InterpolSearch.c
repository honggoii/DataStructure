#include <stdio.h>

typedef int Key; // Å½»ö Å°

typedef double Data; // Å½»ö µ¥ÀÌÅÍ

typedef struct item
{
	Key searchKey; // Å½»ö Å°
	Data searchData; // Å½»ö µ¥ÀÌÅÍ
} Item;

int ISearch(int ar[], int first, int last, int target)
{
	int s; 

	if (ar[first] > target || ar[last] < target)
		// target¿¡ ÀúÀåµÈ °ªÀÌ firstº¸´Ù ÀÛ°Å³ª lastº¸´Ù Å©¸é
		// Àç±Í Å»Ãâ Á¶°Ç
		return -1; // Å½»ö ½ÇÆÐ

	// ÀÌÁø Å½»ö°úÀÇ Â÷ÀÌ
	s = ((double)(target-ar[first]) / (ar[last]-ar[first])*
		(last - first)) + first;

	if (ar[s] == target)
		return s; // Å½»öµÈ Å¸°Ù ÀÎµ¦½º ¹ÝÈ¯
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
		printf("Å½»ö ½ÇÆÐ\n");
	else
		printf("Å¸°Ù ÀúÀå ÀÎµ¦½º: %d \n", idx);

	idx = ISearch(arr, 0, sizeof(arr) / sizeof(int) - 1, 10);
	if (idx == -1)
		printf("Å½»ö ½ÇÆÐ\n");
	else
		printf("Å¸°Ù ÀúÀå ÀÎµ¦½º: %d \n", idx);

	return 0;
}