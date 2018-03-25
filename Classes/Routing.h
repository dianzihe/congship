#pragma once
#include "base.h"
#include <list>
#include <vector>
using namespace std;

//class CHero;
class CRouting
{
private:
	CRouting(void);
public:
	~CRouting(void);

	static CRouting &instance()
	{
		static CRouting s;
		return s;
	};

	void init( /*CHero* p*/ );

	//¿ªÊ¼µ¼º½£¬
	bool runNavigation( const int mapId, Point pos);

	void moveToDestMap();

	void flyTo(int map_id, int map_x, int map_y);

	void onArriveNextPos();

	bool isNeedContinueDestMap();

private:
	void _SeekMapPath(int startMap, int destMap, int parent, vector<int> &pathIn, vector<int> &pathOut);

private:
	int								m_destMapId;
	Point						m_destPos;
	int								m_dataId;
	//CHero*							m_pHero;
	list<int>						m_listMapPath;
};
