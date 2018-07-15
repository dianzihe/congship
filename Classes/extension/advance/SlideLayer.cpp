//
//  SlideLayer.cpp
//  SanguoHeros
//
//  Created by Nikita on 13-4-3.
//
//

#include "SlideLayer.h"
SlideLayer::SlideLayer():m_fMinStroke(100),m_fMoveDistance(200),m_tSlideType(Slide_Horizontal),m_tTouchBuffer(),m_tOldPosition(),m_bHold(false),m_tTargetPosition(),m_fMinValue(0),m_fMaxValue(512)
{
    
}

SlideLayer::~SlideLayer()
{
    
}

bool SlideLayer::init()
{
    if(!CCLayer::init())
        return false;
    setTouchEnabled(true);
    return true;
}

void SlideLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool SlideLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(isTouchInside(pTouch))
    {
        m_tTouchBuffer = getParent()->convertTouchToNodeSpace(pTouch);
        m_tTargetPosition = m_tOldPosition = getPosition();
        m_bHold = true;
        CCObject* obj = NULL;
        CCARRAY_FOREACH(getChildren(), obj)
        {
            CCTouchDelegate* delegate = dynamic_cast<CCTouchDelegate*>(obj);
            if(delegate)
                delegate->ccTouchBegan(pTouch, pEvent);
        }
        return true;
    }
    return false;
}

void SlideLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(!m_bHold)
        return;
    CCPoint buf_pos = getParent()->convertTouchToNodeSpace(pTouch);
    switch (m_tSlideType) {
        case Slide_Horizontal:
        {
            float dx = buf_pos.x - m_tTouchBuffer.x;
            setPositionX(m_tOldPosition.x + dx);
            if(dx >= m_fMinStroke)
            {
                moveRight();
            }
            else if(dx <= -m_fMinStroke)
            {
                moveLeft();
            }
            break;
        }
        case Slide_Vertical:
        {
            float dy = buf_pos.y - m_tTouchBuffer.y;
            setPositionY(m_tOldPosition.y + dy);
            if(dy >= m_fMinStroke)
            {
                moveUp();
            }
            else if(dy <= -m_fMinStroke)
            {
                moveDown();
            }
            break;
        }
    }
    CCObject* obj = NULL;
    CCARRAY_FOREACH(getChildren(), obj)
    {
        CCTouchDelegate* delegate = dynamic_cast<CCTouchDelegate*>(obj);
        if(delegate)
            delegate->ccTouchMoved(pTouch, pEvent);
    }
}

void SlideLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bHold = false;
    CCPoint p = getParent()->convertTouchToNodeSpace(pTouch);
    CCPoint delta = CCPointMake(m_tTargetPosition.x-getPosition().x, m_tTargetPosition.y-getPosition().y);
    float dis = ccpLength(delta);
    CCMoveTo* a1 = CCMoveTo::create(dis/1500, m_tTargetPosition);
//    CCEaseBounceOut* a2 = CCEaseBounceOut::create(a1);
    runAction(a1);
    float dx = fabsf(p.x - m_tTouchBuffer.x);
    float dy = fabsf(p.y - m_tTouchBuffer.y);
    bool buf = false;
    switch (m_tSlideType) {
        case Slide_Horizontal:
            if (dx < 10)
                buf = true;
            break;
        case Slide_Vertical:
            if(dy < 10)
                buf = true;
            break;
    }
    CCObject* obj = NULL;
    CCARRAY_FOREACH(getChildren(), obj)
    {
        CCTouchDelegate* delegate = dynamic_cast<CCTouchDelegate*>(obj);
        if(delegate)
        {
            if(buf)
                delegate->ccTouchEnded(pTouch, pEvent);
            else
                delegate->ccTouchCancelled(pTouch, pEvent);
        }
    }
}

void SlideLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void SlideLayer::setMinStroke(float var)
{
    m_fMinStroke = var;
}

float SlideLayer::getMinStroke()
{
    return m_fMinStroke;
}

void SlideLayer::setMoveDistance(float var)
{
    m_fMoveDistance = var;
}

float SlideLayer::getMoveDistance()
{
    return m_fMoveDistance;
}

void SlideLayer::setType(SlideType var)
{
    m_tSlideType = var;
}

SlideType SlideLayer::getType()
{
    return m_tSlideType;
}

void SlideLayer::setMinValue(float var)
{
    m_fMinValue = var;
}

float SlideLayer::getMinValue()
{
    return m_fMinValue;
}

void SlideLayer::setMaxValue(float var)
{
    m_fMaxValue = var;
}

float SlideLayer::getMaxValue()
{
    return m_fMaxValue;
}

bool SlideLayer::isTouchInside(cocos2d::CCTouch *pTouch)
{
    CCPoint touchLocation = pTouch->getLocation(); // Get the touch position
    touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
    CCRect bBox=boundingBox();
    return bBox.containsPoint(touchLocation);
}

void SlideLayer::moveLeft()
{
    m_tTargetPosition.x = m_tOldPosition.x - m_fMoveDistance;
    if(m_tTargetPosition.x < m_fMinValue)
        m_tTargetPosition.x = m_fMinValue;
}

void SlideLayer::moveRight()
{
    m_tTargetPosition.x = m_tOldPosition.x + m_fMoveDistance;
    if(m_tTargetPosition.x > m_fMaxValue)
        m_tTargetPosition.x = m_fMaxValue;
}

void SlideLayer::moveUp()
{
    m_tTargetPosition.y = m_tOldPosition.y + m_fMoveDistance;
    if(m_tTargetPosition.y > m_fMaxValue)
        m_tTargetPosition.y = m_fMaxValue;
}

void SlideLayer::moveDown()
{
    m_tTargetPosition.y = m_tOldPosition.y - m_fMoveDistance;
    if(m_tTargetPosition.y < m_fMinValue)
        m_tTargetPosition.y = m_fMinValue;
}











