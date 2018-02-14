#ifndef __SHIP_MAP_H__
#define __SHIP_MAP_H__
#include "base.h"
#include "cocos2d.h"
//#include "BusPathSeeker.h"
#include "MapSettingCfg.h"
#include "MapCfg.h"
//#include "../BaseModule/ImageCenter/ImageCenter.h"
#include "MapTile.h"
#include "ActorType.h"
#define MAP_RENDER_TILE_W	256
#define MAP_RENDER_TILE_H	256

#define MAP_PHY_TILE_W	32
#define MAP_PHY_TILE_H	32

#define MAP_UPDATE_CUT_DIS	MAP_PHY_TILE_W

#define MAP_TILE_FLAG_PHY	(1<<0)//物理层
#define MAP_TILE_FLAG_TRANS	(1<<1)//半透明

#define GetTileCenterPixelX(tileX) (tileX * MAP_PHY_TILE_W + MAP_PHY_TILE_W/2)
#define GetTileCenterPixelY(tileY) (tileY * MAP_PHY_TILE_H + MAP_PHY_TILE_H/2)

#define GetTileX(pixelX) (pixelX/MAP_PHY_TILE_W)
#define GetTileY(pixelY) (pixelY/MAP_PHY_TILE_H)

//动态载入值，行走n格进行载入与释放
#define DYNAMIC_LOAD_FLAG		1

enum MAP_LAYER
{
	MAP_LAYER_TILE,
	MAP_LAYER_GROUND,
	MAP_LAYER_ACTOR,
	MAP_LAYER_AIR,
};

//class CCamera;
//class CPlayer;
class ActorManager;
class Actor;
//class SceneObj;
//, public CPathSeekerDelegate
class Map : public Node
{
	CC_SYNTHESIZE(int, m_mapID, MapID);
	CC_SYNTHESIZE(int, m_mapType,MapType);
	CC_SYNTHESIZE(string, m_mapName, MapName);

	enum TargetState
	{
		TargetState_Monster = 1,
		TargetState_Npc = 2,
		TargetState_Rounting = 3,
		TargetState_Player = 4,
	};

	//寻路部分空
public:
	typedef std::vector<MapTile*> MapTileContainer;
	//typedef std::vector<SceneObj*> MapSceneObjectContainer;
	//获取站台数据
	//virtual LPBUS_STATIONS		getStations();
	//获取格子代价
	virtual int getCost(int col, int row);
	//获取格子大小
	virtual  void getTileSize( int *width, int *height);
	//获取使用bus寻路的最短路径
	virtual  int getUseBusPathMinDis();
	//获取最大的站点ID
	virtual  int getMaxStationId();
public:
	Map(void);
	~Map(void);

	void initialize( const MapSettingData* pMapData );
	void unInitialize();

	/*
	bool ccTouchBegan(Touch* touch, CCEvent* event);
	bool ccTouchMoved(CCTouch* touch, CCEvent* event);
	bool ccTouchEnd(CCTouch* touch, CCEvent* event, bool isTeleportMove );
	*/
	virtual void update(float dt);

	bool CanWalkThrough(int phyTileX, int phyTileY);//{return (m_phyData[REVERSE_Y(phyTileY, m_heightInPhy)*m_widthInPhy + phyTileX]&MAP_TILE_FLAG_PHY) == 0;};
	
	template< typename T1, typename T2 >
	bool CanWalkThrough( T1 phyTileX, T2 phyTileY )
	{
		return CanWalkThrough( (int)phyTileX, (int)phyTileY );
	}

	bool IsTransparent(int phyTileX, int phyTileY);//{return (m_phyData[REVERSE_Y(phyTileY, m_heightInPhy)*m_widthInPhy + phyTileX]&MAP_TILE_FLAG_TRANS) != 0;};

	//void GetPlayerPath(CPlayer* player, const CCPoint& start, const CCPoint& end);

	//void visit( );
	//CCamera*  GetCamera(){return m_camera;};
	void UpdateCamera(float dt);
	void UpadteTileAndObjectCut();  //裁剪
	void SetCameraType(int t);
	void SetCameraTarget(const Point& pos);
	void UpdateAllNpcIcon();

	void setActorManager( ActorManager *p){ m_pActorManager = p; };
	void addActorToMap(Actor *actor);
	void delActorFromMap(Actor *actor);

	void addActorToAirNode(Actor *actor);
	void delActorFromAirNode(Actor *actor);
	void removeActorFromAirNode(Actor *actor);

	void addActorToGroundNode(Actor *actor);
	void delActorFromGroundNode(Actor *actor);
	void removeActorFromGroundNode(Actor *actor);

	int getWidthInPixel(){ return m_pMapCfgData->widthInPixel; };
	int getHeightInPixel(){ return m_pMapCfgData->heightInPixel; };

	const MapSettingData* getMapSettingData()	{ return m_pMapSettingData; }

	void doReleaseMemory();

	long long	getServerMapID( void )const			{ return m_nServerMapID; }
	void	setServerMapID( long long n )			{ m_nServerMapID = n; }

	float	getHoldTime(){ return m_fMapHoldAllTime; }
	void	restHoldTime(){ m_fMapHoldAllTime = -1.0f; m_fMapHoldTime = -1.0f; }

	Point GetAccessPosByStep( const Point& beginPos, const Point& endPos );

	bool isMapPackgeNeedUpdate();

	void LoadMapSceneObjects(MapData* pMapData);
	void ReleaseMapSceneObjects();

	void UpdateSceneObjects(float dt);

	float getSceneScale();
	//判断点击状态
	ACTORTYPE JugdeTargetState(Touch* touch, Event* event);
private:
	//更新动态载入
	void updateDynamicLoad();
private:
	//CCamera* m_camera;
	//寻路者
	//CBusPathSeeker	*m_pathSeeker;
	//地图块数据
	//CCSprite**  m_ppTiles;
	
	MapTileContainer m_ppTiles;
	//MapSceneObjectContainer m_pMapSceneObjects;

	Point  m_lastUpdateCut; //上次裁剪计算的位置
	//地图tile层
	Node *m_pTileNode;
	//地图Ground层
	Node *m_pGroundNode;
	//地图actor层
	Node *m_pActorNode;
	//地图Air层
	Node *m_pAirNode;
	//actor管理者
	ActorManager*  m_pActorManager;
	//地图配置数据
	MapData	*m_pMapCfgData;
	const MapSettingData* m_pMapSettingData;

	//RenderBatchData* m_pMiniMapTexture;

	long long			m_nServerMapID;

	float			m_fMapHoldTime;
	float			m_fMapHoldAllTime;
	float			m_fMapHoldAllTimeTeleport;
	Touch	m_HoldTouch;
	//
	Point	m_startTouchPos;
	//触摸时间
	float m_fTouchTime;
	//触摸次数
	int  m_nTouchCount;
	//更新打怪时间
	float m_fAtkTime;
	
};
#endif