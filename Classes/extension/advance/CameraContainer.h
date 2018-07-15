//
//  CameraContainer.h
//  HiCocos2DX
//
//  Created by Nikita on 12-9-22.
//  Copyright (c) 2012 Intelligame. All rights reserved.
//

#ifndef HiCocos2DX_CameraLayer_h
#define HiCocos2DX_CameraLayer_h

#include "cocos2d.h"

using namespace cocos2d;

static const float CAMERA_DEFAULT_SPEED = 100;

class CameraContainer : public CCNode
{
public:
    CameraContainer();
    virtual ~CameraContainer();
    virtual bool init();
    virtual void update(float delta);
    virtual void setContentSize(const CCSize & size);
    void clean();
    void setRestrainRegion(const CCPoint & min,const CCPoint & max);
    void getRestrainRegion(CCPoint & min,CCPoint & max);
    CC_PROPERTY(float, speed, Speed);
    CC_PROPERTY(CCNode*, follow_target, FollowTarget);
    CC_PROPERTY(CCPoint, focus, Focus);
    CC_PROPERTY(CCPoint, focus_point, FocusPoint);
    CC_PROPERTY(CCPoint, target_point, TargetPoint);
    NODE_FUNC(CameraContainer);
    CREATE_FUNC(CameraContainer);
    CCNode * const getContainer();
    void moveCamera(const CCPoint& dir);
protected:
    bool need_update;
    CCNode * background;
    CCPoint restrain_min_point;
    CCPoint restrain_max_point;
};

#endif
