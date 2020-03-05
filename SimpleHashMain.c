#include <stdio.h>
#include <stdlib.h>
#include "Person.h"
#include "Table.h"

int MyHashFunc(int k)
{
	return k % 100;
}

int main(void)
{
	Table myTbl;
	Person* np;
	Person* sp;
	Person* rp;

	TBLInit(&myTbl, MyHashFunc);

	// ������ �Է�
	np = MakePersonData(20120003, "LEE", "Seoul");
	TBLInsert(&myTbl, GetSSN(np), np);

	np = MakePersonData(20120012, "KIM", "Jeju");
	TBLInsert(&myTbl, GetSSN(np), np);

	np = MakePersonData(20120003, "HAN", "Kangwon");
	TBLInsert(&myTbl, GetSSN(np), np);

	// ������ Ž��
	sp = TBLSearch(&myTbl, 20120003);
	if (sp != NULL)
		ShowPerinfo(sp);

	sp = TBLSearch(&myTbl, 20120012);
	if (sp != NULL)
		ShowPerinfo(sp);

	sp = TBLSearch(&myTbl, 20120049);
	if (sp != NULL)
		ShowPerinfo(sp);

	// ������ ����
	rp = TBLDelete(&myTbl, 20120003);
	if (rp != NULL)
		free(rp);

	rp = TBLDelete(&myTbl, 20120012);
	if (rp != NULL)
		free(rp);

	rp = TBLDelete(&myTbl, 20120049);
	if (rp != NULL)
		free(rp);

	return 0;
}