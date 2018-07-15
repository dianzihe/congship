//
//  SpriteButton.h
//  SanguoHeros
//
//  Created by 伟 李 on 12-11-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef SanguoHeros_SpriteButton_h
#define SanguoHeros_SpriteButton_h

#include "cocos2d.h"

USING_NS_CC;

class SpriteButton : public CCLayer,public CCRGBAProtocol
{
public:
    SpriteButton();
    virtual ~SpriteButton();
    virtual bool init();
    static SpriteButton* createWithFrame(CCSpriteFrame* frameNormal,CCSpriteFrame* frameHighlight,CCSpriteFrame* frameDisable);
    static SpriteButton* createWithSprite(CCSprite* sprite);
    CREATE_FUNC(SpriteButton);
    virtual void registerWithTouchDispatcher(void);
    // default implements are used to call script callback if exist
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    // event handle setter
    virtual void setPressedDownHandler(CCObject* object,SEL_MenuHandler handle);
    virtual void setPressedUpHandler(CCObject* object,SEL_MenuHandler handle);
    virtual void setPressedMoveInsideHandler(CCObject* object,SEL_MenuHandler handle);
    virtual void setPressedMoveOutsideHandler(CCObject* object,SEL_MenuHandler handle);
    // CCRGBAProtocol
    CC_PROPERTY(GLubyte, m_cOpacity, Opacity); 
    CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tColor, Color);
    bool m_bIsOpacityModifyRGB;
    bool isOpacityModifyRGB();
    void setOpacityModifyRGB(bool bOpacityModifyRGB);
    // frame getter
    virtual void setNormalFrame(CCSpriteFrame* frame);
    virtual CCSpriteFrame* getNormalFrame();
    virtual void setHighlightFrame(CCSpriteFrame* frame);
    virtual CCSpriteFrame* getHighlightFrame();
    virtual void setDisableFrame(CCSpriteFrame* frame);
    virtual CCSpriteFrame* getDisableFrame();
    // zoom in on highlight
    CC_PROPERTY(bool, m_bZoomInOnHighlight, ZoomInOnHighlight);
    
    virtual void cleanup();
    CC_PROPERTY(bool, m_bEnable, Enable);
    
    CC_PROPERTY(ccColor3B,m_cUnableColor,UnableColor);
protected:
    virtual void onPressedDown();
    virtual void onPressedUp();
    virtual void onPressedMoveInside();
    virtual void onPressedMoveOutside();
    virtual void onPressedCancel();
    
    virtual bool isAllParentVisible();
    
    SEL_MenuHandler m_pPressedDownHandle;
    CCObject* m_pPressedDownHandleObject;
    SEL_MenuHandler m_pPressedUpHandle;
    CCObject* m_pPressedUpHandleObject;
    SEL_MenuHandler m_pPressedMoveInsideHandle;
    CCObject* m_pPressedMoveInsideHandleObject;
    SEL_MenuHandler m_pPressedMoveOutsideHandle;
    CCObject* m_pPressedMoveOutsideHandleObject;
    
    bool m_bTouched;
    CCSpriteFrame* m_pFrameNormal;
    CCSpriteFrame* m_pFrameHighlight;
    CCSpriteFrame* m_pFrameDisable;
    CCSprite* m_pSprite;
    bool m_bSpriteMode;
    
    bool isSpriteMode();
    bool isTouchInside(CCTouch* pTouch);
    virtual void initWithFrame(CCSpriteFrame* frameNormal,CCSpriteFrame* frameHighlight,CCSpriteFrame* frameDisable);
    virtual void initWithSprite(CCSprite* sprite);
    
};

#endif
