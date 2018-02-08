#pragma once

//#include "base.h"

//��ɫ���Լ�¼����
//Ϊ�˺ͷ�����erlang(Сд)����һ�£���Сд
enum CharProperty_Type
{
	CharProperty_attack						=	0	,//������
	CharProperty_defence					=	1	,//������
	CharProperty_ph_def						=	2	,//������
	CharProperty_fire_def					=	3	,//����
	CharProperty_ice_def					=	4	,//������
	CharProperty_elec_def					=	5	,//�翹��
	CharProperty_poison_def					=	6	,//������
	CharProperty_max_life					=	7	,//����ֵ����
	CharProperty_life_recover				=	8	,//�������
	CharProperty_been_attack_recover		=	9	,//���л�Ѫ
	CharProperty_damage_recover				=	10	,//�˺���Ѫ
	CharProperty_coma_def					=	11	,//���Եֿ�
	CharProperty_hold_def					=	12	,//����ֿ�
	CharProperty_silent_def					=	13	,//��Ĭ�ֿ�
	CharProperty_move_def					=	14	,//���ٵֿ�
	CharProperty_hit						=	15	,//����
	CharProperty_dodge						=	16	,//����
	CharProperty_block						=	17	,//��
	CharProperty_crit						=	18	,//����
	CharProperty_pierce						=	19	,//��͸
	CharProperty_attack_speed				=	20	,//����
	CharProperty_tough						=	21	,//����
	CharProperty_crit_damage_rate			=	22	,//�����˺�����
	CharProperty_block_dec_damage			=	23	,//�񵲼���
	CharProperty_phy_attack_rate			=	24	,//�����˺�����
	CharProperty_fire_attack_rate			=	25	,//���˺�����
	CharProperty_ice_attack_rate			=	26	,//���˺�����
	CharProperty_elec_attack_rate			=	27	,//���˺�����
	CharProperty_poison_attack_rate			=	28	,//���˺�����
	CharProperty_phy_def_rate				=	29	,//�������˺�����
	CharProperty_fire_def_rate				=	30	,//�����˺�����
	CharProperty_ice_def_rate				=	31	,//�����˺�����
	CharProperty_elec_def_rate				=	32	,//�����˺�����
	CharProperty_poison_def_rate			=	33	,//�����˺�����
	CharProperty_treat_rate					=	34	,//ʩ������Ч������
	CharProperty_treat_rate_been			=	35	,//������Ч������
	CharProperty_life_recover_MaxLife		=	36	,//������ذ�������ֵ�İٷֱȻָ�
	CharProperty_move_speed					=	37	,//�ƶ��ٶ�

	CharProperty_coma_def_rate				=	38	,//���Եֿ���
	CharProperty_hold_def_rate				=	39	,//����ֿ���
	CharProperty_silent_def_rate			=	40	,//��Ĭ�ֿ���
	CharProperty_move_def_rate				=	41	,//���ٵֿ���
	CharProperty_hit_rate					=	42	,//������
	CharProperty_dodge_rate					=	43	,//������
	CharProperty_block_rate					=	44	,//����
	CharProperty_crit_rate					=	45	,//������
	CharProperty_pierce_rate				=	46	,//��͸��
	CharProperty_attack_speed_rate			=	47	,//������
	CharProperty_tough_rate					=	48	,//������

	CharProperty_all_def					=	49  ,//ȫ����
	CharProperty_all_exception				=	50	,//ȫ�쳣
	CharProperty_all_exception_rate			=	51	,//ȫ�쳣��
	CharProperty_all_damage					=	52	,//��ȫ�˺�
	CharProperty_def_damage					=	53	,//��ȫ�˺�

	CharProperty_Count						=	55	,//���Ը���
};

//���������ɫ����
enum CharNameColorType
{
	//���ܹ���
	CharNameColorType_CanNotAttack			= 0,
	//���Թ���
	CharNameColorType_CanAttack				= 1,
	//����
	CharNameColorType_Dead					= 2,
};

//��ɫ����
struct CharProperty
{
	int	attack;
	int	defence;
	int	ph_def;
	int	fire_def;
	int	ice_def;
	int	elec_def;
	int	poison_def; 
	int	max_life;
	int	life_recover;
	int	been_attack_recover;
	int	damage_recover;
	int	coma_def; 
	int	hold_def;
	int	silent_def;
	int	move_def;
	int	hit;
	int	dodge;
	int	block;
	int	crit;
	int	pierce; 
	int	attack_speed;
	int	tough;
	int	crit_damage_rate;
	int	block_dec_damage;
	int	phy_attack_rate;
	int	fire_attack_rate;
	int	ice_attack_rate;
	int	elec_attack_rate;
	int	poison_attack_rate;
	int	phy_def_rate;
	int	fire_def_rate;
	int	ice_def_rate;
	int	elec_def_rate;
	int	poison_def_rate;
	int	treat_rate;
	int	on_treat_rate;
	int	move_speed;
};
