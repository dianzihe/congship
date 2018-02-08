#include "ActorManager.h"
//#include "GameScene.h"
//#include "Monster.h"
//#include "ASprite.h"
#include "Actor.h"
//#include "Hero.h"
//#include "Player.h"
//#include "effect.h"
//#include "map.h"
//#include "Target.h"
//#include "../BaseModule/Combat/CombatModule.h"
//#include "../BaseModule/Navigation/NavigationModule.h"
//#include "../BaseModule/Motion/RoutingModule.h"
//#include "Npc.h"
/*
#include "Object.h"
#include "platform.h"
#include "Routing.h"
#include "SystemSetUI.h"
#include "MessageTips.h"
#include "Text.h"
#include "TextDef.h"
#include "Pet.h"
#include "GameHangUp.h"
#include "TargetList.h"
*/

//extern void OnBtnStopHangUp(UI *ui, void *data);
ActorManager::ActorManager(void)
{
	/*
	m_hero = NULL;
	m_click =NULL;
	m_pick = NULL;
	m_aoe = NULL;
	m_pMap = NULL;
	*/
	// 跟服务器对应的封装方法
	//%%构建物件ID，暂时32位(前1位永为0保持正数，8位服务器ID，4位类型ID，19位ID值)，以后改为64位
	ActorID Index = 1;
	ActorID ServerID = 1;
	ActorID TypeID = 0xff;
	timeNonce=0;

	m_clientActorID = (ServerID << 55) | ( TypeID << 51 ) | Index;
}

ActorManager::~ActorManager(void)
{
}

ActorID ActorManager::incClientActorID()
{
	return ++m_clientActorID;
}

void ActorManager::update(float dt)   //改
{
	m_nDispPlayerNum = 0;
	/*
	bool isSheild_diff_camp = CSystemSetUI::instance().isSet(ShieldSet_EnermyCamp);
	bool isSheild_same_camp = CSystemSetUI::instance().isSet(ShieldSet_SelfCamp);
	bool isSheild_limit		= CSystemSetUI::instance().isLimitDispPlayer();
	int	 sheild_limit		= CSystemSetUI::instance().getShieldValueByIndex(ShieldSet_DispPlayerLimit);
	ActorID  targetID		= Target::instance().getTargetID();
	

	for( MAP_ACTORS::iterator iter = m_mapActors.begin(); iter != m_mapActors.end(); ++iter )
	{
		Actor* pActor = iter->second;
		pActor->setIsSheild(false);

		//屏蔽玩家
		if (pActor->getActorType() == ACTORTYPE_PLAYER)
		{
			//CPlayer* player = (CPlayer*)pActor;
			
			//屏蔽敌对阵营玩家
			if ( isSheild_diff_camp	&& player->GetGuildName() != m_hero->GetGuildName())
			{
				player->setIsSheild(true);
			}

			////屏蔽己方阵营玩家
			if ( isSheild_same_camp && player->GetGuildName() == m_hero->GetGuildName())
			{
				player->setIsSheild(true);
			}

			////限制周围玩家数量
			if ( isSheild_limit 
				&& !player->isSheild())
			{
				player->setIsSheild( m_nDispPlayerNum ++ >=  sheild_limit);
			}
			
			////剧情地图屏蔽玩家
			if(m_pMap && m_pMap->getMapID() == 24)
			{
				player->setIsSheild(true);
			}
		}

		pActor->update(dt);
	}

	if( m_lstWaitToDelActorIDs.size() )
	{
		for( LIST_ACTORIDS::iterator iter = m_lstWaitToDelActorIDs.begin(); iter != m_lstWaitToDelActorIDs.end(); ++iter )
		{
			DelActor( *iter );
		}
		m_lstWaitToDelActorIDs.clear();
	}
	*/
}

/*
bool ActorManager::ccTouchBegan(CCTouch* touch, CCEvent* event)
{

	cocos2d::CCPoint touchLocation = touch->locationInView();
	touchLocation = cocos2d::CCDirector::sharedDirector()->convertToGL(touchLocation);

	vector<Actor*> selectObjects;

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
				selectObjects.push_back( pActor );
			}
		}
	}

	//只选择NPC
	for( int i=0; i<(int)selectObjects.size(); ++i )
	{
		if( selectObjects[i]->getActorType() == ACTORTYPE_NPC )
		{
			Actor *pNpc = selectObjects[i];
			selectObjects.clear();
			selectObjects.push_back(pNpc);
		}
	}

	CHero* hero = GameScene::GetActorManager()->GetHero();
	Pick* pick =  GameScene::GetScene()->m_actorManager->Getpick();
	//npc
	int singleClickValue = CSystemSetUI::instance().getSetValueByIndex(FunctionSet_SingleClick);
	bool isSingleClick = false;
	for(int i=0; i<(int)selectObjects.size(); i++ )
	{
		Actor* actor = selectObjects[i];
		int targetID = (int)Target::instance().getTargetID();
		int actorID = (int)actor->getActorID();
		if(singleClickValue > 0)
		{
			isSingleClick = true;
		}
		if(singleClickValue <= 0 && Target::instance().getTargetID() == actor->getActorID())
		{
			isSingleClick = true;
		}
		Target::instance().SetCurTargetID(actor->getActorID());

		if(  hero->canAttackTarget(actor) )
		{
			if(isSingleClick )
			{
				Target::instance().SetCurTargetID(actor->getActorID());
				if (CGameHangUp::GetInstance().getGuaji())
				{
					Target::instance().clearTarget();
					NavigationModule *heroNavigation = GameScene::GetHeroNavigation();
					heroNavigation->CancelNavigation();
					Target::instance().addCurrentTarget(actor->getActorID());
					HangUpMonsterTask *newTask = new HangUpMonsterTask(heroNavigation);
					newTask->SetDataID(0);
					heroNavigation->AddTask(newTask);
				}
				else
				{
					Target::instance().clearTarget();
					CGameHangUp::GetInstance().setFanJi(false);
					Target::instance().addCurrentTarget(actor->getActorID());
					NavigationModule* heroNavigation = GameScene::GetHeroNavigation();
					heroNavigation->CancelNavigation();
					FixFightTask* newTask = new FixFightTask(heroNavigation);
					newTask->SetTargetID(Target::instance().getTarget());
					heroNavigation->AddTask(newTask);
				}
				//}
			}
			pick->setVisible(true);
			Target::instance().update();
			return true;
		}

		if(actor->getActorType() == ACTORTYPE_TRANSPORT)
		{
			CRouting::instance().runNavigation( 0, actor->getPosition() );
		}
		else if(actor->getActorType() == ACTORTYPE_NPC)
		{
			if(CGameHangUp::GetInstance().getGuaji())
			{
				OnBtnStopHangUp(NULL,NULL);
			}
			CNpc* npc = dynamic_cast<CNpc*> (actor);
			if ( npc )
			{
				if(isSingleClick)
				{
					//走向NPC 并且对话
					Target::instance().clearTarget();
					CGameHangUp::GetInstance().setFanJi(false);
					NavigationModule* heroNavigation = GameScene::GetHeroNavigation();
					heroNavigation->CancelNavigation();
					FixDialogTask* newTask = new FixDialogTask(heroNavigation);
					newTask->SetTargetID(npc->getActorID());
					heroNavigation->AddTask(newTask);
				}
				pick->setVisible(true);
				Target::instance().update();
				return true;
			}
		}
		else if (actor->getActorType() == ACTORTYPE_PLAYER)
		{
			CPlayer* player = dynamic_cast<CPlayer*> (actor);

			if (player)
			{
				pick->setVisible(true);
				Target::instance().update();
				return true;
			}
		}
		else if(actor->getActorType() == ACTORTYPE_MONSTER)
		{
			CMonster* pMonster = dynamic_cast<CMonster*> (actor);
			CHero* hero = GameScene::GetActorManager()->GetHero();
			if ( pMonster && pMonster->GetStateMachine()->getCurrentState() != eCharactorState_Death )
			{
				NavigationModule* heroNavigation = GameScene::GetHeroNavigation();
				heroNavigation->CancelNavigation();
				FixFightTask* newTask = new FixFightTask(heroNavigation);
				newTask->SetTargetID(pMonster->getActorID());
				heroNavigation->AddTask(newTask);

				pick->setVisible(true);
				Target::instance().updata();
				return true;
			}
			else
			{
				pick->changepoint(NULL);
			}
		}
		else if(actor->getActorType() == ACTORTYPE_COLLECT || actor->getActorType() == ACTORTYPE_FLAG)
		{
			CObject *pObject = dynamic_cast<CObject*> (actor);
			if(pObject)
			{
				if(isSingleClick)
				{
					if(CGameHangUp::GetInstance().getGuaji())
					{
						OnBtnStopHangUp(NULL,NULL);
					}
					Target::instance().clearTarget();
					CGameHangUp::GetInstance().setFanJi(false);
					NavigationModule *heroNavigation = GameScene::GetHeroNavigation();
					heroNavigation->CancelNavigation();
					FixCollectTask* newTask = new FixCollectTask(heroNavigation);
					newTask->SetTargetID(pObject->getActorID());
					heroNavigation->AddTask(newTask);

				}
				pick->setVisible(true);
				Target::instance().update();
				return true;
			}
		}
		else if (actor->getActorType() == ACTORTYPE_PET)
		{
			CPet* pet = dynamic_cast<CPet*> (actor);

			if (pet)
			{
				pick->setVisible(true);
				Target::instance().update();
				return true;
			}
		}
	}

	return false;
}
*/
void ActorManager::AddActor(Actor* actor)
{
	ActorID nActorID = actor->getActorID();

	if( FindActor(nActorID) )
	{
		//ERROR_LOG( "ActorManager::AddActor nActorID[%lld] exist", nActorID );
		DelActor( nActorID );
	}
	m_mapActors[nActorID] = actor;
	/*
	m_pMap->addActorToMap(actor);
	if( actor->getActorType() == ACTORTYPE_PLAYER )
	{
		CPlayer* player = (CPlayer*)actor;
		player->showFactionName(CSystemSetUI::instance().getHideCampNameFlag());
	}
	*/
	if( actor->getActorType() == ACTORTYPE_TRANSPORT )
	{
 		m_mapTransportActors[nActorID] = actor;
	}
}
void ActorManager::DelActor(ActorID nActorID)
{
	MAP_ACTORS::iterator iterFind = m_mapActors.find( nActorID );
	if( iterFind != m_mapActors.end() )
	{
		if( iterFind->second->getActorType() == ACTORTYPE_PLAYER )
		{
			/*
			CPlayer *p = (CPlayer*)(iterFind->second);
			if( p && p->getConvoyActorID() )
			{
				DelActor(p->getConvoyActorID());
			}
			*/
		}
		//CCLOG("actorName===========================%s", iterFind->second->GetName().c_str());
		//m_pMap->delActorFromMap(iterFind->second);
		m_mapActors.erase( iterFind );
	}

	iterFind = m_mapTransportActors.find( nActorID );
	if( iterFind != m_mapTransportActors.end() )
	{
		m_mapTransportActors.erase( iterFind );
	}
}

void ActorManager::DelayDelActor( ActorID nActorID )
{
	m_lstWaitToDelActorIDs.push_back( nActorID );
}

void ActorManager::onChangeMap()
{
	MAP_ACTORS mapTemp( m_mapActors );
	for( MAP_ACTORS::iterator iter = mapTemp.begin(); iter != mapTemp.end(); ++iter )
	{
		Actor* pActor = iter->second;
		if( pActor->getCleanFlag() )
		{
			DelActor( iter->first );
		}
	}

	/*
	// 切换地图，取消挂机状态
	NavigationModule *heroNavigation = GameScene::GetHeroNavigation();

	if (heroNavigation->GetCurTask())
	{
		NavigationTaskType ntype = heroNavigation->GetCurTask()->GetNavigationTaskType();
		if ( ntype == eNavigationTaskType_HangUpMonster
			|| ntype == eNavigationTaskType_HangUpInCopyRoutTask)
		{
			heroNavigation->CancelNavigation();
		}
	}
	*/
}

void ActorManager::onGameStateEnter()
{
	/*
	if( !m_click )
	{
		//初始化地图点击动画
		m_click = Click::node();
		m_click->init();
		AddActor(m_click );
	}
	if( !m_pick )
	{
		//初始化角色选中
		m_pick = Pick::node();
		m_pick->init();
		AddActor(m_pick );
	}
	if( !m_aoe )
	{
		//初始化AOE选择框
		m_aoe = AOEpick::node();
		m_aoe->init();
		AddActor(m_aoe );
	}
	*/
}

void ActorManager::onGameStateLeave()
{
	MAP_ACTORS mapTemp( m_mapActors );
	for( MAP_ACTORS::iterator iter = mapTemp.begin(); iter != mapTemp.end(); ++iter )
	{
		DelActor( iter->first );
	}
	/*
	m_hero = NULL;
	m_click = NULL;
	m_pick = NULL;
	m_aoe = NULL;
	*/
}

void ActorManager::updateAllNpcIcon()
{
	for( MAP_ACTORS::iterator iter = m_mapActors.begin(); iter != m_mapActors.end(); ++iter )
	{
		Actor* pActor = iter->second;
		switch( pActor->getActorType() )
		{
		case ACTORTYPE_NPC:
			{
				//CNpc* pNpc = (CNpc*)pActor;
				//pNpc->UpdateIcon();
			}
			break;
		}
	}
}

void ActorManager::getActors( int nActorType, int nDataID, vector<Actor*>& vOut )
{
	vOut.clear();
	for( MAP_ACTORS::iterator iter = m_mapActors.begin(); iter != m_mapActors.end(); ++iter )
	{
		Actor* pActor = iter->second;
		if( pActor->getActorType() == nActorType &&
			pActor->getDataID() == nDataID )
		{
			vOut.push_back( pActor );
		}
	}
}

void ActorManager::getActors( int nActorType, vector<Actor*>& vOut )
{
	vOut.clear();
	for(MAP_ACTORS::iterator it=m_mapActors.begin(); it!=m_mapActors.end(); it++)
	{
		Actor *pActor = it->second;
		if(pActor->getActorType() == nActorType)
		{
			vOut.push_back(pActor);
		}
	}
}

void ActorManager::getActors( MAP_ACTORS& vOut )
{
	vOut = m_mapActors;
}

//自动选择一个目标，在使用技能时无目标时调用
Actor	*ActorManager::AutoSelectTarget()
{
	Actor *pReturn = NULL;
	int	dis = 0;
	int	x=0; 
	int	y=0;
	int	disNew = 0;
	/*
	CCPoint heroPos = GetHero()->getPosition();
	for( MAP_ACTORS::iterator iter = m_mapActors.begin(); iter != m_mapActors.end(); ++iter )
	{
		Actor* pActor = iter->second;
		if( pActor->isVisible() && !pActor->isDead() )
		{
			if(pActor->getActorType() == ACTORTYPE_MONSTER )
			{
				x = (int)(heroPos.x-pActor->getPositionX());
				y = (int)(heroPos.y-pActor->getPositionY());
				disNew = x*x+y*y;
				if(pReturn == NULL || disNew < dis )
				{
					pReturn = pActor;
					dis = disNew;
				}
			}
			else if((pActor->getActorType() == ACTORTYPE_PLAYER || pActor->getActorType() == ACTORTYPE_PET) && m_hero->canAttackTarget(pActor) )
			{
				x = (int)(heroPos.x-pActor->getPositionX());
				y = (int)(heroPos.y-pActor->getPositionY());
				disNew = x*x+y*y;
				if(pReturn == NULL || disNew < dis )
				{
					pReturn = pActor;
					dis = disNew;
				}
			}
		}
	}
	*/
	return pReturn;
}

void ActorManager::onHeroPosSet()
{
	if( m_mapTransportActors.empty() )
		return;

	/*
	for( MAP_ACTORS::iterator iter = m_mapTransportActors.begin(); iter != m_mapTransportActors.end(); ++iter )
	{
		Actor* pActor = iter->second;
		float x = fabs(pActor->getPositionX() - m_hero->getPositionX());
		float y = fabs(pActor->getPositionY() - m_hero->getPositionY());
		
		if( x <= MAP_PHY_TILE_W*2 &&
			y <= MAP_PHY_TILE_H*2)
		{
			cc_timeval now;
			CCTime::gettimeofdayCocos2d(&now,NULL);
			if(now.tv_sec - timeNonce >= 5)
			{
				timeNonce = now.tv_sec;
				CObject *pObj = dynamic_cast<CObject*>(pActor);
				if( pObj&&pObj->getActorType() == ACTORTYPE_TRANSPORT )
				{
					const MapSettingData *pMapData = MapSettingCfg::instance().getMapSettingCfgData((int)pObj->getActorParam());
					if(pMapData && pMapData->mapFaction != -1 )
					{
						if( m_hero->getFaction() != pMapData->mapFaction )
						{
							MessageTips::showMessageTips(CText::GetText(CTextDef::TRANS_OPPOSITE_MAP));
							return;
						}
					}
				}
				m_hero->GetRoutingModule()->ClientStopMove();
				pk::U2GS_InteractObject toServer;
				toServer.nActorID = pActor->getActorID();
				toServer.Send();
			}
			break;
		}
	}
	*/
}
void ActorManager::setOtherChaFractionName(bool showFraction)
{
	MAP_ACTORS::iterator it = m_mapActors.begin();
	MAP_ACTORS::iterator end = m_mapActors.end();
	for (; it != end; ++it)
	{
		Actor* pActor = it->second;
		/*
		if (pActor->getActorType() == ACTORTYPE_PLAYER && pActor != GetHero())
		{
			//CPlayer* player = (CPlayer*)pActor;
			//player->showFactionName(showFraction);
		}
		*/
	}
}
void ActorManager::doReleaseMemory()
{
	/*
    if(GetHero() == NULL)
        return;
	MAP_ACTORS::iterator it = m_mapActors.begin();
	MAP_ACTORS::iterator end = m_mapActors.end();
	
	for (; it != end; ++it)
	{
		Actor* pActor = it->second;
		if (pActor->getActorType() == ACTORTYPE_PLAYER && pActor != GetHero())
		{
			CPlayer* player = (CPlayer*)pActor;
			if(!player->isPartGray(eGrayPart_Body))
			{
				SpriteInfo _SpriteInfo;
				_SpriteInfo._ActorGender = player->getSex();
				_SpriteInfo._ActorID = player->getCamp();
				_SpriteInfo._ActorType = ACTORTYPE_PLAYER;
				_SpriteInfo._EquipLevel = player->getEquipCoatID();
				ASprite* pOrigin = player->GetAnimation()->GetSprite(eAnimPart_Body);
				ASprite* pReplace = AspriteManager::instance().FindReplaceSpriteWhenMemoryLack(_SpriteInfo);
				player->GetAnimation()->ChangeToReplaceASprite(
					player,
					pOrigin,
					pReplace,
					ACTORTYPE_PLAYER,
					eGrayPart_Body);
			}
			//////////////////////////////////////////////////////////////////////////
			if(!player->isPartGray(eGrayPart_Weapon))
			{
				SpriteInfo _SpriteInfo;
				_SpriteInfo._ActorGender = player->getSex();
				_SpriteInfo._ActorID = player->getCamp();
				_SpriteInfo._ActorType = ACTORTYPE_WEAPON;
				_SpriteInfo._EquipLevel = player->getEquipWeaponID();
				ASprite* pOrigin = player->GetAnimation()->GetSprite(eAnimPart_Weapon);
				ASprite* pReplace = AspriteManager::instance().FindReplaceSpriteWhenMemoryLack(_SpriteInfo);
				player->GetAnimation()->ChangeToReplaceASprite(
					player,
					pOrigin,
					pReplace,
					ACTORTYPE_WEAPON,
					eGrayPart_Weapon);
			}
			//////////////////////////////////////////////////////////////////////////
			if(!player->isPartGray(eGrayPart_Mount))
			{
				SpriteInfo _SpriteInfo;
				_SpriteInfo._ActorGender = player->getSex();
				_SpriteInfo._ActorID = player->getCamp();
				_SpriteInfo._ActorType = ACTORTYPE_MOUNT;
				_SpriteInfo._EquipLevel = player->getEquipWeaponID();
				ASprite* pOrigin = player->GetAnimation()->GetSprite(eAnimPart_Mount);
				ASprite* pReplace = AspriteManager::instance().FindReplaceSpriteWhenMemoryLack(_SpriteInfo);
				player->GetAnimation()->ChangeToReplaceASprite(
					player,
					pOrigin,
					pReplace,
					ACTORTYPE_MOUNT,
					eGrayPart_Mount);
			}
		}
		else if (pActor->getActorType() == ACTORTYPE_PET)
		{
			CPet* pPet = (CPet*)pActor;
			if(pPet->isGray())
				continue;
			if(pPet->getMasterID() != GetHero()->getActorID())
			{
				SpriteInfo _SpriteInfo;
				_SpriteInfo._ActorGender = 0;
				_SpriteInfo._ActorID = (int)pActor->getActorID();
				_SpriteInfo._ActorType = ACTORTYPE_PET;
				_SpriteInfo._EquipLevel = 0;
				ASprite* pOrigin = pActor->GetAnimation()->GetSprite(eAnimPart_Body);
				ASprite* pReplace = AspriteManager::instance().FindReplaceSpriteWhenMemoryLack(_SpriteInfo);
				pActor->GetAnimation()->ChangeToReplaceASprite(
					pActor,
					pOrigin,
					pReplace,
					ACTORTYPE_PET,
					eGrayPart_Body);
			}
		}
	}

	for ( int i = 0; i < 4; ++i )
	{
		SpriteInfo _SpriteInfo;
		_SpriteInfo._ActorType = ACTORTYPE_SKILLSFX;
		_SpriteInfo._ActorID = i + 1;
		std::string name = AspriteManager::instance().GetSpriteName(_SpriteInfo);
		ASprite* pSprite = AspriteManager::instance().GetSprite(name);
		if(pSprite)
			pSprite->ReleaseTextureToDelayLoad();

		for ( int j = 0; j < 2; ++j )
		{
			SpriteInfo _SpriteInfo;
			_SpriteInfo._ActorType = ACTORTYPE_WEAPONSFX;
			_SpriteInfo._ActorID = i;
			_SpriteInfo._ActorGender = j;
			std::string name = AspriteManager::instance().GetSpriteName(_SpriteInfo);
			ASprite* pSprite = AspriteManager::instance().GetSprite(name);
			if(pSprite)
				pSprite->ReleaseTextureToDelayLoad();
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//monsterSFX
	for ( int i = 4; i < 10; ++i )
	{
		SpriteInfo _SpriteInfo;
		_SpriteInfo._ActorType = ACTORTYPE_SKILLSFX;
		_SpriteInfo._ActorID = i + 1;
		std::string name = AspriteManager::instance().GetSpriteName(_SpriteInfo);
		ASprite* pSprite = AspriteManager::instance().GetSprite(name);
		if(pSprite)
			pSprite->ReleaseTextureToDelayLoad();
	}
	*/
}

#define		SelectTarget_TargetListCount	5

struct ActorDis
{
	float		dis;
	Actor*	pActor;

	bool operator <   (const ActorDis& rhs ) 
	{
		return dis < rhs.dis;
	};
};

Actor	*ActorManager::SelectTarget()
{
	//if( !m_hero )
	//	return NULL;
	static	int	lastSelectMapID = 0;
	static	cocos2d::Point	lastSelectHeroPos = cocos2d::Vec2();
	static	int	lastSelectIndex	=	0;

	/*
	if( GameScene::GetMap()->getMapID() != lastSelectMapID || fabs(m_hero->getPositionX()-lastSelectHeroPos.x) >= 100 || fabs(m_hero->getPositionY()-lastSelectHeroPos.y) >= 100 )
	{
		lastSelectIndex = 0;
	}
	lastSelectMapID = GameScene::GetMap()->getMapID();
	lastSelectHeroPos = m_hero->getPosition();
	*/

	list<ActorDis>	tempActor;
	for( MAP_ACTORS::iterator iter = m_mapActors.begin(); iter != m_mapActors.end(); ++iter )
	{
		Actor* pActor = iter->second;
		if( pActor->isVisible() /*&& !pActor->isDead()*/ )
		{
			if(pActor->getActorType() == ACTORTYPE_MONSTER )
			{
				ActorDis	actor;
				actor.dis = (pActor->getPositionX()-lastSelectHeroPos.x)*(pActor->getPositionX()-lastSelectHeroPos.x)
					+ (pActor->getPositionY()-lastSelectHeroPos.y)*(pActor->getPositionY()-lastSelectHeroPos.y);
				actor.pActor = pActor;
				tempActor.push_back(actor);
			}
			else if((pActor->getActorType() == ACTORTYPE_PLAYER || pActor->getActorType() == ACTORTYPE_PET)/* && m_hero->canAttackTarget(pActor) */ )
			{
				ActorDis	actor;
				actor.dis = (pActor->getPositionX()-lastSelectHeroPos.x)*(pActor->getPositionX()-lastSelectHeroPos.x)
					+ (pActor->getPositionY()-lastSelectHeroPos.y)*(pActor->getPositionY()-lastSelectHeroPos.y);
				actor.pActor = pActor;
				tempActor.push_back(actor);
			}
		}
	}

	tempActor.sort();
	Actor * pReturn = NULL;

	 int i=0;
	 for( list<ActorDis>::iterator it = tempActor.begin(); it !=tempActor.end(); ++it )
	 {
		 if( i>= lastSelectIndex )
		 {
			 if( ++lastSelectIndex >= SelectTarget_TargetListCount ) lastSelectIndex = 0;
			 return it->pActor;
		 }
		 ++i;
		 pReturn = it->pActor;
	 }
	 lastSelectIndex = 0;
	return pReturn;
}
