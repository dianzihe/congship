//
//  LoadingProgressNode.cpp
//  SanguoHeros
//
//  Created by 伟 李 on 12-12-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "LoadingProgressNode.h"

LoadingProgressNode::LoadingProgressNode():m_pBackground(NULL),m_pBar(NULL),m_pFrameBackground(NULL),m_pFrameBar(NULL),m_pLoadFunc(NULL),m_pLoadFuncObject(NULL),m_pProgress(NULL),m_bStarted(false),m_fDuration(0)
{
    ignoreAnchorPointForPosition(false);
}

LoadingProgressNode::~LoadingProgressNode()
{
//    CC_SAFE_RELEASE_NULL(m_pLoadFuncObject);
    CC_SAFE_RELEASE_NULL(m_pFrameBackground);
    CC_SAFE_RELEASE_NULL(m_pFrameBar);
    CC_SAFE_RELEASE_NULL(m_pBackground);
    CC_SAFE_RELEASE_NULL(m_pBar);
    CC_SAFE_RELEASE_NULL(m_pProgress);
}

bool LoadingProgressNode::init()
{
    if(!CCLayer::init())
        return false;
    scheduleUpdate();
    return true;
}

LoadingProgressNode* LoadingProgressNode::createWithFrame(cocos2d::CCSpriteFrame *background, cocos2d::CCSpriteFrame *bar,float duration)
{
    assert(background);
    assert(bar);
    LoadingProgressNode* pRef = create();
    pRef->initWithFrame(background, bar,duration);
    return pRef;
}

void LoadingProgressNode::initWithFrame(cocos2d::CCSpriteFrame *background, cocos2d::CCSpriteFrame *bar,float duration)
{
    CC_SAFE_RETAIN(background);
    CC_SAFE_RETAIN(bar);
    m_fDuration = duration;
    m_pFrameBar = bar;
    m_pFrameBackground = background;
    m_pBackground = CCSprite::createWithSpriteFrame(m_pFrameBackground);
    m_pBar = CCSprite::createWithSpriteFrame(m_pFrameBar);
    CC_SAFE_RETAIN(m_pBackground);
    CC_SAFE_RETAIN(m_pBar);
    m_pProgress = CCProgressTimer::create(m_pBar);
    m_pProgress->setType(kCCProgressTimerTypeBar);
    m_pProgress->setMidpoint(CCPointMake(0, 0.5));
    m_pProgress->setBarChangeRate(CCPointMake(1, 0));
    CC_SAFE_RETAIN(m_pProgress);
    CCSize size = m_pBackground->getContentSize();
    setContentSize(size);
    m_pBackground->setPosition(CCPointMake(size.width/2, size.height/2));
    addChild(m_pBackground);
    m_pProgress->setPosition(CCPointMake(size.width/2, size.height/2));
    m_pProgress->setAnchorPoint(CCPointMake(0.5, 0.5));
    addChild(m_pProgress);
}

void LoadingProgressNode::setLoadHandle(cocos2d::CCObject *target, loadFunc func)
{
//    CC_SAFE_RELEASE_NULL(m_pLoadFuncObject);
//    CC_SAFE_RETAIN(target);
    m_pLoadFuncObject = target;
    m_pLoadFunc = func;
}

void LoadingProgressNode::start()
{
    assert(!m_bStarted);
    m_bStarted = true;
    m_pProgress->setPercentage(0);
    CCProgressTo* action = CCProgressTo::create(m_fDuration, 100);
    m_pProgress->runAction(action);
}

void LoadingProgressNode::update(float dt)
{
    if(!m_bStarted)
        return;
    if(m_pLoadFuncObject)
    {
        (m_pLoadFuncObject->*m_pLoadFunc)(m_pProgress->getPercentage());
    }
}