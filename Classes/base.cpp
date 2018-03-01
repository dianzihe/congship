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