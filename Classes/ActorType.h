#ifndef _ACTIONTYPE_H__
#define _ACTIONTYPE_H__

enum ACTORTYPE
{
	ACTORTYPE_ANIMATION = 0,//ֻ�ж�����ʾ�Ļ���ACTOR
	ACTORTYPE_PLAYER,//���ƶ���������Ϊ��ACTOR
	ACTORTYPE_NPC,//NPC
	ACTORTYPE_MONSTER,//����
	ACTORTYPE_HERO,//����
	ACTORTYPE_SKILLSFX, //������Ч
	ACTORTYPE_OTHERSFX,//ͨ����Ч
	ACTORTYPE_WEAPONSFX, //������Ч--����װ��
	ACTORTYPE_TRANSPORT, // ���͵�
	ACTORTYPE_COLLECT,	//�ɼ���
	ACTORTYPE_PATHFIND_POINT,	//Ѱ·��
	ACTORTYPE_PET,						//����
	ACTORTYPE_WEAPON,// ����
	ACTORTYPE_MOUNT,// ����
	ACTORTYPE_WING,// ���
	ACTORTYPE_OBJECT_NORMAL,//ͨ��Object
	ACTORTYPE_SCENEOBJECT,//����Object
	ACTORTYPE_FLAG,	//����
	ACTORTYPE_CONVOY, // �ڳ�
	ACTORTYPE_MAGICWEAPONSFX, // ����������Ч
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
	Object_Type_Player				= 1,			//�������ͣ����
	Object_Type_Npc					= 2,			//�������ͣ�npc
	Object_Type_Monster			= 3,			//�������ͣ�monster
	Object_Type_System				= 4,			//�������ͣ�ϵͳ
	Object_Type_Guild				= 5,			//�������ͣ�����
	Object_Type_Team				= 6,			//�������ͣ�����
	Object_Type_Object				= 7,			//������ͣ�object
	Object_Type_TRANSPORT		= 8,			//������ͣ����͵�
	Object_Type_COLLECT			= 9,			//������ͣ��ɼ�
	Object_Type_Pet					= 10,		//������ͣ�����
	Object_Type_Equipment		= 11,		//������ͣ�װ��
	Object_Type_Map					= 12,		//������ͣ���ͼ
	Object_Type_Task					= 13,		//������ͣ�����
	Object_Type_SkillEffect			= 14,		//������ͣ�������Ч
	Object_Type_Normal			= 15,		//������ͣ�ͨ��
	Object_Type_Daily				= 16,		//������ͣ��ճ�
	Object_Type_Mount				= 17,		//������ͣ�����
	Object_Type_Item					= 18,		//������ͣ���Ʒ
	Object_Type_Mail					= 19,		//������ͣ��ʼ�
};

#endif
