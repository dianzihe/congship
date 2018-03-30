//////////////////////////////////////////////////////////////////////////
// 玩家相关定义
#pragma once

// 玩家最高等级
#define Max_Player_Level		100
// 最大玩家角色数量
#define Max_Player_Count		3
//显示的角色最大数量
#define Max_ShowPlayer_Count		12

// 玩家性别男
#define Player_Sex_Man			0
// 玩家性别女
#define Player_Sex_Woman		1

// 阵营天玑
#define CAMP_TIANJI				0
// 阵营玄宗
#define CAMP_XUANZONG			1
// 阵营数量(无阵营)
#define CAMP_COUNT				2
// 守护玩法 守护方    3
#define CAMP_DEFEND 3 
// 守护玩法 进攻方    4
#define CAMP_ATTACK 4

//	玩家名字最大字节数量
#define Max_Player_Name_Len		20


// 高手称号
#define Player_Master_Common 0  //无称号
#define Player_Master_Elite 1  //精英
#define Player_Master_Superior 2  //高手

//	钱类型
enum Money_Type
{
	Money_Money					= 0,	//	铜币
	Money_BindedMoney			= 1,	//	绑定铜币
	Money_Gold					= 2,	//	元宝
	Money_BindedGold			= 3,	//	绑定元宝
	Money_RechargeAmmount		= 4,	//  充值总金额 

	Money_Count,
};

//	钱变化原因
enum Money_Change_Type
{
	Money_Change_Equip			= 0,	//	装备激活
	Money_Change_GM				= 1,	//	GM
	Money_Change_Task			= 2,	//	任务奖励
};

// 玩家职业类型
enum Player_Class_Type
{
	Player_Class_Sword		= 0,	//	天玄
	Player_Class_Spear		= 1,	//	近卫
	Player_Class_Fan		= 2,	//	百花
	Player_Class_Knife		= 3,	//	拜火
	Player_Class_Count,
};

enum HeroCombatSkill
{
	eCombatSkill_Sword = 24001, // 天玄
	eCombatSkill_Spear = 24002, // 近卫
	eCombatSkill_Fan = 24003,   // 百花
	eCombatSkill_Knife = 24004, // 拜火
};

enum Exp_Change_Type
{
	Exp_Change_Task							=0,		//任务获得经验
	Exp_Change_KillMonster				=1,		//杀怪获得经验
	Exp_Change_GM							=2,		//GM经验
	Exp_Change_UseItem					=3,		//使用物品获得
	Exp_Change_PlatformSend			=4,		//平台发放
	Exp_Change_Convoy					=5,		//护送获得经验
	Exp_Change_Active						=6,		//活跃值兑换
	Exp_Change_Unknow					=7
};

//	生物状态标签，逻辑或关系
enum Actor_State_Flag_Type
{
	// player、npc共享部分
	Actor_State_Flag_Unkown						= 0,	//未初始化
	Actor_State_Flag_Loading					= 1,	//加载中
	Actor_State_Flag_WaitEnterMap				= 2,	//等待玩家进入地图
	Actor_State_Flag_EnteredMap					= 4,	//玩家已经进入地图
	Actor_State_Flag_Dead						= 8,	//已死亡
	Actor_State_Flag_Fighting					= 32,	//战斗状态
	Actor_State_Flag_God						= 64,	//无敌状态
	Actor_State_Flag_Disable_Attack				= 128,	//禁止攻击状态
	Actor_State_Flag_Disable_Move				= 256,	//禁止移动状态
	Actor_State_Flag_Disable_Hold				= 512,	//昏迷状态

	// 玩家专享部分
	Player_State_Flag_TalkingWithNpc			= 1024, //Npc对话中
	Player_State_Flag_CollectingWithNpc			= 2048, //Npc采集中
	Player_State_Flag_TradeWithPlayer			= 4096, //与玩家交互中（玩家交易）
	Player_State_Flag_ChangingMap				= 8192, //地图切换中
	Player_State_Flag_PK_Kill					= 16384,//%%0x4000	//	黄名
	Player_State_Flag_PK_Kill_Value				= 32768, //0x8000	//	红名
	Player_State_Flag_Just_Disable_Move			= 131072, //	禁止移动状态，直接设置，技能不能解

	// Monster专享状态( 0x200000--0x4000000 )
	Monster_State_Flag_GoBacking				= 2097152, //0x200000 //往回跑重置

};

//移动状态
#define Object_MoveState_Stand		0	//站立
#define Object_MoveState_Moving	1	//移动中

#define  Object_FlyState_Land			0		//地面
#define  Object_FlyState_Flying		1		//飞行
//飞行高度
#define Object_Fly_Height				150

//与服务器同步的最大移动节点数
#define Player_MaxMove_SendToServer_Node_Num   10
//与服务器同步的最大距离
#define Player_MaxMove_SendToServer_Dis				800

enum QIE_CUO_FAIL
{
	QIE_CUO_FAIL_LEVEL_MY = -1, //%%切磋邀请失败，己方等级不够
	QIE_CUO_FAIL_LEVEL_TARGET = -2, //%%切磋邀请失败，对方等级不够
	QIE_CUO_FAIL_MAP = -3, //%%切磋邀请失败，地图限制
	QIE_CUO_FAIL_FIGHTSTATE = -4, //%%切磋邀请失败，不能在战斗状态
	QIE_CUO_FAIL_INVALID_CALL = -5, //%%切磋邀请失败，无效的操作
	QIE_CUO_FAIL_DISTANCE = -6, //%%切磋邀请失败，距离太远
	QIE_CUO_FAIL_REFUSE = -7, //%%切磋邀请失败，对方拒绝
	QIE_CUO_FAIL_IN_CONVOY = -8,//切磋邀请失败，正在护送
	QIE_CUO_FAIL_DES_IN_CONVOY = -9, //切磋邀请失败，对方在护送中
};

enum SHALU_OP_RESULT
{
	SHALU_OPENED	= 1, //%%杀戮模式打开
	SHALU_CLOSED	= 2, //%%杀戮模式关闭
	SHALU_OPENED_VALUE = 3,
	SHALU_OP_FAIL_INVALID_CALL	= -1, //%%杀戮模式开关操作无效
	SHALU_OP_FAIL_CDING	= -2, //%%杀戮模式关闭冷却中
	SHALU_OP_UPDATE_VALUE	= -3, //%%杀戮值更新
};

//查看装备返回
#define LookPlayerInfo_Failed_NotOnline			-1		//对方不在线
#define LookPlayerInfo_Failed_Self				-2		//不能查看自己
#define LookPlayerInfo_Failed_UnKnow			-3		//未知错误

//激活码领取结果返回
enum ACTIVE_CODE_GET_RESULT
{
	ACTIVE_CODE_GET_SUCC				= 0,	//	激活码领取成功
	ACTIVE_CODE_GET_FAIL_NOT_EXIST		= 1,	//	激活码不存在
	ACTIVE_CODE_GET_FAIL_GETED			= 2,	//	激活码已经领取过
	ACTIVE_CODE_GET_FAIL_INVALID		= 3,	//	操作失败
	ACTIVE_CODE_GET_FAIL_FULLBAG		= 4,	//	背包已满
	ACTIVE_CODE_GET_FAIL_EXIST          = 5,    //  已领取过该礼包
};

//等级礼包领取返回
#define GetLevelGift_Result_Succ							0	//领取成功
#define GetLevelGift_Result_LevelNotEnough		-1 //等级不足
#define GetLevelGift_Result_BagFull						-2 //背包已满
#define GetLevelGift_Result_NotGift						-3	//没有礼包可领了