//
//  BossGameFrontLayer.h
//  dangdangtang
//
//  Created by haotao on 11-12-1.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#ifndef dangdangtang_BossGameFrontLayer_h
#define dangdangtang_BossGameFrontLayer_h
#include "GameFrontLayerInterFace.h"
/*
#include "WBossHero.h"
#include "../battle_base/WTouches.h"

#include "../battle_base/WBEvent.h"
#include "net.h"
#include "../battle_base/WBPixelByte.h"
#include "../battle_base/GameFrontLayerInterFace.h"
#include "WBoss3_Shield.h"
#include "WBoss3_1.h"
#include "WBoss3_2.h"
*/
//class BossBattleScene;
//class WMap;

class BossGameFrontLayer :public GameFrontLayerInterFace
{

	//CC_SYNTHESIZE(BossBattleScene *, m_BattleScene, BattleScene);
	CC_SYNTHESIZE(Scene *, m_BattleScene, BattleScene);


	// CC_SYNTHESIZE(int,m_currentHero,CurrentHero);   //当前轮到这个角色操作
	//WCharacter *m_myHeroCircle;

	CC_SYNTHESIZE(bool, m_isGameOver, IsGameOver)
protected:



	enum
	{
		EVENT_ERROR = -1,
		EVENT_MOVE_PLAYER = 0, //移动角色
		EVENT_DEATH,
		EVENT_USE_SKILL_ITEM,                    //使用指定技能道具
		EVENT_SHOOT,                                  //射击
		EVENT_FLY,//飞行
		EVENT_BIGSKILL,                                //使用大招
		EVENT_ROUND_PASS,                        //跳过这一回合
		EVENT_NEXT_ROUND,                       //下一个人
		EVENT_UPDATE_ANGRYVALUE,        //更新怒气值
		EVENT_WAITNEXTROUND,                //等行进入下一回合
		EVENT_GAMEOVER,                           //游戏结束
		EVENT_REBORN,                                //重生
		EVENT_PLAYER_LOST,                       //玩家掉线
		EVENT_BUILDGUAI,                            //生成怪
		EVENT_TRANSFORM, //变身


		EVENT_SCR_NORMAL,
		EVENT_SCR_ZOOM_TO_HERO,
		EVENT_SCR_FOLLOW_BULLET,
		EVENT_SCR_FOLLOW_HERO,
		EVENT_SCR_CENTER_TO_HERO_NOW,
		EVENT_SCR_ZOOM_OUT,
		EVENT_SCR_ZOOM_TO_BOSS,
		EVENT_SCR_ZOOM_TO_MELEE,
		EVENT_SCR_FOLLOW_MELEE,

		EVENT_SCR_ZOOM_TO_TARGET, // 对准目标角色
		EVENT_SCR_BOSS3_ZOOM_OUT,
		EVENT_SCR_PLAYER_GET_SHIELD, // 玩家获得护盾效果
		EVENT_SCR_PLAYER_LOSS_SHIELD, // 玩家失去护盾效果

	};

	typedef struct
	{
		int playerOrGuai;
		int value;
		int playerid;
	}UPDATE_ANGYVALUE;

	typedef struct
	{
		int playerOrGuai;
		int playerid; //角色id
		int itemid;
	}USE_SKILL_ITEM;


	typedef struct
	{
		Vec2 startPos;
		int playerOrGuai;
		int playerId;
		int leftOrRight;
		int times;
	}PLAYERMOVE;


	bool isShootingNow;
	int m_greateExplodeZoomToHero; //大boss放超必时需要把镜头移向被打角色位置

	bool m_wasHudOpen;

	/**
	 * @brief 处理事件
	 */
	void processEvent();

	//void SendMsgTransform(BOSSMAPBATTLE_OtherChange *pChange);

public:

	bool getStartSpeedPowerWithSpeedNormal(Vec2 &speedNormal, Vec2 &startPos,
		Vec2 &endPos, float &power);
	bool getStartSpeedNormal(Vec2 &startPos,
		Vec2 &endPos, Vec2 &SpeedNormal);
	bool getStartSpeedNormal2(Vec2 &startPos,
		Vec2 &endPos, Vec2 &SpeedNormal);
	// void processCurrentEvent(); 
private:

	int m_screan_status;

	void checkBulletCount();

	bool m_showisyourturn;
	void setSpring(CCPoint targetPosition);
	bool m_showRoundNum;


	float m_SpringTime;
	float m_SpringDistance;
	CCPoint m_SpringPosition;
	CCPoint m_TargetPosition;
	float    m_SpringUpDown;

	bool m_zoomTobullet;

	CCPoint m_meleeCenter;
	float m_meleeScale;

	//gamestatus
	enum
	{
		E_SCR_NORMAL,       //可以随便移动屏幕,不是自己时不有操作
		E_SCR_SHOOTTING,  //射击中检测要不要跟随
		E_SCR_WAIT_FOR_NEXT_ROUND,//等待进入下一轮
		E_SCR_ZOOM_TO_HERO,//不能做任何操作,如果自己点屏时,可以停止缩放
		E_SCR_FOLLOW_BULLET,//跟踪炮弹
		E_SCR_FOLLOW_HERO,//跟踪当前英雄位置
		E_SCR_ZOOM_TO_BOSS,
		E_SCR_ZOOM_TO_MELEE,
		E_SCR_FOLLOW_MELEE,
		E_SCR_SPRING, //震荡
		E_SCR_CENTER_TO_HERO_NOW, //马上对准角色
		E_SCR_ZOOM_OUT,
		E_SCR_NONE,
		E_SCR_ZOOM_TO_TARGET, // 对准指定目标角色
		E_SCR_ZOOM_OUT_BOSS3,
	};



	//WTouches *m_lpTouches;

	bool m_lockForHud;

	float m_dt;

	enum
	{
		E_TS_NONE = 0,
		E_TS_ZOOM,
		E_TS_MOVE_SCREAN,
		E_TS_MOVE_PLAYER,
		E_TS_PLAYER_SHOOT,
		E_TS_DONT_TOUCH
	};
	int m_touch_status; //现在处理哪个触摸模式下


	float playermove_press_time;
	CCPoint playermove_press_point;

	CCPoint screanmove_LastPoint;

	float m_normalscale;
	float m_lastScale;
	CCPoint m_lastScrCenterPoint;

	float m_screanLockTime;

	CCPoint m_shootPressPoint;
	Vec2   m_currentHeroPoint;

	//  bool canNextRound;

	int m_RoundNum;

	CCPoint m_zoomTargetPos;








	/*
	WBossHero *getDistanceLessVsHero(WBossHero *myHero);
	WBossHero *getHpLessVsHero(WBossHero *myHero);
	WBossHero *getPreTargetVsHero(WBossHero *myHero);
	WBossHero *getRandVsHero(WBossHero *myHero);
	*/
public:


	virtual void updateHud();


	/*
   void SendMsgShoot(const CCPoint &startPos,const Vec2 &speed,int face);
   void SendMsgUpdateAngryValue(int playerOrGuai,int playerid,int value);
   void SendMsgUseSkill(int playerOrGuai,int playerid,int itemid);
   void SendMsgDeath(int playerOrGuai,int playerid);
   void SendMsgNextRound();
   void SendMsgPassRound();
   void SendMsgFly(const CCPoint &startPos,const Vec2 &speed,int face);
   void SendMsgUseBigSkill();
   void SendMsgCenterToHero();
   void SendMsgReborn(BOSSMAPBATTLE_PlayerReborn *pReborn);
   void SendMsgBuildGuai(BOSSMAPBATTLE_OtherBuildGuai *pBuildGuai);

   void SendMsgPlayerLost(const vector<int> &playerIds);

   void SendMsgMoverPlayer(int playerOrGuai,int playerId,const Vec2 &startPos,int leftOrRight,int times);

   void SendMsgZoomToTarget(int iTargetId);
   void SendMsgNormal();

   void SendMsgGameOver();

   void EndCurrentMsg();
   */



	/**
	 * @brief 网络协议的处理
	 */
	/*
	static void OnNetWork(ProtocolReader* pProtocolReader, void* pThis);


	WChara *GetCurrentChara();

	WChara *GetOldChara();

	WChara *GetCharaById(int iid);



	void LoadMap(WMap *pMap);
	void testLoadMap(WMap *pMap);
	*/
	void BuildHero();

	virtual void onEnter();
	virtual void onExit();

	void update(float dt);


	int m_AIstatusForPlayer; //智能状态    
	void AICtrlForPlayer();

	void checkTouch();
	void processTouch();

	void processScrean();

	void setWindLevel();

	BossGameFrontLayer();
	~BossGameFrontLayer();


	static void onSelfLost(void *data, int msg, int param1, int param2);

	void startNewRound();

	//void bossStartProcess(WChara *lpChara);

	int getMeleeGuaiCount();
	int getRangedGuaiCount();
	int getGuaiCount();

	//WChara *getWillDieInGreateExplode();

	// Added By Mrj, For Boss3, Start
#if OPEN_BOSSMAP_3
public:
	void SendMsgPlayerGetShield();
	void SendMsgPlayerLossShield();
	void Boss3GetPowerEnd();

protected:
	void castBoss3Skill(vector<WBossHero*>& rTargets);
	void castBoss31Skill_PowerUp(bool isShow = false);
	void castBoss32Skill_ChangePos(vector<WBossHero*>& rTargets);
	void showBoss3Shield(bool isShow);
	void Boss3GettingAnim();
	void getPowerAnimCallBack();
	WBoss3_Shield* BuildBoss3Shield();
	Vec2 getRandPosition(int randNum);

	WBoss3_1* getBoss31();
	WBoss3_2* getBoss32();

	int             m_roundOfCastPowerUp; // 上一次出现小球的回合
	int             m_roundOfGetShield; // 玩家上一次获得盾的回合
	bool            m_castPowerUp;     // 出现小球，下个BOSS回合，BOSS攻击力2.5倍
	bool            m_bossGetPowerUp;  // BOSS是否吸收过小球，用来控制光球消失
	bool            m_playerGetShieldRound; // 是否经过了玩家吸收盾的回合
	// 以上3个字段用来控制BOSS技能的出现和消失
	int             m_iBoss3EndGetPowerCount;
	cwSngSprite*    m_boss3PowerBall;
	cwSngSprite*    m_boss3_1ball;
	cwSngSprite*    m_boss3_2ball;
	WBoss3_Shield*  m_boss3Shied;
#endif
	// Added By Mrj, For Boss3, End
};

#endif
