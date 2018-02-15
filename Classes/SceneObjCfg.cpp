#include "SceneObjCfg.h"
#include "BinTable.h"
#include "Text.h"
#include "TextDef.h"
#include "cocos2d.h"

using namespace cocos2d;

SceneObjCfg::SceneObjCfg()
{
	init("specialscene");
}

SceneObjCfg::~SceneObjCfg()
{

}

bool SceneObjCfg::init( const char* pszItemCfgName )
{
	if( !pszItemCfgName )
	{
		log( "SceneObjCfg::init false pszItemCfgName=NULL" );
		return false;
	}

	TTableGroup  group;
	group.Load(pszItemCfgName);
	TTable* tableItem =  group.GetTable("specialscene");

	if( !tableItem )
	{
		log("SceneObjCfg::init false GetTable pszItemCfgName[%s]", pszItemCfgName);
		return false;
	}

	for( int i = 0; i < tableItem->m_recordCount; ++i )
	{
		int nRecordIndex = i + 1;
		SceneObjData stItemData;
		stItemData.m_nID = tableItem->GetField( nRecordIndex, "id" );
		stItemData.m_Type = (SceneObjType)0;
		stItemData.m_Name = tableItem->GetFieldString( nRecordIndex, "name" );
		stItemData.m_AnimationID = tableItem->GetField( nRecordIndex, "spriteID" );
		stItemData.m_Scale = tableItem->GetField( nRecordIndex, "scale" ) / 10000.0f;
		stItemData.m_Layer = tableItem->GetField( nRecordIndex, "layer" );

		if( findSceneObjDataByID(stItemData.m_nID) )
		{
			log("SceneObjCfg::init false exist id[%d] pszItemCfgName[%s]", stItemData.m_nID, pszItemCfgName);
			continue;
		}

		m_itemDatas[stItemData.m_nID] = stItemData;
	}

	return true;
}
