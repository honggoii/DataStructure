#pragma once
#ifndef __SLOT_H__
#define __SLOT_H__

#include "Person.h"

typedef int Key; // �ֹε�Ϲ�ȣ
typedef Person* Value; // ����ü ������ �ּ� ��

enum SlotStatus {EMPTY, DELETED, INUSE};

typedef struct _slot
{
	Key key;
	Value val;
	enum SlotStatus status;
} Slot;

#endif