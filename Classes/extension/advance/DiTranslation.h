//
//  DiTranslation.h
//  SanguoHeros
//
//  Created by 伟 李 on 12-11-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef SanguoHeros_DiTranslation_h
#define SanguoHeros_DiTranslation_h

#include "cocos2d.h"

USING_NS_CC;

class DiTranslation : public CCLayer
{
public:
    DiTranslation();
    virtual ~DiTranslation();
    virtual bool init();
    
    CREATE_FUNC(DiTranslation);
    
    virtual void registerWithTouchDispatcher(void);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void addDelegate(CCObject* delegate,...);
    virtual void removeDelegate(CCObject* delegate,...);
    virtual void removeAllDelegate();
    
    CC_PROPERTY(bool, m_bEnable, Enable);
protected:
    CCArray* m_pDelegates;
    CCArray* m_pBuffer;

    bool isAllParentVisible();
};

#endif
