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
