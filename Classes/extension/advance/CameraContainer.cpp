//
//  CameraContainer.cpp
//  HiCocos2DX
//
//  Created by Nikita on 12-9-22.
//  Copyright (c) 2012年 Intelligame. All rights reserved.
//

#include <iostream>
#include "CameraContainer.h"

using namespace cocos2d;

CameraContainer::CameraContainer() : speed(CAMERA_DEFAULT_SPEED),focus(0.5,0.5),target_point(0,0),follow_target(NULL),restrain_min_point(-5000,-5000),restrain_max_point(5000,5000)
{
    
}

CameraContainer::~CameraContainer()
{
    
}

bool CameraContainer::init()
{
    background = CCNode::create();
    background->setAnchorPoint(CCPointMake(0, 0));
    addChild(background);
    scheduleUpdate();
    return true;
}

void CameraContainer::setSpeed(float var)
{
    CC_ASSERT(!var);
    speed = var;
}

float CameraContainer::getSpeed()
{
    return speed;
}

void CameraContainer::setFollowTarget(cocos2d::CCNode *target)
{
    follow_target = target;
    need_update = true;
}

CCNode * CameraContainer::getFollowTarget()
{
    return follow_target;
}

void CameraContainer::setFocusPoint(cocos2d::CCPoint var)
{
    focus_point = var;
    need_update = true;
}

CCPoint CameraContainer::getFocusPoint(){
    return focus_point;
}

void CameraContainer::setFocus(CCPoint var)
{
    focus = var;
    setFocusPoint(CCPointMake(focus.x*this->getContentSize().width, focus.y*getContentSize().height));
}

CCPoint CameraContainer::getFocus()
{
    return focus;
}

void CameraContainer::setTargetPoint(CCPoint var)
{
    target_point = var;
    follow_target = NULL;
    need_update = true;
}

CCPoint CameraContainer::getTargetPoint()
{
    return target_point;
}

void CameraContainer::update(float delta)
{
    if(follow_target)
    {
        CCPoint p1 = follow_target->getParent()->convertToWorldSpace(follow_target->getPosition());
        CCPoint p2 = convertToWorldSpace(focus_point);
        CCPoint dir = ccpNeg(ccpSub(p1, p2));
        moveCamera(dir);
    }
}

void CameraContainer::moveCamera(const cocos2d::CCPoint& dir)
{
    if(dir.x || dir.y)
    {
        float nx = background->getPositionX() + dir.x;
        float ny = background->getPositionY() + dir.y;
        float restrain_width = restrain_max_point.x-restrain_min_point.x;
        float restrain_height = restrain_max_point.y - restrain_min_point.y;
        //边界约束检测
        if(restrain_width <= getContentSize().width)
        {
            nx = (getContentSize().width - restrain_width)/2 - restrain_min_point.x;
        }
        else{
            if(nx > -restrain_min_point.x)
                nx = -restrain_min_point.x;
            if(nx < - restrain_max_point.x + getContentSize().width)
                nx = - restrain_max_point.x + getContentSize().width;
        }
        if(restrain_height <= getContentSize().height)
        {
            ny = (getContentSize().height - restrain_height)/2 - restrain_min_point.y;
        }
        else{
            if(ny > -restrain_min_point.y)
                ny = -restrain_min_point.y;
            if(ny < - restrain_max_point.y + getContentSize().height)
                ny = - restrain_max_point.y + getContentSize().height;
        }
        background->setPosition(CCPointMake(nx, ny));
    }
}

void CameraContainer::clean()
{
    follow_target = NULL;
}

void CameraContainer::setContentSize(const CCSize &size)
{
    CCNode::setContentSize(size);
    setFocusPoint(CCPointMake(getContentSize().width*focus.x, getContentSize().height*focus.y));
    need_update = true;
}

//void CameraContainer::setContentSizeInPixels(const CCSize &size)
//{
//    CCNode::setContentSizeInPixels(size);
//    setFocusPoint(CCPointMake(getContentSize().width*focus.x, getContentSize().height*focus.y));
//    need_update = true;
//}

CCNode * const CameraContainer::getContainer()
{
    return background;
}

void CameraContainer::setRestrainRegion(const CCPoint & min, const CCPoint & max)
{
    CC_ASSERT(min.x < max.x && min.y < max.y);
    restrain_min_point = min;
    restrain_max_point = max;
}

void CameraContainer::getRestrainRegion(CCPoint &min, CCPoint &max)
{
    min = restrain_min_point;
    max = restrain_max_point;
}

