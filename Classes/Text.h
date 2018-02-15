#ifndef __TEXT_H__
#define __TEXT_H__

#include "base.h"
#include <vector>
#include <string>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

typedef std::vector<string> TextCache;

class CText
{
	CC_SYNTHESIZE(int, m_count, Count);
public:
	CText();
	~CText();
	static CText* Instance();

	bool Init();
	void Uninit();

	static string GetText(int id);
private:
	TextCache m_textCache;
};
#endif
//EOF
