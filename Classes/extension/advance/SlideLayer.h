//
//  SlideLayer.h
//  SanguoHeros
//
//  Created by Nikita on 13-4-3.
//
//

#ifndef SanguoHeros_SlideLayer_h
#define SanguoHeros_SlideLayer_h

#include "cocos2d.h"
#include "SlideBar.h"

USING_NS_CC;

class SlideLayer : public CCLayer
{
public:
    SlideLayer();
    virtual ~ SlideLayer();
    virtual bool init();
    CREATE_FUNC(SlideLayer);

    // default implements are used to call script callback if exist
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);

    CC_PROPERTY(float, m_fMinStroke, MinStroke);
    CC_PROPERTY(float, m_fMoveDistance, MoveDistance);
    CC_PROPERTY(SlideType, m_tSlideType, Type);
    CC_PROPERTY(float, m_fMinValue, MinValue);
    CC_PROPERTY(float, m_fMaxValue, MaxValue);
    
    bool isTouchInside(CCTouch* pTouch);
protected:
    CCPoint m_tTouchBuffer;
    CCPoint m_tOldPosition;
    CCPoint m_tTargetPosition;
    bool m_bHold;
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
};

#endif
