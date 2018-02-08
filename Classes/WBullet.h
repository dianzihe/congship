//
//  WBullet.h
//  dandandao
//
//  Created by haotao on 12-3-18.
//  Copyright (c) 2012�� __MyCompanyName__. All rights reserved.
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


    ///@brief ��������
    CC_SYNTHESIZE(int,m_attack,Attack);						///< ������
    CC_SYNTHESIZE(float, m_ExplodeRadius, ExplodeRadius)	///< ��ը�뾶
    
    CC_SYNTHESIZE(int, m_SpecialType, SpecialType)			///<���⹥��Ч�� 0:���� 1:׷��
    CC_SYNTHESIZE(int, m_shootType, ShootType)				///< 0:Ͷ�� 1:���
    
    //CC_SYNTHESIZE(GameFrontLayerInterFace *,m_lpGameFrontLayer,GameFrontLayer); ///<���ڳ���
    //CC_SYNTHESIZE(WHero *,m_lpHero,Hero);					///< �ĸ���ɫ���������
    //CC_SYNTHESIZE(WGuai *,m_lpGuai,Guai);					///< �ĸ���ɫ���������
    CC_SYNTHESIZE(float, m_flyTime, FlyTime);				///< ���е�ʱ��
    CC_SYNTHESIZE(float, m_TrackRadius, TrackRadius);		//ת��Ϊ׷��ģʽ�ķ�Χ
    //CC_SYNTHESIZE(WHero *, m_targetHero, TargetHero)
    CC_SYNTHESIZE(Sprite *, m_target, Target);
    
    float m_trackTime;
    
    //����ģʽ
    CC_SYNTHESIZE(int, m_flyMode,FlyMode);
    enum
    {
            E_FLYMODE_NORMAL,	//��ͨ����ģʽ
            E_FLYMODE_TRACK,    //׷�ٷ���ģʽ
    };
    
    ParticleSystem*	m_emitter;		///< ������Ч
    int m_currentPositionIndex;		///< ��ǰ����������
    int m_prePositionIndex;			///< ǰһ������
    
    int getHurt(int radius/*,WHero *pHero*/);///< ���㵱ǰ��Ҫ�����˺�
    
    void calcHurt(Vec2 lastPositon);///< �����˺�
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
        DEF_NORMAL =0,  //һ�����
        DEF_EXPLODE,      //��ը
        DEF_FREEZE,
    } ;
    
    virtual void onEnter();
    virtual void onExit();
    
    void update(float dt);
    
    
    
};

#endif
