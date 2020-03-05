#pragma once
#ifndef __SLOT2_H__
#define __SLOT2_H__

#include "Person.h"

typedef int Key; // 주민등록번호
typedef Person* Value; // 구조체 변수의 주소 값

typedef struct _slot
{
	Key key;
	Value val;
} Slot;

#endif