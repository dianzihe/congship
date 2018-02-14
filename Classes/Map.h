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

#define MAP_TILE_FLAG_PHY	(1<<0)//�����
#define MAP_TILE_FLAG_TRANS	(1<<1)//��͸��

#define GetTileCenterPixelX(tileX) (tileX * MAP_PHY_TILE_W + MAP_PHY_TILE_W/2)
#define GetTileCenterPixelY(tileY) (tileY * MAP_PHY_TILE_H + MAP_PHY_TILE_H/2)

#define GetTileX(pixelX) (pixelX/MAP_PHY_TILE_W)
#define GetTileY(pixelY) (pixelY/MAP_PHY_TILE_H)

//��̬����ֵ������n������������ͷ�
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

	//Ѱ·���ֿ�
public:
	typedef std::vector<MapTile*> MapTileContainer;
	//typedef std::vector<SceneObj*> MapSceneObjectContainer;
	//��ȡվ̨����
	//virtual LPBUS_STATIONS		getStations();
	//��ȡ���Ӵ���
	virtual int getCost(int col, int row);
	//��ȡ���Ӵ�С
	virtual  void getTileSize( int *width, int *height);
	//��ȡʹ��busѰ·�����·��
	virtual  int getUseBusPathMinDis();
	//��ȡ����վ��ID
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
	void UpadteTileAndObjectCut();  //�ü�
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
	//�жϵ��״̬
	ACTORTYPE JugdeTargetState(Touch* touch, Event* event);
private:
	//���¶�̬����
	void updateDynamicLoad();
private:
	//CCamera* m_camera;
	//Ѱ·��
	//CBusPathSeeker	*m_pathSeeker;
	//��ͼ������
	//CCSprite**  m_ppTiles;
	
	MapTileContainer m_ppTiles;
	//MapSceneObjectContainer m_pMapSceneObjects;

	Point  m_lastUpdateCut; //�ϴβü������λ��
	//��ͼtile��
	Node *m_pTileNode;
	//��ͼGround��
	Node *m_pGroundNode;
	//��ͼactor��
	Node *m_pActorNode;
	//��ͼAir��
	Node *m_pAirNode;
	//actor������
	ActorManager*  m_pActorManager;
	//��ͼ��������
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
	//����ʱ��
	float m_fTouchTime;
	//��������
	int  m_nTouchCount;
	//���´��ʱ��
	float m_fAtkTime;
	
};
#endif