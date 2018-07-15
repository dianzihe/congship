//
//  LoadingProgressNode.h
//  SanguoHeros
//
//  Created by 伟 李 on 12-12-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef SanguoHeros_LoadingProgressNode_h
#define SanguoHeros_LoadingProgressNode_h

#include "cocos2d.h"

USING_NS_CC;

typedef void (CCObject::*loadFunc)(float percent);
#define loadFunc_selector(func) (loadFunc)(&func)
#define loadStep(var,value,percent) if(percent >= value && var < value && (var = value))

class LoadingProgressNode : public CCLayer
{
public:
    LoadingProgressNode();
    virtual ~LoadingProgressNode();
    virtual bool init();
    CREATE_FUNC(LoadingProgressNode);
    static LoadingProgressNode* createWithFrame(CCSpriteFrame* background,CCSpriteFrame* bar,float duration);
    void setLoadHandle(CCObject* target,loadFunc func);
    void start();
    virtual void update(float dt);
protected:
    CCSpriteFrame* m_pFrameBackground;
    CCSpriteFrame* m_pFrameBar;
    CCSprite* m_pBackground;
    CCSprite* m_pBar;
    CCObject* m_pLoadFuncObject;
    loadFunc m_pLoadFunc;
    CCProgressTimer* m_pProgress;
    bool m_bStarted;
    float m_fDuration;
    
    virtual void initWithFrame(CCSpriteFrame* background,CCSpriteFrame* bar,float duration);
};

#endif
