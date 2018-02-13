#pragma once

#include "base.h"
#include <string>
#include <map>
#include <list>
#include <vector>

using namespace std;

////技能学习结果
enum TSkillStudyErr
{
	ESSErr_Success		=  0 ,       //学习成功
	ESSErr_PlayerLvl	=  -1,       //玩家级别不够
	ESSErr_Money		=  -2,       //玩家钱不够
	ESSErr_NoItem		=  -3,       //没有所需物品
	ESSErr_AlreadyStuey =  -4,       //以学过该技能
	ESSErr_NoSkill		=  -5,       //技能不存在
	ESSErr_OPFrequent	=  -6,       //操作频繁
	ESSErr_Credit		=  -7,       //声望不够
	ESSErr_NoGuild		=  -8,       //没有加入仙盟
	ESSErr_GuildLevel	=  -9,       //仙盟等级不够
	ESSErr_YueLiZhiBuGou = - 10,      //玩家阅历值不够
	ESSErr_NotLearnFrontSkill = -12,  //没有学习前置技能
};


//技能飞行动画类型
enum SKILL_FLY_EFFECT_TYPE
{
	 SKILL_FLY_EFFECT_TYPE_SELF				=1,			//自身出发
	 SKILL_FLY_EFFECT_TYPE_ENEMY			=2,			//敌人出发
	 SKILL_FLY_EFFECT_TYPE_TARGET			=3			//自己选择目标
};

//目标类型
enum SKILL_TARGET_TYPE
{
	SKILL_TARGET_CASTER_SELF					=0,//施法者自己
	SKILL_TARGET_CASTER_CIRCULAR_ENEMY			=1, //施法者附近的敌人,圆形
	SKILL_TARGET_CASTER_CIRCULAR_PARTNER		=2, //施法者附近的队友（包括施法者），圆形
	SKILL_TARGET_CIRCULAR_PARTNER				=3,  //范围内队友，如果施法者在这个范围内也能够被选择，圆形,用于指定范围，无需选择目标的技能
	SKILL_TARGET_ENEMY							=4, //敌人
	SKILL_TARGET_ENEMY_CIRCULAR_ENEMY			=5, //敌人附近的敌人，（包括被选为目标的敌人），圆形
	SKILL_TARGET_CASTER_SECTOR_ENEMY			=6, //施法者前方的敌人，扇形
	SKILL_TARGET_CASTER_RECTANGLE_ENEMY			=7, //施法者前方的敌人，矩形
	SKILL_TARGET_CIRCULAR_ENEMY					=8,//范围内敌人，圆形
	SKILL_TARGET_MASTER							=9,//主人（宠物对主人使用的技能）
	SKILL_TARGET_MASTER_CIRCULAR_PARTNER		=10,//主人和主人附近的队友
	SKILL_TARGET_PET							=11,//宠物（主人对宠物使用的技能）
	SKILL_TARGET_CHAIN_ENEMY					=12, //链式选择敌人
};

//技能类型
enum SKILL_TYPE
{
	SKILL_TYPE_ZHUDONG = 1,//主动
	SKILL_TYPE_BEIDONG   = 2,	//被动
	SKILL_TYPE_CHUFA		 = 3, //技能先触发状态
};
//是否为半圆
enum Semicircle_Type
{
	IS_SEMICIRCLE = 0,//为半圆
	NOT_SEMICIRCLE,  //不为半圆
};
//附加effect类型
enum EFFECT_TYPE
{
	SKILL_EFFECT_TYPE_NONE = 0,//没有附加effect
	SKILL_EFFECT_TYPE_BUFF   = 1,//buff
};

// 技能所属职业
enum SkillClassType
{
	SkillClass_JinWei  = 0, // 天玄门
	SkillClass_BaiHuo  = 1, // 禁卫府
	SkillClass_BaiHua  = 2, // 百花谷
	SkillClass_TieQi  = 3, // 拜火教
	SkillClass_TianXuan  = 4, // 唐家堡
	SkillClass_PetAtk   = 100, //  小师妹外功
	SkillClass_PetMAtk   = 101, // 小师妹内功
	SkillClass_PetAid   = 102, // 小师妹辅助
	SkillClass_JiangHu   = 200, // 江湖武学
	SkillClass_Secret   = 201, // 秘籍武学
	SkillClass_Monster  = 300, // 怪物
	SkillClass_Guild  = 400, // 帮派
	SkillClass_Item   = 401, // 物品
	SkillClass_System  = 402, // 系统
	SkillClass_Unusual  = 403, // 特殊技能
};


// 技能触发类型
enum SkillTriggerType
{
	SkillTrigger_Passive    = 0,    //	被动
	SkillTrigger_Init		= 1,	//	主动
	SkillTrigger_Attacks    = 2,    //  攻击触发
	SkillTrigger_Injured    = 3,    //  被攻击触发
};

// 技能使用目标类型
enum SkillUseTargetType
{
	SkillUseTarget_Enemy	= 0,	//	敌人
	SkillUseTarget_Self		= 1,	//	自己
	SkillUseTarget_Friend	= 2,	//	友方（适用于玩家，怪物（怪物只适用于群体技能）
	SkillUseTarget_SelfPosEnemy	= 3,	//	自身位置的敌人 （适用于玩家, 怪物，必须是群攻技能）
	SkillUseTarget_Master	= 4,	//	主人 （只适用于宠物）
	SkillUseTarget_Pet		= 5,	//宠物（只适用于玩家）
	SkillUseTarget_Team		= 6,	//队伍（适用于玩家，宠物）
	SkillUseTarget_Guild		= 7,	//帮会（只适用于玩家）
};


// 技能击中特殊判断
enum SkillHitSpecType
{
	SkillHitSpec_Normal				= 0x0,	//	攻击做正常判定
	SkillHitSpec_Not_HitTest		= 0x1,	//	不做命中判定
	SkillHitSpec_Not_DodgeTest		= 0x2,	//	不做闪避判定
};

// 技能特殊情况使用
enum SkillUseSpecType
{
	SkillUseSpec_Normal				= 0x0,	//	不做特殊使用判断
	SkillUseSpec_Comal				= 0x1,	//	昏迷时可以使用
	SkillUseSpec_Silent				= 0x2,	//	沉默时可以使用
	SkillUseSpec_Dead				= 0x4,	//	死亡后使用
};

//%%伤害类型0所有，1物理， 2火，4冰，8电，16毒
enum TSkillDamageType
{
	ESkillDamageType_All	=	0,//
	ESkillDamageType_Phy	=	1,
	ESkillDamageType_Fire	=	2,
	ESkillDamageType_Ice	=	4,
	ESkillDamageType_Elec	=	8,
	ESkillDamageType_Poison	=	16,
};

//技能效果类型
enum
{
	SkillEffectType_CreateBuffer				=	1,	//创建Buffer，Param1=Buffer的SkillID
	SkillEffectType_RemoveTargetState	=	2,	//使用或者生效后移除目标的某个或多个状态，填写0则不移除，使用位运算可填写多个，Param1=值
	SkillEffectType_RunScriptEvent			=	3,	//执行script中的effect函数，主要用于副本中boss的技能效果, Param1为event ID, 调用方式为objectEvent:onEvent( Attacker, event_id, 0),
	SkillEffectType_CreateMonster			=	4,	//技能效果，招怪
	SkillEffectType_Sprint						=	5,	//技能效果，冲刺到目标
};


struct EffectData
{
	int effect_type;				//附加effect类型
	int effect_target_type;		//技能使用目标类型SkillUseTargetType
	int param1;					//
	int param2;					//
	int param3;					//
	int param4;					//
};

struct SkillInfo
{
	int  id;							//id
	//string name;					//name
	int SkillClass;					//技能职业
	int Studylevel;				//技能习得等级
	int Money_Type;				//需求货币类型
	int CastMoney;				//技能学习消耗金钱
	int Need_Experience;        //玩家学习所需要的阅历
	int Need_Item;              //学习技能所需要的道具类型
	int Item_Quantity;          //学习技能所需要的道具数量
	int petskill_del;            // 
	int groupId;					//技能组id
	int level;						//技能等级
	int branchof;					//附加于哪个技能
	int nSkillIcon;				//技能图标
	int SkillAct;					//技能动作
	int EffectGroup;				//特效组
	int EffectID;					//特效ID
	int FlyType;					//飞行动画类型(1.自身出发点2.以敌人为出发点3.自己选择目标)
	int Ranger;					//技能攻击距离(单位为像素)
	int SkillRange;				//技能范围(0.单体,>0目标周围范围)
	int SkillCoolDown;			//技能CD时间(单位:毫秒)
	int SkillCoolDownGroup;		//始冷却时，与其同冷却组的所有技能都开始冷却，并且采用技能A的冷却时间，用于共享冷却时间的技能，道具等等
	int Skill_GlobeCoolDown;		//是否触发公共CD
	int Skill_TriggerType;			//技能触发类型SkillTriggerType
	int TriggerChance;              //触发几率
	int ProcSkill;                  //触发指定技能id
	int ProcChance;                  //触发指定技能几率
	int DamageType;					//伤害类型
	int DamagePercent;				//外伤害百分比
	int DamageFixValue;				//内伤害固定值
	int EffectTimes;				//技能作用次数
	int CreateAOE;					//是否为创建AOE Object 【杨全福】0:不创建 不为零创建
	int AOEDelay;					//技能作用间隔
	int AOEEffectTarget;			//AOE效果施放目标
	int AOEEffectBind;				//AOE效果绑定被施放者
	int Skill_UseTargetType;		//技能使用目标类型SkillUseTargetType
	int Skill_Hate;					//技能仇恨值：
	int Use_Spec;					//特殊的可使用情况：1.昏迷时可以使用，2.沉默时可以使用，4.死亡后使用
	int Skill_school;				//Chaos_School 默认混乱系，乱七八糟的技能可以划为该系，比如红药，buff药，传送卷轴等等
	int SkillAttackType;			//技能攻击方式分为，近战攻击，远程攻击，魔法攻击，混乱攻击，（混乱攻击不做战斗结果判定，吃药，传送，加增益等等技能）
	int MaxEffectCount;				//技能效果作用最大角色个数
	int ShakeType;					//技能抖动类型
	int ShakeRate;					//技能抖动几率
	//string SkillNote;				//技能说明
	int Base_point;
    int Attack_Start_Sound;
    int Attack_Success_Sound;
    int Hit_Sound;
	int attackType;					//技能目标类型
	string	useMap;					//使用地图限制
	int	max_count;				//最大累计次数
	int	aggressiveTime;         //一张图累计多少次使用
	int hit_recover;           //命中回血系数百分比
	int add_crit;              //附加暴击
	int add_hitrecover;        //附加命中回血
	int add_damageRecover;     //附加伤害回血
	int Mobile_Type;           //移动类型
	int Removing;               //单位像素
	int MDamagePercent;         //内功百分比伤害
	int MDamageFixValue;       //内功固定值伤害
	int DefDamagePercent;      //外防百分比伤害
	int MDefDamagePercent;     //内防百分比伤害
	int Hit_Number;           //连击序号
	int EffectWeaponID;         //武器sfx
	int skill_nerve;        //技能所属秘籍
	int Semicircle;				//标识是否为半圆 0：否 1：是
	int hit_times;              //技能Mac
	vector<EffectData> vEffect; //技能附加效果

	std::string getSkillIcon() const
	{
		char tmp[256];
		sprintf(tmp, "Icon/SkillIcon/s%d.png", nSkillIcon);
		return tmp;
	}
};

struct SkillGroup
{
	int groupId;
	int maxLevel;
	vector<SkillInfo>  levels;
};

struct SkillNoteInfo
{
	int skillId;
	std::string skillnote;
};
struct SkillNoteData
{
	int groupId;
	vector<SkillNoteInfo> vSkillId;
	SkillNoteData()
	{
		groupId = -1;
	}
};

class SkillCfg
{
private:
	SkillCfg();
public:
	~SkillCfg();

	static SkillCfg& instance( void )
	{
		static SkillCfg	s;
		return s;
	} 

	bool	init( const char* pFile, const char *pFileEffect );

	map<int, SkillInfo>& getSkillCfgTable(){ return m_mapSkillCfgTable; };
	map<int, SkillInfo> &getSpecialSkillCfgTable(){ return m_mapSpecialSkillCfgTable; };
	const SkillInfo* getSkillCfgData(int id)
	{
		map<int, SkillInfo>::iterator it = m_mapSkillCfgTable.find(id);
		if( it == m_mapSkillCfgTable.end() )
			return nullptr;
		return &it->second;
	}

	const SkillInfo *getSkillCfgDataByGroupAndLevel(int group, int level);

	const SkillGroup *getSkillGroup(int groupId)
	{
		map<int, SkillGroup>::iterator it=m_mapSkillGroupTable.find(groupId);
		if( it==m_mapSkillGroupTable.end() )
			return nullptr;
		return &it->second;
	}

	const map<int, SkillGroup>& getSkillGroupTable(){ return m_mapSkillGroupTable;};

	const EffectData* getSkillEffectDtatByType( int skillid, int type )
	{
		map<int, SkillInfo>::iterator it = m_mapSkillCfgTable.find(skillid);
		if( it == m_mapSkillCfgTable.end() )
			return nullptr;

		for( size_t i=0; i<it->second.vEffect.size(); ++i )
		{
			if( it->second.vEffect[i].effect_type == type )
				return &(it->second.vEffect[i]);
		}
		return nullptr;
	}
    //查询秘籍所属技能
	const SkillInfo * getCheats (int neverId , int LevelId);
	std::string getName(SkillInfo * pInfo);
	std::string getSkillNode(SkillInfo * pInfo);
	std::string getName(const SkillInfo * pInfo);
	std::string getSkillNode(const SkillInfo * pInfo);

	bool isRepeatSkillNote(int groupId,string name,int skillId);

private:
	map<int, SkillInfo>  m_mapSkillCfgTable;
	map<int, SkillInfo>  m_mapSpecialSkillCfgTable;
	map<int, SkillGroup> m_mapSkillGroupTable;
	map<int, list<int> >  m_mapSkillBranchTable;
	map<int, SkillNoteData> m_mapNameDesc;
};