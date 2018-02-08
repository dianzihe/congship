#include "behaviac/agent/agent.h"
#include "behaviac/agent/registermacros.h"
#pragma once

class PlaneEnemy;
class NPC : public behaviac::Agent
{
public:
	BEHAVIAC_DECLARE_AGENTTYPE(NPC, behaviac::Agent);

    //typedef struct  refresh_delay
    //{
    int level0_daly;
    int level1_daly;
    int level2_daly;
    int level3_daly;
    int level4_daly;
    //    void reset()
    //    {

    //    }

    //    DECLARE_BEHAVIAC_OBJECT_STRUCT(NPC::refresh_delay);
    //}refresh_delay_type;

    //level��������ķ���
	int  Level1Up_Score;
	int  Level2Up_Score;
	int  Level3Up_Score;
	int  Level4Up_Score;
    NPC();
    ~NPC();
    NPC(void* parent);
    void initData();
    void spawnEnemy();
    void* getParent();
    // set NPC parent
    void setParent(const void* parent);
    void setLeveUpScore(int level, int score);
    int getGameLevel();
    // set the game current level
    int getLevel(int score);

    //create method for behaviac
    void Update();
	//const char* (*enemyBrain)(Projectile* s);

private:
    void* m_parent;
   
public:

    bool m_canBossRefresh;
    int m_level;
	behaviac::vector<int> delayTime;
	//int delayTime;
};
