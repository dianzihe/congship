#include "WMover.h"

WMover::WMover():
m_prePosition(Vec2()),
m_position(Vec2()),
m_speed(Vec2()),
m_acceleration(Vec2()),
m_center(Vec2()),
m_radius(0),
m_rotate(0),
m_collisionType(E_COLLISION_POINT)
{
}

WMover::~WMover()
{
    
}

void WMover::updatePostion()
{
    m_speed+=m_acceleration;
  
    m_prePosition=m_position;
    m_position+=m_speed;
}

void WMover::updatePostion(float dt)
{
    m_acceleration*=dt;
    m_speed+=m_acceleration;
    m_speed*=dt;
    m_prePosition=m_position;
    m_position+=m_speed;
}
