//
//  ScrollBar.h
//  SanguoHeros
//
//  Created by 伟 李 on 12-12-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef SanguoHeros_ScrollBar_h
#define SanguoHeros_ScrollBar_h

#include "cocos2d.h"

USING_NS_CC;

typedef void (CCObject::*slideBarChanged)(CCObject* sender,float percentage);
#define slidebarchanged_selector(func) (slideBarChanged)(&func)

typedef enum {Slide_Horizontal,Slide_Vertical} SlideType;

class SlideBar : public CCLayer
{
public:
    SlideBar();
    virtual ~SlideBar();
    virtual bool init();
    CREATE_FUNC(SlideBar);
    static SlideBar* createWithFrame(CCSpriteFrame* bar,CCSpriteFrame* slider,const CCSize& size);
    void initWithFrame(CCSpriteFrame* bar,CCSpriteFrame* slider,const CCSize& size);
    CC_PROPERTY(float, m_fPercentage, Percentage);
    void setChangedHandle(CCObject* target,slideBarChanged func);
    void setType(SlideType type);
    void setEnable(bool var);
    bool isEnable();
    void setSlideRegion(const CCRect& rect);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
protected:
    CCSprite* m_pBar;
    CCSprite* m_pSlider;
    CCRect m_rectSlideRegion;
    CCObject* m_pChangedHandleObject;
    slideBarChanged m_pChangedHandle;
    bool m_bTouchInside;
    SlideType m_nType;
    bool m_bEnable;
    
    bool isTouchInside(CCTouch* pTouch);
    float calculatePercentage(const CCPoint& p);
    virtual void onSlideChanged(float percentage);
};

#endif
