//
//  MathHelper.h
//  SpaceWarriors
//
//  Created by Nikita on 13-6-13.
//
//

#ifndef SpaceWarriors_MathHelper_h
#define SpaceWarriors_MathHelper_h

#include "cocos2d.h"

USING_NS_CC;

class MathHelper
{
public:
    inline static float getAngle(const CCPoint& target,const CCPoint& origin)
    {
        CCPoint sub = ccpSub(target, origin);
        return getAngle(sub);
    }
    
    inline static float getAngle(const CCPoint& sub)
    {
        float angle = atan2f(sub.y,sub.x);
        return angle;
    }
    
    inline static float Degrees_CW2CCW(float angle)
    {
        float re = - fmodf(angle, 360.0f);
        if(re < 0)
            re += 360;
        return re;
    }

    inline static float Degrees_CCW2CW(float angle)
    {
        float re = - fmodf(angle, 360.0f);
        if(re < 0)
            re += 360;
        return re;
    }
};

#endif
