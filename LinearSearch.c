void HanoiTower(int num, char from, char by, char to) {
	if (num == 1)
		printf("원반1을 %c에서 %c로 이동 \n", from, to);
	else {
		HanoiTower(num - 1, from, to, by);				// n-1개를 A에서 B로 이동
		printf("원반%d를 %c에서 %c로 이동 \n", from, to);	// 마지막 원반을 A에서 C로 이동
		HanoiTower(num - 1, by, from, to);				// n-1개를 B에서 C로 이동
	}
} 