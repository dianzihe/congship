#include "base.h"

static int quadrantToDir[9] =
{
	0, //eDirection_Right,		// 0
	1, //eDirection_RightUp,	// 1
	2, //eDirection_Up,			// 2
	3, //eDirection_LeftUp,		// 3
	4, //eDirection_Left,		// 4
	5, //eDirection_LeftDown,	// 5
	6, //eDirection_Down,		// 6
	7, //eDirection_RightDown,  // 7
	8  //eDirection_Right,		// 8
};

void WriteObjectBuff(char*& buf, ObjectBuff& value)
{
	Writeint(buf, value.buff_id);
	Writeint16(buf, value.allValidTime);
	Writeint8(buf, value.remainTriggerCount);
}
void ReadObjectBuff(char*& buf, ObjectBuff& value)
{
	Readint(buf, value.buff_id);
	Readint16(buf, value.allValidTime);
	Readint8(buf, value.remainTriggerCount);
}

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
//	assert(type >= 0 && type < LT_MAX);
	return s[type];
}

cocos2d::Sprite *GetSprite(const std::string& filename)
{
	Sprite *psprite = Sprite::create();

	// Search in the cache, first
	SpriteFrameCache *sfc = SpriteFrameCache::getInstance();
	SpriteFrame *psf = sfc->spriteFrameByName(filename.c_str());

	std::string::size_type pos;
	if (!psf && (pos = filename.find_last_of('/')) != filename.npos){
		std::string lastPart(filename.begin() + pos + 1, filename.end());
		psf = sfc->spriteFrameByName(lastPart.c_str());
	}

	if (psf){
		psprite->initWithSpriteFrame(psf);
	}
	else {
		log("WARNING : %s not in a PACK!", filename.c_str());
		if (!psprite->initWithFile(filename.c_str())) {
			log("ERROR: %s is not in resources", filename.c_str());
			return NULL;
		}
	}
	return psprite;
}


bool _isTextUTF8(const char* str, size_t length)
{
	int bytes = 0;
	unsigned char chr;
	bool allAscii = true;
	for (size_t i = 0; i < length; ++i) {
		chr = *(str + i);
		if ((chr & 0x80) != 0) {
			allAscii = false;
		}
		if (bytes == 0) {
			if (chr >= 0x80) {
				if (chr >= 0xFC && chr <= 0xFD)
					bytes = 6;
				else if (chr >= 0xF8)
					bytes = 5;
				else if (chr >= 0xF0)
					bytes = 4;
				else if (chr >= 0xE0)
					bytes = 3;
				else if (chr >= 0xC0)
					bytes = 2;
				else {
					return false;
				}
				--bytes;
			}
		}
		else {
			if ((chr & 0xC0) != 0x80) {
				return false;
			}
			--bytes;
		}
	}
	if (bytes > 0) {
		return false;
	}
	if (allAscii) {
		return false;
	}
	return true;
}

void SET_DIR_BY_TWOPOINT(const Point &p1, const Point &p2, int& dir)
{
	Point p3 = p2 - p1;
	log("SET_DIR_BY_TWOPOINT-->[%.2f, %.2f]-->%.2f--%.2f", p3.x, p3.y, fabs(p3.x), fabs(p3.y));
	if (!(fabs(p3.x) < FLT_EPSILON && fabs(p3.y) < FLT_EPSILON))
	{
		double r = ccpAngleSigned(Vec2(10, 0), p3);
		log("SET_DIR_BY_TWOPOINT-->r:%.2f", r);
		if (r < 0) 
			r += (FLOAT_PI * 2);
		r = r + FLOAT_PI / 8 - 0.01f;
		int quadrant = (int)(r / (FLOAT_PI / 4));
		log("SET_DIR_BY_TWOPOINT-->r:%d", quadrant);
		dir = quadrantToDir[quadrant];
		log("SET_DIR_BY_TWOPOINT-->dir:%d", dir);
	}
}

