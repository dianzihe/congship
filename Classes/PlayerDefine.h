//////////////////////////////////////////////////////////////////////////
// �����ض���
#pragma once

// �����ߵȼ�
#define Max_Player_Level		100
// �����ҽ�ɫ����
#define Max_Player_Count		3
//��ʾ�Ľ�ɫ�������
#define Max_ShowPlayer_Count		12

// ����Ա���
#define Player_Sex_Man			0
// ����Ա�Ů
#define Player_Sex_Woman		1

// ��Ӫ����
#define CAMP_TIANJI				0
// ��Ӫ����
#define CAMP_XUANZONG			1
// ��Ӫ����(����Ӫ)
#define CAMP_COUNT				2
// �ػ��淨 �ػ���    3
#define CAMP_DEFEND 3 
// �ػ��淨 ������    4
#define CAMP_ATTACK 4

//	�����������ֽ�����
#define Max_Player_Name_Len		20


// ���ֳƺ�
#define Player_Master_Common 0  //�޳ƺ�
#define Player_Master_Elite 1  //��Ӣ
#define Player_Master_Superior 2  //����

//	Ǯ����
enum Money_Type
{
	Money_Money					= 0,	//	ͭ��
	Money_BindedMoney			= 1,	//	��ͭ��
	Money_Gold					= 2,	//	Ԫ��
	Money_BindedGold			= 3,	//	��Ԫ��
	Money_RechargeAmmount		= 4,	//  ��ֵ�ܽ�� 

	Money_Count,
};

//	Ǯ�仯ԭ��
enum Money_Change_Type
{
	Money_Change_Equip			= 0,	//	װ������
	Money_Change_GM				= 1,	//	GM
	Money_Change_Task			= 2,	//	������
};

// ���ְҵ����
enum Player_Class_Type
{
	Player_Class_Sword		= 0,	//	����
	Player_Class_Spear		= 1,	//	����
	Player_Class_Fan		= 2,	//	�ٻ�
	Player_Class_Knife		= 3,	//	�ݻ�
	Player_Class_Count,
};

enum HeroCombatSkill
{
	eCombatSkill_Sword = 24001, // ����
	eCombatSkill_Spear = 24002, // ����
	eCombatSkill_Fan = 24003,   // �ٻ�
	eCombatSkill_Knife = 24004, // �ݻ�
};

enum Exp_Change_Type
{
	Exp_Change_Task							=0,		//�����þ���
	Exp_Change_KillMonster				=1,		//ɱ�ֻ�þ���
	Exp_Change_GM							=2,		//GM����
	Exp_Change_UseItem					=3,		//ʹ����Ʒ���
	Exp_Change_PlatformSend			=4,		//ƽ̨����
	Exp_Change_Convoy					=5,		//���ͻ�þ���
	Exp_Change_Active						=6,		//��Ծֵ�һ�
	Exp_Change_Unknow					=7
};

//	����״̬��ǩ���߼����ϵ
enum Actor_State_Flag_Type
{
	// player��npc������
	Actor_State_Flag_Unkown						= 0,	//δ��ʼ��
	Actor_State_Flag_Loading					= 1,	//������
	Actor_State_Flag_WaitEnterMap				= 2,	//�ȴ���ҽ����ͼ
	Actor_State_Flag_EnteredMap					= 4,	//����Ѿ������ͼ
	Actor_State_Flag_Dead						= 8,	//������
	Actor_State_Flag_Fighting					= 32,	//ս��״̬
	Actor_State_Flag_God						= 64,	//�޵�״̬
	Actor_State_Flag_Disable_Attack				= 128,	//��ֹ����״̬
	Actor_State_Flag_Disable_Move				= 256,	//��ֹ�ƶ�״̬
	Actor_State_Flag_Disable_Hold				= 512,	//����״̬

	// ���ר����
	Player_State_Flag_TalkingWithNpc			= 1024, //Npc�Ի���
	Player_State_Flag_CollectingWithNpc			= 2048, //Npc�ɼ���
	Player_State_Flag_TradeWithPlayer			= 4096, //����ҽ����У���ҽ��ף�
	Player_State_Flag_ChangingMap				= 8192, //��ͼ�л���
	Player_State_Flag_PK_Kill					= 16384,//%%0x4000	//	����
	Player_State_Flag_PK_Kill_Value				= 32768, //0x8000	//	����
	Player_State_Flag_Just_Disable_Move			= 131072, //	��ֹ�ƶ�״̬��ֱ�����ã����ܲ��ܽ�

	// Monsterר��״̬( 0x200000--0x4000000 )
	Monster_State_Flag_GoBacking				= 2097152, //0x200000 //����������

};

//�ƶ�״̬
#define Object_MoveState_Stand		0	//վ��
#define Object_MoveState_Moving	1	//�ƶ���

#define  Object_FlyState_Land			0		//����
#define  Object_FlyState_Flying		1		//����
//���и߶�
#define Object_Fly_Height				150

//�������ͬ��������ƶ��ڵ���
#define Player_MaxMove_SendToServer_Node_Num   10
//�������ͬ����������
#define Player_MaxMove_SendToServer_Dis				800

enum QIE_CUO_FAIL
{
	QIE_CUO_FAIL_LEVEL_MY = -1, //%%�д�����ʧ�ܣ������ȼ�����
	QIE_CUO_FAIL_LEVEL_TARGET = -2, //%%�д�����ʧ�ܣ��Է��ȼ�����
	QIE_CUO_FAIL_MAP = -3, //%%�д�����ʧ�ܣ���ͼ����
	QIE_CUO_FAIL_FIGHTSTATE = -4, //%%�д�����ʧ�ܣ�������ս��״̬
	QIE_CUO_FAIL_INVALID_CALL = -5, //%%�д�����ʧ�ܣ���Ч�Ĳ���
	QIE_CUO_FAIL_DISTANCE = -6, //%%�д�����ʧ�ܣ�����̫Զ
	QIE_CUO_FAIL_REFUSE = -7, //%%�д�����ʧ�ܣ��Է��ܾ�
	QIE_CUO_FAIL_IN_CONVOY = -8,//�д�����ʧ�ܣ����ڻ���
	QIE_CUO_FAIL_DES_IN_CONVOY = -9, //�д�����ʧ�ܣ��Է��ڻ�����
};

enum SHALU_OP_RESULT
{
	SHALU_OPENED	= 1, //%%ɱ¾ģʽ��
	SHALU_CLOSED	= 2, //%%ɱ¾ģʽ�ر�
	SHALU_OPENED_VALUE = 3,
	SHALU_OP_FAIL_INVALID_CALL	= -1, //%%ɱ¾ģʽ���ز�����Ч
	SHALU_OP_FAIL_CDING	= -2, //%%ɱ¾ģʽ�ر���ȴ��
	SHALU_OP_UPDATE_VALUE	= -3, //%%ɱ¾ֵ����
};

//�鿴װ������
#define LookPlayerInfo_Failed_NotOnline			-1		//�Է�������
#define LookPlayerInfo_Failed_Self				-2		//���ܲ鿴�Լ�
#define LookPlayerInfo_Failed_UnKnow			-3		//δ֪����

//��������ȡ�������
enum ACTIVE_CODE_GET_RESULT
{
	ACTIVE_CODE_GET_SUCC				= 0,	//	��������ȡ�ɹ�
	ACTIVE_CODE_GET_FAIL_NOT_EXIST		= 1,	//	�����벻����
	ACTIVE_CODE_GET_FAIL_GETED			= 2,	//	�������Ѿ���ȡ��
	ACTIVE_CODE_GET_FAIL_INVALID		= 3,	//	����ʧ��
	ACTIVE_CODE_GET_FAIL_FULLBAG		= 4,	//	��������
	ACTIVE_CODE_GET_FAIL_EXIST          = 5,    //  ����ȡ�������
};

//�ȼ������ȡ����
#define GetLevelGift_Result_Succ							0	//��ȡ�ɹ�
#define GetLevelGift_Result_LevelNotEnough		-1 //�ȼ�����
#define GetLevelGift_Result_BagFull						-2 //��������
#define GetLevelGift_Result_NotGift						-3	//û�����������