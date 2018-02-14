#ifndef __SHIP_MAP_CFG_H__
#define __SHIP_MAP_CFG_H__

#include "base.h"
#include "MapSettingCfg.h"
#include <vector>
#include <string>
#include <map>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;
//#include "BusPathSeeker.h"

//class Map;
//class ConfigChecking;
class MapObject
{
	//friend class Map;
	friend class ConfigChecking;

	int type;
	int id; 
	int x;
	int y;
	vector<int> params;	
private:
	string name;
public:
	string GetName();
};

class DanamicMapObject: public MapObject
{
	int virtualID;
};

class TransportData : public MapObject
{
	TransportData(MapObject &obj);

	int getDestMapId();

	Point getPos();

	int getLevelLimit();
};


class MapData
{
	int id;
	//��ͼ�ϵĹ�����NPC
	vector<MapObject> objects;
	vector<DanamicMapObject> dynamic_objects;//��ͼ�ж�̬��object ��Ŀǰ��ս���õ�
	//��ͼ�ϵĴ��͵�
	vector<TransportData> transport;
	//Ѱ·վ̨����
	//BUS_STATIONS busStations;
	//Ѱ·վ�����ID
	int	iMaxStationId;
	//��ͼ�����
	char* phyData;
	//��Դ��
	string  resName;
	//���ؿ�
	int  widthInPixel;
	//���ӿ�
	int  widthInTile;
	//������
	int  widthInPhy;
	//���ظ�
	int  heightInPixel;
	//���Ӹ�
	int  heightInTile;
	//������
	int  heightInPhy;
	string name;//��ͼ����

	void loadData( const MapSettingData* pMapSettingData );

	MapData()
	{
		phyData=nullptr;
	}


	~MapData()
	{
		SAFE_DELETE_ARRAY(phyData);
	}
};

class ObjectPos
{
	int mapID;
	int posX;
	int posY;

	ObjectPos()
	{
		mapID = 0;
		posX = 0;
		posY = 0;
	}
};

class MapCfg
{
private:
	MapCfg();
public:
	~MapCfg();

	static MapCfg& instance( void )
	{
		static MapCfg	s;
		return s;
	}

	bool init( map<int, MapSettingData> *pMapSetting );

	const MapData *getMapCfgData(int dataId)
	{
		map<int, MapData*>::iterator it = m_mapCfgTable.find(dataId);
		if( it == m_mapCfgTable.end() )
			return nullptr;
		return it->second;
	}

	const ObjectPos *getNpcPosByID(int dataID)
	{
		map<int, ObjectPos*>::iterator it = m_objNpcPosTable.find(dataID);
		if(it == m_objNpcPosTable.end())
			return nullptr;
		return it->second;
	}

	const ObjectPos *getPilePosByID(int dataID)
	{
		map<int, ObjectPos*>::iterator it = m_objPilePosTable.find(dataID);
		if(it == m_objPilePosTable.end())
			return nullptr;
		return it->second;
	}
	
private:
	map<int, MapData*>  m_mapCfgTable;
	map<int, ObjectPos*> m_objNpcPosTable;	//npcλ�ñ�
	map<int, ObjectPos*> m_objPilePosTable;	//׮׮λ�ñ�
};
#endif