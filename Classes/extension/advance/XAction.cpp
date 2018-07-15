//
//  XAction.cpp
//  SanguoHeros
//
//  Created by 伟 李 on 13-1-15.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "XAction.h"

//
// RemoveSelf
//
RemoveSelfAndClean * RemoveSelfAndClean::action() 
{
    return RemoveSelfAndClean::create();
}

RemoveSelfAndClean * RemoveSelfAndClean::create() 
{
    RemoveSelfAndClean *pRet = new RemoveSelfAndClean();
    
    if (pRet) {
        pRet->autorelease();
    }
    
    return pRet;
}

void RemoveSelfAndClean::update(float time) {
    CC_UNUSED_PARAM(time);
    m_pTarget->getParent()->removeChild(m_pTarget, true);
}

CCFiniteTimeAction *RemoveSelfAndClean::reverse() {
    return NULL;
}

CCObject* RemoveSelfAndClean::copyWithZone(CCZone *pZone) {
    CCZone *pNewZone = NULL;
    RemoveSelfAndClean *pRet = NULL;
    
    if (pZone && pZone->m_pCopyObject) {
        pRet = (RemoveSelfAndClean*) (pZone->m_pCopyObject);
    } else {
        pRet = new RemoveSelfAndClean();
        pZone = pNewZone = new CCZone(pRet);
    }
    
    CCActionInstant::copyWithZone(pZone);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}
