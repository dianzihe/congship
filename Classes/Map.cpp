#include "Map.h"
#include "Hero.h"
#include "GameScene.h"
#include "ActorManager.h"
#include "TextDef.h"
#include "Binary.h"
#include "BinTable.h"
#include "Text.h"
#include "ActorManager.h"
#include "Actor.h"
#include "SceneObj.h"
#include "SceneObjCfg.h"
#include "Shake.h"

//#include "ImageCenter.h"
//#include "Camera.h"
//#include "PathSeeker.h"

/*
//#include "MyMathExtension.h"
//#include "effect.h"
//#include "Npc.h"
//#include "UIProgressBar.h"
#include "package.h"
#include "GameState.h"
#include "GameMainUI.h"
#include "MessageTips.h" 
#include "MonsterCfg.h"
#include "NpcCfg.h"
#include "Routing.h"
#include "../BaseModule/Navigation/NavigationModule.h"
#include "../BaseModule/Combat/SkillFilterModule.h"
#include "SceneInstance.h"
#include "../BaseModule/Shake/Shake.h"
#include "../../CocosDenshion/include/SimpleAudioEngine.h"
#include "../BaseModule/Motion/RoutingModule.h"
#include "BuffListUI.h"
#include "../BaseModule/Motion/TeleportModule.h"
#include "../InputSystem/GameCMDSystem.h"
#include "CCMemoryMonitor.h"
#include "../InputSystem/TeleportCMD.h"
#include "../InputSystem/GameCMDSystem.h"
#include "BattleUI.h"
#include "DirectionHandleUI.h"
#include "CCFileUtils.h"

#include "GameHangUp.h"
#include "Target.h"
*/
//const int ID_BACKGROUND = 0;
//const int ID_FRONT		= 1;
#define     STOP_GUAJITIME 1.0f
#define  FreshAtk_Time 1.0f
//extern void OnBtnStopHangUp(UI *ui, void *data);
const char* resDir = "Map/";

const string getBackgroudFileDir(int id)
{
	char buf[256];
	sprintf( buf, "%s%d.png", resDir, id );

	return buf;
}


DQMap::DQMap(void)
{
	//m_camera = new DQCamera();

	//m_pathSeeker = &CBusPathSeeker::instance();
	//m_pathSeeker->setDelegate(this);
	m_ppTiles.clear();
	m_pActorManager = NULL;

	m_pTileNode = new Node();
	addChild(m_pTileNode, MAP_LAYER_TILE);
	m_pGroundNode = new Node();
	addChild(m_pGroundNode, MAP_LAYER_GROUND);
	m_pActorNode = new Node();
	addChild(m_pActorNode, MAP_LAYER_ACTOR);
	m_pAirNode = new Node();
	addChild(m_pAirNode, MAP_LAYER_AIR);
	m_pMapCfgData = NULL;
	m_pMapSettingData = NULL;
	m_nServerMapID = 0;
	m_fMapHoldTime = -1.0f;
	m_fMapHoldAllTime = -1.0f;
	m_fTouchTime = 0.0f;
	m_nTouchCount = 1;
	m_fAtkTime = 0.0f;
}

DQMap::~DQMap(void)
{
	//SAFE_DELETE(m_camera);

	m_ppTiles.clear();
}

float DQMap::getSceneScale()
{
	//return m_camera->getSceneScale();
	return .8f;
}
/*
//获取站台数据
LPBUS_STATIONS DQMap::getStations()
{
	return &m_pMapCfgData->busStations;
}
*/

//获取格子代价
int	DQMap::getCost(int col, int row)
{
	if(CanWalkThrough(col, row))
		return 1;
	else
		return -1;
}

void DQMap::getTileSize(int *width, int *height)
{
	*width = MAP_PHY_TILE_W;
	*height = MAP_PHY_TILE_H;
}

//获取最大的站点ID
int DQMap::getMaxStationId()
{
	return m_pMapCfgData->iMaxStationId;
}

int DQMap::getUseBusPathMinDis()
{
	return 0;
}

void DQMap::initialize(const MapSettingData* pMapData)
{
	if( !pMapData )
		return;
	const MapData *pData = MapCfg::instance().getMapCfgData(pMapData->id);
	if( !pData )
		return;
	/*
	if( m_pMapSettingData ){
		if( m_pMapSettingData->type == Map_Type_Battle ){
			//上一个地图是战场，表示正在离开战场
			//如果是在战场战斗状态，就进入可以进入战场的状态，如果是战场结束状态，就去掉战场状态
			if( CBattleUI::instance().getState() == eBattleState_Fighting )
				CBattleUI::instance().ChangeState(eBattleState_CanEnter);
			else
				CBattleUI::instance().ChangeState(eBattleState_NULL);
		}
	}else{
		if( CBattleUI::instance().getState() != eBattleState_CanEnter)
			CBattleUI::instance().ChangeState(eBattleState_NULL);
	}
	*/
	unInitialize();

	m_pMapSettingData = pMapData;
	setMapID(pMapData->id);
	setMapName( pMapData->name );
	setMapType(pMapData->type);
	m_pMapCfgData = (MapData*)pData;
	LoadMapSceneObjects(m_pMapCfgData);

	if( m_pMapSettingData && m_pMapSettingData->type == Map_Type_Battle ){
		//本地图是战场，表示进入战场
		//CBattleUI::instance().ChangeState(eBattleState_Fighting);
	}

	//重置寻路者大小
	//m_pathSeeker->setSeekSize(m_pMapCfgData->widthInPhy, m_pMapCfgData->heightInPhy);

	//地图tile管理数据
	//m_ppTiles = new CCSprite*[m_pMapCfgData->widthInTile*m_pMapCfgData->heightInTile];
	//memset(m_ppTiles, NULL,m_pMapCfgData->widthInTile*m_pMapCfgData->heightInTile*sizeof(CCSprite*));

	m_ppTiles.resize(m_pMapCfgData->widthInTile * m_pMapCfgData->heightInTile);
	MapTileContainer::iterator it = m_ppTiles.begin();
	MapTileContainer::iterator end = m_ppTiles.end();
	while(it != end)
	{
		*it = NULL;
		++it;
	}

	char buff[128];
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	sprintf(buff, "Minimap/%s.wen",pMapData->MiniMap.c_str());
#else
	sprintf(buff, "Minimap/%s.png",pMapData->MiniMap.c_str());
#endif
	ImageCenter::instance().LoadResource(buff);
	//m_pMiniMapTexture = ImageCenter::instance().GetRenderBatch(buff);

	m_lastUpdateCut = ccp(MAP_PHY_TILE_W*2, MAP_PHY_TILE_H*2);

	//播放音乐
	char str[256];
	sprintf( str, "Music/%s.spd", m_pMapSettingData->music.c_str());
	if(!FileUtils::getInstance()->isFileExist(FileUtils::getInstance()->fullPathForFilename(str).c_str())){
		//strcpy_s(str, 256, "Music/guigucun.spd");  android编译不过， strcpy_s不是跨平台的
		memset(str, 0, 256);
		sprintf(str,"Music/guigucun.spd");
	}
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(str, true);
	/*
	if(pMapData->type != 2)
	{
		switch(pMapData->pkFlag_Kill)
		{
		case 0:
			{
				MessageTips::showMessageTips(CText::GetText(CTextDef::Enter_SafeMap).c_str());
			}
			break;
		case 2:
			{
				MessageTips::showMessageTips(CText::GetText(CTextDef::Enter_PKMap_Without_KillPoint).c_str());
			}
			break;
		case 1:
			{
				MessageTips::showMessageTips(CText::GetText(CTextDef::Enter_PKMap_With_KillPoint).c_str());
			}
			break;
		case 3:
			{
				MessageTips::showMessageTips(CText::GetText(CTextDef::Enter_PKMap_By_Faction).c_str());
			}
			break;
		case 4:
			{
				MessageTips::showMessageTips(CText::GetText(CTextDef::Enter_PKMap_By_Team).c_str());
			}
			break;
		}
	}
	*/
}

void DQMap::unInitialize()
{
	if(m_pMapCfgData && !m_ppTiles.empty())
	{
		assert( m_ppTiles.size() == m_pMapCfgData->widthInTile * m_pMapCfgData->heightInTile );
		ImageCenter::instance().UnLoadResource(m_pMapSettingData->MiniMap.c_str());
		for( int i=0; i<m_pMapCfgData->widthInTile; ++i ){
			for( int j=0; j<m_pMapCfgData->heightInTile; ++j ){
				//CCSprite *p = m_ppTiles[i+j*m_pMapCfgData->widthInTile];

				MapTile* tile = m_ppTiles[i + j * m_pMapCfgData->widthInTile];
				if (tile){
					removeChild(tile, true);
					
					SAFE_RELEASE(tile);
				}

// 				if( p )
// 				{
// 					CCTextureCache::sharedTextureCache()->removeTexture(p->getTexture());
// 					removeChild(p, true);
// 				}
			}
		}
	}
	m_pTileNode->removeAllChildrenWithCleanup(true);

	m_ppTiles.clear();

	//GameScene::GetActorManager()->cleartimeNonce();

	ReleaseMapSceneObjects();
}

void DQMap::addActorToMap(Actor *actor)
{
	if(actor == NULL )
		return;
	m_pActorNode->addChild(actor);
}

void DQMap::delActorFromMap(Actor *actor)
{
	if( actor == NULL )
		return;
	/*
	if( BuffListUI::instance().getShowBuffCharactor() == actor ){
		BuffListUI::instance().setShowBuffCharactor(NULL);
	}
	*/

	m_pActorNode->removeChild(actor, true);
}

void DQMap::addActorToAirNode(Actor *actor)
{
	if(actor == NULL )
		return;
	m_pAirNode->addChild(actor);
}

void DQMap::delActorFromAirNode(Actor *actor)
{
	if( actor == NULL )
		return;
	m_pAirNode->removeChild(actor, true);
}

void DQMap::removeActorFromAirNode(Actor *actor)
{
	if( actor == NULL )
		return;
	m_pAirNode->removeChild(actor, false);
}

void DQMap::addActorToGroundNode(Actor *actor)
{
	if(actor == NULL )
		return;
	m_pGroundNode->addChild(actor);
}

void DQMap::delActorFromGroundNode(Actor *actor)
{
	if( actor == NULL )
		return;
	m_pGroundNode->removeChild(actor, true);
}

void DQMap::removeActorFromGroundNode(Actor *actor)
{
	if( actor == NULL )
		return;
	m_pGroundNode->removeChild(actor, false);
}
#define		MAP_TOUCH_ONEE_MOVE_TIME	0.3f
#define		MAP_TOUCH_TELEPORT_MOVE_TIME	0.5f

/*
bool DQMap::ccTouchBegan(CCTouch* touch, CCEvent* event)
{

	CHero * pHero =GameScene::GetActorManager()->GetHero();
	if (pHero && pHero->getTianTiFight())
	{
		return false;
	}
	m_HoldTouch = *touch;
	m_fMapHoldTime = 0.0f;
	m_fMapHoldAllTime = 0.0f;
	m_fMapHoldAllTimeTeleport = 0.0f;
	m_startTouchPos = touch->locationInView();
	if (m_fTouchTime <= STOP_GUAJITIME)
	{
		++m_nTouchCount;
	}
	else
	{
		m_nTouchCount = 1;
	}
	m_fTouchTime = 0.0f;
	return true;
}


bool DQMap::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	m_HoldTouch = *touch;
	return true;
}

bool DQMap::ccTouchEnd(CCTouch* touch, CCEvent* event, bool isTeleportMove)
{
	CHero * pHero =GameScene::GetActorManager()->GetHero();
	if (pHero && pHero->getTianTiFight())
	{
		return false;
	}

	CCPoint pt = touch->locationInView();
	CCPoint touPos(pt.x, REVERSE_Y(pt.y, m_camera->getSceneScreenSize().height));
	//如果进行了点击移动，停止摇杆移动
	CDirectHandleUI::instance().ChangeDirection(  eDirection_NULL );
	//test
	CHero* hero = GameScene::GetScene()->m_actorManager->GetHero();
	if(m_pMapCfgData == NULL)
		return false;
	{
		if( isTeleportMove && m_fMapHoldAllTimeTeleport <= MAP_TOUCH_TELEPORT_MOVE_TIME && (fabs(pt.x-m_startTouchPos.x) > 50 || fabs(pt.y-m_startTouchPos.y) > 50) )
		{
			if(hero->canMove())
			{
				TeleportCMD *pCmd = new TeleportCMD(hero->getActorID());
				pCmd->SetIsHost(true);
				CCPoint dir;
				dir.x = pt.x - m_startTouchPos.x;
				dir.y = -pt.y + m_startTouchPos.y;
				float len = dir.x * dir.x + dir.y * dir.y;
				len = sqrtf(len);
				dir.x = dir.x / len;
				dir.y = dir.y / len;
				CCPoint targetPos = hero->getPosition();
				targetPos.x += dir.x * MaxTeleportMoveDis;
				targetPos.y += dir.y * MaxTeleportMoveDis;
				targetPos = GetAccessPosByStep( hero->getPosition(), targetPos );
				pCmd->SetTargetPos(targetPos);
				hero->GetGameCMDSystem()->PushGameCMD(pCmd);
				CGameHangUp::GetInstance().setFanJi(false);
				if (CGameHangUp::GetInstance().getGuaji())
				{
					OnBtnStopHangUp(NULL,NULL);
				}
				else
				{
					Target::instance().clearTarget();
					SkillFilterModule::instance().FilterFinish();
					NavigationModule* heroNavigation = GameScene::GetHeroNavigation();
					heroNavigation->CancelNavigation();

				}
			}
		}
 		else if( GameScene::GetActorManager()->ccTouchBegan(touch, event))
		{
			CGameHangUp::GetInstance().setFanJi(false);
			if (CGameHangUp::GetInstance().getGuaji())
			{
				m_nTouchCount = 0;
				m_fTouchTime = 0.0f;
			}
			
			return true;
		}
		else
		{
			ACTORTYPE eACTORTYPE = JugdeTargetState(touch,event);
			//hx: 如果该点是在物理层上 则寻找一个最近的可以到达的点
			CCPoint target = m_camera->ScreenToWorldPos(ccp(pt.x,pt.y));
			if(CanWalkThrough(GetTileX(target.x), GetTileY(target.y)))
			{

			}
			else
			{
				target = GetAccessPosByStep( hero->getPosition(), target );
			}
			//hero->SetTargetPos(target);;
			//WP TODO:
			if ((m_nTouchCount>=2 || m_fTouchTime>=STOP_GUAJITIME)&& CGameHangUp::GetInstance().getGuaji())
			{
				CGameHangUp::GetInstance().setGuaji(false);
				CGameHangUp::GetInstance().setFanJi(false);
				NavigationModule* heroNavigation = GameScene::GetHeroNavigation();
				heroNavigation->CancelNavigation();
				SkillFilterModule::instance().FilterFinish();
				CGameMainUI::instance()->hideHangUping();
				CRouting::instance().runNavigation(0, target);
				Click* click =  GameScene::GetScene()->m_actorManager->GetClick();
				//清空TargetList列表
				//Target::instance().clearTarget();

				//	if(!click->isVisible())
				{
					click->setPosition(m_camera->ScreenToWorldPos(ccp(pt.x,pt.y)));
					click->PlayClick();
				}
			}
			else if (CGameHangUp::GetInstance().getGuaji() && !CGameHangUp::GetInstance().getFreeTime() && CGameHangUp::GetInstance().DisTanceSafe(target))
			{
				CGameHangUp::GetInstance().setFanJi(false);
				NavigationModule* heroNavigation = GameScene::GetHeroNavigation();
				heroNavigation->CancelNavigation();
				SkillFilterModule::instance().FilterFinish();
				CRouting::instance().runNavigation(0, target);
				Click* click =  GameScene::GetScene()->m_actorManager->GetClick();
				click->setPosition(m_camera->ScreenToWorldPos(ccp(pt.x,pt.y)));
				click->PlayClick();
				CGameHangUp::GetInstance().m_HeroRunPoint = target;
				CGameHangUp::GetInstance().setFreeTime(true);
				//CRouting::instance().runNavigation(0,CGameHangUp::GetInstance().m_HeroPoint);
			}
			else if (CGameHangUp::GetInstance().getGuaji())
			{
			}
			else
			{
				CGameHangUp::GetInstance().setFanJi(false);
				Target::instance().clearTarget();
				NavigationModule* heroNavigation = GameScene::GetHeroNavigation();
				heroNavigation->CancelNavigation();
				SkillFilterModule::instance().FilterFinish();
				if(CGameMainUI::instance()->m_progressBar->isVisible())
				{
					CGameMainUI::instance()->m_progressBar->setVisible(false);
				}
				CRouting::instance().runNavigation(0, target);
				Click* click =  GameScene::GetScene()->m_actorManager->GetClick();

				//	if(!click->isVisible())
				{
					click->setPosition(m_camera->ScreenToWorldPos(ccp(pt.x,pt.y)));
					click->PlayClick();
				}
			}
		}
	}

	//CGameState* p = (CGameState*)(GameScene::GetScene()->GetState());
	//if(p){
	//	CGameMainUI* self = p->getGMI();
	//	if(self){
	//		if(self->m_progressBar->isVisible()){
	//			int collectGoodsID = GameScene::GetActorManager()->GetHero()->getCollectGoodsID();
	//			CNpc *pCollectGoods = dynamic_cast<CNpc*> (GameScene::GetActorManager()->FindActor(ACTORTYPE_NPC, collectGoodsID));
	//			if(pCollectGoods){
	//				pk::MsgCollectGoods collectMsg;
	//				collectMsg.goodsID = GameScene::GetActorManager()->GetHero()->getCollectGoodsID();
	//				collectMsg.collectFlag = 1;
	//				collectMsg.collectTime = (int)((self->m_progressBar->getPercentage() * pCollectGoods->m_collectTime)/100);
	//				collectMsg.Send();
	//				//OutputDebugStringA( "MsgCollectGoods sended 2" );
	//			}
	//			self->m_progressBar->interruptProgress();
	//		}
	//	}
	//}

	return true;
}
*/
bool DQMap::CanWalkThrough(int phyTileX, int phyTileY)
{
	if(phyTileX < 0 || phyTileY < 0 || phyTileX >= m_pMapCfgData->widthInPhy || phyTileY >= m_pMapCfgData->heightInPhy)
		return false;
	return (m_pMapCfgData->phyData[REVERSE_Y(phyTileY, m_pMapCfgData->heightInPhy)*m_pMapCfgData->widthInPhy + phyTileX]&MAP_TILE_FLAG_PHY) == 0;
};

bool DQMap::IsTransparent(int phyTileX, int phyTileY)
{
	if(phyTileX < 0 || phyTileY < 0 || phyTileX >= m_pMapCfgData->widthInPhy || phyTileY >= m_pMapCfgData->heightInPhy)
		return false;
	return (m_pMapCfgData->phyData[REVERSE_Y(phyTileY, m_pMapCfgData->heightInPhy)*m_pMapCfgData->widthInPhy + phyTileX]&MAP_TILE_FLAG_TRANS) != 0;
};

CCPoint DQMap::GetAccessPosByStep(const CCPoint& beginPos, const CCPoint& endPos)
{
	CCPoint target = endPos;
	/*
	while(!CCPoint::CCPointEqualToPoint(target, beginPos))
	{
		float xoff = beginPos.x - target.x;
		float yoff = beginPos.y - target.y;
		if(!(fabsf(xoff) < FLT_EPSILON && fabsf(yoff) < FLT_EPSILON)){
			MOVE_V1_TO_V2(target.y, beginPos.y, GET_SPEED_SUB(yoff, xoff, MAP_PHY_TILE_W));
			MOVE_V1_TO_V2(target.x, beginPos.x, GET_SPEED_SUB(xoff, yoff, MAP_PHY_TILE_H));
			if(CanWalkThrough(GetTileX(target.x), GetTileY(target.y))){
				break;
			}
		}else{
			break;
		}
	}
	*/
	return target;
}

/*
void DQMap::GetPlayerPath(CPlayer* player, const CCPoint& start, const CCPoint& end)
{
	CCPoint destiny = end;
	if(!CanWalkThrough(destiny.x/MAP_PHY_TILE_W, destiny.y/MAP_PHY_TILE_H))
	{
		destiny = GetAccessPosByStep(start, end);
		if(!CanWalkThrough(destiny.x/MAP_PHY_TILE_W, destiny.y/MAP_PHY_TILE_H))
			return;
	}

	TileCoord tileStart;
	TileCoord tileDest;

	tileStart.col = (int)(start.x / MAP_PHY_TILE_W);
	tileStart.row = (int)(start.y / MAP_PHY_TILE_H);

	tileDest.col = (int)(destiny.x / MAP_PHY_TILE_W);
	tileDest.row = (int)(destiny.y / MAP_PHY_TILE_H);

	CPathSeeker::Pathway ways;

	m_pathSeeker->SeekPath( tileStart, tileDest, &ways ); 
	
	while(ways.Pop(tileStart))
	{
		RoutingCMD* newCMD = new RoutingCMD(player->getActorID());
		player->GetGameCMDSystem()->PushGameCMD(newCMD);
		player->GetRoutingModule()->AddTargetPath(ccp(GetTileCenterPixelX(tileStart.col), GetTileCenterPixelY(tileStart.row)));
	}
}

void DQMap::UpdateCamera(float dt)
{
	m_camera->update(dt, this);
	if( fabs(fabs(m_camera->getCurPos().x)-fabs(m_lastUpdateCut.x)) >= MAP_UPDATE_CUT_DIS ||
		fabs(fabs(m_camera->getCurPos().y)-fabs(m_lastUpdateCut.y)) >= MAP_UPDATE_CUT_DIS )
	{
		m_lastUpdateCut = m_camera->getCurPos();
		UpadteTileAndObjectCut();
	}

	CCPoint cameraPos = m_camera->getCurPos();
	//抖动
	if(CShake::instance().IsShake())
	{
		CShake::instance().Update(dt);
		CCPoint pos = CShake::instance().getCurPos();
		cameraPos = (ccpNeg(pos));
	}
	else
	{
		cameraPos = ccpNeg(cameraPos);
	}
	cameraPos.x *= m_camera->getSceneScale();
	cameraPos.y *= m_camera->getSceneScale();
	setPosition(cameraPos);
	setScale(m_camera->getSceneScale());
}
*/
void DQMap::UpadteTileAndObjectCut()
{
	//CCSprite *node = NULL;
	MapTile* tile = NULL;

	for( int i=0; i<m_pMapCfgData->widthInTile*m_pMapCfgData->heightInTile; ++i)
	{
		//node = m_ppTiles[i];

		tile = m_ppTiles[i];

		if(tile)
		{
			CCRect rectTile = CCRectMake(
				tile->getPositionX(), 
				tile->getPositionY(), 
				tile->getContentSize().width, 
				tile->getContentSize().height);
			tile->setVisible(true);
			/*
			if( !CCRect::CCRectIntersectsRect(rectTile, m_camera->getCurRectInWindow()))
				tile->setVisible(false);
			else
				tile->setVisible(true);
			*/
		}
	}
}

void DQMap::update(float dt)
{
	m_fAtkTime +=dt;
	if( !m_pMapCfgData )
		return;
	//UpdateCamera(dt);
	updateDynamicLoad();
	UpdateSceneObjects(dt);
	m_fMapHoldAllTimeTeleport += dt;
	if( m_fMapHoldTime >= 0.0f ){
		m_fMapHoldTime+=dt;
		if( m_fMapHoldTime >= MAP_TOUCH_ONEE_MOVE_TIME ){
			//MOVETOUCH
			//ccTouchEnd(&m_HoldTouch, NULL, false);
			m_fMapHoldTime = 0;
		}
	}
	if( m_fMapHoldAllTime >= 0.0f )
		m_fMapHoldAllTime += dt;

	MapTile* tile = NULL;
	for( int i=0; i<m_pMapCfgData->widthInTile*m_pMapCfgData->heightInTile; ++i){
		tile = m_ppTiles[i];
		if(tile){
			tile->tick(dt);
		}
	}
	if (m_fTouchTime>= 0.0f){
		m_fTouchTime+=dt;
	}
	/*
	if (CGameHangUp::GetInstance().getGuaji())
	{
		CHero *pHero = GameScene::GetActorManager()->GetHero();
		if (!pHero)
		{
			return;
		}
		 float  x = CGameHangUp::GetInstance().m_HeroRunPoint.x - pHero->getPositionX();
		 float  y = CGameHangUp::GetInstance().m_HeroRunPoint.y - pHero->getPositionY();
		 if (x < 20 && x>-20 &&y > -20 && y <20 && !CGameHangUp::GetInstance().getRemove() && CGameHangUp::GetInstance().getFreeTime())
		{
				CRouting::instance().runNavigation(0, (CGameHangUp::GetInstance().m_HeroPoint));
				CGameHangUp::GetInstance().setRemove(true);
		}
		x = (CGameHangUp::GetInstance().m_HeroPoint.x - pHero->getPositionX());
		y = (CGameHangUp::GetInstance().m_HeroPoint.y - pHero->getPositionY());
		if (x < 20 && x > -20 && y >-20 &&y <20 && CGameHangUp::GetInstance().getRemove() && CGameHangUp::GetInstance().getFreeTime())
		{
			CGameHangUp::GetInstance().StartAuto();
			CGameHangUp::GetInstance().setRemove(false);
			CGameHangUp::GetInstance().setFreeTime(false);
		}
	}
	*/
}
/*
void DQMap::visit()
{PROFILE("Map::visit");
	SceneInstance::instance().PushSFXToGroundNode(m_pGroundNode);
	SceneInstance::instance().PushSFXToAirNode(m_pAirNode);

    {PROFILE("CCNode::visit");
        CCNode::visit();
    }

	m_pGroundNode->removeAllChildrenWithCleanup(false);
	m_pAirNode->removeAllChildrenWithCleanup(false);

	SceneInstance::instance().RenderBackUI();
}
*/
void DQMap::doReleaseMemory()
{
    if(m_pMapCfgData == NULL)
        return;

	for( int i=0; i<m_pMapCfgData->widthInTile; ++i )
	{
		for( int j=0; j<m_pMapCfgData->heightInTile; ++j )
		{
			MapTile *p = m_ppTiles[i + j * m_pMapCfgData->widthInTile];
			if (p)
			{
				p->unLoad();
			}
		}
	}
}


//更新动态载入
void DQMap::updateDynamicLoad()
{
	/*
    if(m_ppTiles.empty())
        return;
	int w = (int)m_camera->getSceneScreenSize().width/MAP_RENDER_TILE_W+1;
	int h = (int)m_camera->getSceneScreenSize().height/MAP_RENDER_TILE_H+1;
    if((int)m_camera->getSceneScreenSize().width % MAP_RENDER_TILE_W != 0)
        w++;
    if((int)m_camera->getSceneScreenSize().height % MAP_RENDER_TILE_H != 0)
        h++;
	int tileCol = (int)(m_camera->getCurPos().x/MAP_RENDER_TILE_W);
	int tileRow = (int)(REVERSE_Y(m_camera->getCurPos().y/MAP_RENDER_TILE_H, m_pMapCfgData->heightInTile)+1);

	//需要显示的格子
	int showSTileCol = tileCol;
	int showSTileRow =  tileRow-h + 1;
	int showETileCol = tileCol+w -1;
	int showETileRow =  tileRow;

	for( int i=0; i<m_pMapCfgData->widthInTile; ++i )
	{
		for( int j=0; j<m_pMapCfgData->heightInTile; ++j )
		{
			//CCSprite *p = m_ppTiles[i+j*m_pMapCfgData->widthInTile];
			
			MapTile *p = m_ppTiles[i + j * m_pMapCfgData->widthInTile];
			//需要释放的
			if( (i<showSTileCol || i>showETileCol) || (j<showSTileRow || j>showETileRow))
			{
				if( p )
				{
					//CCTextureCache::sharedTextureCache()->removeTexture(p->getTexture());
					p->removeFromParentAndCleanup(true);
					SAFE_RELEASE(p);
					m_ppTiles[i+j*m_pMapCfgData->widthInTile] = NULL;
				}
			}
			else
			//需要显示的
			{
				if( !p )
				{
					char path[128];
					sprintf(path, "Map/%s/%d_%d.wen", m_pMapCfgData->resName.c_str(), i,j);

					p = new MapTile();
					p->setUsingTextureWhenUnloaded(m_pMiniMapTexture);
					p->setIndexingData(i, j, m_pMapCfgData->widthInTile, m_pMapCfgData->heightInTile);
					p->Load(path, CCRectMake(0,0,MAP_RENDER_TILE_W,MAP_RENDER_TILE_H));

					//CCSprite* s = CCSprite::spriteWithFile(path, CCRectMake(0,0,MAP_RENDER_TILE_W,MAP_RENDER_TILE_H));
// 					if(s == NULL)
// 						continue;
					p->setAnchorPoint( ccp(0,0) );	
					p->setPosition(ccp(i*MAP_RENDER_TILE_W, REVERSE_Y(j, m_pMapCfgData->heightInTile)*MAP_RENDER_TILE_H));
					addChild(p, MAP_LAYER_TILE);
					m_ppTiles[i + j*m_pMapCfgData->widthInTile] = p;
				}
			}
		}
	}
	*/
}

/*
void DQMap::SetCameraType(int t)
{
	//m_camera->setCameraType(t);
}

void DQMap::SetCameraTarget(const CCPoint& pos)
{
	m_camera->setTargetPos(pos);
}
*/
void DQMap::UpdateAllNpcIcon()
{
	//GameScene::GetActorManager()->updateAllNpcIcon();
}

bool DQMap::isMapPackgeNeedUpdate()
{
	if(m_pMapCfgData)
	{
		char path[128];
		sprintf(path, "Map/%s/0_0.wen", m_pMapCfgData->resName.c_str());
		return !FileUtils::getInstance()->isFileExist(FileUtils::getInstance()->fullPathForFilename(path).c_str());
	}
	return false;
}

void DQMap::LoadMapSceneObjects(MapData* pMapData)
{
	vector<MapObject>::iterator it = pMapData->objects.begin();
	while(it != pMapData->objects.end())
	{
		if(it->type == ACTORTYPE_SCENEOBJECT)
		{
			int nSceneObjId = it->id;
			const SceneObjData* pObjData = SceneObjCfg::instance().findSceneObjDataByID( nSceneObjId );
			if( !pObjData )
			{
				++it;
				continue;
			}

            CCPoint pos = ccp(it->x, it->y);
			if(pObjData->m_Layer == eSceneObjLayer_Actor)
			{
				SceneObj* pObj = SceneObj::node();
				pObj->onLookInfoSceneObject( nSceneObjId, pos, pObjData );
			}
			else
			{
				SceneObj* pObj = new SceneObj;
				pObj->onLookInfoSceneObject( nSceneObjId, pos, pObjData );
				m_pMapSceneObjects.push_back(pObj);
			}
		}
		++it;
	}
}

void DQMap::ReleaseMapSceneObjects()
{
	MapSceneObjectContainer::iterator it = m_pMapSceneObjects.begin();
	while(it != m_pMapSceneObjects.end())
	{
		SceneObj* pSceneObj = *it;
		if(pSceneObj)
		{
			if(pSceneObj->GetSceneObjData()->m_Layer == eSceneObjLayer_Air)
			{
				removeActorFromAirNode(pSceneObj);
			}
			if(pSceneObj->GetSceneObjData()->m_Layer == eSceneObjLayer_Ground)
			{
				removeActorFromGroundNode(pSceneObj);
			}
		}
		SAFE_DELETE(pSceneObj);
		++it;
	}
	m_pMapSceneObjects.clear();
}

void DQMap::UpdateSceneObjects(float dt)
{
	MapSceneObjectContainer::iterator it = m_pMapSceneObjects.begin();
	while(it != m_pMapSceneObjects.end())
	{
		SceneObj* pSceneObj = *it;
		pSceneObj->update(dt);
		++it;
	}
}

ACTORTYPE DQMap::JugdeTargetState(CCTouch* touch, CCEvent* event)
{
	/*
	cocos2d::CCPoint touchLocation = touch->locationInView();
	touchLocation = cocos2d::CCDirector::sharedDirector()->convertToGL(touchLocation);

	Actor* selectObjects =NULL;
	MAP_ACTORS m_mapActors;

	GameScene::GetActorManager()->getActors(m_mapActors);
	for( MAP_ACTORS::iterator iter = m_mapActors.begin(); iter != m_mapActors.end(); ++iter )
	{
		Actor* pActor = iter->second;
		if( pActor->isVisible() 
			&& pActor->getCanBeenClick() )
		{
			const CCRect& rect = pActor->getSelectRect();

			CCPoint local = pActor->convertToNodeSpace(touchLocation);

			cocos2d::CCRect r = CCRectMake(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);

			if (cocos2d::CCRect::CCRectContainsPoint(r, local))
			{
				selectObjects =  pActor ;
				break;
			}
		}
	}

	if (selectObjects)
	{
		switch(selectObjects->getActorType())
		{
		case ACTORTYPE_PLAYER:
			return ACTORTYPE_PLAYER;
		case ACTORTYPE_NPC:
			return ACTORTYPE_NPC;
		case ACTORTYPE_MONSTER:
			return ACTORTYPE_MONSTER;
		case ACTORTYPE_COLLECT:
			return ACTORTYPE_COLLECT;
		case ACTORTYPE_CONVOY:
			return ACTORTYPE_CONVOY;
		case ACTORTYPE_MOUNT:
			return ACTORTYPE_MOUNT;
		}
	}
	*/
	return ACTORTYPE_Count;
}
