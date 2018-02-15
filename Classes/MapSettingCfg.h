#pragma once

#include "base.h"
#include <string>
#include <map>

using namespace std;

enum EnterMap_Fail_Type
{
	EnterMap_Fail_Invalid_Call = -1,//��Ч�Ĳ���
	EnterMap_Fail_Exist_Player = -2,//�Ѿ��ڵ�ͼ��
	EnterMap_Fail_Exist_Ready_Player = -3,//�Ѿ��ڵȴ���ҽ���
	EnterMap_Fail_CD = -4, //���븱��CD������
	EnterMap_Fail_Distance = -5, //���븱����ڲ�����
	EnterMap_Fail_FightState= -6, //ս��״̬���ܽ��븱��
	EnterMap_Fail_NotTeamLeader= -7, //���Ƕӳ������ܴ�������
	EnterMap_Fail_PlayerLevel = -8, //�ȼ�������
	EnterMap_Fail_HasTeam = -9, //�Ѿ��ڶ�����
	EnterMap_Fail_ResetFail_HasPlayer = -10, //�����л�����ң�����ʧ��
	EnterMap_Fail_ResetSucc = -11, //�������óɹ�
	EnterMap_Fail_ResetNomap = -12, //���������Ѿ����
	EnterMap_Fail_ForceTransOut = 13, //��󽫱����ͳ�����
	EnterMap_Fail_In_Convoy = 14, //���ڻ��Ͳ��ܽ��и���
	EnterMap_Fail_Vigour = -15,//����ֵ���㣬���ܽ��븱��
	EnterMap_Fail_VipLevel = -16,//���VIP�ȼ�����
	EnterMap_Fail_ForeMap = -17,//ǰ�ø���û�������ս
	EnterMap_Fail_StateError = -18,//״̬�쳣
	EnterMap_Fail_PetCharacter = -19,
	EnterMap_Fail_CantTransToMap =  -20,
    EnterMap_Fail_FrontMapNotFinsh = -21,
	EnterMap_Fail_CountNotEnough = -22,//����������ս��������
};

//%%��ͼ����
enum MapType
{
	Map_Type_Normal_World = 1, //%%�����ͼ
	Map_Type_Normal_Copy = 2, //%%һ�㸱����ͼ
	Map_Type_Normal_Guild = 3, //%%һ�����˵�ͼ
	Map_Type_Battle = 4, //%%ս����ͼ
	Map_Type_Arena = 5,//������
	Map_Type_TerrioryWar = 6,//��ص�ͼ
};

struct MapSettingData
{
	int id;				//id
	int type;			//type
	string name;		//name
	string descript;	//����
	string res;			//��Դ��
	string MiniMap;		//С��ͼ��Դ���ļ���
	string MapScn;		//��ͼ������Դ�ļ���
	int initPosX;		//
	int initPosY;		//
	int	PlayerEnter_MinLevel;
	int	PlayerEnter_MaxLevel;
	int	PlayerActiveEnter_Times; //��Ծ����
	int	PlayerActiveTime_Item;	//���ӻ�Ծ������Ҫ�ĵ���
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

	bool pkFlag_Camp;	//�Ƿ������ӪPK��������1����������0
	int pkFlag_Kill;	//�Ƿ�����ɱ¾PK��������1����������0
	bool pkFlag_QieCuo;	//�Ƿ�����д裬������1����������0

	int AutoFightInCopyMapRoutPosX;	//	�ڸ����йһ�ֹͣʱѰ·��X
	int AutoFightInCopyMapRoutPosY;	//	�ڸ����йһ�ֹͣʱѰ·��Y

	int  mapFaction;
	string	music;

	int	laminate_Minlevel;//ɨ������ȼ�
	int	laminate_money;//ɨ������ͭ��
	int	laminate_drop_out;

	int	daliy;		// ��ʾ���ճ����-���� true / false

	int pkflag_all;//�Ƿ�������ȫ��PKģʽ
	int pkflag_guild;//�Ƿ����������PKģʽ
	int pkflag_team;//�Ƿ����������PKģʽ
	int pkflag_kindevil;//�Ƿ��������ƶ�PKģʽ
	int laminate_money_type;//ɨ�������������
	int need_energy;//������ɨ���������ֵ
	int kindevil;//�Ƿ������ƶ�ֵ
	int vipLevel; //vip����ȼ�
	int revive;//�Ƿ�������
	int headicon;//BOSSͷ��
	int battleshow; //�Ƽ�ս����
	int difficulty; //���ɹ���
	int petcharacter1;//����or����
	int petcharacter2;//����or�侲
	int petover;//Сʦ���Ƿ��ս
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