#pragma once
#ifndef __SLOT2_H__
#define __SLOT2_H__

#include "Person.h"

typedef int Key; // �ֹε�Ϲ�ȣ
typedef Person* Value; // ����ü ������ �ּ� ��

typedef struct _slot
{
	Key key;
	Value val;
} Slot;

#endif