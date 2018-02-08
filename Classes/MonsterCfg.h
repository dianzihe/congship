#pragma once

//#include "base.h"
#include <string>
#include <map>
using namespace std;

enum MonsterType
{
	MonsterType_Normal = 0,//普通怪
	MonsterType_Elite,//精英怪
	MonsterType_NormalBoss,//普通boss
	MonsterType_CopyMapBoss,//副本boss
	MonsterType_FieldBoss,//野外boss
};

struct MonsterData
{
	int id;							//id
	string name;					//名字
	int animation;					//动画ID
	int mobHead;					//头像
	int level;						//等级
	int exp;						//获得经验
	int attackSpeed;				//攻击间隔（毫秒）
	int attack;						//攻击力
	int defence;					//防御力
	int max_life;					//生命值上限
	int ph_def;						//物理抗性
	int fire_def;					//火抗性
	int ice_def;					//冰抗性
	int elec_def;					//电抗性
	int poison_def;					//毒抗性
	int hit_rate_rate;				//命中率
	int dodge_rate;					//闪避率
	int block_rate;					//格挡率
	int crit_rate;					//暴击率
	int coma_def_rate;				//昏迷抵抗率
	int hold_def_rate;				//定身抵抗率
	int silent_def_rate;			//沉默抵抗率
	int move_def_rate;				//减速抵抗率
	int baseSkillID;				//基础技能

	int monsterCd;					//刷新时间
	int PatrolRadius;				//巡逻半径
	int WatchRadius;				//视野半径
	int FollowRadius;				//追击半径
	int Active;						//主动or被动
	int droplist;					//掉落数据
	int faction;					//阵营
	int attack_mode;				//攻击模式
	float modelscale;				//模型放缩
	float	wildMaxScale;			//狂暴最大縮放值
	int monstertype;				//怪物类型
};

class MonsterCfg
{
private:
	MonsterCfg();
public:
	~MonsterCfg();

	static MonsterCfg& instance( void )
	{
		static MonsterCfg	 s;
		return s;
	}

	bool init(const char *pFile);

	const map<int, MonsterData> &getMonsterTable(){ return m_mapMonsterTable; };
	const MonsterData *getMonsterCfgData( int id)
	{
		map<int, MonsterData>::iterator it = m_mapMonsterTable.find(id);
		if( it == m_mapMonsterTable.end() )
			return NULL;
		return &it->second;
	}

private:
	map<int, MonsterData>  m_mapMonsterTable;
};