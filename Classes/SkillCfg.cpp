#include "SkillCfg.h"
#include "BinTable.h"
#include <algorithm>

SkillCfg::SkillCfg()
{
	init("skill", "skill_effect");
}

SkillCfg::~SkillCfg()
{
}


bool	SkillCfg::init( const char* pFile, const char *pFileEffect )
{
	if( pFile == NULL || pFileEffect==NULL )
		return false;
	m_mapSkillCfgTable.clear(); 
	m_mapSpecialSkillCfgTable.clear();
	m_mapSkillGroupTable.clear();
	TTableGroup group;
	group.Load(pFile);


	TTable* pTable =  group.GetTable( "skill" );
	if( !pTable )
		return false;

	SkillNoteData skillNotedata;
	SkillNoteInfo skillNoteInfodata;
	for( int i=1; i<=pTable->m_recordCount; ++i )
	{
		SkillInfo data;
		data.id = pTable->GetField(i, "SkillID");
		string name = pTable->GetFieldString(i, "SkillName");
		data.SkillClass = pTable->GetField(i, "SkillClass");
		data.Studylevel = pTable->GetField(i, "Studylevel");
		data.Money_Type=pTable->GetField(i,"Money_Type");
		data.CastMoney = pTable->GetField(i, "CastMoney");
		data.Need_Experience = pTable->GetField(i, "Need_Experience");
		data.Need_Item = pTable->GetField(i, "Need_Item");
		data.Item_Quantity=pTable->GetField(i,"Item_Quantity");
		data.petskill_del=pTable->GetField(i,"petskill_del");
		data.groupId = pTable->GetField(i, "SkillGroup");
		data.level = pTable->GetField(i, "ExtendLevel");
		data.branchof = pTable->GetField(i, "branchof");
		data.nSkillIcon = pTable->GetField(i, "SkillIcon");
		//char sz[256];
		//sprintf( sz, "Icon/SkillIcon/s%d.png", nSkillIcon );//需要改回nskillicon
		//data.SkillIcon = sz;
		data.SkillAct = max( pTable->GetField(i, "SkillAct")-1, 0 );
		data.EffectGroup = pTable->GetField(i, "EffectGroup");
		data.EffectID = pTable->GetField(i, "EffectID");
		data.FlyType = pTable->GetField(i, "FlyType");
		data.Ranger = pTable->GetField(i, "Ranger");
		data.SkillRange = pTable->GetField(i, "SkillRange");
		data.SkillCoolDown = pTable->GetField(i, "SkillCoolDown");
		data.SkillCoolDownGroup = pTable->GetField(i, "SkillCoolDownGroup");
		data.Skill_GlobeCoolDown = pTable->GetField(i, "Skill_GlobeCoolDown");
		data.Skill_TriggerType = pTable->GetField(i, "SkillTriggerType");
		data.TriggerChance= pTable->GetField(i,"TriggerChance");   
		data.ProcSkill=pTable->GetField(i, "ProcSkill");   
		data.ProcChance=pTable->GetField(i, "ProcChance");
		data.DamageType = pTable->GetField(i, "DamageType");
		data.DamagePercent = pTable->GetField(i, "DamagePercent");
		data.DamageFixValue = pTable->GetField(i, "DamageFixValue");
	    data.EffectTimes = max( 1, pTable->GetField(i, "EffectTimes") );
		data.CreateAOE = pTable->GetField(i, "CreateAOE");
		data.AOEDelay = pTable->GetField(i, "AOEDelay");
		data.AOEEffectTarget = pTable->GetField(i, "AOEEffectTarget");
		data.AOEEffectBind = pTable->GetField(i, "AOEBind");
		data.Skill_UseTargetType = pTable->GetField(i, "SkillUseTargetType");
		data.Skill_Hate = pTable->GetField(i, "Skill_Hate");
		data.Use_Spec = pTable->GetField(i, "Use_Spec");
		data.Skill_school = pTable->GetField(i, "Skill_school");
		data.SkillAttackType = pTable->GetField(i, "SkillAttackType");
        data.MaxEffectCount = pTable->GetField(i, "MaxEffectCount");
		data.ShakeType = pTable->GetField(i, "ShakeType");
		data.ShakeRate = pTable->GetField(i, "ShakeRate");
		string SkillNote = pTable->GetFieldString(i, "SkillInfo");
		data.Base_point = pTable->GetField(i, "Base_point");
		data.Attack_Start_Sound = pTable->GetField(i, "Attack_Start");
		data.Attack_Success_Sound = pTable->GetField(i, "Attack_Succeed");
		data.Hit_Sound = pTable->GetField(i, "Hit_Sound");
		data.attackType = pTable->GetField(i,"attackType");
		data.useMap = pTable->GetFieldString(i,"useMap");
		data.max_count = pTable->GetField(i,"max_count");
		data.aggressiveTime = pTable->GetField(i,"aggressiveTime");
		data.hit_recover = pTable->GetField(i,"hit_recover");
		data.add_crit = pTable->GetField(i,"add_crit");
		data.add_hitrecover = pTable->GetField(i,"add_hitrecover");
		data.add_damageRecover = pTable->GetField(i,"add_damageRecover");
		data.Mobile_Type =  pTable->GetField(i,"Mobile_Type");
		data.Removing =  pTable->GetField(i,"Removing");
		data.MDamagePercent = pTable->GetField(i,"MDamagePercent");
		data.MDamageFixValue = pTable->GetField(i,"MDamageFixValue");
		data.DefDamagePercent = pTable->GetField(i,"DefDamagePercent");
		data.MDefDamagePercent = pTable->GetField(i,"MDefDamagePercent");
		data.Hit_Number = pTable->GetField(i,"Hit_Number");
		data.EffectWeaponID = pTable->GetField(i,"EffectWeaponID");
        data.Semicircle = pTable->GetField(i,"Semicircle");
		data.skill_nerve = pTable->GetField(i,"skill_nerve");
        data.Semicircle = pTable->GetField(i,"Semicircle");
		data.hit_times = pTable->GetField(i,"hit_times");
		m_mapSkillCfgTable[data.id] = data;
		//////////////////////////////////////////////////////////////////////////
		if (skillNotedata.groupId != data.groupId)
		{
			skillNotedata.vSkillId.clear();
		}
		skillNotedata.groupId = data.groupId;

		skillNoteInfodata.skillId =data.id;
		skillNoteInfodata.skillnote =name + "^";
		skillNoteInfodata.skillnote += SkillNote;
		if (data.SkillClass == SkillClass_Unusual)
			m_mapSpecialSkillCfgTable[data.id] = data;
		if(isRepeatSkillNote(data.groupId,skillNoteInfodata.skillnote,skillNoteInfodata.skillId))
		{
			continue;
		}
		skillNotedata.vSkillId.push_back(skillNoteInfodata);
		m_mapNameDesc[data.groupId] = skillNotedata;
	}

	map<int, SkillInfo>::iterator it = m_mapSkillCfgTable.begin();
	for(; it != m_mapSkillCfgTable.end(); ++it )
	{
		map<int, SkillGroup>::iterator itGroup = m_mapSkillGroupTable.find(it->second.groupId);
		if( itGroup == m_mapSkillGroupTable.end() )
		{
			SkillGroup group;
			group.groupId = it->second.groupId;
			group.levels.push_back(it->second);
			group.maxLevel =group.levels.size();
			m_mapSkillGroupTable[group.groupId] = group;
		}
		else
		{
			itGroup->second.levels.push_back(it->second);
			itGroup->second.maxLevel = itGroup->second.levels.size();
		}
	}

	TTableGroup group2;
	group2.Load(pFileEffect);
	pTable =  group2.GetTable( "skill_effect" );
	for( int i=0; i<pTable->m_recordCount; ++i )
	{
		int skillId = pTable->GetField(i, "skill_id");
		map<int, SkillInfo>::iterator it = m_mapSkillCfgTable.find(skillId);
		if( it == m_mapSkillCfgTable.end() )
			continue;
		EffectData data;
		data.effect_type = pTable->GetField(i, "effect_typea");
		data.effect_target_type = pTable->GetField(i, "effect_target_type");
		data.param1 = pTable->GetField(i, "param1");
		data.param2 = pTable->GetField(i, "param2");
		data.param3 = pTable->GetField(i, "param3");
		data.param4 = pTable->GetField(i, "param4");
		it->second.vEffect.push_back(data);
	}
	return true;
}

const SkillInfo *SkillCfg::getSkillCfgDataByGroupAndLevel(int group, int level)
{
	map<int, SkillGroup>::iterator itGroup = m_mapSkillGroupTable.find(group);
	if(itGroup == m_mapSkillGroupTable.end())
		return NULL;

	if(level > itGroup->second.maxLevel)
		return NULL;

	vector<SkillInfo>::iterator itLevel = itGroup->second.levels.begin();
	for( ; itLevel != itGroup->second.levels.end(); ++itLevel )
	{
		if( itLevel->level == level )
			return &(*itLevel);
	}
	return NULL;
}

const SkillInfo * SkillCfg::getCheats( int neverId , int LevelId)
{
	map<int,SkillGroup>::iterator it = m_mapSkillGroupTable.find(int(SkillClass_Secret));
	if (it == m_mapSkillGroupTable.end())
	{
		return NULL;
	}

	vector<SkillInfo>::iterator itLevel = it->second.levels.begin();
	for( ; itLevel != it->second.levels.end(); ++itLevel)
	{
		if (itLevel->skill_nerve == neverId && itLevel->level == LevelId)
		{
			return &(*itLevel);
		}
	}
	return NULL;
}

std::string SkillCfg::getName(SkillInfo * pInfo)
{
	if(pInfo == NULL)
		return "";

	std::string tmp1 = "";
	std::string tmp = "";
	map<int, SkillNoteData>::iterator itr = m_mapNameDesc.find(pInfo->groupId);
	if(itr == m_mapNameDesc.end())
		return "";

	vector<SkillNoteInfo>::iterator it = itr->second.vSkillId.begin();
	
	if (it == itr->second.vSkillId.end())
	{
		return "";
	}

	for ( ;it != itr->second.vSkillId.end(); ++it)
	{
		if (pInfo->id >= it->skillId)
		{
			tmp1 = it->skillnote;
		}
		if (pInfo->id <= it->skillId)
		{
			tmp = it->skillnote;
			break;
		}
	}
	int pos = tmp.find('^');
	if(pos == -1)
		return "";

	return tmp.substr(0, pos);
}

std::string SkillCfg::getSkillNode(SkillInfo * pInfo)
{
	if(pInfo == NULL)
		return "";

	std::string tmp = "";
	std::string tmp1 = "";
	map<int, SkillNoteData>::iterator itr = m_mapNameDesc.find(pInfo->groupId);
	if(itr == m_mapNameDesc.end())
		return "";

	vector<SkillNoteInfo>::iterator it = itr->second.vSkillId.begin();

	if (it == itr->second.vSkillId.end())
	{
		return "";
	}

	for ( ;it != itr->second.vSkillId.end(); ++it)
	{
		if (pInfo->id >= it->skillId)
		{
			tmp1 = it->skillnote;
		}
		if (pInfo->id <= it->skillId)
		{
			tmp = it->skillnote;
			break;
		}
	}

	int pos = tmp1.find('^');
	if(pos == -1)
		return "";

	return tmp1.substr(pos+1, tmp.length());
}

std::string SkillCfg::getName(const SkillInfo * pInfo)
{
	if(pInfo == NULL)
		return "";

	std::string tmp = "";
	map<int, SkillNoteData>::iterator itr = m_mapNameDesc.find(pInfo->groupId);
	if(itr == m_mapNameDesc.end())
		return "";

	vector<SkillNoteInfo>::iterator it = itr->second.vSkillId.begin();

	if (it == itr->second.vSkillId.end())
	{
		return "";
	}

	string tmp1;
	for ( ;it != itr->second.vSkillId.end(); ++it)
	{
		if (pInfo->id <= it->skillId)
		{
			tmp = it->skillnote;
			break;
		}
	}
	int pos = tmp.find('^');
	if(pos == -1)
		return "";

	return tmp.substr(0, pos);
}

std::string SkillCfg::getSkillNode(const SkillInfo * pInfo)
{
	if(pInfo == NULL)
		return "";

	std::string tmp = "";
	map<int, SkillNoteData>::iterator itr = m_mapNameDesc.find(pInfo->groupId);
	if(itr == m_mapNameDesc.end())
		return "";

	vector<SkillNoteInfo>::iterator it = itr->second.vSkillId.begin();

	if (it == itr->second.vSkillId.end())
	{
		return "";
	}

	for ( ;it != itr->second.vSkillId.end(); ++it)
	{
		if (pInfo->id <= it->skillId)
		{
			tmp = it->skillnote;
			break;
		}
	}

	int pos = tmp.find('^');
	if(pos == -1)
		return "";

	return tmp.substr(pos+1, tmp.length());
}

bool SkillCfg::isRepeatSkillNote( int groupId,string name , int skillId)
{
	map<int, SkillNoteData> :: iterator it = m_mapNameDesc.find(groupId);
	if (it == m_mapNameDesc.end())
	{
		return false;
	}

	SkillNoteData stData = it->second;
	vector<SkillNoteInfo>::iterator iter = stData.vSkillId.begin();
	if (iter == stData.vSkillId.end())
	{
		return false;
	}
	for (;iter != stData.vSkillId.end();++iter)
	{
		if(!strcmp(iter->skillnote.c_str(),name.c_str()))
		{
			(*iter).skillId = skillId;
			m_mapNameDesc[stData.groupId] = stData;
			return true;
		}
	}
	return false;
}

