//
//  SpriteButton.cpp
//  SanguoHeros
//
//  Created by 伟 李 on 12-11-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "SpriteButton.h"

SpriteButton::SpriteButton():m_pFrameNormal(NULL),m_pFrameHighlight(NULL),m_pFrameDisable(NULL),m_bIsOpacityModifyRGB(false),m_bTouched(false),m_pPressedUpHandle(NULL),m_pPressedUpHandleObject(NULL),m_pPressedMoveInsideHandle(NULL),m_pPressedMoveInsideHandleObject(NULL),m_pPressedMoveOutsideHandle(NULL),m_pPressedMoveOutsideHandleObject(NULL),m_pPressedDownHandle(NULL),m_pPressedDownHandleObject(NULL),m_pSprite(NULL),m_bZoomInOnHighlight(false),m_bEnable(true),m_cOpacity(0), m_tColor(ccBLACK),m_bSpriteMode(false)
{
    ccColor3B color = {128,128,128};
    setUnableColor(color);
}

SpriteButton::~SpriteButton()
{
    CC_SAFE_RELEASE_NULL(m_pFrameDisable);
    CC_SAFE_RELEASE_NULL(m_pFrameHighlight); 
    CC_SAFE_RELEASE_NULL(m_pFrameNormal);
}

void SpriteButton::cleanup()
{
    CCLayer::cleanup();
//    CC_SAFE_RELEASE_NULL(m_pPressedDownHandleObject);
//    CC_SAFE_RELEASE_NULL(m_pPressedUpHandleObject);
//    CC_SAFE_RELEASE_NULL(m_pPressedMoveInsideHandleObject);
//    CC_SAFE_RELEASE_NULL(m_pPressedMoveOutsideHandleObject);
}

bool SpriteButton::init()
{
    if(!CCLayer::init())
        return false;
    setTouchEnabled(true);
    ignoreAnchorPointForPosition(false);
    return true;
}

void SpriteButton::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 2, true);
}

SpriteButton* SpriteButton::createWithFrame(cocos2d::CCSpriteFrame *frameNormal, cocos2d::CCSpriteFrame *frameHighlight, cocos2d::CCSpriteFrame *frameDisable)
{
    assert(frameNormal);
    SpriteButton* pRef = create();
    pRef->m_bSpriteMode = false;
    pRef->initWithFrame(frameNormal, frameHighlight, frameDisable);
    return pRef;
}

SpriteButton* SpriteButton::createWithSprite(cocos2d::CCSprite *sprite)
{
    CCAssert(sprite, "SpriteButton::createWithSprite(sprite)-sprite cannot be null!");
    SpriteButton* pRef = create();
    pRef->m_bSpriteMode = true;
    pRef->initWithSprite(sprite);
    return pRef;
}

void SpriteButton::initWithFrame(cocos2d::CCSpriteFrame *frameNormal, cocos2d::CCSpriteFrame *frameHighlight, cocos2d::CCSpriteFrame *frameDisable)
{
    CCAssert(frameNormal, "normal frame cannot be null!");
    m_pFrameNormal = frameNormal;
    m_pFrameHighlight = frameHighlight;
    m_pFrameDisable = frameDisable;
    CC_SAFE_RETAIN(m_pFrameNormal);
    CC_SAFE_RETAIN(m_pFrameHighlight);
    CC_SAFE_RETAIN(m_pFrameDisable);
    m_pSprite = CCSprite::createWithSpriteFrame(m_pFrameNormal);
    CCSize size = m_pSprite->getContentSize();
    setContentSize(size);
    m_pSprite->setPosition(CCPointMake(size.width/2,size.height/2));
    addChild(m_pSprite);
}

void SpriteButton::initWithSprite(cocos2d::CCSprite *sprite)
{
    m_pSprite = sprite;
    CCSize size = m_pSprite->getContentSize();
    setContentSize(size);
    m_pSprite->setPosition(CCPointMake(size.width/2, size.height/2));
    addChild(m_pSprite);
}

void SpriteButton::setPressedDownHandler(cocos2d::CCObject *object, SEL_MenuHandler handle)
{
//    CC_SAFE_RELEASE_NULL(m_pPressedDownHandleObject);
    m_pPressedDownHandleObject = object;
//    CC_SAFE_RETAIN(m_pPressedDownHandleObject);
    m_pPressedDownHandle = handle;
}

void SpriteButton::setPressedUpHandler(cocos2d::CCObject *object, SEL_MenuHandler handle)
{
//    CC_SAFE_RELEASE_NULL(m_pPressedUpHandleObject);
    m_pPressedUpHandleObject = object;
//    CC_SAFE_RETAIN(m_pPressedUpHandleObject);
    m_pPressedUpHandle = handle;
}

void SpriteButton::setPressedMoveInsideHandler(cocos2d::CCObject *object, SEL_MenuHandler handle)
{
//    CC_SAFE_RELEASE_NULL(m_pPressedMoveInsideHandleObject);
    m_pPressedMoveInsideHandleObject = object;
//    CC_SAFE_RETAIN(m_pPressedMoveInsideHandleObject);
    m_pPressedMoveInsideHandle = handle;
}

void SpriteButton::setPressedMoveOutsideHandler(cocos2d::CCObject *object, SEL_MenuHandler handle)
{
//    CC_SAFE_RELEASE_NULL(m_pPressedMoveOutsideHandleObject);
    m_pPressedMoveOutsideHandleObject = object;
//    CC_SAFE_RETAIN(m_pPressedMoveOutsideHandleObject);
    m_pPressedMoveOutsideHandle = handle;
}

bool SpriteButton::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bTouched = false;
    if(!m_bEnable)
        return false;
    if(!isVisible())
        return false;
    if(!isAllParentVisible())
        return false;
    if(!isTouchInside(pTouch))
        return false;
    m_bTouched = true;
    onPressedDown();
    if(m_bZoomInOnHighlight)
    {
        CCScaleTo* action = CCScaleTo::create(0.1, 1.1);
        runAction(action);
    }
    return true;
}

void SpriteButton::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(!m_bTouched)
        return;
    bool inside = isTouchInside(pTouch);
    if(inside)
    {
        onPressedMoveInside();
    }
    else 
    {
        onPressedMoveOutside();
    }
}

void SpriteButton::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(!m_bTouched)
        return;
	
	/*if (!isTouchInside(pTouch))
	{
		if(m_bZoomInOnHighlight || getScale() > 1)
		{
			CCScaleTo* action = CCScaleTo::create(0.1, 1.0);
			runAction(action);
		}
		return;
	}*/

    onPressedUp();
    if(m_bZoomInOnHighlight || getScale() > 1)
    {
        CCScaleTo* action = CCScaleTo::create(0.1, 1.0);
        runAction(action);
    }
}

void SpriteButton::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(!m_bTouched)
        return;
    onPressedCancel();
}

bool SpriteButton::isTouchInside(cocos2d::CCTouch *pTouch)
{
    CCPoint touchLocation = pTouch->getLocation(); // Get the touch position
    touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
    CCRect bBox=boundingBox();
    return bBox.containsPoint(touchLocation);
}

void SpriteButton::onPressedDown()
{
    if(!m_bSpriteMode && m_pFrameHighlight)
    {
        m_pSprite->setDisplayFrame(m_pFrameHighlight);
    }
    if(m_pPressedDownHandleObject)
    {
        (m_pPressedDownHandleObject->*m_pPressedDownHandle)(this);
    }
}

void SpriteButton::onPressedMoveInside()
{
    if(m_pPressedMoveInsideHandleObject)
    {
        (m_pPressedMoveInsideHandleObject->*m_pPressedMoveInsideHandle)(this);
    }
}

void SpriteButton::onPressedMoveOutside()
{
    if(m_pPressedMoveOutsideHandleObject)
    {
        (m_pPressedMoveOutsideHandleObject->*m_pPressedMoveOutsideHandle)(this);
    }
}

void SpriteButton::onPressedUp()
{
    if(!m_bSpriteMode)
        m_pSprite->setDisplayFrame(m_pFrameNormal);
    if(m_pPressedUpHandleObject)
    {
        (m_pPressedUpHandleObject->*m_pPressedUpHandle)(this);
    }
}

void SpriteButton::onPressedCancel()
{
    m_bTouched = false;
    if(!m_bSpriteMode)
        m_pSprite->setDisplayFrame(m_pFrameNormal);
    setScale(1.0);
}

void SpriteButton::setZoomInOnHighlight(bool var)
{
    m_bZoomInOnHighlight = var;
}

bool SpriteButton::getZoomInOnHighlight()
{
    return m_bZoomInOnHighlight;
}

void SpriteButton::setEnable(bool var)
{
    if(m_bEnable == var)
        return;
    m_bEnable = var;
    if(m_bEnable)
    {
        if(!m_bSpriteMode)
            m_pSprite->setDisplayFrame(m_pFrameNormal);
        setColor(ccWHITE);
    }
    else
    {
        if(m_pFrameDisable)
        {
            if(!m_bSpriteMode)
                m_pSprite->setDisplayFrame(m_pFrameDisable);
        }
        else
        {
            ccColor3B color = m_cUnableColor;
            setColor(color);
        }
    }
}

bool SpriteButton::getEnable()
{
    return m_bEnable;
}

//CRGBA protocol
void SpriteButton::setColor(const ccColor3B& color)
{
    m_tColor=color;
    CCObject* child;
    CCArray* children=getChildren();
    CCARRAY_FOREACH(children, child)
    {
        CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);        
        if (pNode)
        {
            pNode->setColor(m_tColor);
        }
    }
}

const ccColor3B& SpriteButton::getColor(void)
{
    return m_tColor;
}


void SpriteButton::setOpacity(GLubyte opacity)
{
    m_cOpacity = opacity;
    
    CCObject* child;
    CCArray* children=getChildren();
    CCARRAY_FOREACH(children, child)
    {
        CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);        
        if (pNode)
        {
            pNode->setOpacity(opacity);
        }
    }
    
}

GLubyte SpriteButton::getOpacity()
{
    return m_cOpacity;
}


void SpriteButton::setOpacityModifyRGB(bool bOpacityModifyRGB)
{
    m_bIsOpacityModifyRGB=bOpacityModifyRGB;
    CCObject* child;
    CCArray* children=getChildren();
    CCARRAY_FOREACH(children, child)
    {
        CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);        
        if (pNode)
        {
            pNode->setOpacityModifyRGB(bOpacityModifyRGB);
        }
    }
}

bool SpriteButton::isOpacityModifyRGB()
{
    return m_bIsOpacityModifyRGB;
}

void SpriteButton::setNormalFrame(cocos2d::CCSpriteFrame *frame)
{
    CC_SAFE_RETAIN(frame);
    CC_SAFE_RELEASE_NULL(m_pFrameNormal);
    m_pFrameNormal = frame;
    m_pSprite->setDisplayFrame(m_pFrameNormal);
}

CCSpriteFrame* SpriteButton::getNormalFrame()
{
    return m_pFrameNormal;
}

void SpriteButton::setHighlightFrame(cocos2d::CCSpriteFrame *frame)
{
    CC_SAFE_RETAIN(frame);
    CC_SAFE_RELEASE_NULL(m_pFrameHighlight);
    m_pFrameHighlight = frame;
}

CCSpriteFrame* SpriteButton::getHighlightFrame()
{
    return m_pFrameHighlight;
}

void SpriteButton::setDisableFrame(cocos2d::CCSpriteFrame *frame)
{
    CC_SAFE_RETAIN(frame);
    CC_SAFE_RELEASE_NULL(m_pFrameDisable);
    m_pFrameDisable = frame;
}

CCSpriteFrame* SpriteButton::getDisableFrame()
{
    return m_pFrameDisable;
}

bool SpriteButton::isAllParentVisible()
{
    CCNode* parent = getParent();
    while (parent) 
    {
        if(parent->isVisible())
        {
            parent = parent->getParent();
        }
        else 
        {
            return false;
        }
    }
    return true;
}

void SpriteButton::setUnableColor(ccColor3B color)
{
    m_cUnableColor = color;
}

ccColor3B SpriteButton::getUnableColor()
{
    return m_cUnableColor;
}

bool SpriteButton::isSpriteMode()
{
    return m_bSpriteMode;
}