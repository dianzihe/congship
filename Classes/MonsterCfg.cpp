#include "MonsterCfg.h"
//#include "BinTable.h"

MonsterCfg::MonsterCfg()
{
	init( "monster" );
}

MonsterCfg::~MonsterCfg()
{

}

bool MonsterCfg::init(const char *pFile)
{
	/*
	if( pFile == NULL )
		return false;
	m_mapMonsterTable.clear(); 
	TTableGroup* pTableGroup = BinTable::GetTalbeGroup( pFile );
	if( !pTableGroup )
		return false;

	TTable* pTable =  pTableGroup->GetTable( "monster" );
	if( !pTable )
		return false;
		
	for( int i = 1; i <= pTable->m_recordCount; ++i )
	{
		MonsterData data;
		data.id = pTable->GetField(i, "id");
		data.name = pTable->GetFieldString( i, "name" );
		data.animation = pTable->GetField(i, "animation");
		data.mobHead = pTable->GetField(i, "mobhead");
		data.level = pTable->GetField(i, "level");
		data.exp = pTable->GetField(i, "exp");

		data.attackSpeed = pTable->GetField(i, "attackSpeed");
		data.attack = pTable->GetField(i, "attack");
		data.defence = pTable->GetField(i, "defence");
		data.max_life = pTable->GetField(i, "max_life");
		data.ph_def = pTable->GetField(i, "ph_def");
		data.fire_def = pTable->GetField(i, "fire_def");
		data.ice_def = pTable->GetField(i, "ice_def");
		data.elec_def = pTable->GetField(i, "elec_def");
		data.poison_def = pTable->GetField(i, "poison_def");
		data.hit_rate_rate = pTable->GetField(i, "hit_rate_rate");
		data.dodge_rate = pTable->GetField(i, "dodge_rate");
		data.block_rate = pTable->GetField(i, "block_rate");
		data.crit_rate = pTable->GetField(i, "crit_rate");
		data.coma_def_rate = pTable->GetField(i, "coma_def_rate");
		data.hold_def_rate = pTable->GetField(i, "hold_def_rate");
		data.silent_def_rate = pTable->GetField(i, "silent_def_rate");
		data.move_def_rate = pTable->GetField(i, "move_def_rate");
		data.baseSkillID = pTable->GetField(i, "BaseSkill_ID");

		data.monsterCd = pTable->GetField(i, "monsterCd");
		data.PatrolRadius = pTable->GetField(i, "PatrolRadius");
		data.WatchRadius = pTable->GetField(i, "WatchRadius");
		data.FollowRadius = pTable->GetField(i, "FollowRadius");
		data.Active = pTable->GetField(i, "Active");
		data.droplist = pTable->GetField(i, "droplist");
		data.faction = pTable->GetField(i, "faction");
		data.attack_mode = pTable->GetField(i, "attack_mode");
		int nmodelscale = pTable->GetField(i, "modelscal");
		data.modelscale = nmodelscale / 10000.0f;

		int wildMaxScale = pTable->GetField( i, "wildFigure" );
		data.wildMaxScale =wildMaxScale / 10.f;
		data.monstertype = pTable->GetField( i, "monstertype");
		m_mapMonsterTable[data.id] = data;
	}
	*/
	return true;
}