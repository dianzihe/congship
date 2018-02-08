#pragma once
#include "behaviac/agent/agent.h"
#include "behaviac/agent/registermacros.h"
#include "cocos2d.h"
#include "PlaneHero.h"

USING_NS_CC;
class PlaneHero;
class Enemy;
class Hero :
    public behaviac::Agent
{
public:
	BEHAVIAC_DECLARE_AGENTTYPE(Hero, behaviac::Agent);

    Hero();
    ~Hero();

    void findAnNearestEnemy();
    bool isWillBeCrashOnNearestEnemy();
    void EscapeEnemyCrash();
    bool hasEnemyInFrontCanAttack();
    void findAnEnemyAndAttack();
	void AdjustHeroPosition(Node* hero = NULL);
	Node* getNearestEnemy(Point position);
	Node* getNearestEnemy();
	bool isWillBeCrashEnemy(Node* enemy, Point position);
	Node* getEnemyInFrontOfPosition(Point position);
	Node* findAnEnemy();
    bool wait20Frame();
    //m_isAI表示是否使用AI
    bool m_isAI;
    void setAI(bool value);
    //do Ai action automatic
    void AIAction(float level);
private:
    Enemy* nearestEnemy;
    //PlaneHero* m_plane;
	PlaneHeroPtr m_plane;
    int waitTime;
public:

	//PlaneHero* getPlane();
	PlaneHeroPtr getPlane();

	//void setPlane(PlaneHero* heroPlane);
	void setPlane(PlaneHeroPtr heroPlane);
};