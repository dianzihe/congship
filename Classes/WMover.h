


#ifndef _WMover_Include_file_
#define _WMover_Include_file_

#include "cocos2d.h"
//#include "Box2D.h"
//#include "WBRect.h"
using namespace cocos2d;

class WMover
{
    
    CC_SYNTHESIZE(Vec2,m_prePosition,MoverPrePosition);		///< 上一次的位置
    CC_SYNTHESIZE(Vec2,m_position, MoverPosition);			///< 当前的位置
    CC_SYNTHESIZE(Vec2,m_speed,MoverSpeed);					///< 速度
    CC_SYNTHESIZE(Vec2,m_acceleration,MoverAcceleration);	///< 加速度
    CC_SYNTHESIZE(float, m_rotate, MoverRotate);			///< 当前的旋转角度(弧度制
    CC_SYNTHESIZE(Vec2, m_center,MoverCenter);				///<中心点
	CC_SYNTHESIZE(float, m_radius, MoverRadius);			///<碰撞范围
	CC_SYNTHESIZE(int, m_collisionType, MoverCollisionType);///< 碰撞类型   

    inline Vec2 getMoverCenter()
    {
        return m_center;
    }
    
    
    enum
    {
        E_COLLISION_POINT,
        E_COLLISION_CIRCLE,
        
    };
public:
    WMover();
    
    virtual ~WMover();
    
    void updatePostion();
    
    void updatePostion(float dt);
 
    
};




#endif 