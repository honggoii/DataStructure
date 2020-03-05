#ifndef __PERSON_H__
#define __PERSON_H__

#define STR_LEN 50

typedef struct _person
{
	int ssn; // �ֹε�Ϲ�ȣ
	char name[STR_LEN]; // �̸�
	char addr[STR_LEN]; // �ּ�
} Person;

int GetSSN(Person* p);
void ShowPerinfo(Person* p);
Person* MakePersonData(int ss, char* name, char* addr);

#endif