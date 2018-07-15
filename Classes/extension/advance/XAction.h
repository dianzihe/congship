//
//  XAction.h
//  SanguoHeros
//
//  Created by 伟 李 on 13-1-15.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef SanguoHeros_XAction_h
#define SanguoHeros_XAction_h

#include "cocos2d.h"

USING_NS_CC;

class RemoveSelfAndClean : public CCActionInstant
{
public:
    RemoveSelfAndClean(){}
    virtual ~RemoveSelfAndClean(){}
    //super methods
    virtual void update(float time);
    virtual CCFiniteTimeAction * reverse(void);
    virtual CCObject* copyWithZone(CCZone *pZone);
public:
    //override static method
    /** Allocates and initializes the action 
     @deprecated: This interface will be deprecated sooner or later.
     */
    CC_DEPRECATED_ATTRIBUTE static RemoveSelfAndClean * action();
    
    /** Allocates and initializes the action */
    static RemoveSelfAndClean * create();
};

#endif
