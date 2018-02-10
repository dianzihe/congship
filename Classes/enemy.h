#pragma once

//#include "behaviac_generated/types/behaviac_types.h"
#include "behaviac/behaviac.h"
#include "cocos2d.h"
USING_NS_CC;
class PlaneEnemy;
class Enemy : public behaviac::Agent
{
public:
	BEHAVIAC_DECLARE_AGENTTYPE(Enemy, behaviac::Agent);

    Enemy();
    Enemy(int type);

    ~Enemy();

    void createAnEnemyWithType(int type);

    PlaneEnemy* getPlane();//get plane
    void setPlane(Node* heroPlane);

    void setSpeed(float speed);
    float getSpeed();

    int getEnemyType();
    float getRandomSpeedByInitSpeed(float initSpeed);
    void init();

    bool isAlive();
	void m1();
private:
    Node* nearestEnemy;
    PlaneEnemy* m_plane;
	
public:
    float speed;
	int enemyType;
	float initSpeed; 
	float randomSpeed;
	behaviac::vector<float> m_init_speed;
};