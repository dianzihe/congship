//
//  GameFrontLayer.cpp
//  dangdangtang
//
//  Created by haotao on 11-12-1.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "GameFrontLayer.h" 
//#include "ddd_global.h"
//#include "../battle_base/WBPixelSprite.h"
//#include "BattleScene.h"
//#include "WHud.h"
//#include "../battle_base/WBUtil.h"
//#include "SettlementScene.h"
//#include "../map/WMap.h"
#define system_path "gameResources/battle/map/maptest/"
//#include "WMusic.h"
//#include "Teach/WTeach.h"
//#include "WBItemSkill.h"

GameFrontLayer::GameFrontLayer()
{
	/*
	m_lpTouches=new WTouches();
	m_lpTouches->retain();

	assert(m_lpTouches);

	m_lpTouches->EnableTouch(kCCMenuTouchPriority);

	*/
	autorelease();
	scheduleUpdate();

	m_currentWBEvent = NULL;


	m_showisyourturn = false;
	m_showRoundNum = false;

	m_isGameOver = false;

	isShootingNow = false;

	// canNextRound=false;

	//_controller=NULL;

	m_lockForHud = false;

	//m_PixelByte=NULL;
#if (NOT_USE_STENCIL_SPRITE == 1)
	//m_PixelByte=NULL;
#else
	m_stencilSprite = NULL;
#endif

	m_AIstatus = 0;

	m_RoundNum = 1;
}

GameFrontLayer::~GameFrontLayer()
{

	// WMusic::shareMusic()->unLoadBattleSounds();

	removeAllChildrenWithCleanup(true);




	unscheduleUpdate();
	/*
	if(m_lpTouches)
	{
	m_lpTouches->DisableTouch();

	CC_SAFE_RELEASE_NULL(m_lpTouches);

	}

	CC_SAFE_RELEASE_NULL(_controller);

	CC_SAFE_RELEASE_NULL(m_heros);
	*/
#if (NOT_USE_STENCIL_SPRITE == 1)
	//CC_SAFE_RELEASE_NULL(m_PixelSprites);
	//CC_SAFE_DELETE(m_PixelByte);
#else
	CC_SAFE_RELEASE_NULL(m_stencilSprite);
#endif
	// CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void GameFrontLayer::setWindLevel()
{

	//int level=WDDD_GLOBAL.m_lpBattleGlobal->getWindLevel();

	//getBattleScene()->getHudLayer()->setWindLevel(level);
	//m_wind=Vec2(level*0.01,0);
}



void GameFrontLayer::onEnter()
{
	CCLayer::onEnter();
	m_touch_status = E_TS_NONE;
	playermove_press_time = 0;
	//WMusic::shareMusic()->PlaySound(WMusic::E_S_ROUND);

	m_currentWBEvent = NULL;
	/*
	WBEvent *lpEvent = new WBEvent(EVENT_SCR_ZOOM_TO_HERO, 0);
	SendEventToQueue(lpEvent);
	*/


	WHero *lpHero = GetCurrentHero();
	/*
	if(lpHero->getPlayerId()==WDDD_GLOBAL.m_lpBattleGlobal->myHero->getPlayerId())
	{
	m_showisyourturn=true;
	//WHud *lpGLayer=(WHud *)m_BattleScene->getHudLayer();
	//lpGLayer->setShowIsYourTurn(true);
	}
	*/
	/*
	getBattleScene()->getHudLayer()->setShowNewRound(true);

	float dZoom=_controller->_zoomInLimit-_controller->_zoomOutLimit;
	m_normalscale=dZoom*0.6+_controller->_zoomOutLimit;
	m_lastScale=m_normalscale;
	*/
	setWindLevel();
	/*
	CCSize s=getContentSizeInPixels();
	setScale(_controller->_zoomOutLimit);
	_controller->centerOnPoint(CCPointMake(s.width/2, 0));


	WDDD_GLOBAL.m_pNetSocketConnection->registerProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_SomeOneDead);
	WDDD_GLOBAL.m_pNetSocketConnection->registerProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_UpdateHP);
	WDDD_GLOBAL.m_pNetSocketConnection->registerProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_CanStartCurRound);
	WDDD_GLOBAL.m_pNetSocketConnection->registerProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_OtherPlayerMove);
	WDDD_GLOBAL.m_pNetSocketConnection->registerProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_OtherSkillEquip);
	WDDD_GLOBAL.m_pNetSocketConnection->registerProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_ChangeAngryValue);
	WDDD_GLOBAL.m_pNetSocketConnection->registerProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_OtherBigSkill);
	WDDD_GLOBAL.m_pNetSocketConnection->registerProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_OtherShoot);
	WDDD_GLOBAL.m_pNetSocketConnection->registerProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_OtherFly);
	WDDD_GLOBAL.m_pNetSocketConnection->registerProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_OtherPass);
	WDDD_GLOBAL.m_pNetSocketConnection->registerProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_GameOver);
	//    WDDD_GLOBAL.m_pNetSocketConnection->registerProtocolProcesser(OnNetWork, this, Protocol::MAIN_ROOM, Protocol::ROOM_EnterRoomOk);

	WDDD_GLOBAL.m_pNetSocketConnection->registerProtocolProcesser(OnNetWork,this,Protocol::MAIN_BATTLE,Protocol::BATTLE_AttackSequence);

	WDDD_GLOBAL.m_pNetSocketConnection->registerProtocolProcesser(OnNetWork,this,Protocol::MAIN_BATTLE,Protocol::BATTLE_PlayerReborn);

	WDDD_GLOBAL.m_pNetSocketConnection->registerProtocolProcesser(OnNetWork,this,Protocol::MAIN_BATTLE,Protocol::BATTLE_PlayerLose);

	WDDD_GLOBAL.m_pNetSocketConnection->registerProtocolProcesser(OnNetWork,this,Protocol::MAIN_BATTLE,Protocol::BATTLE_AIControlCommon);
	WDDD_GLOBAL.m_pNetSocketConnection->registerProtocolProcesser(OnNetWork,this,Protocol::MAIN_BATTLE,Protocol::BATTLE_OtherUsingFace);

	WDDD_GLOBAL.m_pNetSocketConnection->registerProtocolProcesser(OnNetWork,this, Protocol::MAIN_BATTLE, Protocol::BATTLE_OtherUseFly);
	*/
}

void GameFrontLayer::onExit()
{
	/*
	WDDD_GLOBAL.m_pNetSocketConnection->unregisterProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_SomeOneDead);
	WDDD_GLOBAL.m_pNetSocketConnection->unregisterProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_UpdateHP);
	WDDD_GLOBAL.m_pNetSocketConnection->unregisterProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_CanStartCurRound);
	WDDD_GLOBAL.m_pNetSocketConnection->unregisterProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_OtherPlayerMove);
	WDDD_GLOBAL.m_pNetSocketConnection->unregisterProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_OtherSkillEquip);
	WDDD_GLOBAL.m_pNetSocketConnection->unregisterProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_ChangeAngryValue);
	WDDD_GLOBAL.m_pNetSocketConnection->unregisterProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_OtherBigSkill);
	WDDD_GLOBAL.m_pNetSocketConnection->unregisterProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_OtherShoot);
	WDDD_GLOBAL.m_pNetSocketConnection->unregisterProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_OtherFly);
	WDDD_GLOBAL.m_pNetSocketConnection->unregisterProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_OtherPass);
	WDDD_GLOBAL.m_pNetSocketConnection->unregisterProtocolProcesser(OnNetWork, this, Protocol::MAIN_BATTLE, Protocol::BATTLE_GameOver);

	//    WDDD_GLOBAL.m_pNetSocketConnection->unregisterProtocolProcesser(OnNetWork, this, Protocol::MAIN_ROOM, Protocol::ROOM_EnterRoomOk);

	WDDD_GLOBAL.m_pNetSocketConnection->unregisterProtocolProcesser(OnNetWork,this,Protocol::MAIN_BATTLE,Protocol::BATTLE_AttackSequence);

	WDDD_GLOBAL.m_pNetSocketConnection->unregisterProtocolProcesser(OnNetWork,this,Protocol::MAIN_BATTLE,Protocol::BATTLE_PlayerReborn);

	WDDD_GLOBAL.m_pNetSocketConnection->unregisterProtocolProcesser(OnNetWork,this,Protocol::MAIN_BATTLE,Protocol::BATTLE_PlayerLose);

	WDDD_GLOBAL.m_pNetSocketConnection->unregisterProtocolProcesser(OnNetWork,this,Protocol::MAIN_BATTLE,Protocol::BATTLE_AIControlCommon);

	WDDD_GLOBAL.m_pNetSocketConnection->unregisterProtocolProcesser(OnNetWork,this,Protocol::MAIN_BATTLE,Protocol::BATTLE_OtherUsingFace);

	WDDD_GLOBAL.m_pNetSocketConnection->unregisterProtocolProcesser(OnNetWork,this, Protocol::MAIN_BATTLE, Protocol::BATTLE_OtherUseFly);

	ClearEventQueue();
	DELETEOBJ(m_currentWBEvent);
	CCLayer::onExit();

	if(m_isGameOver==false)
	{
	WDDD_GLOBAL.m_lpBattleGlobal->end();
	}
	*/
}

WHero *GameFrontLayer::GetCurrentHero()
{
	WHero *lpHero = NULL;
	/*
	int curPlayerId=WDDD_GLOBAL.m_lpBattleGlobal->getCurPlayerId();

	for(int i=0; i<WDDD_GLOBAL.m_lpBattleGlobal->heros->count(); i++)
	{
	lpHero=(WHero *)WDDD_GLOBAL.m_lpBattleGlobal->heros->objectAtIndex(i);

	if(lpHero->getPlayerId()==curPlayerId)
	{
	break;
	}
	}
	*/

	return lpHero;
}

WHero *GameFrontLayer::GetOldHero()
{

	WHero *lpHero = NULL;
	/*
	int curPlayerId=WDDD_GLOBAL.m_lpBattleGlobal->getOldPlayerId();

	for(int i=0; i<WDDD_GLOBAL.m_lpBattleGlobal->heros->count(); i++)
	{
	lpHero=(WHero *)WDDD_GLOBAL.m_lpBattleGlobal->heros->objectAtIndex(i);

	if(lpHero->getPlayerId()==curPlayerId)
	{
	break;
	}
	}

	*/
	return lpHero;
}


void GameFrontLayer::BuildHero()
{
	/*
	m_heros=WDDD_GLOBAL.m_lpBattleGlobal->heros;
	m_heros->retain();

	for(int i=0; i<m_heros->count(); i++)
	{
	WHero *lpHero=(WHero *)m_heros->objectAtIndex(i);
	lpHero->setGameFrontLayer(this);
	lpHero->start();
	log("HeroPos:%f,%f",lpHero->getMoverPosition().x,lpHero->getMoverPosition().y);
	addChild(lpHero);
	}

	// m_currentHero=0;

	m_lastScrCenterPoint=WDDD_GLOBAL.m_lpBattleGlobal->myHero->getPositionInPixels();
	WAnimationNode *pNode=WCharacter::AnimationWithFileCircle(WDDD_GLOBAL.getLocalResFile(DEF_SYSTEM_HUD_PATH"Photosphere.png"), 4, 166, 166, 0, 0, 0.4);

	m_myHeroCircle=WCharacter::node();
	m_myHeroCircle->AddAnimationToDict(0, pNode);
	m_myHeroCircle->setAnimation(0);
	//WDDD_GLOBAL.m_aniManager.GetSampleAnimation(WANI_IWCO_BATTLEEFFICIENTS, "Photosphere");
	CCPoint pos=WDDD_GLOBAL.m_lpBattleGlobal->myHero->getAnchorPointInPixels();
	pos.y+=30;
	m_myHeroCircle->setPositionInPixels(pos);
	m_myHeroCircle->PlayRepeat();

	//    ccBlendFunc tagBlendFunc;
	//    tagBlendFunc.src=GL_SRC_ALPHA;
	//    tagBlendFunc.dst=GL_ZERO;
	//    m_myHeroCircle->setBlendFunc(tagBlendFunc);

	//    WFinger *lpFinger=WTeach::shareTeach()->getFinger(WTeach::E_TP_PULL);
	//
	//    if(lpFinger)
	//    {
	//        CCPoint pos=WDDD_GLOBAL.m_lpBattleGlobal->myHero->getAnchorPointInPixels();
	//        pos.y+=WDDD_GLOBAL.m_lpBattleGlobal->myHero->getMoverCenter().y;
	//        lpFinger->setPositionInPixels(pos);
	//        WDDD_GLOBAL.m_lpBattleGlobal->myHero->setFinger(lpFinger);
	//        WDDD_GLOBAL.m_lpBattleGlobal->myHero->addChild(lpFinger,2);
	//    }

	WDDD_GLOBAL.m_lpBattleGlobal->myHero->addChild(m_myHeroCircle,-2);
	*/
}



void GameFrontLayer::LoadMap(WMap *pMap)
{
	//initMap(pMap);

	BuildHero();
}






bool GameFrontLayer::getStartSpeedNormal(Vec2 &startPos,
	Vec2 &endPos, Vec2 &SpeedNormal)
{
	/*
	Vec2 a = m_gravityFly + m_wind;

	Vec2 reA(-a.x, -a.y);

	Vec2 sNormal = endPos - startPos;

	reA.normalize();
	sNormal.normalize();

	Vec2 v(reA.x - sNormal.x, reA.y - sNormal.y);

	float lenth = v.normalize();

	int r = 2 + rand() % 2;

	lenth /= r;

	SpeedNormal = Vec2(sNormal.x + v.x*lenth, sNormal.y + v.y*lenth);

	SpeedNormal.normalize();
	*/
	return true;
}

bool GameFrontLayer::getStartSpeedNormal2(Vec2 &startPos,
	Vec2 &endPos, Vec2 &SpeedNormal)
{
	/*
	Vec2 a = m_gravityFly + m_wind;

	Vec2 reA(-a.x, -a.y);

	Vec2 sNormal = endPos - startPos;

	reA.normalize();
	sNormal.normalize();

	Vec2 v(sNormal.x - reA.x, sNormal.y - reA.y);

	float lenth = v.normalize();

	int r = 2 + rand() % 2;

	lenth /= r;

	SpeedNormal = Vec2(reA.x + v.x*lenth, reA.y + v.y*lenth);

	SpeedNormal.normalize();
	*/
	return true;
}

bool GameFrontLayer::getStartSpeedPowerWithSpeedNormal(Vec2 &speedNormal, Vec2 &startPos,
	Vec2 &endPos, float &power)
{

	/*
	Vec2 a = m_gravityFly + m_wind;

	Vec2 reA(-a.x, -a.y);

	Vec2 speed = speedNormal;
	// speed.y=-speed.y;

	Vec2 s = endPos - startPos;

	Vec2 sNormal = s;

	float distance = sNormal.normalize();

	if (distance <= 0)
	{
		power = 0;
		return true;
	}

	float length = reA.normalize();

	if (length <= 0)
	{
		float dot = b2Dot(speed, sNormal);

		if (dot == 0)
		{
			power = 3.0f; //
			return true;
		}
		else
		{
			return false;
		}
	}

	float E_S = b2Cross(speed, sNormal);
	float E_A = b2Cross(speed, reA);

	if (E_S == 0 || E_A == 0)
	{
		return false;
	}


	if (E_S*E_A < 0.0)
	{
		float dt = (float)sqrtf(2.0f*(s.y*speed.x - s.x*speed.y) / (a.y*speed.x - a.x*speed.y));

		if (dt <= 0)
		{
			return false;
		}

		power = (s.x - 0.5f*a.x*dt*dt) / (speed.x*dt);
	}
	else
	{
		return false;
	}
	*/
	return true;
}

WHero *GameFrontLayer::getDistanceLessVsHero(WHero *myHero)
{
	WHero *lpHero;
	WHero *disLessHero = NULL;
	float dis = FLT_MAX;
	for (int i = 0; i < m_heros->count(); i++)
	{
		lpHero = (WHero *)m_heros->objectAtIndex(i);

		if (lpHero->getCamp() != myHero->getCamp()
			&& !lpHero->getIsDead() && !lpHero->getLoseNet())
		{

			Vec2 D = myHero->getMoverPosition();
			D -= lpHero->getMoverPosition();
			float Dis = D.length();

			if (Dis < dis)
			{
				disLessHero = lpHero;
				dis = Dis;
			}
		}
	}

	return disLessHero;
}

WHero *GameFrontLayer::getHpLessVsHero(WHero *myHero)
{
	WHero *lpHero;
	WHero *HPLessHero = NULL;
	float HP = FLT_MAX;
	for (int i = 0; i < m_heros->count(); i++)
	{
		lpHero = (WHero *)m_heros->objectAtIndex(i);

		if (lpHero->getCamp() != myHero->getCamp()
			&& !lpHero->getIsDead() && !lpHero->getLoseNet())
		{

			if (lpHero->getHP() < HP)
			{
				HPLessHero = lpHero;
				HP = lpHero->getHP();
			}
		}
	}

	return HPLessHero;
}
WHero *GameFrontLayer::getPreTargetVsHero(WHero *myHero)
{
	int r = rand() % 2;
	WHero *lpHero = NULL;

	if (r == 0)
	{
		lpHero = myHero->getPreTargetHero();
		if (lpHero && !lpHero->getIsDead() && !lpHero->getLoseNet())
		{
			lpHero = NULL;
		}
	}
	else
	{
		for (int i = 0; i < m_heros->count(); i++)
		{
			lpHero = (WHero *)m_heros->objectAtIndex(i);

			if (lpHero->getCamp() == myHero->getCamp()
				&& !lpHero->getIsDead() && !lpHero->getLoseNet())
			{
				lpHero = lpHero->getPreTargetHero();
				if (lpHero && !lpHero->getIsDead() && !lpHero->getLoseNet())
				{
					break;
				}
			}
		}
	}

	return lpHero;
}


WHero *GameFrontLayer::getRandVsHero(WHero *myHero)
{
	WHero *lpHero;


	vector<WHero *> li;

	for (int i = 0; i < m_heros->count(); i++)
	{
		lpHero = (WHero *)m_heros->objectAtIndex(i);

		if (lpHero->getCamp() != myHero->getCamp()
			&& !lpHero->getIsDead() && !lpHero->getLoseNet())
		{
			li.push_back(lpHero);
		}
	}

	if (li.size() <= 0)
	{
		return NULL;
	}

	int r = rand() % li.size();

	return li[r];
}

void GameFrontLayer::AICtrl()
{
}

void GameFrontLayer::checkTouch()
{
}
void GameFrontLayer::processTouch()
{

}

void GameFrontLayer::processEvent()
{

}




void GameFrontLayer::setSpring(CCPoint targetPosition)
{
	if (m_TargetPosition.x == targetPosition.x && m_TargetPosition.y == m_TargetPosition.y)
	{
		return;
	}

	m_SpringTime = 0.5f;
	m_SpringDistance = 5.0f;


	m_screan_status = E_SCR_SPRING;
	m_SpringPosition = getPosition();
	m_TargetPosition = targetPosition;

	m_SpringUpDown = 0;

}


void GameFrontLayer::checkBulletCount()
{
	/*
	CCArray *lpChildren = getChildren();

	int childcount = lpChildren->count();


	int bulletcount = 0;
	for (int i = 0; i < childcount; i++)
	{
		CCNode *lpNode = (CCNode *)lpChildren->objectAtIndex(i);

		if (lpNode->getTag() == DEF_OBJ_TYPE_BULLET)
		{

			bulletcount++;
			break;

		}

	}

	if (bulletcount != 0)
	{
		SendEventToQueue(new WBEvent(EVENT_SCR_FOLLOW_BULLET, 0));
		m_currentWBEvent->End();
		m_screan_status = E_SCR_NONE;
	}
	*/
}
void GameFrontLayer::processScrean()
{
	switch (m_screan_status)
	{
	case E_SCR_NORMAL:
	{
		WHero *pHero = GetCurrentHero();

		if (pHero->getIsFreeze())
		{
			break;
		}


		checkTouch();
		processTouch();

		if (pHero->getCtrlType() == 2)
		{
			if (pHero->getIsDead() == false && pHero->getIsFreeze() == false) AICtrl();
		}

	}
	break;

	case E_SCR_SHOOTTING:
	{
		checkBulletCount();
	}
	break;

	case E_SCR_WAIT_FOR_NEXT_ROUND:
	{
		if (m_waitForNextRoundTime >= 0)
		{
			m_waitForNextRoundTime -= m_dt;

			if (m_waitForNextRoundTime < 0)
			{
				// getBattleScene()->getHudLayer()->showCircleLoading();
			}
		}
		log("E_SCR_WAIT_FOR_NEXT_ROUND");
	}
	break;

	case E_SCR_ZOOM_TO_HERO:
	{


	}
	break;

	case E_SCR_FOLLOW_BULLET:
	{
	
	}
	break;

	case E_SCR_SPRING:
	{

	}
	break;

	case E_SCR_FOLLOW_HERO:
	{



	}
	break;

	case E_SCR_CENTER_TO_HERO_NOW:
	{


	}
	break;

	case E_SCR_ZOOM_OUT:
	{

	}
	break;

	default:
		break;
	}
}


void GameFrontLayer::update(float dt)
{
	/*
	if(!WDDD_GLOBAL.m_pNetSocketConnection)
	return;

	//处理网络收发
	//  WBSendProtocolListener();
	WDDD_GLOBAL.m_pNetSocketConnection->receiveListener();

	m_dt=dt; //保存时间方便读取

	if(m_myHeroCircle)
	{
	//每一个动画锚点都不一样,所以需要更新
	CCPoint pos=WDDD_GLOBAL.m_lpBattleGlobal->myHero->getAnchorPointInPixels();
	pos.y+=30;
	m_myHeroCircle->setPositionInPixels(pos);
	}
	*/
	//处理事件队列
	processEvent();

	//处理当前接收到的事件
	//   processCurrentEvent();

	//处理屏幕移动
	processScrean();

}

void GameFrontLayer::updateHud()
{
	//getBattleScene()->getHudLayer()->updateHud();
}

void GameFrontLayer::onSelfLost(void *data, int msg, int param1, int param2)
{
	/*
	if(WDDD_GLOBAL.isMustTeach)
	{
	cwSngDirector::sharedDirector()->replaceScene(Scene_IsLand::scene());
	}
	else if(WDDD_GLOBAL.m_lpBattleGlobal->getBattleLocalMode() == DEF_BATTLEMODE_QULIFYING)
	{
	cwSngDirector::sharedDirector()->replaceScene(Scene_Qualifying::scene());
	}
	else
	{
	cwSngDirector::sharedDirector()->replaceScene(Scene_Hall::scene());
	}
	*/
}




