
#ifndef _WHero_include_file_
#define _WHero_include_file_

#include <vector>
#include "cocos2d.h"
//#include "animation.h"   
#include "WBdefine.h"
#include "WMover.h"
#include "WBEvent.h"

/*
#include "../battle_base/WBItem.h"
#include "../battle_base/WShopCharacter.h"
#include "../battle_base/WBWeaponSkill.h"
*/
//#include "WTeach.h"

//class GameFrontNewTeachLayer;
//class GameFrontLayer;
//class GameFrontTeachLayer;

using namespace std;
using namespace cocos2d;

class CAICombination
{
public:
    vector<char> skills;
    vector<char> items;
    
    vector<char*> attack_plan;
    vector<char*> assistant_plan;
    ~CAICombination()
    {
        for(int i=0; i<attack_plan.size(); i++)
        {
            delete attack_plan[i];
        }
        
        for(int i=0; i<assistant_plan.size(); i++)
        {
            delete assistant_plan[i];
        }
    }
};



class WHero:public Sprite,public WMover
{
	map<int, Animation *> *m_lpAnimationDict;  ///<动作集
	CC_SYNTHESIZE(int, m_animationStatus, AnimationStatus); ///<动画状态
	CC_SYNTHESIZE(bool, m_isShowAchorPoint, IsShowAchorPoint);
private:
	Animation *m_lpCurrentAnimationNode;  ///< 当前使用的动画
	CCAction *m_lpCurrentAnimationAction; ///< 当前使用的动画动作

    CC_SYNTHESIZE(bool, m_loseNet,LoseNet);//玩家已经掉线
   
    float m_dt; //时间保存,方便读取
    
    bool m_IsInit;  ///< 是否已经初始化
    
    ///@brief 基本属性
    CC_SYNTHESIZE(int, m_RoomId, RoomId);                    ///< 原来房间id
    CC_SYNTHESIZE(int, m_PlayerId, PlayerId);                     ///< 当前的角色id
    CC_SYNTHESIZE(int, m_BattleId, BattleId);                     ///< 对战
    CC_SYNTHESIZE_PASS_BY_REF(string, m_PlayerName, PlayerName); ///< 角色名称
    CC_SYNTHESIZE(int, m_Level, Level);                             ///< 角色等级
    CC_SYNTHESIZE(int, m_boyOrGirl,BoyOrGirl);               ///< 男还是女
    CC_SYNTHESIZE(int, m_Camp, Camp);                           ///< 属于哪一方的
    CC_SYNTHESIZE(int, m_CampPosition, CampPosition);
    CC_SYNTHESIZE(int,m_maxHP,MaxHP)                          ///<  最大生命值
    CC_SYNTHESIZE(int,m_maxPF,MaxPF)                           ///<  最大体力
    CC_SYNTHESIZE(int,m_maxSP,MaxSP)                           ///<  最大怒气值
    
    CC_SYNTHESIZE(int, m_ctrlType,CtrlType);  ///< 控制类型 0:自己 1:别人 2:AI
    
    
    CC_SYNTHESIZE_PASS_BY_REF(string, m_title, Title); ///< 称号
    CC_SYNTHESIZE_PASS_BY_REF(string, m_community, Community); ///<公会名称
    
    ///@brief 武力属性
    CC_SYNTHESIZE(int,m_attack,Attack)                                                  ///< 普通攻击力
    CC_SYNTHESIZE(int,m_BigSkillAttack,BigSkillAttack)                 ///< 爆击攻击力
    CC_SYNTHESIZE(int,m_CriticalhitAttackRate,CriticalhitAttackRate)                 ///< 爆击攻击陪数
    CC_SYNTHESIZE(int,m_defence,Defence)                                            ///< 防御力
    CC_SYNTHESIZE(int, m_BigSkillType, BigSkillType) ///大招类型
    
    ///@brief 基本动态属性
    CC_SYNTHESIZE(int,m_HP,HP)                    ///<  生命值
    CC_SYNTHESIZE(int,m_SP,SP)                      ///<  怒气值
    CC_SYNTHESIZE(float,m_PF,PF)                      ///<  体力
    CC_SYNTHESIZE(bool, m_isDead, IsDead)  ///< 死了吗
    
    
    ///@brief 攻击属性
    CC_SYNTHESIZE(bool,m_isCriticalhit,IsCriticalHit)                     ///< 是否爆击
    CC_SYNTHESIZE(float,m_AttackMultiple, AttackMultiple)     ///< 攻击力的陪数
    CC_SYNTHESIZE(int,m_AttackTimes,AttackTimes)                     ///< 攻击的次数
    CC_SYNTHESIZE(int,m_AttackDivideNum,AttackDivideNum)    ///< 分裂的数量
    CC_SYNTHESIZE(int, m_bulletSpecialType, BulletSpecialType) //使的特殊技能 0:冰冻 1:追踪 2:原子弹
    CC_SYNTHESIZE(bool, m_isBigSkill, IsBigSkill)                            ///< 是否大招
    CC_SYNTHESIZE(bool, m_fly, Fly) ///< 是否飞行
    CC_SYNTHESIZE(bool, m_isItemFly, IsItemFly)
    CC_SYNTHESIZE(bool, m_isFreeze, IsFreeze)
    CC_SYNTHESIZE(int, m_FreezeLastRound, FreezeLastRound)
    CC_SYNTHESIZE(int, m_FlyLockLastRound, FlyLockLastRound);
    
    
    
    
    CC_SYNTHESIZE(int, m_BuffAttack, BuffAttack) ///< 攻击力增副
    CC_SYNTHESIZE(int, m_BuffCriticalAttack, BuffCriticalAttack) ///< 爆击力增副
    CC_SYNTHESIZE(float, m_BuffMovePFCostRate, BuffMovePFCostRate) ////< 移动体力消耗体力
    
#if OPEN_FIFTH
  
    CC_SYNTHESIZE(int, m_WSSkillType, WSSkillType) // 武器技能类型
    //多回合持续
    CC_SYNTHESIZE(int, m_WSLastHurt, WSLatHurt) ///< 持续伤害
    CC_SYNTHESIZE(int, m_WSLastHurtRound, WSLastHurtRound) ///< 持续伤害剩作回合数
    CC_SYNTHESIZE(int, m_WSLastTired, WSLastTired) ///< 持续降低体力上限
    CC_SYNTHESIZE(int, m_WSLastTiredRound, WSLastTiredRound) ///< 持续降低体力上限回合数
    CC_SYNTHESIZE(int, m_WSLastSeal, WSLastSeal) ///< 持续封印
    CC_SYNTHESIZE(int, m_WSLastSealRound, WSLastSealRound) ///<持续封印回合数
    CC_SYNTHESIZE(int, m_WSLastFlyLockRound, WSLastFlyLockRound) ///<持续锁定飞行
    CC_SYNTHESIZE(int, m_WSLastFlyLock, WSLastFlyLock) ///<持续锁定飞行

    
    //单回合
     
    CC_SYNTHESIZE(float, m_WSAttackRate, WSAttackRate) ///< 武器技能,攻击力增副
    CC_SYNTHESIZE(int, m_WSHurt, WSHurt)///< 伤害增加
    CC_SYNTHESIZE(int, m_WSIsCriticalAttack, WSIsCriticalAttack) ///< 是不是暴击
    CC_SYNTHESIZE(float, m_WSGetHurtToBloodRate, WSGetHurtToBloodRate) ///< 获取攻击百分之多少加血
    CC_SYNTHESIZE(float, m_WSAttackLowdownRate, WSAttackLowdownRate) ///< 攻击力下降百分比
    CC_SYNTHESIZE(int, m_WSAttackTimesUp, WSAttackTimesUp) ///< 攻击次数上升
    CC_SYNTHESIZE(int, m_WSIsFollowAttack, WSIsFollowAttack) ///< 是否跟跟踪
    CC_SYNTHESIZE(int, m_WSIsAttom, WSIsAttom) ///< 是否原子弹
    
    CC_SYNTHESIZE(int, m_WSSkillType_s, WSSkillType_s) // 武器技能类型
    CC_SYNTHESIZE(int, m_WSLastHurt_s, WSLastHurt_s) ///< 持续伤害
    CC_SYNTHESIZE(int, m_WSLastHurtRound_s, WSLastHurtRound_s) ///< 持续伤害剩作回合数
    CC_SYNTHESIZE(int, m_WSLastTired_s, WSLastTired_s) ///< 持续降低体力上限
    CC_SYNTHESIZE(int, m_WSLastTiredRound_s, WSLastTiredRound_s) ///< 持续降低体力上限回合数
    CC_SYNTHESIZE(int, m_WSLastSeal_s, WSLastSeal_s) ///< 持续封印
    CC_SYNTHESIZE(int, m_WSLastSealRound_s, WSLastSealRound_s) ///<持续封印回合数
    CC_SYNTHESIZE(int, m_WSLockFlyRound_s, WSLockFlyRound_s)
    
#endif

    CC_SYNTHESIZE(int, m_shootAttackRateIndex, shootAttackRateIndex);
    
    CC_SYNTHESIZE(float, m_ExplodeRadius, ExplodeRadius)        ///< 爆炸半径
    
    CC_SYNTHESIZE(int, m_isHide, IsHide) //隐藏
    CC_SYNTHESIZE(int, m_HideRoundLast, HideRoundLast) ///<隐身剩余回合数
    
    
    //CC_SYNTHESIZE(GameFrontLayer *,m_lpGameFrontLayer,GameFrontLayer); ///<所在场景
#if(OPEN_NEWTEACH)
    //CC_SYNTHESIZE(GameFrontNewTeachLayer *,m_lpGameFrontTeachLayer,GameFrontTeachLayer); ///<所在场景
#else
    //CC_SYNTHESIZE(GameFrontTeachLayer *,m_lpGameFrontTeachLayer,GameFrontTeachLayer); ///<所在场景
#endif
    
    
    Sprite *m_pAngryFire;
    //WShopCharacter *m_lpSCCharacter; ///< 商城的角色形象
    CC_SYNTHESIZE(Sprite *,m_lpSpecialEffect,lpSpecialEffect);///< 特效
    Sprite *m_lpPlayerIcon;
    
    Sprite *m_lpWeaponSkillEffect;///< 武器技能特效
    
    CC_SYNTHESIZE(int, m_weaponType, WeaponType)   ///< 武器类型0:投掷 1:射击
    
    CC_SYNTHESIZE(Animation *,m_BulletAni,BulletAni);                                  ///< 炮弹动画
    CC_SYNTHESIZE(Animation *,m_BulletAniAngry,BulletAniAngry);              ///< 爆怒时的炮弹动画
    CC_SYNTHESIZE(Animation *,m_BulletAniExplode,BulletAniExplode);       ///< 炮弹爆炸
    CC_SYNTHESIZE(Animation *, m_BulletAniFreezeExplode, BulletAniFreezeExplode) ///<冰冻炮弹
    CC_SYNTHESIZE(Animation *,m_BulletAniRear,BulletAniRear);                   ///< 炮弹尾巴
    
    CC_SYNTHESIZE(Image *,m_BulletCilcleImage,BulletCilcleImage);                      ///<  炮弹爆炸挖坑图
    CC_SYNTHESIZE(Image *,m_BulletCilcleImageMark,BulletCilcleImageMark);     ///<  炮弹爆炸挖坑图模板
    
    CC_SYNTHESIZE(float, m_RadiusForHurtCheck, RadiusForHurtCheck)///< 被炸范围
    CC_SYNTHESIZE(float, m_RadiusForBulletCollisionCheck, RadiusForBulletCollisionCheck)///< 用于判断与炸弹的碰撞
    
    ///@brief 运行状态
    CC_SYNTHESIZE(int, m_newRunStatus, NewRunStatus);//新的状态
    CC_SYNTHESIZE(int, m_runStatus, RunStatus);
    
    ///@brief 是否在准备状态中,就是是否可以切换状态
    CC_SYNTHESIZE(bool, m_IsStandby, IsStandby);
   
    ///@brief ai控制id
    CC_SYNTHESIZE(int, m_aiCtrlId, AiCtrlId)
    CC_SYNTHESIZE(bool, m_useItem, UseItem) //是不是使用道具
    //CC_SYNTHESIZE_PASS_BY_REF(CAICombination, m_AICombination,AICombination);//道具使用组合
    
    CC_SYNTHESIZE(CCArray *,m_currentUsedItems,CurrentUsedItems); ///< 当前使用的道具

    CC_SYNTHESIZE(bool,m_isShowPoint,IsShowPoint);///< 是否显示虚线点
    
    CC_SYNTHESIZE(int   ,      m_face, Face)
    
    CC_SYNTHESIZE(WHero *, m_preTargetHero, PreTargetHero)
    
#if OPEN_FIFTH
    CC_SYNTHESIZE(CCArray *,m_weaponSkills,WeaponSkills);
    CC_SYNTHESIZE(Sprite*, m_WSSpecial, WSSpecial); //武器技能特效
    
    void CheckWeaponSkillTouchOff();///< 检测武器技能是否触发
    //void processWeaponSkill(const WBWeaponSkill *lpSkill);///< 处理武器技能
    
    //@param lpOwnerPlayer 是谁射我的
    void beShootedInWeaponSkill(const WHero *lpOwnerPlayer);
    void clearWeaponSkill();
    void updateWeaponSkillPerRound();
    void clearWeaponSkill_s();
#endif

    vector<Vec2> m_positionCollection;
    int m_currentPositionIndex;
    
    void fly_start();
    
    void fly();
    
    
    static void getCircleImg(const string &path, Image **pCircle, Image **pCircleMark);
    
    
public:   
    int getCurCriticalType();
    
	//WBItem m_skills[4];
    //WBItem m_items[4];
     
    virtual void onEnter();
    
	//virtual void draw(void);
    
    void start();
    void stop();
    
    WHero();
    virtual ~WHero();
    
    //运行状态
    enum
    {
        DEF_ST_NORMAL =0,       //待机
        DEF_ST_MOVE_LEFT,       //向左移动
        DEF_ST_MOVE_RIGHT,     //向右移动
        DEF_ST_ITEMSKILL,  //使用道具
        DEF_ST_SHOOT,       //射击
        DEF_ST_FLY,             //飞行
        DEF_ST_DEATH,       //死亡
        DEF_ST_HURT,         //伤害
        DEF_ST_FREEZE,      //冻结
        DEF_ST_BIGSKILL,    //大招
        DEF_ST_SUREWIN,   //胜利
        DEF_ST_FAIL,           //失败
        DEF_ST_FLASH,       //闪烁
        DEF_ST_REBORN,    //复活
        DEF_ST_NONE=-1,   //空的状态,用于转换状态时
    };
    
    queue<WBEvent *> m_EventManager;
    queue<WBEvent *> m_quickEventManager;//立即执行的事件队列，一般会是一些只发数值的操作
    WBEvent *m_currentWBEvent; //当前正在执行的事件
    
    void SendMsgMove(const Vec2 &pos, int leftOrRight,int st_move_times);
    void SendMsgShoot(const CCPoint &startPos,const Vec2 &speed,int face);
    void SendMsgFly(const CCPoint &startPos,const Vec2 &speed,int face);
    void SendMsgUseItem(int type,int subtype);
    void SendMsgDeath();
    void SendMsgHurt(int playerid,int hurtValue,int criticalType);
    void SendMsgBIGSKILL();
    void SendMsgSureWin();
    void SendMsgFail();
    void SendMsgNormal();
    void SendMsgFreeze();
    void SendMsgReborn(const Vec2 &position);
   
	void setAnimation(int dwAniID);
	void playRepeat();
	boolean isCurrentAnimationDone();
	void playOnce();
	int getAnimationStatus();
    /**
     * @brief 清理事件队列
     */
    void ClearEventQueue();
    
    /**
     * @brief 发送事件到事件队列
     */
    void SendEventToQueue(WBEvent *pEvent); 
    
    
    //动画状态
    enum
    {
        DEF_NORMAL =0,      //一般待机
        DEF_NORMAL_2,       //待机2
        DEF_SUREWIN,           //胜利手式
        DEF_ITEMSKILL,         //使用道具动画
        DEF_MOVE,                //移动
        DEF_SHOOT_START, //开始射击动画
        DEF_SHOOT_REPEAT,//重复射击动画
        DEF_SHOOT_END,      //射击结束
        DEF_SHOOT_BIG_START, //开始射击动画(大招)
        DEF_SHOOT_BIG_REPEAT,//重复射击动画(大招)
        DEF_SHOOT_BIG_END,      //射击结束(大招)
        DEF_HURT,                 //受到伤害
        DEF_FLY,                     //飞行
        DEF_GHOST,               //鬼魂
        
    };
    
    //特效动画
    enum
    {
        DEF_SE_FROZEN_1,        //冰冻前段动画
        DEF_SE_FROZEN_2,        //处于冰冻时的动画
        DEF_SE_USE_ITEM,        //使用道具
        DEF_SE_ADD_BLOOD,   //加血
        DEF_SE_HIDE,                //隐身
        DEF_SE_BIGSKILL,          //大招
    };
    
    enum
    {
        DEF_FACE_RIGHT=1,
        DEF_FACE_LEFT   =0,
    };
    
    
    typedef struct
    {
        CCPoint startPos;
        Vec2 speed;
        int         face;
    }SHOOT_OR_FLY_STRUCT;
    
    typedef struct
    {
        int playerId;
        int hurt;
        int ciriticalType; //0:一般 1:爆击 2:超爆击
        
    }HURT_STRUCT;
    
    typedef struct
    {
        Vec2 startPos;
        int times;
    }MOVE_STRUCT;
    
    /**
     * @brief 生成一个角色
     * @param strList        动画穿着描述表
     * @param boyOrGirl  1:男还是0:女
     * @param weaponType 攻击方式 0:投掷 1:射击
     */
    static WHero *BuildHero(const vector<string> &strList,int boyOrGirl, int weaponType);
    
    /**
     * @brief 清理每回合的属性
     */
    void PropertyRoundClear();
    
 void setPlayerLose();

    /**
    * @brief 开始触摸控制
    */
    int TouchCheckBeginMove(CCTouch *touch);
    bool TouchCheckBeginControl(CCTouch *touch);
    void TouchControlStart();
    void TouchControl(CCTouch *touch);
    void TouchControlEnd(bool shoot);
    
    CCPoint st_shoot_startPos;
//    float st_shoot_angle;
//    float st_shoot_power;
    Vec2 st_shoot_speed;
   
    bool m_isCollsionPre;
    
    bool m_needCheckCollsion;
    
     void buildAiCombination();
private:    
    void checkCollision();
    void checkCollisionInFly();
    
    float              st_normal_timer;
   
    CCPoint m_Points[DEF_EHERO_MAX_POINT];///< 虚线点集
    int           m_PointsUsedCount;///< 已有点的数量
    bool        m_IsTouchControlStarted;//是不是进入触摸控制
    CCPoint st_normal_oldTouchPoint; //上一次的触点
    
    void st_normal();
    
    float st_move_timer;
    int         st_move_times;

    
    void SetLeftRight(int leftRight);
    void st_move();
    
    
 
    int    st_shoot_bigskill;       //0:不是大招, 1:是大招
    int    st_shoot_step;            //射击步骤,用来
    
    

    void st_shoot();
    void st_shoot_calc();//计算生成炮弹
    
    
    void st_hurt();
    void st_freeze(); //冻结
    
    Vec2  m_oldPosBeforeFly;
    float m_flytime;
    void st_fly();
    
    CCBlink *m_blink;
    void st_flash();
    
    void ShowSpecialEffect(int effect);
    
    
    
    
    //处理状态转换
    void ProcessMessage();
    
    //处理不同状态
    void ProcessStatus();
    
    

    
    
    void update(float dt);
    
    void onStartBigSkillShoot();
public:
#if(OPEN_NEWTEACH)
    CCSprite *smallCould;
    CCSprite *bigCould;
    CC_SYNTHESIZE(bool, m_isCouldVisiable, isCouldVisiable);
    void createHeroCould();
#endif
    
    
};












#endif