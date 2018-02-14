#include "MapCfg.h"
#include "Actor.h"
#include "MonsterCfg.h"
//#include "NpcCfg.h"
//#include "Text.h"
//#include "TextDef.h"
//#include "Binary.h"
//#include "Map.h"
//#include "ObjectCfg.h"


string MapObject::GetName()
{
	/*
	if( name.size() == 0 )
	{
		switch( type )
		{
		case ACTORTYPE_MONSTER:
			{
				const MonsterData *pData = MonsterCfg::instance().getMonsterCfgData(id);
				if(pData)
				{
					name = pData->name;
				}
			}
			break;
		
		case ACTORTYPE_NPC:
			{
				const NpcData *pData = NpcCfg::instance().getNpcCfgData(id);
				if( pData )
				{
					name = pData->name;
				}
			}
			break;
		case ACTORTYPE_COLLECT:
			{
				const ObjectData *pData = ObjectCfg::instance().findObjectDataByID(id);
				if(pData)
				{
					name = pData->m_name;
				}
			}
			break;
		}
		
	}
*/
	return name;
}
	
TransportData::TransportData(MapObject &obj)
{
	type = obj.type;
	id = obj.id;
	x = obj.x;
	y = obj.y;
	params = obj.params;
}



int TransportData::getDestMapId()
{
	if(params.size())
		return params[0];
	return 0;
}

CCPoint TransportData::getPos()
{
	if(params.size() >=3)
	{
		return ccp(params[1], params[2]);
	}
	return CCPointZero;
}

int TransportData::getLevelLimit()
{
	if(params.size() >=4)
	{
		return params[3];
	}
	return 0;
}

MapCfg::MapCfg()
{
	init(&(MapSettingCfg::instance().getMapSettingCfgTable()));
}

MapCfg::~MapCfg()
{
	map<int, MapData*>::iterator it = m_mapCfgTable.begin();
	for( ; it != m_mapCfgTable.end(); ++it )
	{
		SAFE_DELETE(it->second);
	}
	m_mapCfgTable.clear();

	for(map<int, ObjectPos*>::iterator it=m_objNpcPosTable.begin(); it!=m_objNpcPosTable.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	m_objNpcPosTable.clear();

	for(map<int, ObjectPos*>::iterator it=m_objPilePosTable.begin(); it!=m_objPilePosTable.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	m_objPilePosTable.clear();
}

void MapData::loadData( const MapSettingData* pMapSettingData )
{
	resName = pMapSettingData->res;
	name=pMapSettingData->name;
	string ss = ("Map/" + pMapSettingData->MapScn );

	unsigned long len = 0;
	char* data = (char*)CCFileUtils::sharedFileUtils()->getFileData( ss.c_str(), "rb", &len );
	if (data ==  NULL)
	{
		char txt[256];
		sprintf(txt,"%s",CText::GetText(CTextDef::MAP_NULL).c_str());
		//MessageTips::showMessageTips(txt);
		return;
	}

	int off = 0;
	string name;
	BUFF_READ_STRING2(name, data, off);
	BUFF_READ_INT(widthInPhy, data, off);
	BUFF_READ_INT(heightInPhy, data, off);
	widthInPixel = widthInPhy * MAP_PHY_TILE_W;
	widthInTile = widthInPixel/MAP_RENDER_TILE_W;

	heightInPixel = heightInPhy * MAP_PHY_TILE_H;
	heightInTile = heightInPixel/MAP_RENDER_TILE_H;

	phyData = new char[widthInPhy*heightInPhy];
	memset(phyData, 0, sizeof(char) * widthInPhy*heightInPhy);
	for(int i = 0; i < widthInPhy; i++)
	{
		for(int j = 0; j < heightInPhy; j++)
		{
			int v;
			BUFF_READ_BYTE(v, data, off);
			phyData[i + j*widthInPhy] |= v;
		}
	}

	if ( off < (int)len )
	{
		int count;
		BUFF_READ_INT(count, data, off);
		for( int i=0; i<count; ++i )
		{
			MapObject object;
			BUFF_READ_INT( object.type, data, off );
			BUFF_READ_INT( object.id, data, off );
			BUFF_READ_INT( object.x, data, off );
			BUFF_READ_INT( object.y, data, off );

			object.y = heightInPixel - object.y;

			int paramCount;
			BUFF_READ_INT( paramCount, data, off );
			for(int i=0; i<paramCount; i++)
			{
				int str;
				BUFF_READ_INT( str, data, off );
				object.params.push_back(str);
			}
			objects.push_back(object);

			if( object.type == ACTORTYPE_TRANSPORT)
			{
				TransportData tr(object);
				transport.push_back(tr);
			}
		}
	}

	int busStationCount = 0;
	int childCount = 0;
	iMaxStationId = 0;
	BUFF_READ_INT( busStationCount, data, off );
	for( int i=0; i<busStationCount; ++i )
	{
		BusStation station;
		BUFF_READ_INT( station.stationId, data, off );
		BUFF_READ_INT( station.pos.col, data, off );
		BUFF_READ_INT( station.pos.row, data, off );
		station.pos.row = heightInPhy-station.pos.row;
		BUFF_READ_INT( childCount, data, off );
		for( int j=0; j<childCount; ++j )
		{
			StationReachInfo info;
			BUFF_READ_INT( info.stationId, data, off );
			station.canReachStations.push_back(info);
		}
		if(station.stationId>iMaxStationId) 
			iMaxStationId=station.stationId;

		if(childCount)
			busStations[station.stationId] = station;
	}
	SAFE_DELETE_ARRAY(data);
}

bool	MapCfg::init( map<int, MapSettingData> *pMapSetting )
{
	if( !pMapSetting )
		return false;
	map<int, MapSettingData>::iterator itSet = pMapSetting->begin();
	for( ; itSet != pMapSetting->end(); ++itSet )
	{
		MapData *data = new MapData();
		data->loadData( &(itSet->second) );
		data->id = itSet->second.id;

		for(vector<MapObject>::iterator objIt = data->objects.begin(); objIt!=data->objects.end(); objIt++)	//npcÎ»ÖÃÓë×®×®Î»ÖÃ
		{
			if(objIt->type == ACTORTYPE_PATHFIND_POINT)
			{
				const ObjectPos *pPointPos = getPilePosByID(objIt->id);
				if(!pPointPos)
				{
					ObjectPos *pObjPos = new ObjectPos;
					pObjPos->mapID = data->id;
					pObjPos->posX = objIt->x;
					pObjPos->posY = objIt->y;
					m_objPilePosTable.insert(make_pair(objIt->id, pObjPos));
				}
			}
			if(objIt->type == ACTORTYPE_NPC)
			{
				const ObjectPos *pPointPos = getNpcPosByID(objIt->id);
				if(!pPointPos)
				{
					ObjectPos *pObjPos = new ObjectPos;
					pObjPos->mapID = data->id;
					pObjPos->posX = objIt->x;
					pObjPos->posY = objIt->y;
					m_objNpcPosTable.insert(make_pair(objIt->id, pObjPos));
				}
			}
		}
		
		m_mapCfgTable[data->id] = data;
	}
	return true;
}