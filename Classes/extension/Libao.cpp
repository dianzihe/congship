#include "Libao.h"
#include "extension/advance/SpriteButton.h"
#include "UISetLayerb.h"
#include "extension/advance/UILoadingi.h"
#include "JniMethods.h"
#include "MusicHelper.h"
#include "PayID.h"
#include "GeneralDialog.h"
#include "MusicHelper.h"
#include "StageScene.h"
#include "HelpShieldLayer.h"
#include "JniMethods.h"
#include "PayID.h"
#include "GameTask.h"
#include "towcoms.h"
Libao::Libao() 
{
	//UISetLayerb::shared()->setUIDialogLiBao(this);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(DATADECODE_ADDHEAD("pic/ui_store1.plist"), DATADECODE_ADDHEAD("pic/ui_store1.png"));
}

Libao::~Libao()
{
	//UISetLayerb::shared()->setUIDialogLiBao(NULL);
}
Libao * Libao::create(GeneralDialog *obj)
{
	Libao *l=new Libao();
	if (l && l->init()) 
	{ 
		l->m_pHandleObject=obj;
		l->autorelease(); 
		return l; 
	} 
	else 
	{ 
		delete l; 
		l = NULL; 
		return NULL; 
	} 
}
bool Libao::init()
{
	if (!DiTranslation::init())
	{
		return false;
	}
	this->scheduleUpdate();

	CCLog("1");

	CCLayerColor* colorlayer = CCLayerColor::create(ccc4(0,0,0,200));
	colorlayer->setContentSize(CCSizeMake(900, 600));
	colorlayer->ignoreAnchorPointForPosition(false);
	colorlayer->setAnchorPoint(ccp(0.5, 0.5));
	colorlayer->setPosition(ccp(400, 240));
	addChild(colorlayer, -2);

	this->runAction(CCSequence::create(CCScaleTo::create(0.1f,1.03f),CCScaleTo::create(0.1f,0.98f),CCScaleTo::create(0.1f,1),NULL));

	CCSprite* bg = CCSprite::createWithSpriteFrameName("jf_bg.png");
	bg->setPosition(ccp(400, 240));
	this->addChild(bg, -1);

	CCSprite* jinbiIcon = CCSprite::createWithSpriteFrameName("icon_jinbi.png");
	jinbiIcon->setPosition(ccp(136, 480 - 75));
	this->addChild(jinbiIcon, 1);
	CCSprite* icon_zhuanshi = CCSprite::createWithSpriteFrameName("icon_zhuanshi.png");
	icon_zhuanshi->setPosition(ccp(309.5, 480 - 75));
	this->addChild(icon_zhuanshi, 1);

	CCLog("2");

	SpriteButton* m_pBtReturn = SpriteButton::createWithFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("jf_an_fanhui.png"),NULL,NULL);
	m_pBtReturn->setZoomInOnHighlight(true);
	m_pBtReturn->setPosition(ccp( 643, 480 - 76.5));
	m_pBtReturn->setPressedUpHandler(this,menu_selector(Libao::onReturnPressed));
	addChild(m_pBtReturn, 3);

	m_pCoinsValue = UILoadingi::create("09", DATADECODE_ADDHEAD("pic/zi_11x16.png"), 11, 16, '0', false);
	m_pCoinsValue->setAnchorPoint(ccp(0, 1));
	m_pCoinsValue->setPosition(ccp(154, 480 - 69));
	this->addChild(m_pCoinsValue, 2);

	m_pZuanShiValue = UILoadingi::create("09", DATADECODE_ADDHEAD("pic/zi_11x16_lan.png"), 11, 16, '0', false);
	m_pZuanShiValue->setAnchorPoint(ccp(0, 1));
	m_pZuanShiValue->setPosition(ccp(332, 480 - 69));
	this->addChild(m_pZuanShiValue, 2);

	buy1=SpriteButton::createWithSprite(CCSprite::spriteWithFile("extension/libao1.png"));
	//buy1 = SpriteButton::createWithFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("6822.png"),NULL,NULL);
	buy1->setTag(1);
	buy1->setZoomInOnHighlight(true);
	buy1->setPosition(ccp( 212, 480 - 211));
	buy1->setPressedUpHandler(this,menu_selector(Libao::onSelectPressed));
	addChild(buy1, 3);

	buy2=SpriteButton::createWithSprite(CCSprite::spriteWithFile("extension/libao2.png"));
	//buy2 = SpriteButton::createWithFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("pai_th.png"),NULL,NULL);
	buy2->setTag(2);
	buy2->setZoomInOnHighlight(true);
	buy2->setPosition(ccp( 406, 480 - 161));
	buy2->setPressedUpHandler(this,menu_selector(Libao::onSelectPressed));
	addChild(buy2, 3);
	
	buy3=SpriteButton::createWithSprite(CCSprite::spriteWithFile("extension/libao3.png"));
	//buy3 = SpriteButton::createWithFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("pai_nzuanshi.png"),NULL,NULL);
#if (OPERATORS_WAY == OPERATORS_JIDI_JIANGSHI)
	buy3 = SpriteButton::createWithFrame(
		CCSpriteFrame::create("jiangshibixusi_and/pai_nzuanshi.png", CCRectMake(0, 0, 178, 100)),
		NULL,NULL);
#endif
	buy3->setTag(3);
	buy3->setZoomInOnHighlight(true);
	buy3->setPosition(ccp( 587, 480 - 161));
	buy3->setPressedUpHandler(this,menu_selector(Libao::onSelectPressed));
	addChild(buy3, 3);

	buy4=SpriteButton::createWithSprite(CCSprite::spriteWithFile("extension/libao4.png"));
	//buy4 = SpriteButton::createWithFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("pai_jinbao.png"),NULL,NULL);
#if (OPERATORS_WAY == OPERATORS_JIDI_JIANGSHI)
	buy4 = SpriteButton::createWithFrame(
		CCSpriteFrame::create("jiangshibixusi_and/pai_jinbao.png", CCRectMake(0, 0, 178, 100)),
		NULL,NULL);
#endif
	buy4->setTag(4);
	buy4->setZoomInOnHighlight(true);
	buy4->setPosition(ccp( 406, 480 - 262));
	buy4->setPressedUpHandler(this,menu_selector(Libao::onSelectPressed));
	addChild(buy4, 3);

	buy5=SpriteButton::createWithSprite(CCSprite::spriteWithFile("extension/libao5.png"));
	//buy5 = SpriteButton::createWithFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("pai_zhwz.png"),NULL,NULL);
	buy5->setTag(5);
	buy5->setZoomInOnHighlight(true);
	buy5->setPosition(ccp( 587, 480 - 262));
	buy5->setPressedUpHandler(this,menu_selector(Libao::onSelectPressed));
	addChild(buy5, 3);


	CCLog("3");

	m_pTextInfo = CCSprite::createWithSpriteFrameName("pai_hjq02.png");
	m_pTextInfo->setPosition(ccp(311.5f, 480 - 377.5f));
	this->addChild(m_pTextInfo, 2);


	m_pBuyBtn = SpriteButton::createWithSprite(CCSprite::createWithSpriteFrameName("an_lingqu.png"));
	//m_pBuyBtn = SpriteButton::createWithFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("an_lingqu.png"),NULL,NULL);
	m_pBuyBtn->setZoomInOnHighlight(true);
	m_pBuyBtn->setPosition(ccp( 601, 480 - 370.5f ));
	m_pBuyBtn->setPressedUpHandler(this,menu_selector(Libao::onBuyPressed));
	addChild(m_pBuyBtn, 3);

	this->addDelegate(m_pBtReturn, m_pBuyBtn, buy1, buy2, buy3, buy4, buy5, NULL);
	CCLog("4");
	return true;
}

void Libao::onSelectPressed( CCObject* obj )
{
	CCNode* node = dynamic_cast<CCNode*>(obj);
	int tag = node->getTag();

	this->m_nCurSelectN = tag;

}

void Libao::onBuyPressed( CCObject* obj )
{
	int buyindex=0;
	switch(m_nCurSelectN)
	{
	case 1:
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//JniMethods::iapRequest(PAYID_BUYJIATELIN);
		buyindex=0;
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		//UISetLayerb::shared()->iapResultSuccess(PAYID_BUYJIATELIN);
		// 		towcoms *tow=towcoms::create(0);
		// 		addChild(tow);
		buyindex=0;
#endif
		break;
	case 2:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//JniMethods::iapRequest(PAYID_BUYCOINSFULI);
		buyindex=10;
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		//UISetLayerb::shared()->iapResultSuccess(PAYID_BUYCOINSFULI);
		buyindex=10;
#endif
		break;
	case 3:
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//JniMethods::iapRequest(PAYID_BUY240DIAMOND);
		buyindex=11;
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		//UISetLayerb::shared()->iapResultSuccess(PAYID_BUY240DIAMOND);
		buyindex=11;
#endif
		break;
	case 4:
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//JniMethods::iapRequest(PAYID_BUYGIFTJINGBAO);
		buyindex=12;
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		//UISetLayerb::shared()->iapResultSuccess(PAYID_BUYGIFTJINGBAO);
		buyindex=12;
#endif
		break;
	case 5:
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//JniMethods::iapRequest(PAYID_BUYGIFTZHANHUO);
		buyindex=13;
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		//UISetLayerb::shared()->iapResultSuccess(PAYID_BUYGIFTZHANHUO);
		buyindex=13;
#endif
		break;
	}
	towcoms *tow=towcoms::create(buyindex,this);
	addChild(tow,20000,8787);
}

void Libao::update( float dt )
{
// 	if (m_bUpdateNext)
// 	{
// 		//m_bUpdateNext = false;
// 	} else 
// 	{
// 		return;
// 	}
	if (UISetLayerb::shared()->openWIndow == 8787 )
	{
		UISetLayerb::shared()->openWIndow = 0;
		removeChildByTag(8787,true);
	}
	switch (m_nCurSelectN)
	{
	case 1:
		m_pBuyBtn->setVisible(true);
		//m_pHasBuy->setVisible(false);
		m_pTextInfo->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("pai_hjq02.png"));
		break;
	case 2:
		{
			int i = 0;
			if (OPERATORS_WAY == OPERATORS_MMLOW)
			{
				i = 3;
			}
			// 			if (UISetLayerb::shared()->giftInfo[i] == 0)
			// 			{
			m_pBuyBtn->setVisible(true);
			//m_pHasBuy->setVisible(false);
			// 			} else 
			// 			{
			// 				m_pBuyBtn->setVisible(true);
			// 				m_pHasBuy->setVisible(true);
			// 			}
			m_pTextInfo->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("pai_th02.png"));
		}
		break;
	case 3:
		m_pBuyBtn->setVisible(true);
		//m_pHasBuy->setVisible(false);
		m_pTextInfo->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("pai_zuanshi_02.png"));

#if (OPERATORS_WAY == OPERATORS_JIDI_JIANGSHI)
		m_pTextInfo->setDisplayFrame( CCSpriteFrame::create("jiangshibixusi_and/pai_zuanshi_02.png", CCRectMake(0, 0, 361, 67)) );
#endif

		break;
	case 4:
		// 		if (UISetLayerb::shared()->giftInfo[1] == 0)
		// 		{
		m_pBuyBtn->setVisible(true);
		//m_pHasBuy->setVisible(false);
		// 		} else 
		// 		{
		// 			m_pBuyBtn->setVisible(false);
		// 			m_pHasBuy->setVisible(true);
		//}
		m_pTextInfo->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("pai_jinbao02.png"));
		break;
	case 5:
		// 		if (UISetLayerb::shared()->giftInfo[2] == 0)
		// 		{
		m_pBuyBtn->setVisible(true);
		//m_pHasBuy->setVisible(false);
		// 		} else 
		// 		{
		// 			m_pBuyBtn->setVisible(false);
		// 			m_pHasBuy->setVisible(true);
		/*		}*/
		m_pTextInfo->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("pai_zhwz02.png"));
		break;
	}

	m_pCoinsValue->setValue(UISetLayerb::shared()->getCoinsValue(), true);
	m_pZuanShiValue->setValue(UISetLayerb::shared()->getZuanValue(), true);
}

void Libao::onReturnPressed( CCObject* obj )
{
	this->removeFromParentAndCleanup(true);
	MusicHelper::shared()->playEffect(SAE_COMMON_EFFECT_BUTTONCLICK, false);
	m_pHandleObject->onNextLive();
}
