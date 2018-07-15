//
//  ScrollBar.cpp
//  SanguoHeros
//
//  Created by 伟 李 on 12-12-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "SlideBar.h"

SlideBar::SlideBar():m_fPercentage(0),m_nType(Slide_Horizontal),m_pBar(NULL),m_pSlider(NULL),m_pChangedHandleObject(NULL),m_pChangedHandle(NULL),m_bTouchInside(false),m_bEnable(true)
{
    ignoreAnchorPointForPosition(false);
}

SlideBar::~SlideBar()
{
    
}

bool SlideBar::init()
{
    if(!CCLayer::init())
        return false;
    setTouchEnabled(true);
    return true;
}

SlideBar* SlideBar::createWithFrame(cocos2d::CCSpriteFrame *bar, cocos2d::CCSpriteFrame *slider,const CCSize& size)
{
    assert(bar);
    assert(slider);
    SlideBar* pRef = create();
    pRef->initWithFrame(bar, slider,size);
    return pRef;
}

void SlideBar::initWithFrame(cocos2d::CCSpriteFrame *bar, cocos2d::CCSpriteFrame *slider,const CCSize& size)
{
    m_pBar = CCSprite::createWithSpriteFrame(bar);
    setContentSize(size);
    m_pBar->setAnchorPoint(CCPointMake(0.5, 0.5));
    m_pBar->setPosition(CCPointMake(size.width/2, size.height/2));
    addChild(m_pBar);
    m_pSlider = CCSprite::createWithSpriteFrame(slider);
    m_pSlider->setAnchorPoint(CCPointMake(0.5, 0.5));
    addChild(m_pSlider);
    m_rectSlideRegion = CCRectMake(0, 0, size.width, size.height);
    setType(Slide_Horizontal);
}

void SlideBar::setPercentage(float var)
{
    if(var < 0)
        var = 0;
    if(var > 1)
        var = 1;
    if(m_fPercentage != var)
    {
        onSlideChanged(var);
    }
    m_fPercentage = var;
    CCSize size = m_rectSlideRegion.size;
    CCPoint origin = m_rectSlideRegion.origin;
    if(m_nType == Slide_Horizontal)
    {
        m_pSlider->setPosition(CCPointMake(origin.x+size.width*var, origin.y+size.height/2));
    }
    else if(m_nType == Slide_Vertical)
    {
        m_pSlider->setPosition(CCPointMake(origin.x+size.width/2, origin.y+size.height*var));
    }
}

float SlideBar::getPercentage()
{
    return m_fPercentage;
}

bool SlideBar::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bTouchInside = isTouchInside(pTouch);
    if(!m_bEnable || !m_bTouchInside)
        return false;
    float percentage = calculatePercentage(convertTouchToNodeSpace(pTouch));
    setPercentage(percentage);
    return true;
}

void SlideBar::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(!m_bTouchInside)
        return;
    float percentage = calculatePercentage(convertTouchToNodeSpace(pTouch));
    setPercentage(percentage);
}

void SlideBar::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(!m_bTouchInside)
        return;
    float percentage = calculatePercentage(convertTouchToNodeSpace(pTouch));
    setPercentage(percentage);
}

void SlideBar::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 2, true);
}

void SlideBar::setChangedHandle(cocos2d::CCObject *target, slideBarChanged func)
{
    m_pChangedHandleObject = target;
    m_pChangedHandle = func;
}

bool SlideBar::isTouchInside(cocos2d::CCTouch *pTouch)
{
    CCPoint touchLocation = pTouch->getLocation(); // Get the touch position
    touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
    CCRect bBox=boundingBox();
    return bBox.containsPoint(touchLocation);
}

void SlideBar::setType(SlideType type)
{
    m_nType = type;
    setPercentage(m_fPercentage);
}


void SlideBar::setEnable(bool var)
{
    m_bEnable = var;
}

bool SlideBar::isEnable()
{
    return m_bEnable;
}

float SlideBar::calculatePercentage(const cocos2d::CCPoint &p)
{
    float re = 0;
    CCSize size = m_rectSlideRegion.size;
    CCPoint origin = m_rectSlideRegion.origin;
    if(m_nType == Slide_Horizontal)
    {
        if(p.x < origin.x)
            re = 0;
        else if(p.x > origin.x + size.width)
            re = 1;
        else
            re = (p.x - origin.x) / size.width;
    }
    else if(m_nType == Slide_Vertical)
    {
        if(p.y < origin.y)
            re = 0;
        else if(p.y > origin.y + size.height)
            re = 1;
        else
            re = (p.y-origin.y) / size.height;
    }
    return re;
}

void SlideBar::onSlideChanged(float percentage)
{
    if(m_pChangedHandleObject)
    {
        (m_pChangedHandleObject->*m_pChangedHandle)(this,percentage);
    }
}

void SlideBar::setSlideRegion(const cocos2d::CCRect &rect)
{
    m_rectSlideRegion = rect;
    setPercentage(m_fPercentage);
}























