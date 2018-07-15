//
//  DiTranslation.cpp
//  SanguoHeros
//
//  Created by 伟 李 on 12-11-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "DiTranslation.h"

DiTranslation::DiTranslation():m_pDelegates(NULL),m_pBuffer(NULL),m_bEnable(true)
{
    m_pDelegates = new CCArray();
    m_pBuffer = new CCArray();
}

DiTranslation::~DiTranslation()
{
    CC_SAFE_RELEASE_NULL(m_pDelegates);
    CC_SAFE_RELEASE_NULL(m_pBuffer);
}

bool DiTranslation::init()
{
    if(!CCLayer::init())
        return false;
    setTouchEnabled(true);
    return true;
}

void DiTranslation::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -99, true);
}

bool DiTranslation::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(!m_bEnable)
        return false;
    if(!isAllParentVisible())
        return false;
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pDelegates, pObj)
    {
        CCTouchDelegate* delegate = dynamic_cast<CCTouchDelegate*>(pObj);
        if(delegate)
        {
            assert(delegate != this);
            if(delegate->ccTouchBegan(pTouch, pEvent))
            {
                m_pBuffer->addObject(pObj);
            }
        }
    }
    return true;
}

void DiTranslation::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pBuffer, pObj)
    {
        CCTouchDelegate* delegate = dynamic_cast<CCTouchDelegate*>(pObj);
        if(delegate)
        {
            delegate->ccTouchMoved(pTouch, pEvent);
        }
    }
}

void DiTranslation::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pBuffer, pObj)
    {
        CCTouchDelegate* delegate = dynamic_cast<CCTouchDelegate*>(pObj);
        if(delegate)
        {
            delegate->ccTouchEnded(pTouch, pEvent);
        }
    }
    m_pBuffer->removeAllObjects();
}

void DiTranslation::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pBuffer, pObj)
    {
        CCTouchDelegate* delegate = dynamic_cast<CCTouchDelegate*>(pObj);
        if(delegate)
        {
            delegate->ccTouchCancelled(pTouch, pEvent);
        }
    }
    m_pBuffer->removeAllObjects();
}

void DiTranslation::addDelegate(CCObject* delegate, ...)
{
    assert(delegate);
    va_list params;
    va_start(params, delegate);
    CCObject* next = delegate;
    do 
    {
        if(!m_pDelegates->containsObject(next) && dynamic_cast<CCTouchDelegate*>(next))
        {
            assert(next != this);
            m_pDelegates->addObject(next);
        }
        next = va_arg(params, CCObject*);
    } while (next);
    va_end(params);
}

void DiTranslation::removeDelegate(cocos2d::CCObject *delegate, ...)
{
    assert(delegate);
    va_list params;
    va_start(params, delegate);
    CCObject* next = delegate;
    do 
    {
        if(m_pDelegates->containsObject(next) && dynamic_cast<CCTouchDelegate*>(next))
        {
            m_pDelegates->removeObject(next);
        }
        next = va_arg(params, CCObject*);
    } while (next);
    va_end(params);
}

void DiTranslation::removeAllDelegate()
{
    m_pDelegates->removeAllObjects();
}

void DiTranslation::setEnable(bool var)
{
    m_bEnable = var;
}

bool DiTranslation::getEnable()
{
    return m_bEnable;
}

bool DiTranslation::isAllParentVisible()
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


















