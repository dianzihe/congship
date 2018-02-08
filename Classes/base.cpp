#include "base.h"
Language GetCurrentLanguage()
{
	return _curLanguage;
}

const char* GetLanguageTypeString(Language type)
{
	static const char* s[] = {
		"",
		"cht",
		"kor",
		"yhz"
	};
	assert(type >= 0 && type < LT_MAX);
	return s[type];
}
