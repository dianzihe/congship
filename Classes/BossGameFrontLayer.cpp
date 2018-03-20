//
//  BossGameFrontLayer.cpp
//  dangdangtang
//
//  Created by haotao on 11-12-1.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "BossGameFrontLayer.h" 
/*
#include "ddd_global.h"
#include "../battle_base/WBPixelSprite.h"
#include "BossBattleScene.h"
#include "WBossHud.h"
#include "../battle_base/WBUtil.h"
#include "BossSettlementScene.h"
#include "../map/WMap.h"
#define system_path "gameResources/battle/map/maptest/"
#include "WMusic.h"
#include "Teach/WTeach.h"
#include "../battle/WBItemSkill.h"
#include "../battle_base/WBdefine.h"
#include "../../ui/ui_bossmap/Scene_BossmapIsland.h"
#if OPEN_FIFTH
#include "../../ui/ui_bossmap/Scene_SelectBossmap.h"
#endif
*/



BossGameFrontLayer::BossGameFrontLayer()
{
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

#if(NOT_USE_STENCIL_SPRITE == 1)
	//m_PixelByte=NULL;
#else
	m_stencilSprite = NULL;
#endif


	m_AIstatusForPlayer = 0;

	m_RoundNum = 1;

	// Added By Mrj, For Boss3, Start
#if OPEN_BOSSMAP_3
	m_iBoss3EndGetPowerCount = 0;
	m_roundOfCastPowerUp = 0;
	m_roundOfGetShield = 0;
	m_boss3PowerBall = NULL;
	m_boss3_1ball = NULL;
	m_boss3_2ball = NULL;
	m_boss3Shied = NULL;
	m_castPowerUp = false;          // 出现小球，下个BOSS回合，BOSS攻击力2.5倍
	m_bossGetPowerUp = false;       // BOSS是否吸收过小球，用来控制光球消失
	m_playerGetShieldRound = false; // 是否经过了玩家吸收盾的回合
	// 以上3个字段用来控制BOSS技能的出现和消失
#endif
	// Added By Mrj, For Boss3, End
}

BossGameFrontLayer::~BossGameFrontLayer()
{

	// WMusic::shareMusic()->unLoadBattleSounds();

	removeAllChildrenWithCleanup(true);


	while (m_EventManager.size())
	{
		WBEvent *pEvent = m_EventManager.front();
		m_EventManager.pop();
		CC_SAFE_DELETE(pEvent);
	}

	while (m_quickEventManager.size())
	{
		WBEvent *pEvent = m_quickEventManager.front();
		m_quickEventManager.pop();
		CC_SAFE_DELETE(pEvent);
	}

	unscheduleUpdate();

	//CC_SAFE_RELEASE_NULL(_controller);

	// CC_SAFE_RELEASE_NULL(m_heros);

#if(NOT_USE_STENCIL_SPRITE == 1)
	//CC_SAFE_RELEASE_NULL(m_PixelSprites);
	//CC_SAFE_DELETE(m_PixelByte);
#else
	CC_SAFE_RELEASE_NULL(m_stencilSprite);
#endif
	// CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void BossGameFrontLayer::setWindLevel()
{

}



void BossGameFrontLayer::onEnter()
{
	CCLayer::onEnter();

	m_touch_status = E_TS_NONE;
	playermove_press_time = 0;


	m_currentWBEvent = NULL;
	startNewRound();

	/*
	WChara *lpHero = GetCurrentChara();
	if (lpHero
		&& lpHero->getCharaType() == WDDD_GLOBAL.m_lpBattleGlobal->m_bossMyHero->getCharaType()
		&& lpHero->getPlayerId() == WDDD_GLOBAL.m_lpBattleGlobal->m_bossMyHero->getPlayerId())
	{
		m_showisyourturn = true;
		WHud *lpGLayer = (WHud *)m_BattleScene->getHudLayer();
		lpGLayer->setShowIsYourTurn(true);
	}


	getBattleScene()->getHudLayer()->setShowNewRound(true);
	*/

}

void BossGameFrontLayer::onExit()
{
}

void BossGameFrontLayer::BuildHero()
{
	/*
	m_heros = WDDD_GLOBAL.m_lpBattleGlobal->m_bossHeros;
	m_heros->retain();

	for (int i = 0; i<m_heros->count(); i++)
	{
		WBossHero *lpHero = (WBossHero *)m_heros->objectAtIndex(i);
		lpHero->setGameFrontLayer(this);
		lpHero->start();
		WLog("HeroPos:%f,%f", lpHero->getMoverPosition().x, lpHero->getMoverPosition().y);
		addChild(lpHero, 1);
	}

	m_guais = WDDD_GLOBAL.m_lpBattleGlobal->m_bossGuais;
	m_guais->retain();
	*/
	for (int i = 0; i<m_guais->count(); i++)
	{
		WBossGuai *lpGuai = (WBossGuai *)m_guais->objectAtIndex(i);
		if (lpGuai->getPlayerId() != -1)
		{
			lpGuai->setGameFrontLayer(this);
			lpGuai->start();
			addChild(lpGuai);
		}
	}

	// m_currentHero=0;

	//m_lastScrCenterPoint = WDDD_GLOBAL.m_lpBattleGlobal->m_bossMyHero->getPositionInPixels();

	WAnimationNode *pNode = WCharacter::AnimationWithFileCircle(WDDD_GLOBAL.getLocalResFile(DEF_SYSTEM_HUD_PATH"Photosphere.png"), 4, 166, 166, 0, 0, 0.4);

	m_myHeroCircle = WCharacter::node();
	m_myHeroCircle->AddAnimationToDict(0, pNode);
	m_myHeroCircle->setAnimation(0);
	//WDDD_GLOBAL.m_aniManager.GetSampleAnimation(WANI_IWCO_BATTLEEFFICIENTS, "Photosphere");
	CCPoint pos = WDDD_GLOBAL.m_lpBattleGlobal->m_bossMyHero->getAnchorPointInPixels();
	pos.y += 30;
	m_myHeroCircle->setPositionInPixels(pos);
	m_myHeroCircle->PlayRepeat();

	WDDD_GLOBAL.m_lpBattleGlobal->m_bossMyHero->addChild(m_myHeroCircle, -2);
}

bool BossGameFrontLayer::getStartSpeedNormal(Vec2 &startPos,
	Vec2 &endPos, Vec2 &SpeedNormal)
{
	return true;
}

bool BossGameFrontLayer::getStartSpeedNormal2(Vec2 &startPos,
	Vec2 &endPos, Vec2 &SpeedNormal)
{
	return true;
}

bool BossGameFrontLayer::getStartSpeedPowerWithSpeedNormal(Vec2 &speedNormal, Vec2 &startPos,
	Vec2 &endPos, float &power)
{
	return true;
}

void BossGameFrontLayer::AICtrlForPlayer()
{
}

void BossGameFrontLayer::checkTouch()
{
	
}
void BossGameFrontLayer::processTouch()
{
	
}



void BossGameFrontLayer::processEvent()
{
	while (m_EventManager.size() > 0)
	{
		if (m_currentWBEvent != NULL)
		{
			//if (!m_currentWBEvent->isEnd()) break;

			//DELETEOBJ(m_currentWBEvent);
		}

		m_currentWBEvent = m_EventManager.front();
		m_EventManager.pop();



		switch (m_currentWBEvent->getType()) {


		case EVENT_ERROR:
			break;

		case EVENT_MOVE_PLAYER: //移动角色
		{

		}
		break;

		case EVENT_DEATH:
		{
	
		}
		break;

		case EVENT_FLY:
		{



		}
		break;

		case EVENT_USE_SKILL_ITEM://使用指定技能道具
		{
	
		}
		break;

		case EVENT_SHOOT://射击
		{


		}
		break;

		case EVENT_BIGSKILL://使用大招
		{
		
		}
		break;

		case EVENT_WAITNEXTROUND:
		{
		
		}
		break;

		case EVENT_NEXT_ROUND:
		{
			startNewRound();

		}
		break;



		case EVENT_GAMEOVER:
		

			break;

		case EVENT_REBORN:
		{
	
		}

		break;

		case EVENT_BUILDGUAI:
		{
		
		}
		break;

		case EVENT_PLAYER_LOST:
		{
		
		}
		break;

		case EVENT_TRANSFORM:
		{
	
		}
		break;

		case EVENT_SCR_ZOOM_OUT:
			m_screan_status = E_SCR_ZOOM_OUT;
			m_touch_status = E_TS_DONT_TOUCH;

			break;


		case EVENT_SCR_NORMAL:
			m_screan_status = E_SCR_NORMAL;
			//m_currentWBEvent->End();
			m_touch_status = E_TS_NONE;
			break;

		case EVENT_SCR_ZOOM_TO_BOSS:
			m_screan_status = E_SCR_ZOOM_TO_BOSS;
			m_screanLockTime = 0.0f;
			break;

		case EVENT_SCR_ZOOM_TO_HERO:
			m_screan_status = E_SCR_ZOOM_TO_HERO;
			m_screanLockTime = 0.0f;
			break;
		case EVENT_SCR_FOLLOW_BULLET:
			m_zoomTobullet = false;
			m_screan_status = E_SCR_FOLLOW_BULLET;
			break;
		case EVENT_SCR_FOLLOW_HERO:
			m_screan_status = E_SCR_FOLLOW_HERO;
			break;

		case EVENT_SCR_CENTER_TO_HERO_NOW:
			m_screan_status = E_SCR_CENTER_TO_HERO_NOW;
			break;

		case EVENT_SCR_ZOOM_TO_MELEE:
		{
			
		}
		break;

		case EVENT_SCR_ZOOM_TO_TARGET:
		{
			
		}
		break;

#if OPEN_BOSSMAP_3
		case EVENT_SCR_BOSS3_ZOOM_OUT:
			m_screan_status=E_SCR_ZOOM_OUT_BOSS3;
			//m_touch_status=E_TS_DONT_TOUCH;
			m_screanLockTime = 0.0f;
			m_currentWBEvent->End();
			break;


		case EVENT_SCR_PLAYER_GET_SHIELD:
		{
			WChara *lpChara=NULL;
			for(int i=0; i<WDDD_GLOBAL.m_lpBattleGlobal->m_bossHeros->count(); i++) {
				lpChara=(WChara *)WDDD_GLOBAL.m_lpBattleGlobal->m_bossHeros->objectAtIndex(i);

				WBossHero* pPlayer = (WBossHero*)lpChara;
				if(!pPlayer || pPlayer->getIsDead()) continue;

				pPlayer->SendMsgGetShield();
			}
			m_roundOfGetShield = m_RoundNum;
			m_currentWBEvent->End();
		}
		break;

		case EVENT_SCR_PLAYER_LOSS_SHIELD:
		{
			WChara *lpChara=NULL;
			for(int i=0; i<WDDD_GLOBAL.m_lpBattleGlobal->m_bossHeros->count(); i++) {
				lpChara=(WChara *)WDDD_GLOBAL.m_lpBattleGlobal->m_bossHeros->objectAtIndex(i);

				WBossHero* pPlayer = (WBossHero*)lpChara;
				if(!pPlayer || pPlayer->getIsDead()) continue;

				pPlayer->SendMsgLossShield();
			}
			m_currentWBEvent->End();
		}
		break;

#endif



		default:
			break;
		}
	}

	while (m_quickEventManager.size() > 0)
	{
		WBEvent *pEvent = m_quickEventManager.front();
		m_quickEventManager.pop();

		switch (pEvent->getType())
		{
		case EVENT_ERROR:

			break;

		case EVENT_UPDATE_ANGRYVALUE:
		{
			
		}
		break;
		}

		
		//DELETEOBJ(pEvent);

	}
}

//void BossGameFrontLayer::processCurrentEvent()
//{
//    if(!m_currentWBEvent) return;
//    
//    switch (m_currentWBEvent->getType()) {
//            
//            
//        case EVENT_ERROR:
//        break;
//            
//        case EVENT_MOVE_CURRENT_PLAYER: //移动角色
//        {
//            
//        }
//        break;
//            
//            
//        case EVENT_USE_SKILL_ITEM://使用指定技能道具
//            
//        break;
//            
//        case EVENT_SHOOT://射击
//        {
//            
//        }
//        break;
//            
//        case EVENT_BIGSKILL://使用大招
//            
//        break;                               
//            
//        case EVENT_ROUND_PASS: //跳过这一回合                       
//            
//        break;
//            
//        case EVENT_NEXT_ROUND:                 
//        {
//    
//        }
//        break;
//            
//        case EVENT_SCR_NORMAL:
//
//            break;
//            
//        case EVENT_SCR_ZOOM_TO_HERO:
//   
//            break;  
//        case EVENT_SCR_FOLLOW_BULLET:
//      
//            break;
//        case EVENT_SCR_FOLLOW_HERO:
//          
//            break;
//            
//            
//        default:
//            break;
//    }
//}


void BossGameFrontLayer::setSpring(CCPoint targetPosition)
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


void BossGameFrontLayer::checkBulletCount()
{
}
void BossGameFrontLayer::processScrean()
{
	log("m_screan_status%d", m_screan_status);
	switch (m_screan_status)
	{
	case E_SCR_NORMAL:
	{
		

	}
	break;

	case E_SCR_SHOOTTING:
	{
		checkBulletCount();
	}
	break;

	case E_SCR_WAIT_FOR_NEXT_ROUND:
	{
		log("E_SCR_WAIT_FOR_NEXT_ROUND");
	}
	break;

	case E_SCR_ZOOM_TO_MELEE:
	{

	}
	break;

	case E_SCR_ZOOM_TO_TARGET:
	{

	}
	break;

	case E_SCR_FOLLOW_MELEE:
	{
		

	}
	break;

	case E_SCR_ZOOM_TO_BOSS:
	{
		
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

#if OPEN_BOSSMAP_3
	case E_SCR_ZOOM_OUT_BOSS3:
	{

		setScale(getScale()+(_controller->_zoomOutLimit-getScale())*0.1);
		if(_controller->centerOnPoint(CCPointMake(getContentSizeInPixels().width/2, getContentSizeInPixels().height/2),0.2)) {
			//EndCurrentMsg();
			//SendEventToQueue(new WBEvent(EVENT_SCR_NORMAL,0));
			m_screanLockTime+=m_dt;
			if(m_screanLockTime >= 1.0f) {
				castBoss31Skill_PowerUp(true);
				showBoss3Shield(true);
				SendEventToQueue(new WBEvent(EVENT_SCR_NORMAL,0));
				//m_screan_status = E_SCR_NORMAL;
			}
		}
	}
	break;
#endif

	default:
		break;
	}
}


void BossGameFrontLayer::update(float dt)
{
	//if (!WDDD_GLOBAL.m_pNetSocketConnection)
	//	return;

	//处理网络收发
	//  WBSendProtocolListener();
	//WDDD_GLOBAL.m_pNetSocketConnection->receiveListener();

	m_dt = dt; //保存时间方便读取
	/*
	if (m_myHeroCircle)
	{
		//每一个动画锚点都不一样,所以需要更新
		CCPoint pos = WDDD_GLOBAL.m_lpBattleGlobal->m_bossMyHero->getAnchorPointInPixels();
		pos.y += 30;
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

void BossGameFrontLayer::onSelfLost(void *data, int msg, int param1, int param2)
{
	//    BossGameFrontLayer *pG=(BossGameFrontLayer *)data;
	//    pG->m_isGameOver=false;
#if OPEN_FIFTH
	cwSngDirector::sharedDirector()->replaceScene(Scene_SelectBossmap::scene(WDDD_GLOBAL.SCENETAG_HALL));//(WDDD_GLOBAL.SCENETAG_HALL);
#else
	//cwSngDirector::sharedDirector()->replaceScene(Scene_BossmapIsland::scene(WDDD_GLOBAL.SCENETAG_HALL));
#endif
}

void BossGameFrontLayer::updateHud()
{
	//getBattleScene()->getHudLayer()->updateHud();
}

void BossGameFrontLayer::startNewRound()
{
	bool isNewRound = false;
	//更新风力
	setWindLevel();

	
	// Added By Mrj, For Boss3, End
}

int BossGameFrontLayer::getMeleeGuaiCount()
{
	int count = 0;



	return count;
}

int BossGameFrontLayer::getRangedGuaiCount()
{
	int count = 0;




	return count;
}

int BossGameFrontLayer::getGuaiCount()
{
	int count = 0;




	return count;
}



// Added By Mrj, For Boss3, Start
#if OPEN_BOSSMAP_3
void BossGameFrontLayer::castBoss3Skill(vector<WBossHero*>& rTargets) {
	int iRandnumCount = WDDD_GLOBAL.m_lpBattleGlobal->getBattleRandNum().size();
	if(iRandnumCount > 0) {
		WChara *lpChara=GetCurrentChara();
		if(lpChara) {
			if(lpChara->getBossId() == DEF_BOSS_BOSS3_1) {
				// 32%PowerUp
				int randnum = WDDD_GLOBAL.m_lpBattleGlobal->getBattleRandNum()[iRandnumCount - 1];
				int ps = randnum % 100;

				bool isCastPowerUp = (ps >= 33 && ps <= 33 + 25) ? true : false;
				if(isCastPowerUp && !m_castPowerUp) {
					//castBoss31Skill_PowerUp(true);
					//showBoss3Shield(true);
					Boss3GettingAnim();
				}
			} else if(lpChara->getBossId() == DEF_BOSS_BOSS3_2) {
				// 35%Change Player Position
				int randnum = WDDD_GLOBAL.m_lpBattleGlobal->getBattleRandNum()[iRandnumCount - 1];
				int ps = randnum % 100;

				bool isChangePos = (ps >= 23 && ps <= 23 + 60) ? true : false;
				if(isChangePos) {
					castBoss32Skill_ChangePos(rTargets);
				}
			}
		}
	}
}
void BossGameFrontLayer::castBoss31Skill_PowerUp(bool isShow) {
	if(!m_boss3PowerBall) {
		map<string,string> desc;
		m_boss3PowerBall = cwSngSprite::node();
		if(!m_boss3PowerBall) return;

		addChild(m_boss3PowerBall);
		m_boss3PowerBall->setPosition(CCPointMake(getAnchorPoint().x*getContentSize().width, getAnchorPoint().y*getContentSize().height * 1.5f));
		WAnimationManager::addAnimationToCharater(WANI_IWCO_MONSTEREFFICIENTS, "boss3Efficient2",m_boss3PowerBall, 0, desc,0.1);
	}
	if(!m_boss3_1ball) {
		map<string,string> desc;
		m_boss3_1ball = cwSngSprite::node();
		if(!m_boss3_1ball) return;

		addChild(m_boss3_1ball);
		WAnimationManager::addAnimationToCharater(WANI_IWCO_MONSTEREFFICIENTS, "boss3Efficient6",m_boss3_1ball, 0, desc,0.1);
	}
	if(!m_boss3_2ball) {
		map<string,string> desc;
		m_boss3_2ball = cwSngSprite::node();
		if(!m_boss3_2ball) return;

		addChild(m_boss3_2ball);
		WAnimationManager::addAnimationToCharater(WANI_IWCO_MONSTEREFFICIENTS, "boss3Efficient6",m_boss3_2ball, 0, desc,0.1);
	}

	// 聚气
	for(int i=0; i<m_guais->count(); i++) {
		WChara* lpChara=(WChara *)m_guais->objectAtIndex(i);
		if(!lpChara) continue;

		if(lpChara->getBossId()==DEF_BOSS_BOSS3_1) {
			WBoss3_1* pRet = (WBoss3_1*)lpChara;
			if(pRet) pRet->SendMsgGettingPower(false);
		} else if(lpChara->getBossId()==DEF_BOSS_BOSS3_2) {
			WBoss3_2* pRet = (WBoss3_2*)lpChara;
			if(pRet) pRet->SendMsgGettingPower(false);
		}
	}

	// 显示动画
	if(m_boss3PowerBall) {
		if(isShow) {
			m_roundOfCastPowerUp = m_RoundNum;
			m_castPowerUp = true;
			m_boss3PowerBall->setAnimation(0);
			m_boss3PowerBall->playRepeat();
		} else {
			m_castPowerUp = false;
			m_boss3PowerBall->stopPlay();
		}
		m_boss3PowerBall->setIsVisible(isShow);
	}
	if(m_boss3_1ball){
		if(isShow) {
			m_boss3_1ball->setAnimation(0);
			m_boss3_1ball->playRepeat();

			CCPoint posStart = m_boss3PowerBall->getPositionInPixels();
			m_boss3_1ball->setPositionInPixels(posStart);

			WBoss3_1* pBoss31 = getBoss31();
			if(pBoss31) {
				CCPoint posEnd = CCPoint(pBoss31->getPositionInPixels().x / CC_CONTENT_SCALE_FACTOR(), (pBoss31->getPositionInPixels().y + pBoss31->getContentSizeInPixels().height * 0.8f) / CC_CONTENT_SCALE_FACTOR());
				CCMoveTo* pMoveTo = CCMoveTo::actionWithDuration(3.0f, posEnd);
				CCCallFunc* fnCallBack = CCCallFunc::actionWithTarget(this, callfunc_selector(BossGameFrontLayer::getPowerAnimCallBack));

				m_boss3_1ball->runAction(CCSequence::actions(pMoveTo, fnCallBack, NULL));
			}
		} else {
			m_boss3_1ball->stopPlay();
		}
		m_boss3_1ball->setIsVisible(isShow);
	}
	if(m_boss3_2ball){
		if(isShow) {
			m_boss3_2ball->setAnimation(0);
			m_boss3_2ball->playRepeat();

			CCPoint posStart = m_boss3PowerBall->getPositionInPixels();
			m_boss3_2ball->setPositionInPixels(posStart);

			WBoss3_2* pBoss32 = getBoss32();
			if(pBoss32) {
				CCPoint posEnd = CCPoint(pBoss32->getPositionInPixels().x / CC_CONTENT_SCALE_FACTOR(), (pBoss32->getPositionInPixels().y + pBoss32->getContentSizeInPixels().height * 0.8f) / CC_CONTENT_SCALE_FACTOR());
				CCMoveTo* pMoveTo = CCMoveTo::actionWithDuration(3.0f, posEnd);
				m_boss3_2ball->runAction(pMoveTo);
			}
		} else {
			m_boss3_2ball->stopPlay();
		}
		m_boss3_2ball->setIsVisible(isShow);
	}
}

void BossGameFrontLayer::Boss3GettingAnim() {
	EndCurrentMsg();
	SendEventToQueue(new WBEvent(EVENT_SCR_BOSS3_ZOOM_OUT,0));
	if(m_BattleScene) {
		m_BattleScene->getColorLayerBoss3()->setIsVisible(true);
	}
}

void BossGameFrontLayer::showBoss3Shield(bool isShow) {
	// 显示护盾
	if(!m_boss3Shied) {
		m_boss3Shied = BuildBoss3Shield();
		WDDD_GLOBAL.m_lpBattleGlobal->m_bossGuais->addObject(m_boss3Shied);
		addChild(m_boss3Shied);
		m_boss3Shied->start();
		m_boss3Shied->setCtrlType(DEF_WB_CTRL_OTHER);
		m_boss3Shied->setGameFrontLayer(this);
	}

	if(m_boss3Shied) {
		m_boss3Shied->setIsVisible(isShow);
		m_boss3Shied->setIsDead(!isShow);
		if(isShow) {
			m_boss3Shied->setHP(m_boss3Shied->getMaxHP());

			int iRandnumCount = WDDD_GLOBAL.m_lpBattleGlobal->getBattleRandNum().size();
			int randnum = WDDD_GLOBAL.m_lpBattleGlobal->getBattleRandNum()[m_RoundNum % iRandnumCount];
			int iCenterX = getContentSizeInPixels().width * 0.5f;
			int iCenterY = getContentSizeInPixels().height * 0.5f;
			int iPosX = iCenterX + (randnum - iCenterX) % (int)(iCenterX * 0.5f);
			int iPosY = iCenterY + randnum % (int)(iCenterY * 0.8f);
			m_boss3Shied->setPositionInPixels(CCPoint(iPosX, iPosY));
		} else {

		}
	}
}
void BossGameFrontLayer::castBoss32Skill_ChangePos(vector<WBossHero*>& rTargets) {
	for(int i = 0; i < rTargets.size(); i++) {
		WBossHero* pHero = (WBossHero*)rTargets[i];
		if(!pHero) continue;

		int iRandnumCount = WDDD_GLOBAL.m_lpBattleGlobal->getBattleRandNum().size();
		int randnum = WDDD_GLOBAL.m_lpBattleGlobal->getBattleRandNum()[i % iRandnumCount];

		pHero->SendMsgChangePos(getRandPosition(randnum));
	}
}

WBoss3_1* BossGameFrontLayer::getBoss31() {
	WBoss3_1* pRet = NULL;
	WChara *lpChara=NULL;

	for(int i=0; i<m_guais->count(); i++) {
		lpChara=(WChara *)m_guais->objectAtIndex(i);

		if(lpChara->getBossId()==DEF_BOSS_BOSS3_1 &&
			lpChara->getPlayerId() != -1) {
			pRet = (WBoss3_1*)lpChara;
			break;
		}
	}

	return pRet;
}
WBoss3_2* BossGameFrontLayer::getBoss32() {
	WBoss3_2* pRet = NULL;
	WChara *lpChara=NULL;

	for(int i=0; i<m_guais->count(); i++) {
		lpChara=(WChara *)m_guais->objectAtIndex(i);

		if(lpChara->getBossId()==DEF_BOSS_BOSS3_2 &&
			lpChara->getPlayerId() != -1) {
			pRet = (WBoss3_2*)lpChara;
			break;
		}
	}

	return pRet;
}

WBoss3_Shield* BossGameFrontLayer::BuildBoss3Shield() {
	WBoss3_Shield *lpNewGuai = WBoss3_Shield::BuildGuai();

	if(lpNewGuai) {
		lpNewGuai->setCharaType(DEF_WB_GUAI);
		lpNewGuai->setPlayerId(0);
		lpNewGuai->setBossId(DEF_BOSS_BOSS3_SHIELD);
		lpNewGuai->setGuaiIdInDB(-1);
		lpNewGuai->setMoverPosition(Vec2(getAnchorPoint().x*getContentSize().width, getAnchorPoint().y*getContentSize().height));
		lpNewGuai->setPositionInPixels(CCPointMake(lpNewGuai->getMoverPosition().x, lpNewGuai->getMoverPosition().y));

		lpNewGuai->setPlayerName("护盾");
		lpNewGuai->setCamp(1);
		lpNewGuai->setBoyOrGirl(0);
		lpNewGuai->setWeaponType(0);
		lpNewGuai->setGuaiType(0);
		lpNewGuai->setLevel(0);
		lpNewGuai->setGuaiAttackType(0);
		lpNewGuai->setMaxHP(1);
		lpNewGuai->setMaxSP(0);
		lpNewGuai->setMaxPF(0);
		lpNewGuai->setHP(1);
		lpNewGuai->setSP(0);
		lpNewGuai->setPF(0);
		lpNewGuai->setDefence(0);
		lpNewGuai->setAttack(0);
		lpNewGuai->setExplodeRadius(0);
		lpNewGuai->setCriticalhitAttackRate(0);
		lpNewGuai->setBigSkillType(0);
		lpNewGuai->setIsCouldBuildGuai(false);
		//lpNewGuai->setCouldBuildGuaiList(lpGuai->getCouldBuildGuaiList());

	}
	return lpNewGuai;
}

void BossGameFrontLayer::SendMsgPlayerGetShield() {
	WBEvent *lpEvent=new WBEvent(EVENT_SCR_PLAYER_GET_SHIELD,0);
	if(!lpEvent) return;

	lpEvent->setData(NULL);
	SendEventToQueue(lpEvent);
}
void BossGameFrontLayer::SendMsgPlayerLossShield() {
	WBEvent *lpEvent=new WBEvent(EVENT_SCR_PLAYER_LOSS_SHIELD,0);
	if(!lpEvent) return;

	lpEvent->setData(NULL);
	SendEventToQueue(lpEvent);
}

void BossGameFrontLayer::Boss3GetPowerEnd() {
	m_iBoss3EndGetPowerCount++;
	if(m_iBoss3EndGetPowerCount >= 2) {
		EndCurrentMsg();
		//SendEventToQueue(new WBEvent(EVENT_SCR_NORMAL,0));
		//SendEventToQueue(new WBEvent(EVENT_WAITNEXTROUND,0));
		//isShootingNow = true;
		SendEventToQueue(new WBEvent(EVENT_SCR_ZOOM_TO_BOSS,0));
		//m_screan_status=E_SCR_FOLLOW_BULLET;
		m_iBoss3EndGetPowerCount = 0;
	}
}

void BossGameFrontLayer::getPowerAnimCallBack() {
	if(m_boss3_1ball) {
		m_boss3_1ball->stopPlay();
		m_boss3_1ball->setIsVisible(false);
	}
	if(m_boss3_2ball) {
		m_boss3_2ball->stopPlay();
		m_boss3_2ball->setIsVisible(false);
	}

	// 聚气
	for(int i=0; i<m_guais->count(); i++) {
		WChara* lpChara=(WChara *)m_guais->objectAtIndex(i);
		if(!lpChara) continue;

		if(lpChara->getBossId()==DEF_BOSS_BOSS3_1) {
			WBoss3_1* pRet = (WBoss3_1*)lpChara;
			if(pRet) pRet->SendMsgGettingPower(true);
		} else if(lpChara->getBossId()==DEF_BOSS_BOSS3_2) {
			WBoss3_2* pRet = (WBoss3_2*)lpChara;
			if(pRet) pRet->SendMsgGettingPower(true);
		}
	}
}

Vec2 BossGameFrontLayer::getRandPosition(int randNum)
{
	Vec2 pos;
	Vec2 pos2;
	bool flag=false;

	WMover player;
	bool inSide;
	player.setMoverCollisionType(WMover::E_COLLISION_POINT);
	player.setMoverRadius(50);

	do
	{
		int iCenterX = getContentSizeInPixels().width * 0.5f;
		int posX = iCenterX + (randNum - iCenterX) % (int)(iCenterX / 2);
		pos=Vec2(posX/*randNum%1300+250*/,getContentSizeInPixels().height-200);

		player.setMoverPosition(pos);
		player.setMoverPrePosition(pos);


#if (NOT_USE_STENCIL_SPRITE == 1)
		flag=getPixelByte()->CheckCollision(&player,NULL,NULL,inSide);
#else
		flag=getStencilSprite()->CheckCollision(&player,NULL,NULL,inSide);
#endif
		if(flag)
		{
			flag=false;
			continue;
		}

		for(int i=pos.y; i>0; i--)
		{
			pos2=pos;
			pos2.y=i;
			player.setMoverPosition(pos2);
			player.setMoverPrePosition(pos2);

#if (NOT_USE_STENCIL_SPRITE == 1)
			flag=getPixelByte()->CheckCollision(&player,NULL,NULL,inSide);
#else
			flag=getStencilSprite()->CheckCollision(&player,NULL,NULL,inSide);
#endif

			if(flag)
			{
				break;
			}
		}

		if(flag)
		{
			break;
		}



	}while (flag==false);

	return pos;
}


#endif
// Added By Mrj, For Boss3, End





