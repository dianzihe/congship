#ifndef _ACTIONTYPE_H__
#define _ACTIONTYPE_H__

enum ACTORTYPE
{
	ACTORTYPE_ANIMATION = 0,//只有动画显示的基础ACTOR
	ACTORTYPE_PLAYER,//有移动攻击等行为的ACTOR
	ACTORTYPE_NPC,//NPC
	ACTORTYPE_MONSTER,//怪物
	ACTORTYPE_HERO,//主角
	ACTORTYPE_SKILLSFX, //技能特效
	ACTORTYPE_OTHERSFX,//通用特效
	ACTORTYPE_WEAPONSFX, //武器特效--（换装）
	ACTORTYPE_TRANSPORT, // 传送点
	ACTORTYPE_COLLECT,	//采集物
	ACTORTYPE_PATHFIND_POINT,	//寻路点
	ACTORTYPE_PET,						//宠物
	ACTORTYPE_WEAPON,// 武器
	ACTORTYPE_MOUNT,// 坐骑
	ACTORTYPE_WING,// 翅膀
	ACTORTYPE_OBJECT_NORMAL,//通用Object
	ACTORTYPE_SCENEOBJECT,//场景Object
	ACTORTYPE_FLAG,	//旗帜
	ACTORTYPE_CONVOY, // 镖车
	ACTORTYPE_MAGICWEAPONSFX, // 法宝武器特效
	ACTORTYPE_Count,
};

enum OtherSpriteResID
{
	SPRITE_TASKICON = 0,
	SPRITE_MINIMAP,
	SPRITE_CLICK,
	SPRITE_PICK,
	SPRITE_AOE,
	SPRITE_SHADOW,
	SPRITE_HP,
	SPRITE_TRANSPORT,
	SPRITE_EXPRESSION,
	SPRITE_LOGIN,
	SPRITE_EYE,
};

enum GrayPart
{
	eGrayPart_NotGray		= 0x00000,
	eGrayPart_Body			= 0x00001,
	eGrayPart_Weapon		= 0x00002,
	eGrayPart_Mount			= 0x00004,
	eGrayPart_Wing			= 0x00008,
	eGrayPart_Pet			= 0x00010,
};

enum	Object_Type
{
	Object_Type_Player				= 1,			//物体类型，玩家
	Object_Type_Npc					= 2,			//物体类型，npc
	Object_Type_Monster			= 3,			//物体类型，monster
	Object_Type_System				= 4,			//物体类型，系统
	Object_Type_Guild				= 5,			//物体类型，仙盟
	Object_Type_Team				= 6,			//物体类型，队伍
	Object_Type_Object				= 7,			//物件类型，object
	Object_Type_TRANSPORT		= 8,			//物件类型，传送点
	Object_Type_COLLECT			= 9,			//物件类型，采集
	Object_Type_Pet					= 10,		//物件类型，宠物
	Object_Type_Equipment		= 11,		//物件类型，装备
	Object_Type_Map					= 12,		//物件类型，地图
	Object_Type_Task					= 13,		//物件类型，任务
	Object_Type_SkillEffect			= 14,		//物件类型，技能特效
	Object_Type_Normal			= 15,		//物件类型，通用
	Object_Type_Daily				= 16,		//物件类型，日常
	Object_Type_Mount				= 17,		//物件类型，坐骑
	Object_Type_Item					= 18,		//物件类型，物品
	Object_Type_Mail					= 19,		//物件类型，邮件
};

#endif
