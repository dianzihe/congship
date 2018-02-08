#include"WFadeOutHurtLabel.h"

WFadeOutHurtLabel::WFadeOutHurtLabel()
{

}

WFadeOutHurtLabel::~WFadeOutHurtLabel()
{

}

WFadeOutHurtLabel *WFadeOutHurtLabel::node()
{
	WFadeOutHurtLabel *pLable = new WFadeOutHurtLabel();

	pLable->init();
	pLable->autorelease();

	return pLable;
}

WFadeOutHurtLabel *WFadeOutHurtLabel::LabelWithString(CCPoint pixelpos, int hurt, int hurtLevel)
{
	WFadeOutHurtLabel *lpNode = node();

	Sprite *lpBig = NULL;
	Sprite *lpMinus = NULL;

	LabelBMFont *lpLabel = new  LabelBMFont();


	if (hurtLevel == E_SUPER)
	{
		lpBig = Sprite::createWithSpriteFrameName(DEF_SYSTEM_HUD_PATH"hit_supercoefficient_text.png");
		lpMinus = Sprite::createWithSpriteFrameName(DEF_SYSTEM_HUD_PATH"hit_supercoefficient.png");
		//lpLabel=LabelBMFont::create(itoa(hurt).c_str(), DEF_SYSTEM_HUD_PATH"hit_supercoefficient_num.png", 22/CC_CONTENT_SCALE_FACTOR(), 27/CC_CONTENT_SCALE_FACTOR(), '0');
	}
	else if (hurtLevel == E_CRIT)
	{
		lpBig = Sprite::createWithSpriteFrameName(DEF_SYSTEM_HUD_PATH"hit_coefficient_text.png");
		lpMinus = Sprite::createWithSpriteFrameName(DEF_SYSTEM_HUD_PATH"hit_coefficient.png");
		//lpLabel=CCLabelAtlas::labelWithString(itoa(hurt).c_str(), DEF_SYSTEM_HUD_PATH"hit_coefficient_num.png", 22/CC_CONTENT_SCALE_FACTOR(), 27/CC_CONTENT_SCALE_FACTOR(), '0');
	}
	else
	{
		lpMinus = Sprite::createWithSpriteFrameName(DEF_SYSTEM_HUD_PATH"hit_normal.png");
		//lpLabel=LabelAtlas::labelWithString(itoa(hurt).c_str(), DEF_SYSTEM_HUD_PATH"hit_normal_num.png", 22/CC_CONTENT_SCALE_FACTOR(), 27/CC_CONTENT_SCALE_FACTOR(), '0');
	}

	int width = 0;
	int height = 0;
	if (lpBig)
	{
		lpBig->setAnchorPoint(CCPointMake(0, 0.5));
		//lpBig->setPositionInPixels(CCPointMake(0, 0));
		//CCFadeOut *FadeOut = CCFadeOut::initWithDuration(2.0f, .0f);
		//lpBig->runAction(FadeOut);

		/*
		width+=lpBig->getContentSizeInPixels().width+5;
		height=WMAX(lpBig->getContentSizeInPixels().height, height);
		if(lpNode) lpNode->addChild(lpBig);
		*/
	}

	if (lpMinus)
	{
		/*
		lpMinus->setAnchorPoint(CCPointMake(0, 0.5));
		//lpMinus->setPositionInPixels(CCPointMake(width, 0));
		CCFadeOut *FadeOut=CCFadeOut::actionWithDuration(2.0f);
		lpMinus->runAction(FadeOut);

		width+=lpMinus->getContentSizeInPixels().width+5;
		height=WMAX(lpMinus->getContentSizeInPixels().height, height);

		if(lpNode) lpNode->addChild(lpMinus);
		*/
	}

	if (lpLabel)
	{
		/*
		lpLabel->setAnchorPoint(CCPointMake(0, 0.5));
		//lpLabel->setPositionInPixels(CCPointMake(width, 0));
		CCFadeOut *FadeOut=CCFadeOut::actionWithDuration(2.0f);
		lpLabel->runAction(FadeOut);
		width+=lpLabel->getContentSizeInPixels().width;
		height=WMAX(lpLabel->getContentSizeInPixels().height, height);

		if(lpNode) lpNode->addChild(lpLabel);
		*/
	}

	if (lpNode)
	{
		/*
		//lpNode->setContentSizeInPixels(CCSizeMake(width,height));
		lpNode->setAnchorPoint(CCPointMake(0.5, 0.5));
		lpNode->setPositionInPixels(pixelpos);

		CCMoveBy *pMoveBy=CCMoveBy::actionWithDuration(2.0f,CCPointMake(0,50*CC_CONTENT_SCALE_FACTOR()));
		lpNode->runAction(pMoveBy);
		*/
	}

	return lpNode;

}


//void WFadeOutHurtLabel::onEnter()
//{
//    CCNode::onEnter();
//    
//}
//
//void WFadeOutHurtLabel::onExit()
//{
//
//    CCLabelTTF::onExit();
//}

bool WFadeOutHurtLabel::init()
{


	return true;
}

//void WFadeOutHurtLabel::update(float dt)
//{
//  
//}