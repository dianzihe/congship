#pragma once

#include "base.h"
#include <string>
#include <map>

using namespace std;

enum EnterMap_Fail_Type
{
	EnterMap_Fail_Invalid_Call = -1,//无效的操作
	EnterMap_Fail_Exist_Player = -2,//已经在地图里
	EnterMap_Fail_Exist_Ready_Player = -3,//已经在等待玩家进入
	EnterMap_Fail_CD = -4, //进入副本CD不满足
	EnterMap_Fail_Distance = -5, //距离副本入口不满足
	EnterMap_Fail_FightState= -6, //战斗状态不能进入副本
	EnterMap_Fail_NotTeamLeader= -7, //不是队长，不能创建副本
	EnterMap_Fail_PlayerLevel = -8, //等级不满足
	EnterMap_Fail_HasTeam = -9, //已经在队伍里
	EnterMap_Fail_ResetFail_HasPlayer = -10, //副本中还有玩家，重置失败
	EnterMap_Fail_ResetSucc = -11, //副本重置成功
	EnterMap_Fail_ResetNomap = -12, //副本重置已经完成
	EnterMap_Fail_ForceTransOut = 13, //秒后将被传送出副本
	EnterMap_Fail_In_Convoy = 14, //正在护送不能进行副本
	EnterMap_Fail_Vigour = -15,//体力值不足，不能进入副本
	EnterMap_Fail_VipLevel = -16,//玩家VIP等级不够
	EnterMap_Fail_ForeMap = -17,//前置副本没有完成挑战
	EnterMap_Fail_StateError = -18,//状态异常
	EnterMap_Fail_PetCharacter = -19,
	EnterMap_Fail_CantTransToMap =  -20,
    EnterMap_Fail_FrontMapNotFinsh = -21,
	EnterMap_Fail_CountNotEnough = -22,//神秘天牢挑战次数不足
};

//%%地图类型
enum MapType
{
	Map_Type_Normal_World = 1, //%%世界地图
	Map_Type_Normal_Copy = 2, //%%一般副本地图
	Map_Type_Normal_Guild = 3, //%%一般仙盟地图
	Map_Type_Battle = 4, //%%战场地图
	Map_Type_Arena = 5,//竞技场
	Map_Type_TerrioryWar = 6,//领地地图
};

struct MapSettingData
{
	int id;				//id
	int type;			//type
	string name;		//name
	string descript;	//描述
	string res;			//资源名
	string MiniMap;		//小地图资源主文件名
	string MapScn;		//地图出生资源文件名
	int initPosX;		//
	int initPosY;		//
	int	PlayerEnter_MinLevel;
	int	PlayerEnter_MaxLevel;
	int	PlayerActiveEnter_Times; //活跃次数
	int	PlayerActiveTime_Item;	//增加活跃次数需要的道具
	int	PlayerEnter_Times;
	int	DropItem1;
	int	DropItem2;
	int	DropItem3;
	int	DropItem4;
	int	DropItem5;
	int	DropItem6;
	int	DropItem7;
	int	DropItem8;

	int QuitMapID;
	int QuitMapPosX;
	int QuitMapPosY;

	bool pkFlag_Camp;	//是否可以阵营PK，可以填1，不可以填0
	int pkFlag_Kill;	//是否允许杀戮PK，可以填1，不可以填0
	bool pkFlag_QieCuo;	//是否可以切磋，可以填1，不可以填0

	int AutoFightInCopyMapRoutPosX;	//	在副本中挂机停止时寻路点X
	int AutoFightInCopyMapRoutPosY;	//	在副本中挂机停止时寻路点Y

	int  mapFaction;
	string	music;

	int	laminate_Minlevel;//扫荡所需等级
	int	laminate_money;//扫荡所需铜币
	int	laminate_drop_out;

	int	daliy;		// 显示在日常面板-副本 true / false

	int pkflag_all;//是否允许开启全体PK模式
	int pkflag_guild;//是否允许开启帮会PK模式
	int pkflag_team;//是否允许开启组队PK模式
	int pkflag_kindevil;//是否允许开启善恶PK模式
	int laminate_money_type;//扫荡所需货币类型
	int need_energy;//进入与扫荡所需活力值
	int kindevil;//是否增加善恶值
	int vipLevel; //vip进入等级
	int revive;//是否开启复活
	int headicon;//BOSS头像
	int battleshow; //推荐战斗力
	int difficulty; //几成功力
	int petcharacter1;//成熟or纯真
	int petcharacter2;//热情or冷静
	int petover;//小师妹是否出战
};

class MapSettingCfg
{
private:
	MapSettingCfg();
public:
	~MapSettingCfg();

	static MapSettingCfg& instance( void )
	{
		static MapSettingCfg	s;
		return s;
	}

	bool init( const char* pFile );

	map<int, MapSettingData> &getMapSettingCfgTable(){ return m_mapMapSettingCfgTable;};

	const MapSettingData *getMapSettingCfgData( int id )
	{
		map<int, MapSettingData>::iterator it = m_mapMapSettingCfgTable.find(id);
		if( it == m_mapMapSettingCfgTable.end() )
			return NULL;
		return &it->second;
	}

private:
	map<int, MapSettingData>  m_mapMapSettingCfgTable;
};