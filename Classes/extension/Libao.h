#pragma once

#include "cocos2d.h"
#include "extension/advance/DiTranslation.h"
#include "extension/advance/SpriteButton.h"
#include "extension/advance/UILoadingi.h"
USING_NS_CC;
class GeneralDialog;
class Libao : public DiTranslation
{
	//CC_SYNTHESIZE(bool, m_bUpdateNext, UpdateNext);
public:
	Libao();
	virtual ~Libao();
	virtual bool init();
	static Libao* create(GeneralDialog *obj);
	
	virtual void update(float dt);
private:
	UILoadingi* m_pCoinsValue;
	UILoadingi* m_pZuanShiValue;

	int m_nCurSelectN;
	GeneralDialog* m_pHandleObject;
	SpriteButton* buy1; 
	SpriteButton* buy2;
	SpriteButton* buy3;
	SpriteButton* buy4;
	SpriteButton* buy5;
	CCSprite* m_pTextInfo;
	SpriteButton* m_pBuyBtn;
	CCSprite* m_pHasBuy;

	void onSelectPressed(CCObject* obj);
	void onBuyPressed(CCObject* obj);
	void onReturnPressed(CCObject* obj);
};