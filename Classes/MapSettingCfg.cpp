#include "MapSettingCfg.h"
#include "BinTable.h"

MapSettingCfg::MapSettingCfg()
{
	init("mapsetting");
}

MapSettingCfg::~MapSettingCfg()
{
}


bool MapSettingCfg::init( const char* pFile )
{
	if( pFile == NULL )
		return false;
	m_mapMapSettingCfgTable.clear(); 

	TTableGroup group;
	group.Load(pFile);

	TTable* pTable =  group.GetTable( "mapsetting" );
	if( !pTable )
		return false;

	for( int i=1; i<=pTable->m_recordCount; ++i )
	{
		MapSettingData data;
		data.id = pTable->GetField(i, "id");
		data.name = pTable->GetFieldString(i, "name");
		data.descript = pTable->GetFieldString(i, "descript");
		data.type = pTable->GetField(i, "type");
		data.res = pTable->GetFieldString(i, "res");
		data.MiniMap = pTable->GetFieldString(i, "MiniMap");
		int nMapScn = pTable->GetField(i, "MapScn");
		char sz[256];
		sprintf( sz, "Map%d.scn", nMapScn );
		data.MapScn = sz;
		data.initPosX = pTable->GetField(i, "initPosX");
		data.initPosY = pTable->GetField(i, "initPosY");
		data.PlayerEnter_MinLevel = pTable->GetField(i, "PlayerEnter_MinLevel");
		data.PlayerEnter_MaxLevel = pTable->GetField(i, "PlayerEnter_MaxLevel");
		data.PlayerActiveEnter_Times = pTable->GetField(i, "PlayerActiveEnter_Times");
		data.PlayerActiveTime_Item = pTable->GetField(i, "PlayerActiveTime_Item");
		data.PlayerEnter_Times = pTable->GetField(i, "PlayerEnter_Times");
		data.DropItem1 = pTable->GetField(i, "DropItem1");
		data.DropItem2 = pTable->GetField(i, "DropItem2");
		data.DropItem3 = pTable->GetField(i, "DropItem3");
		data.DropItem4 = pTable->GetField(i, "DropItem4");
		data.DropItem5 = pTable->GetField(i, "DropItem5");
		data.DropItem6 = pTable->GetField(i, "DropItem6");
		data.DropItem7 = pTable->GetField(i, "DropItem7");
		data.DropItem8 = pTable->GetField(i, "DropItem8");

		data.QuitMapID = pTable->GetField(i, "QuitMapID");
		data.QuitMapPosX = pTable->GetField(i, "QuitMapPosX");
		data.QuitMapPosY = pTable->GetField(i, "QuitMapPosY");

		data.pkFlag_Camp = !!pTable->GetField(i, "pkFlag_Camp");
		data.pkFlag_Kill = pTable->GetField(i, "pkFlag_Kill");
		data.pkFlag_QieCuo = !!pTable->GetField(i, "pkFlag_QieCuo");

		data.mapFaction = pTable->GetField(i, "MapFaction");
		data.music = pTable->GetFieldString(i, "Music");
		data.AutoFightInCopyMapRoutPosX = pTable->GetField(i, "AutoFightInCopyMapRoutPosX");
		data.AutoFightInCopyMapRoutPosY = pTable->GetField(i, "AutoFightInCopyMapRoutPosY");

		data.laminate_drop_out =  pTable->GetField(i, "laminate_drop_out");
		data.laminate_Minlevel = pTable->GetField(i, "laminate_Minlevel");
		data.laminate_money = pTable->GetField(i, "laminate_money");

		data.daliy			= pTable->GetField(i, "daliy");

		data.pkflag_all			= pTable->GetField(i, "pkflag_all");
		data.pkflag_guild			= pTable->GetField(i, "pkflag_guild");
		data.pkflag_team			= pTable->GetField(i, "pkflag_team");
		data.pkflag_kindevil			= pTable->GetField(i, "pkflag_kindevil");
		data.laminate_money_type			= pTable->GetField(i, "laminate_money_type");
		data.need_energy			= pTable->GetField(i, "need_energy");
		data.kindevil			= pTable->GetField(i, "kindevil");
		data.revive = pTable->GetField(i,"revive");
		data.vipLevel = pTable->GetField(i,"viplevel");
		data.difficulty = pTable->GetField(i,"difficulty");
		data.headicon = pTable->GetField(i,"headicon");
		data.battleshow = pTable->GetField(i,"battleshow");
		data.petcharacter1 = pTable->GetField(i,"petcharacter1");
		data.petcharacter2 = pTable->GetField(i,"petcharacter2");
		data.petover = pTable->GetField(i,"petover");
		m_mapMapSettingCfgTable[data.id] = data;
	}
	return true;
}