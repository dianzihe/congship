#pragma once

#include "base.h"

#define BUFF_READ_BYTE(dst, data, off)\
	dst = data[off];\
	off++;

#define BUFF_READ_SHORT(dst, data, off)\
	dst = *(short*)(&data[off]);\
	off+=2;

#define BUFF_READ_INT(dst, data, off)\
	dst = *(int*)(&data[off]);\
	off+=4;

#define BUFF_READ_STRING(dst, data, off)\
	{\
	int len111 = *(short*)(&data[off]);\
	off+=2;\
	char buf[1024] = {0};\
	memcpy(buf, &(data[off]), len111);\
	string ss(buf);\
	dst = ss;\
	off+=len111;\
	}

#define BUFF_READ_STRING2(dst, data, off)\
	{\
	int len111 = *(int*)(&data[off]);\
	off+=4;\
	char buf[1024] = {0};\
	memcpy(buf, &(data[off]), len111);\
	string ss(buf);\
	dst = ss;\
	off+=len111;\
	}


