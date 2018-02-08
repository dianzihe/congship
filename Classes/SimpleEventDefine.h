#ifndef _SIMPLEEVENTDEFINE_H__
#define _SIMPLEEVENTDEFINE_H__

#include "base.h"

enum DataType
{
	eType_char,
	eType_uchar,
	eType_short,
	eType_ushort,
	eType_int,
	eType_uint,
	eType_long,
	eType_ulong,
	eType_float,
	eType_double,
	eType_str,
};

#define CharArraySize 512

union TypeData
{
	char _CharData;
	unsigned char _UCharData;
	short _ShortData;
	unsigned short _UShortData;
	int _IntData;
	unsigned int _UIntData;
	long long _LongData;
	unsigned long long _ULongData;
	float _FloatData;
	double _DoubleData;
	char* _pStrData;
	bool _BoolData;
};

struct EventParam
{
	DataType _Type;
	TypeData _Data;
};

#endif
