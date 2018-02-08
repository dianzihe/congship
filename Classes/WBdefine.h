
#ifndef _wbdefine_include_file_
#define _wbdefine_include_file_


#define DEF_OBJ_TYPE_MAN                    1  
#define DEF_OBJ_TYPE_BULLET                2  
#define DEF_OBJ_TYPE_BULLETSMOOK   3  
#define DEF_OBJ_TYPE_GUAI                    4


#define DEF_WB_HIDE_ROUND_MAX 2
#define DEF_WB_FREEZE_ROUND_MAX 2

#define DEF_WB_TOUCH_RADIUS 90    //(单位:像素) 角色控制射

#define DEF_SYSTEM_HUD_PATH      "gameResources/battle/hud/battle_hud_"
#define DEF_SYSTEM_HUD_TRUE_PATH "gameResources/battle/hud/"

#define WBLOADING_PATH                "gameResources/battle/loading/battle_loading_"
#define WBLOADING_TRUE_PATH      "gameResources/battle/loading/"

#define DEF_EXPLODE_IMAGE_PATH "gameResources/battle/explode/"
#define DEF_BATTLE_MAP_PATH       "gameResources/battle/map/"
#define DEF_COMMON_PATH             "gameResources/ui/common/"

#define DEF_BOSSMAP_TARGET_PATH "gameResources/battle/bossmaptarget/"

#define REWARD_PATH "gameResources/battle/reward/battle_reward_"
#define REWARD_TRUE_PATH "gameResources/battle/reward/"

#define SETTLEMENT_PATH "gameResources/battle/settlement/battle_sett_"
#define SETTLEMENT_TRUE_PATH "gameResources/battle/settlement/"

#define DEF_TEACH_PATH "gameResources/ui/teach/"

#define DEF_LOADING_PATH "gameResources/ui/loading/"

#define DEF_MONSTER_ICON_PATH "gameResources/battle/guaiicon/"


#define DEF_WB_SHOOT_POWER_MIN  40    //最小射击力度
#define DEF_WB_SHOOT_POWER_MAX 300  //最大射击力度
#define DEF_WB_SHOOT_POWER_BASE 40   //射击力度基数

#define DEF_EHERO_MAX_POINT 60 //射击线点数

#define DEF_WB_TRACK_DISTANCE       200 //跟踪
#define DEF_WB_BEGIN_TRACK_TIME     30 //周期,开始跟踪
#define DEF_WB_BEGIN_HERO_COLLSION_TIME 3//开始碰人


#define DEF_WB_PLAYER 0
#define DEF_WB_GUAI     1

#define DEF_WB_GUAITYPE_MONSTER 1 //小怪
#define DEF_WB_GUAITYPE_BOSS         2 //boss



#define DEF_WB_CTRL_SELF     0//自己
#define DEF_WB_CTRL_OTHER 1//其他人
#define DEF_WB_CTRL_AI          2//AI

//怪攻击类型
#define DEF_WB_GUAITYPE_MELEE_RANGED 0//会近远攻的怪
#define DEF_WB_GUAITYPE_RANGED   1//只会远攻的怪
#define DEF_WB_GUAITYPE_MELEE       2//只会近攻的怪
#define DEF_WB_GUAITYPE_NOMOVE  3



//群组行动类型
#define DEF_WB_TEAMATTACK_TYPE_NONE    0  //不是群组移动
#define DEF_WB_TEAMATTACK_TYPE_MELEE -1 //近攻的怪群组移动




#define DEF_BATTLEMODE_NORMAL       0 //对战模式
#define DEF_BATTLEMODE_BOSSMAP_1  1 //小副本
#define DEF_BATTLEMODE_BOSSMAP_2  2 //大副本
#define DEF_BATTLEMODE_QULIFYING  4 //对战模式


#define DEF_BATTLE_NORMAL_MODE_ATHLETICS        1//竞技模式
#define DEF_BATTLE_NORMAL_MODE_REBORN              2//复活模式
#define DEF_BATTLE_NORMAL_MODE_MIXUP                 3//混战模式
#define DEF_BATTLE_NORMAL_MODE_BOSS                    4//副本

#define DEF_BOSS_BOSS1       1
#define DEF_BOSS_BOSS2_1    2
#define DEF_BOSS_BOSS2_2    3
#define DEF_BOSS_BOSS3_1    4
#define DEF_BOSS_BOSS3_2    5
#define DEF_BOSS_BOSS3_SHIELD 6
#define DEF_BOSS_BOSS4       7



#define DEF_BOSS_GREATEEXPLODE_RANGE_BOSS1 200
#define DEF_BOSS_GREATEEXPLODE_RANGE_BOSS2 1000

//BOSS-1
#define DEF_WB_BOSS1_MELEE_GUAI_MAX    7
#define DEF_WB_BOSS1_RANGED_GUAI_MAX 2

#define DEF_WB_BOSS2_MELEE_GUAI_MAX  12

#define DEF_WB_BOSSMAP_PASSTIME 30

#define DEF_WB_MAX_REWARDTIME 6
#define DEF_WB_FREE_REWARDTIME 2

#define DEF_BOSS2_TRANSFORM_RATE 0.45//boss2变身比例


//#define registerNetWork(callback,pthis,maintype,subtype) WDDD_GLOBAL.m_pNetSocketConnection->registerProtocolProcesser(callback,pthis,maintype,subtype)
//#define unregisterNetWork(callback,pthis,maintype,subtype) WDDD_GLOBAL.m_pNetSocketConnection->unregisterProtocolProcesser(callback,pthis,maintype,subtype)
//#define WBSendProtocol(protocolObject) {WDDD_GLOBAL.m_pNetSocketConnection->send(protocolObject,false);}

#endif