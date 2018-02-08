#pragma once

//#include "base.h"

//角色属性记录类型
//为了和服务器erlang(小写)保持一致，故小写
enum CharProperty_Type
{
	CharProperty_attack						=	0	,//攻击力
	CharProperty_defence					=	1	,//防御力
	CharProperty_ph_def						=	2	,//物理抗性
	CharProperty_fire_def					=	3	,//火抗性
	CharProperty_ice_def					=	4	,//冰抗性
	CharProperty_elec_def					=	5	,//电抗性
	CharProperty_poison_def					=	6	,//毒抗性
	CharProperty_max_life					=	7	,//生命值上限
	CharProperty_life_recover				=	8	,//生命秒回
	CharProperty_been_attack_recover		=	9	,//击中回血
	CharProperty_damage_recover				=	10	,//伤害回血
	CharProperty_coma_def					=	11	,//昏迷抵抗
	CharProperty_hold_def					=	12	,//定身抵抗
	CharProperty_silent_def					=	13	,//沉默抵抗
	CharProperty_move_def					=	14	,//减速抵抗
	CharProperty_hit						=	15	,//命中
	CharProperty_dodge						=	16	,//闪避
	CharProperty_block						=	17	,//格挡
	CharProperty_crit						=	18	,//暴击
	CharProperty_pierce						=	19	,//穿透
	CharProperty_attack_speed				=	20	,//攻速
	CharProperty_tough						=	21	,//坚韧
	CharProperty_crit_damage_rate			=	22	,//暴击伤害倍率
	CharProperty_block_dec_damage			=	23	,//格挡减伤
	CharProperty_phy_attack_rate			=	24	,//物理伤害乘数
	CharProperty_fire_attack_rate			=	25	,//火伤害乘数
	CharProperty_ice_attack_rate			=	26	,//冰伤害乘数
	CharProperty_elec_attack_rate			=	27	,//电伤害乘数
	CharProperty_poison_attack_rate			=	28	,//毒伤害乘数
	CharProperty_phy_def_rate				=	29	,//防物理伤害乘数
	CharProperty_fire_def_rate				=	30	,//防火伤害乘数
	CharProperty_ice_def_rate				=	31	,//防冰伤害乘数
	CharProperty_elec_def_rate				=	32	,//防电伤害乘数
	CharProperty_poison_def_rate			=	33	,//防毒伤害乘数
	CharProperty_treat_rate					=	34	,//施法治疗效果乘数
	CharProperty_treat_rate_been			=	35	,//被治疗效果乘数
	CharProperty_life_recover_MaxLife		=	36	,//生命秒回按总生命值的百分比恢复
	CharProperty_move_speed					=	37	,//移动速度

	CharProperty_coma_def_rate				=	38	,//昏迷抵抗率
	CharProperty_hold_def_rate				=	39	,//定身抵抗率
	CharProperty_silent_def_rate			=	40	,//沉默抵抗率
	CharProperty_move_def_rate				=	41	,//减速抵抗率
	CharProperty_hit_rate					=	42	,//命中率
	CharProperty_dodge_rate					=	43	,//闪避率
	CharProperty_block_rate					=	44	,//格挡率
	CharProperty_crit_rate					=	45	,//暴击率
	CharProperty_pierce_rate				=	46	,//穿透率
	CharProperty_attack_speed_rate			=	47	,//攻速率
	CharProperty_tough_rate					=	48	,//坚韧率

	CharProperty_all_def					=	49  ,//全抗性
	CharProperty_all_exception				=	50	,//全异常
	CharProperty_all_exception_rate			=	51	,//全异常率
	CharProperty_all_damage					=	52	,//攻全伤害
	CharProperty_def_damage					=	53	,//防全伤害

	CharProperty_Count						=	55	,//属性个数
};

//物件名字颜色类型
enum CharNameColorType
{
	//不能攻击
	CharNameColorType_CanNotAttack			= 0,
	//可以攻击
	CharNameColorType_CanAttack				= 1,
	//死亡
	CharNameColorType_Dead					= 2,
};

//角色属性
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
