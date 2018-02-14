#pragma once

#include "base.h"
#include <string>
#include <map>
using namespace std;

enum MonsterType
{
	MonsterType_Normal = 0,//��ͨ��
	MonsterType_Elite,//��Ӣ��
	MonsterType_NormalBoss,//��ͨboss
	MonsterType_CopyMapBoss,//����boss
	MonsterType_FieldBoss,//Ұ��boss
};

struct MonsterData
{
	int id;							//id
	string name;					//����
	int animation;					//����ID
	int mobHead;					//ͷ��
	int level;						//�ȼ�
	int exp;						//��þ���
	int attackSpeed;				//������������룩
	int attack;						//������
	int defence;					//������
	int max_life;					//����ֵ����
	int ph_def;						//������
	int fire_def;					//����
	int ice_def;					//������
	int elec_def;					//�翹��
	int poison_def;					//������
	int hit_rate_rate;				//������
	int dodge_rate;					//������
	int block_rate;					//����
	int crit_rate;					//������
	int coma_def_rate;				//���Եֿ���
	int hold_def_rate;				//����ֿ���
	int silent_def_rate;			//��Ĭ�ֿ���
	int move_def_rate;				//���ٵֿ���
	int baseSkillID;				//��������

	int monsterCd;					//ˢ��ʱ��
	int PatrolRadius;				//Ѳ�߰뾶
	int WatchRadius;				//��Ұ�뾶
	int FollowRadius;				//׷���뾶
	int Active;						//����or����
	int droplist;					//��������
	int faction;					//��Ӫ
	int attack_mode;				//����ģʽ
	float modelscale;				//ģ�ͷ���
	float	wildMaxScale;			//�����s��ֵ
	int monstertype;				//��������
};

class MonsterCfg
{
private:
	MonsterCfg();
public:
	~MonsterCfg();

	static MonsterCfg& instance( void )
	{
		static MonsterCfg s;
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