void HanoiTower(int num, char from, char by, char to) {
	if (num == 1)
		printf("����1�� %c���� %c�� �̵� \n", from, to);
	else {
		HanoiTower(num - 1, from, to, by);				// n-1���� A���� B�� �̵�
		printf("����%d�� %c���� %c�� �̵� \n", from, to);	// ������ ������ A���� C�� �̵�
		HanoiTower(num - 1, by, from, to);				// n-1���� B���� C�� �̵�
	}
}