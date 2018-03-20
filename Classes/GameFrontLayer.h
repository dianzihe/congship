//
//  GameFrontLayer.h
//  dangdangtang
//
//  Created by haotao on 11-12-1.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#ifndef dangdangtang_GameFrontLayer_h
#define dangdangtang_GameFrontLayer_h


#include "WHero.h"
//#include "../battle_base/WTouches.h"

#include "WBEvent.h"
//#include "net.h"
//#include "../battle_base/WBPixelByte.h"
#include "GameFrontLayerInterFace.h"

//class BattleScene;
//class WMap;

class GameFrontLayer:public GameFrontLayerInterFace
 {
 
    CC_SYNTHESIZE(Scene *, m_BattleScene, BattleScene);
    

   
   // CC_SYNTHESIZE(int,m_currentHero,CurrentHero);   //当前轮到这个角色操作
    //WCharacter *m_myHeroCircle;
    
    
 protected:   
  
    
    
    enum
    {
        EVENT_ERROR=-1,
        EVENT_MOVE_PLAYER=0, //移动角色
        EVENT_DEATH,
        EVENT_USE_SKILL_ITEM,                    //使用指定技能道具
        EVENT_SHOOT,                                  //射击
        EVENT_FLY,//飞行
        EVENT_BIGSKILL,                                //使用大招
        EVENT_ROUND_PASS,                        //跳过这一回合
        EVENT_NEXT_ROUND,                       //下一个人
        EVENT_WAIT_NEW_SQUE,                 //等待新的序列
        EVENT_UPDATE_ANGRYVALUE,        //更新怒气值
        EVENT_WAITNEXTROUND,                //等行进入下一回合
        EVENT_GAMEOVER,                           //游戏结束
        EVENT_REBORN,                                //重生
        EVENT_PLAYER_LOST,                       //玩家掉线
       
        
        
        EVENT_SCR_NORMAL,
        EVENT_SCR_ZOOM_TO_HERO,     
        EVENT_SCR_FOLLOW_BULLET,
        EVENT_SCR_FOLLOW_HERO,
        EVENT_SCR_CENTER_TO_HERO_NOW,
        EVENT_SCR_ZOOM_OUT,
        
    };
    
    typedef struct
    {
        int value;
        int playerid;
    }UPDATE_ANGYVALUE;
    
    typedef struct
    {
        int playerid; //角色id
        int itemid;
    }USE_SKILL_ITEM;
    
    
    typedef struct
    {
        Vec2 startPos;
        int playerId;
        int leftOrRight;
        int times;
    }PLAYERMOVE;

  
    
    bool isShootingNow;
    
    bool m_wasHudOpen;
    
  
    /**
     * @brief 处理事件
     */
    void processEvent(); 
    
    
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

    
    
    //gamestatus
    enum
    {
        E_SCR_NORMAL,       //可以随便移动屏幕,不是自己时不有操作
        E_SCR_SHOOTTING,  //射击中检测要不要跟随
        E_SCR_WAIT_FOR_NEXT_ROUND,//等待进入下一轮
        E_SCR_ZOOM_TO_HERO,//不能做任何操作,如果自己点屏时,可以停止缩放
        E_SCR_FOLLOW_BULLET,//跟踪炮弹
        E_SCR_FOLLOW_HERO,//跟踪当前英雄位置
        E_SCR_SPRING, //震荡
        E_SCR_CENTER_TO_HERO_NOW, //马上对准角色
        E_SCR_ZOOM_OUT,
        E_SCR_NONE,
    };
  
 
     
    //WTouches *m_lpTouches;
    
    bool m_lockForHud;
    
    float m_dt;
    
     float m_waitForNextRoundTime;
    
    enum
    {
        E_TS_NONE=0,
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
    
    
    
    
    
    bool getStartSpeedPowerWithSpeedNormal( Vec2 &speedNormal, Vec2 &startPos,
                                            Vec2 &endPos,float &power);
                                            
     bool getStartSpeedNormal(Vec2 &startPos,
                              Vec2 &endPos,Vec2 &SpeedNormal);
     bool getStartSpeedNormal2(Vec2 &startPos,
                              Vec2 &endPos,Vec2 &SpeedNormal);
                              
     WHero *getDistanceLessVsHero(WHero *myHero);
     WHero *getHpLessVsHero(WHero *myHero);
     WHero *getPreTargetVsHero(WHero *myHero);
     WHero *getRandVsHero(WHero *myHero);
    
public:

     virtual void updateHud();
     
   
	 /*
    void SendMsgShoot(const CCPoint &startPos,const Vec2 &speed,int face);
    void SendMsgUpdateAngryValue(int playerid,int value);
    void SendMsgUseSkill(int playerid,int itemid);
    void SendMsgDeath(int playerid);
    void SendMsgNextRound();
    void SendMsgPassRound();
    void SendMsgFly(const CCPoint &startPos,const Vec2 &speed,int face);
    void SendMsgUseBigSkill();
    void SendMsgCenterToHero();
    void SendMsgReborn(BATTLE_PlayerReborn *pReborn);
    
    void SendMsgPlayerLost(const vector<int> &playerIds);
    
    void SendMsgMoverPlayer(int playerId,const Vec2 &startPos,int leftOrRight,int times);
    void SendMsgGameOver();
    */
    
    
    
    /**
     * @brief 网络协议的处理
     */
    //static void OnNetWork(ProtocolReader* pProtocolReader, void* pThis);
    
    
    WHero *GetCurrentHero();
    
    WHero *GetOldHero();
    
    
     
    //void LoadMap(WMap *pMap);
    //void testLoadMap(WMap *pMap);
    void BuildHero();
    
    virtual void onEnter();
    virtual void onExit();

    void update(float dt);
  
  
    int m_AIstatus; //智能状态    
    void AICtrl();
    
    void checkTouch();
    void processTouch();
    
    void processScrean();
    
    void setWindLevel();
    
      GameFrontLayer();
    ~GameFrontLayer();
    
    
    static void onSelfLost(void *data,int msg,int param1,int param2);

    
};

#endif
