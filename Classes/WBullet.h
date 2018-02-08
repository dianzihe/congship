//
//  WBullet.h
//  dandandao
//
//  Created by haotao on 12-3-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef dandandao_WBullet_h
#define dandandao_WBullet_h
#include "WMover.h"
//#include "animation.h"
//#include "GameFrontLayer.h"
//#include "WHero.h"
#include "WBdefine.h"
//#include "../battle_base/WParticleSun.h"

//class WGuai;
#include "cocos2d.h"
using namespace cocos2d;
using namespace std;
class WBullet:public Sprite,public WMover
{


    ///@brief 武力属性
    CC_SYNTHESIZE(int,m_attack,Attack);						///< 攻击力
    CC_SYNTHESIZE(float, m_ExplodeRadius, ExplodeRadius)	///< 爆炸半径
    
    CC_SYNTHESIZE(int, m_SpecialType, SpecialType)			///<特殊攻击效果 0:冰冻 1:追踪
    CC_SYNTHESIZE(int, m_shootType, ShootType)				///< 0:投掷 1:射击
    
    //CC_SYNTHESIZE(GameFrontLayerInterFace *,m_lpGameFrontLayer,GameFrontLayer); ///<所在场景
    //CC_SYNTHESIZE(WHero *,m_lpHero,Hero);					///< 哪个角色发射出来的
    //CC_SYNTHESIZE(WGuai *,m_lpGuai,Guai);					///< 哪个角色发射出来的
    CC_SYNTHESIZE(float, m_flyTime, FlyTime);				///< 飞行的时长
    CC_SYNTHESIZE(float, m_TrackRadius, TrackRadius);		//转换为追踪模式的范围
    //CC_SYNTHESIZE(WHero *, m_targetHero, TargetHero)
    CC_SYNTHESIZE(Sprite *, m_target, Target);
    
    float m_trackTime;
    
    //飞行模式
    CC_SYNTHESIZE(int, m_flyMode,FlyMode);
    enum
    {
            E_FLYMODE_NORMAL,	//普通飞行模式
            E_FLYMODE_TRACK,    //追踪飞行模式
    };
    
    ParticleSystem*	m_emitter;		///< 粒子特效
    int m_currentPositionIndex;		///< 当前的坐标索引
    int m_prePositionIndex;			///< 前一个索引
    
    int getHurt(int radius/*,WHero *pHero*/);///< 计算当前需要多少伤害
    
    void calcHurt(Vec2 lastPositon);///< 计算伤害
    //virtual void draw(void);
    
    void checkChangeToTrack();
    

    
public:
	static WBullet *buildBullet(Vec2 Position,
		Vec2 speed,
		//GameFrontLayerInterFace *lpGameFrontLayer,
		//WHero *lpHero,
		int m_attack,
		int m_radius,
		bool isBigSkill);
	static WBullet *buildGuaiBullet(Vec2 Position,
		Vec2 speed,
		//GameFrontLayerInterFace *lpGameFrontLayer,
		//WGuai *lpGuai,
		int m_attack,
		int m_radius,
		bool isBigSkill);
  
    bool preCollisionPostion(int prePositionIndex,int m_currentPositionIndex,Vec2 &position);
    
    void checkCollision();
    
    bool checkCollisionHero();
    
    WBullet();
    ~WBullet();
    
    enum 
    {
        DEF_NORMAL =0,  //一般飞行
        DEF_EXPLODE,      //爆炸
        DEF_FREEZE,
    } ;
    
    virtual void onEnter();
    virtual void onExit();
    
    void update(float dt);
    
    
    
};

#endif
