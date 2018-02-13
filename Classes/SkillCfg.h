#pragma once

#include "base.h"
#include <string>
#include <map>
#include <list>
#include <vector>

using namespace std;

////����ѧϰ���
enum TSkillStudyErr
{
	ESSErr_Success		=  0 ,       //ѧϰ�ɹ�
	ESSErr_PlayerLvl	=  -1,       //��Ҽ��𲻹�
	ESSErr_Money		=  -2,       //���Ǯ����
	ESSErr_NoItem		=  -3,       //û��������Ʒ
	ESSErr_AlreadyStuey =  -4,       //��ѧ���ü���
	ESSErr_NoSkill		=  -5,       //���ܲ�����
	ESSErr_OPFrequent	=  -6,       //����Ƶ��
	ESSErr_Credit		=  -7,       //��������
	ESSErr_NoGuild		=  -8,       //û�м�������
	ESSErr_GuildLevel	=  -9,       //���˵ȼ�����
	ESSErr_YueLiZhiBuGou = - 10,      //�������ֵ����
	ESSErr_NotLearnFrontSkill = -12,  //û��ѧϰǰ�ü���
};


//���ܷ��ж�������
enum SKILL_FLY_EFFECT_TYPE
{
	 SKILL_FLY_EFFECT_TYPE_SELF				=1,			//�������
	 SKILL_FLY_EFFECT_TYPE_ENEMY			=2,			//���˳���
	 SKILL_FLY_EFFECT_TYPE_TARGET			=3			//�Լ�ѡ��Ŀ��
};

//Ŀ������
enum SKILL_TARGET_TYPE
{
	SKILL_TARGET_CASTER_SELF					=0,//ʩ�����Լ�
	SKILL_TARGET_CASTER_CIRCULAR_ENEMY			=1, //ʩ���߸����ĵ���,Բ��
	SKILL_TARGET_CASTER_CIRCULAR_PARTNER		=2, //ʩ���߸����Ķ��ѣ�����ʩ���ߣ���Բ��
	SKILL_TARGET_CIRCULAR_PARTNER				=3,  //��Χ�ڶ��ѣ����ʩ�����������Χ��Ҳ�ܹ���ѡ��Բ��,����ָ����Χ������ѡ��Ŀ��ļ���
	SKILL_TARGET_ENEMY							=4, //����
	SKILL_TARGET_ENEMY_CIRCULAR_ENEMY			=5, //���˸����ĵ��ˣ���������ѡΪĿ��ĵ��ˣ���Բ��
	SKILL_TARGET_CASTER_SECTOR_ENEMY			=6, //ʩ����ǰ���ĵ��ˣ�����
	SKILL_TARGET_CASTER_RECTANGLE_ENEMY			=7, //ʩ����ǰ���ĵ��ˣ�����
	SKILL_TARGET_CIRCULAR_ENEMY					=8,//��Χ�ڵ��ˣ�Բ��
	SKILL_TARGET_MASTER							=9,//���ˣ����������ʹ�õļ��ܣ�
	SKILL_TARGET_MASTER_CIRCULAR_PARTNER		=10,//���˺����˸����Ķ���
	SKILL_TARGET_PET							=11,//������˶Գ���ʹ�õļ��ܣ�
	SKILL_TARGET_CHAIN_ENEMY					=12, //��ʽѡ�����
};

//��������
enum SKILL_TYPE
{
	SKILL_TYPE_ZHUDONG = 1,//����
	SKILL_TYPE_BEIDONG   = 2,	//����
	SKILL_TYPE_CHUFA		 = 3, //�����ȴ���״̬
};
//�Ƿ�Ϊ��Բ
enum Semicircle_Type
{
	IS_SEMICIRCLE = 0,//Ϊ��Բ
	NOT_SEMICIRCLE,  //��Ϊ��Բ
};
//����effect����
enum EFFECT_TYPE
{
	SKILL_EFFECT_TYPE_NONE = 0,//û�и���effect
	SKILL_EFFECT_TYPE_BUFF   = 1,//buff
};

// ��������ְҵ
enum SkillClassType
{
	SkillClass_JinWei  = 0, // ������
	SkillClass_BaiHuo  = 1, // ������
	SkillClass_BaiHua  = 2, // �ٻ���
	SkillClass_TieQi  = 3, // �ݻ��
	SkillClass_TianXuan  = 4, // �Ƽұ�
	SkillClass_PetAtk   = 100, //  Сʦ���⹦
	SkillClass_PetMAtk   = 101, // Сʦ���ڹ�
	SkillClass_PetAid   = 102, // Сʦ�ø���
	SkillClass_JiangHu   = 200, // ������ѧ
	SkillClass_Secret   = 201, // �ؼ���ѧ
	SkillClass_Monster  = 300, // ����
	SkillClass_Guild  = 400, // ����
	SkillClass_Item   = 401, // ��Ʒ
	SkillClass_System  = 402, // ϵͳ
	SkillClass_Unusual  = 403, // ���⼼��
};


// ���ܴ�������
enum SkillTriggerType
{
	SkillTrigger_Passive    = 0,    //	����
	SkillTrigger_Init		= 1,	//	����
	SkillTrigger_Attacks    = 2,    //  ��������
	SkillTrigger_Injured    = 3,    //  ����������
};

// ����ʹ��Ŀ������
enum SkillUseTargetType
{
	SkillUseTarget_Enemy	= 0,	//	����
	SkillUseTarget_Self		= 1,	//	�Լ�
	SkillUseTarget_Friend	= 2,	//	�ѷ�����������ң��������ֻ������Ⱥ�弼�ܣ�
	SkillUseTarget_SelfPosEnemy	= 3,	//	����λ�õĵ��� �����������, ���������Ⱥ�����ܣ�
	SkillUseTarget_Master	= 4,	//	���� ��ֻ�����ڳ��
	SkillUseTarget_Pet		= 5,	//���ֻ��������ң�
	SkillUseTarget_Team		= 6,	//���飨��������ң����
	SkillUseTarget_Guild		= 7,	//��ᣨֻ��������ң�
};


// ���ܻ��������ж�
enum SkillHitSpecType
{
	SkillHitSpec_Normal				= 0x0,	//	�����������ж�
	SkillHitSpec_Not_HitTest		= 0x1,	//	���������ж�
	SkillHitSpec_Not_DodgeTest		= 0x2,	//	���������ж�
};

// �����������ʹ��
enum SkillUseSpecType
{
	SkillUseSpec_Normal				= 0x0,	//	��������ʹ���ж�
	SkillUseSpec_Comal				= 0x1,	//	����ʱ����ʹ��
	SkillUseSpec_Silent				= 0x2,	//	��Ĭʱ����ʹ��
	SkillUseSpec_Dead				= 0x4,	//	������ʹ��
};

//%%�˺�����0���У�1���� 2��4����8�磬16��
enum TSkillDamageType
{
	ESkillDamageType_All	=	0,//
	ESkillDamageType_Phy	=	1,
	ESkillDamageType_Fire	=	2,
	ESkillDamageType_Ice	=	4,
	ESkillDamageType_Elec	=	8,
	ESkillDamageType_Poison	=	16,
};

//����Ч������
enum
{
	SkillEffectType_CreateBuffer				=	1,	//����Buffer��Param1=Buffer��SkillID
	SkillEffectType_RemoveTargetState	=	2,	//ʹ�û�����Ч���Ƴ�Ŀ���ĳ������״̬����д0���Ƴ���ʹ��λ�������д�����Param1=ֵ
	SkillEffectType_RunScriptEvent			=	3,	//ִ��script�е�effect��������Ҫ���ڸ�����boss�ļ���Ч��, Param1Ϊevent ID, ���÷�ʽΪobjectEvent:onEvent( Attacker, event_id, 0),
	SkillEffectType_CreateMonster			=	4,	//����Ч�����й�
	SkillEffectType_Sprint						=	5,	//����Ч������̵�Ŀ��
};


struct EffectData
{
	int effect_type;				//����effect����
	int effect_target_type;		//����ʹ��Ŀ������SkillUseTargetType
	int param1;					//
	int param2;					//
	int param3;					//
	int param4;					//
};

struct SkillInfo
{
	int  id;							//id
	//string name;					//name
	int SkillClass;					//����ְҵ
	int Studylevel;				//����ϰ�õȼ�
	int Money_Type;				//�����������
	int CastMoney;				//����ѧϰ���Ľ�Ǯ
	int Need_Experience;        //���ѧϰ����Ҫ������
	int Need_Item;              //ѧϰ��������Ҫ�ĵ�������
	int Item_Quantity;          //ѧϰ��������Ҫ�ĵ�������
	int petskill_del;            // 
	int groupId;					//������id
	int level;						//���ܵȼ�
	int branchof;					//�������ĸ�����
	int nSkillIcon;				//����ͼ��
	int SkillAct;					//���ܶ���
	int EffectGroup;				//��Ч��
	int EffectID;					//��ЧID
	int FlyType;					//���ж�������(1.���������2.�Ե���Ϊ������3.�Լ�ѡ��Ŀ��)
	int Ranger;					//���ܹ�������(��λΪ����)
	int SkillRange;				//���ܷ�Χ(0.����,>0Ŀ����Χ��Χ)
	int SkillCoolDown;			//����CDʱ��(��λ:����)
	int SkillCoolDownGroup;		//ʼ��ȴʱ������ͬ��ȴ������м��ܶ���ʼ��ȴ�����Ҳ��ü���A����ȴʱ�䣬���ڹ�����ȴʱ��ļ��ܣ����ߵȵ�
	int Skill_GlobeCoolDown;		//�Ƿ񴥷�����CD
	int Skill_TriggerType;			//���ܴ�������SkillTriggerType
	int TriggerChance;              //��������
	int ProcSkill;                  //����ָ������id
	int ProcChance;                  //����ָ�����ܼ���
	int DamageType;					//�˺�����
	int DamagePercent;				//���˺��ٷֱ�
	int DamageFixValue;				//���˺��̶�ֵ
	int EffectTimes;				//�������ô���
	int CreateAOE;					//�Ƿ�Ϊ����AOE Object ����ȫ����0:������ ��Ϊ�㴴��
	int AOEDelay;					//�������ü��
	int AOEEffectTarget;			//AOEЧ��ʩ��Ŀ��
	int AOEEffectBind;				//AOEЧ���󶨱�ʩ����
	int Skill_UseTargetType;		//����ʹ��Ŀ������SkillUseTargetType
	int Skill_Hate;					//���ܳ��ֵ��
	int Use_Spec;					//����Ŀ�ʹ�������1.����ʱ����ʹ�ã�2.��Ĭʱ����ʹ�ã�4.������ʹ��
	int Skill_school;				//Chaos_School Ĭ�ϻ���ϵ�����߰���ļ��ܿ��Ի�Ϊ��ϵ�������ҩ��buffҩ�����;���ȵ�
	int SkillAttackType;			//���ܹ�����ʽ��Ϊ����ս������Զ�̹�����ħ�����������ҹ����������ҹ�������ս������ж�����ҩ�����ͣ�������ȵȼ��ܣ�
	int MaxEffectCount;				//����Ч����������ɫ����
	int ShakeType;					//���ܶ�������
	int ShakeRate;					//���ܶ�������
	//string SkillNote;				//����˵��
	int Base_point;
    int Attack_Start_Sound;
    int Attack_Success_Sound;
    int Hit_Sound;
	int attackType;					//����Ŀ������
	string	useMap;					//ʹ�õ�ͼ����
	int	max_count;				//����ۼƴ���
	int	aggressiveTime;         //һ��ͼ�ۼƶ��ٴ�ʹ��
	int hit_recover;           //���л�Ѫϵ���ٷֱ�
	int add_crit;              //���ӱ���
	int add_hitrecover;        //�������л�Ѫ
	int add_damageRecover;     //�����˺���Ѫ
	int Mobile_Type;           //�ƶ�����
	int Removing;               //��λ����
	int MDamagePercent;         //�ڹ��ٷֱ��˺�
	int MDamageFixValue;       //�ڹ��̶�ֵ�˺�
	int DefDamagePercent;      //����ٷֱ��˺�
	int MDefDamagePercent;     //�ڷ��ٷֱ��˺�
	int Hit_Number;           //�������
	int EffectWeaponID;         //����sfx
	int skill_nerve;        //���������ؼ�
	int Semicircle;				//��ʶ�Ƿ�Ϊ��Բ 0���� 1����
	int hit_times;              //����Mac
	vector<EffectData> vEffect; //���ܸ���Ч��

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
    //��ѯ�ؼ���������
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