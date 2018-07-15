//
//  NumberBox.cpp
//  SpaceWarriors
//
//  Created by Nikita on 13-7-17.
//
//

#include "UILoadingi.h"

UILoadingi::UILoadingi():m_nValue(0),m_bShowXSymbol(false),m_bZoomInOnChange(false),m_fRate(100),m_fDelta(0),m_fCurrentValue(0)
{
    
}

UILoadingi::~UILoadingi()
{
    
}

bool UILoadingi::init()
{
    scheduleUpdate();
    return true;
}

UILoadingi* UILoadingi::create(const char *string, const char *charMapFile, unsigned int itemWidth, unsigned int itemHeight, unsigned int startCharMap,bool showX)
{
    UILoadingi* re = create();
    re->initWithString(string, charMapFile, itemWidth, itemHeight, startCharMap);
    re->m_bShowXSymbol = showX;
    re->setValue(0, true);
    return re;
}

void UILoadingi::setValue(int var,bool force)
{
    m_nValue = var;
    if(force)
    {
        m_fCurrentValue = var;
        refreshNumber((int)m_fCurrentValue);
    }
    else
    {
        if (m_bZoomInOnChange)
        {
            CCScaleTo* a1 = CCScaleTo::create(0.2, 1.1);
            CCScaleTo* a2 = CCScaleTo::create(0.2, 1);
            CCFiniteTimeAction* a3 = CCSequence::create(a1,a2,NULL);
            runAction(a3);
        }
    }
    m_fDelta = m_nValue - m_fCurrentValue;
}

int UILoadingi::getValue()
{
    return m_nValue;
}

void UILoadingi::refreshNumber(int num)
{
    CCString* buf = NULL;
    if(m_bShowXSymbol)
        buf = CCString::createWithFormat(":%d",num);
    else
        buf = CCString::createWithFormat("%d",num);
    setString(buf->getCString());
}

void UILoadingi::update(float dt)
{
    if(m_nValue == m_fCurrentValue)
        return;
    float buf = m_fRate * dt;
    m_fCurrentValue += (m_fDelta > 0 ? buf : -buf);
    if(m_fDelta < 0)
    {
        if(m_fCurrentValue < m_nValue)
            m_fCurrentValue = m_nValue;
    }
    else
    {
        if(m_fCurrentValue > m_nValue)
            m_fCurrentValue = m_nValue;
    }
    refreshNumber((int)m_fCurrentValue);
}
