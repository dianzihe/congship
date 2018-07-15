//
//  NumberBox.h
//  SpaceWarriors
//
//  Created by Nikita on 13-7-17.
//
//

#ifndef SpaceWarriors_NumberBox_h
#define SpaceWarriors_NumberBox_h

#include "cocos2d.h"

USING_NS_CC;

class UILoadingi : public CCLabelAtlas
{
public:
    UILoadingi();
    virtual ~ UILoadingi();
    virtual bool init();
    CREATE_FUNC(UILoadingi);
    static UILoadingi * create(const char *string, const char *charMapFile, unsigned int itemWidth, unsigned int itemHeight, unsigned int startCharMap,bool showX);
    
    int getValue();
    void setValue(int num,bool force);
    void update(float dt);
    
    CC_SYNTHESIZE(bool, m_bZoomInOnChange, ZoomInOnNumberChange);
    CC_SYNTHESIZE(float, m_fRate, Rate);
protected:
    int m_nValue;
    float m_fCurrentValue;
    bool m_bShowXSymbol;
    float m_fDelta;

    void refreshNumber(int num);
};

#endif
