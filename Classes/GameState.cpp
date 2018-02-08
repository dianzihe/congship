#include "GameState.h"
#include "ActorManager.h"
#include "GameScene.h"
#include "Hero.h"
#include "base.h"
#include "ui.h"

/*
#include "GameMainUI.h"
#include "MissionUI.h"
#include "NPCMissionUI.h"
#include "package.h"
#include "Player.h"
#include "ShenMiTianLaoUI.h"
#include "Map.h"
#include "effect.h"
#include "ItemBag.h"
#include "EquipmentMainUI.h"
#include "UIEditNew.h"
#include "Shop.h"
#include "CCEGLView.h"
#include "package.h"
#include "SMCharacter.h"
#include "../gameui/TianTiSai/ChampionRankUI.h"
#include "../gameui/TianTiSai/PlayerRankUI.h"
#include "../gameui/TianTiSai/ChampionRankGift.h"
#include "MasterTilTleTip.h"
#include "MessageBoxUI.h"
#include "Text.h"
#include "Exppool.h"
#include "TextDef.h"
#include "ConvoyUI.h"
#include "NpcStore.h"
#include "WorldMap.h"
#include "../BaseModule/Scenario/ScenarioModule.h"
#include "../BaseModule/Navigation/NavigationModule.h"
#include "../BaseModule/Combat/CombatModule.h"
#include "../BaseModule/ImageCenter/ImageCenter.h"
#include "../BaseModule/Loading/LoadingModule.h"
#include "../BaseModule/Guide/GuideModule.h"
#include "../BaseModule/Combat/SkillFilterModule.h"
#include "SceneInstance.h"
#include "IconRemindPage.h"
#include "UpdateMessage.h"
#include "ConSalesBank.h"
#include "MainUIMove.h"
#include "Chat.h"
#include "Task.h"
#include "MissionUI.h"
#include "SkillTips.h"
#include "MessageTips.h"
#include "UpdateMessage.h"
#include "../BaseModule/OpenNewFunction/OpenFunctionUi.h"

#include "MainUIOpenCloseHandle.h"
#include "HeroMount.h"
//#include "../gameui/MountUI.h"
#include "SystemSetUI.h"
#include "FriendUI.h"
#include "GuildUI.h"
#include "Mail.h"
#include "ItemCD.h"
#include "ShortPage.h"
#include "LoginBack.h"
#include "WaitingUI.h"
#include "NumberInputBox.h"
#include "Guild.h"
#include "ItemMgr.h"

#include "ItemTipsUI.h"
#include "BuffListUI.h"

#include "SystemMessage.h"
#include "PlayerTrade.h"
//#include "EquipmentTips.h"
#include "ItemGetUI.h"
#include "RankList.h"
#include "Teamlogic.h"
#include "CTeamUI.h"
#include "ServerNotice.h"
#include "WelfareUI.h"
#include "TargetHeadMenu.h"
#include "RechargeEditUI.h"
#include "CCMemoryMonitor.h"
#include "Variant.h"
#include "RechargeUI_IOS.h"
#include "TokenStore.h"
#include "CopyProgressUI.h"
#include "CopyMapSA.h"
#include "DailyUI.h"
#include "CheckPlayerUI.h"
#include "BazzarItem.h"
#include "Routing.h"
#include "BattleUI.h"
#include "QuestionAndAnswerUI.h"
#include "DirectionHandleUI.h"
#include "Faction.h"
#include "SystemSetUI.h"
#include "LevelGiftUI.h"
#include "OnlineSurveyUI.h"
#include "OnlineLotteryUI.h"
#include "BoundPhone.h"
#include "PrayUI.h"
#include "ZhuXianTaUI.h"
#include "msg_player.h"
#include "../MagicSystem/MagicSystemUI.h"
#include "../common/AppUpdater/UpdateFlow.h"
#include "FriendTeamAdditionUI.h"
#include "NpcItemStore.h"
#include "PlayingCardUI.h"
#include "GiftShortUI.h"
#include "shouHuUI.h"
#include "MFLevelPrompt.h"
#include "SpecialSkillUI.h"
#include "GrowUpUI.h"
#include "FlowersUI.h"
#include "RechargeUI_Android_TW.h"
#include "../update/updateGlobal.h"
#include "GaoShouRankListUI.h"
#include "GaoShouDuiZhanUI.h"
#include "BeaconMainUI.h"
#include "AcupointUI.h"
#include "MFLoginQueue.h"
#include "PlayerSkillPanel.h"
#include "MFShareWeiboUI.h"
#include "PlayerEquipAtrUI.h"
#include "XSMUI.h"
#include "JzfbUI.h"
#include "HorseGrowUI.h"
#include "TaskTeamTabUI.h"
#include "EquipmentTipsXSM.h"
#include "EquipmentPopup.h"
#include "UICombo.h"
#include  "Champion.h"
#include "ChanllengePanelUi.h"
#include "SitDown.h"
#include "EquipQualityUpUIXSM.h"
#include "EquipChangeUIXSM.h"
#include "XSMGiftBag.h"
#include "VIPXSMUI.h"
#include "EquipStrengthUIXSM.h"
#include "EquipQualityUpUIXSM.h"
#include "GameHangUp.h"
#include "TargetList.h"
#include "Target.h"
#include "ChampionSituation.h"
#include "PlayerListUI.h"
#include "ItemGetWayUI.h"
#include "FieldBossUi.h"
#include "KnightIsland.h"
#include "ShenMiTianLaoGaoShouZhuZhen.h"
#include "StrengthGrowUp.h"
#include "ChampionUI.h"
#include "ResolveEquipment.h"
#include "MutipMine.h"
#include "Bath.h"
#include "SevenDaysGift.h"
#include "OnlineAwardUI.h"
#include "../gameui/VitalityConvert.h"
#include "shituUI.h"
#include "shituCfg.h"
//#include "BattlePointUI.h"
*/
static const char* names[] = { "wp11", "wpd2", "test" };

/*
using namespace UpdateTool;
void MessageBoxFunKickOut( enMSG iBoxRet, void *Object, void* data )
{
	GameScene::GetScene()->ChangeState(GAME_STATE_LOGIN);
}


void pk::OnPlayerKickOuted( PlayerKickOuted* value )
{
	g_Net.closeSocket();
	switch( value->reserve )
	{
	case KickoutUser_Reson_ReLogin:
		MessageBoxUI::UIMessageBox( CText::GetText(CTextDef::MSGBOX_TITLE_TISHI), CText::GetText(CTextDef::LOGIN_LS_RESULT_FAIL_KICKOUT) ,MSGBOX_YES, MessageBoxFunKickOut, NULL, NULL );
		break;

	case KickoutUser_Reson_GM:
		MessageBoxUI::UIMessageBox( CText::GetText(CTextDef::MSGBOX_TITLE_TISHI), CText::GetText(CTextDef::LOGIN_LS_RESULT_FAIL_KICKOUT_GM) ,MSGBOX_YES, MessageBoxFunKickOut, NULL, NULL );
		break;

	case KickoutUser_Reson_HeartBeat_Timeout:
		MessageBoxUI::UIMessageBox( CText::GetText(CTextDef::MSGBOX_TITLE_TISHI), CText::GetText(CTextDef::LOGIN_LS_RESULT_FAIL_KICKOUT_HEART) ,MSGBOX_YES, MessageBoxFunKickOut, NULL, NULL );
		break;
	}

	CGameState* pGameState = dynamic_cast<CGameState*>(GameScene::GetScene()->GetState());
	if(pGameState )
	{
		pGameState->mBeKickOutedTime = (long)CCTime::getMSecond();
	}
	MFLoginQueue::shareInstance()->show(false);
}

void pk::OnGS2U_SelPlayerResult(GS2U_SelPlayerResult* value)
{
	CWaitingUI::instance().Close();
	switch(value->result)
	{
	case SelPlayerResult_Succ:
		{
			//进入游戏 释放登陆背景
			LoginBack::instance().unInit();

			GameScene::GetScene()->ChangeState( GAME_STATE_LOADING );
			CRunState* state = GameScene::GetScene()->GetState();
			CLoadingState* loadState = dynamic_cast< CLoadingState* >( state );
			if ( loadState ) {
				// load from login menu
				CLoadingState::setLoadType( 0 );
				g_Net.skipOneFrame();
				g_Net.waitUntilReceived( MSG_ChangeMap );
			}
			//LoadingModule::instance().EnterLoading();
			//LoadingModule::instance().UpdateLoading();
			return;
		}
	case SelPlayer_Result_PlayerCount_Fail:
		MessageBoxUI::UIMessageBox( CText::GetText(CTextDef::MSGBOX_TITLE_TISHI), CText::GetText(CTextDef::LOGIN_LS_RESULT_FAIL_USERNAMEORPASSWORD) ,MSGBOX_YES );
		break;
	case SelPlayer_Result_UserId_Fail:
		MessageBoxUI::UIMessageBox( CText::GetText(CTextDef::MSGBOX_TITLE_TISHI), CText::GetText(CTextDef::LOGIN_LS_RESULT_FAIL_USERNAMEORPASSWORD) ,MSGBOX_YES );
		break;
	case SelPlayer_Result_Player_IsOnline:
		MessageBoxUI::UIMessageBox( CText::GetText(CTextDef::MSGBOX_TITLE_TISHI), CText::GetText(CTextDef::LOGIN_LS_RESULT_FAIL_USERNAMEORPASSWORD) ,MSGBOX_YES );
		break;
	default:
		break;

	}
	//net.closeSocket();
	//net.connect( g_ClientSetup.getLoginIP().c_str(), g_ClientSetup.getLoginPort() );
	GameScene::GetScene()->ChangeState(GAME_STATE_LOGIN);
}

void pk::OnGS2U_HeartBeatAck(GS2U_HeartBeatAck* value)
{
	if (!value)
		return;
	CGameState *pGame = dynamic_cast<CGameState*>(GameScene::GetScene()->GetState());
	if (pGame)
	{
		pGame->getNetInfo();
	}
}
*/
void CGameState::getNetInfo()
{
	/*
	long long timeRec = CCTime::getMSecond();
	mNetworkstate.dealyTime[mNetworkstate.times] = (int)((timeRec - mNetworkstate.lastSendTime)/2);
	mNetworkstate.times +=1;

	if (mNetworkstate.times == TIME_GET_COUNT || mIsEnterGameFirTime)
	{
		if (mIsEnterGameFirTime)
		{
			mNetworkstate.aveTime = mNetworkstate.dealyTime[TIME_GET_FIR];
		}
		else
		{
			mNetworkstate.aveTime = (mNetworkstate.dealyTime[TIME_GET_FIR] +mNetworkstate.dealyTime[TIME_GET_SEC] + mNetworkstate.dealyTime[TIME_GET_THR])/3;
		}
		mIsEnterGameFirTime = false;
		
		showNetStateBtn(mNetworkstate.aveTime);
		
		mNetworkstate.lastSendTime = 0;
		mNetworkstate.times = TIME_GET_FIR;
		memset(mNetworkstate.dealyTime, 0, sizeof(mNetworkstate.dealyTime));
		mNetworkstate.aveTime = 0;
	}
	*/
}
void CGameState::showNetStateBtn(int dealyTime)
{
	/*
	if (!CGameMainUI::instance()->pNetStateFast 
	||  !CGameMainUI::instance()->pNetStateNormal 
	||  !CGameMainUI::instance()->pNetStateSlow)
		return;

	if (dealyTime >= 0 && dealyTime<=100)
	{
		CGameMainUI::instance()->pNetStateFast->setVisible(true);
		CGameMainUI::instance()->pNetStateNormal->setVisible(false);
		CGameMainUI::instance()->pNetStateSlow->setVisible(false);
	}
	else if (dealyTime > 100 && dealyTime < 300)
	{
		CGameMainUI::instance()->pNetStateFast->setVisible(false);
		CGameMainUI::instance()->pNetStateNormal->setVisible(true);
		CGameMainUI::instance()->pNetStateSlow->setVisible(false);
	}
	else if (dealyTime >= 300)
	{
		CGameMainUI::instance()->pNetStateFast->setVisible(false);
		CGameMainUI::instance()->pNetStateNormal->setVisible(false);
		CGameMainUI::instance()->pNetStateSlow->setVisible(true);
	}
	*/
}
//////////////////////////////////////////////////////////////////////////
CGameState::CGameState() 
: mLoadingFrame( 1 )
//, mLoadingUI( NULL )
,mBeKickOutedTime(0)
,mIsEnterGameFirTime(true)
, mIsFirstTimeLoading(true)
{
	mNetworkstate.lastSendTime = 0;
	mNetworkstate.times = 0;
	mNetworkstate.aveTime = 0;
	memset(mNetworkstate.dealyTime, 0, sizeof(mNetworkstate.dealyTime));
}

CGameState::~CGameState()
{
	mBeKickOutedTime = 0;
	OnDestroy();
}
void	ClientToGSOnHeart();

#define		GAME_HEART_TIME	10

static void __ClientToGSOnHeart()
{
	if( !GameScene::GetScene() ) return;
	static unsigned long timeCounter = 0;
	/*
	cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now,NULL);
	if( now.tv_sec-timeCounter >= GAME_HEART_TIME )
	{
		CGameState *pGame =  dynamic_cast<CGameState*>(GameScene::GetScene()->GetState());
		if (pGame) 
			pGame->mNetworkstate.lastSendTime = (int)CCTime::getMSecond();
		pk::U2GS_HeartBeat toServer;
		toServer.Send();
		timeCounter = 0;
		timeCounter = (unsigned long)now.tv_sec;
	}
	*/
}

void	ClientToGSOnHeart()
{
	/*
	if( GameScene::GetScene() && 
		(GameScene::GetScene()->m_eGameState == GAME_STATE_GAME || 
		GameScene::GetScene()->m_eGameState == GAME_STATE_CHARLOBBY || 
		GameScene::GetScene()->m_eGameState == GAME_STATE_CREATEPLAYER || 
		GameScene::GetScene()->m_eGameState == GAME_STATE_LOADING) )
		__ClientToGSOnHeart();
	*/
}

void CGameState::OnDestroy()
{
	/*
	INFO_LOG( "CGameState::OnDestroy begin" );

	if ( isLoading() ) {
		endLoading();
	}

	shituCfg::Instance()->unInit();
	CshituUI::instance().Unload();
	CMutipMine::getInstance().uninit();
	CExppool::Instance().UnInit();
	Variant::instance().Uninitialize();
	LoadingModule::instance().UnInitialize();
	GameScene::GetScene()->GetHeroNavigation()->CancelNavigation();
	//CPlayerEquipment::instance().Uninitialize();
	ItemMgr::instance().Uninitialize();
	SmallBag::instance().release();
	NpcStore::instance().release();
	TokenStore::instance().release();
	ItemBag::instance().release();
	CNpcItemStore::instance().release();
	GameScene::GetActorManager()->onGameStateLeave();
	GameScene::GetScene()->GetCurMap()->unInitialize();
	ChanllengePanelUi::instance().unLoad();
    CNPCMissionUI::Instance()->UnLoad();
	ScenarioModule::instance().UnInitialize();
	CGameMainUI::instance()->UnLoad();
	CChampionRankUI::Instance().UnInit();
	CIconRemindPage::instance().unInit();
	CChampionRankGift::Instance().UnInit();
	CPlayerRankUI::Instance().UnInit();
	RankHistoryUI::Instance().UnInit();
	CChampionMainUI::Instance().UnInit();
	CConSalesBank::instance().unInit();
	CChat::instance().unInit();
	CTaskMgr::Instance()->unLoad();
	XSMUI::instance().unInit();
	CMissionUI::Instance()->unInit();
	CShenMiTianLaoGaoShouZhuZhen::instance().UnInit();
	SkillTips::unInit();
	UICombo::getInstance()->Uninit();
	MessageTips::instance().unInit();
	//CPlayerInfoUI::instance()->unInit();
	CSMCharacter::instance().UnInit();
	CSMCharacterFB::instance().UnInit();
	CPlayerEquipAtrUI::instance()->unInit();
	GameScene::GetHeroNavigation()->UnInitialize();
	SceneInstance::instance().UnInitialize();
	//CHangUpUI::instance()->UnInitialize();
	CBazzarItem::instance().unInit();
	PlayerSkillPanel::GetInstance().UnInit();
	CGameHangUp::GetInstance().UnInit();
	GuideModule::instance().UnInitialize();
	//CMountUI::instance().unInit();
	CHeroMount::instance().unInit();
	CSystemSetUI::instance().Uninitialize();
	CFriendUI::instance()->Uninitialize();
	CGuildUI::instance()->Uninitialize();
	CMAILMgr::Instance()->Uninitialize();
	SkillFilterModule::instance().Uninitialize();
	CItemCD::instance().unInit();
	CShortPage::instance().unInit();
	CShenMiTianLaoUI::instance().UnInit();
	CHeroPet::instance().unInit();
	CWaitingUI::instance().unInit();
	CNumberInputBox::instance().Uninitialize();
	Guild::instance().Uninitialize();
	ItemTipsUI::instance().unInit();
	BuffListUI::instance().unInit();
	CombatModule::instance().CleanAllCombatData();
	CWorldMiniMap::instance().Uninitialize();
	CSystemMessageUI::instance().unInit();
	CPlayerTrade::instance().unInit();
	EquipmentMainUI::instance().UnInit();
	CFriend::Instance()->unInit();
	CItemGetUI::instance().unInit();
	TeamUI::Instance()->unInit();
	CWelfareUI::instance().unInit();
	CCMemoryMonitor::sharedMemoryMonitor()->cleanMemoryWarning();
	CQuestionAndAnswerUI::instance()->uninit();
	ConvoyUI::Instance()->unInitUI();

	CTopUi::instance().uninit();
	CTeam_logicCfg::Instance()->Uninitialize();

	CTargetHeadMenu::instance().unInit();
	CRechargeEditUI::instance().unInit();
	CCheckPlayerUI::instance().unInit();

	EquipmentBagForRefine::instance().UnInit();
	EquipmentBagForQualityUp::instance().UnInit();
	CXSMGiftBag::instance().UnInit();

	CWipeoutUI::instance().unInit();

    OnlineSurveyUI::instance()->uninit();
	CMagicSystemUI::instance().unInit();
	OnlineLotteryUI::shareInstance()->unInit();
	CFriendTeamAdditionUI::instance().unInit();
	CSpecialSkillUI::instance().unInit();
	CGaoShouTopUi::instance().uninit();
	CGaoShouDuiZhanBiaoUI::instance().unInit();
	CBeaconMainUI::instance().uninit();
	CJzfbUI::instance().unInit();
	CHorseGrowUI::instance().unInit();
	MFShareWeiboUI::shareInstance()->unInit();
	CChampionSituation::Instance().unInit();
	CPlayerListUI::Instace().unInit();
	CItemGetWayPanel::Instace().uninit();
	CShop::instance().UnInit();
	StrengthGrowUp::Instance().UnInit();
	CResolveEquipment::Instance().Uninit();
	CSevenDaysGift::instance().uninit();
	COnlineAwardUI::instance().uninit();
	CVitalityConvert::instance().unninit();
	//CBattlePointUI::instance().uninit();
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	CRechargeUI_IOS::instance().uninit();
#endif

 #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (updateGlobal::getInstance()->m_platformID == Platform_TW_ANDROID)
	{
		CRechargeUI_Android_TW::instance().uninit();
	}
#endif

	CCopyProgressUI::instance().unInit();
	CCopyMapSAUI::instance().unInit();

	CDailyUI::instance().uninit();

	VIPXSMUI::Instance().unInit();

	CBattleUI::instance().unInit();

	CDirectHandleUI::instance().unInit();
	CTaskTeamTabUI::instance().unInit();
	CChampionMainUI::Instance().UnInit();
	ChampionUI::Instance().unInit();
	CLevelGiftUI::instance().unInit();
	CBoundPhone::instance().unInit();
	CPrayUI::instance().uninit();
	CZhuXianTaUI::instance().unInit();
	CPlayingCardUI::instance().unInit();
	CGiftShortUI::instance().unInit();
	CMasterTilTleTip::instance().UnInit();
	FieldBossUi::instance().unLoad();
	shouHuUI *pShouHuUI = shouHuUI::Instance();
	if (NULL != pShouHuUI)
	{
		pShouHuUI->unInit();
	}
	CGrowUpUI::instance().unInit();
	CFlowersUI::instance().unInit();
	CAcupointUI::instance().unInit();

	MFLevelPrompt::shareInstance()->uninit();
	MFLoginQueue::shareInstance()->unInit();
	CSitDown::instance().unInit();
	OpenFunctionUi::instance().unLoad();
	Target::instance().unInit();
	CMainUIOpenCloseHandle::instance().UnInit();
	CBath::instance().unInit();
	//net.closeSocket();
	//net.connect( g_ClientSetup.getLoginIP().c_str(), g_ClientSetup.getLoginPort() );

	INFO_LOG( "CGameState::OnDestroy end" );
    
	UIManager::Instance()->clear();
	GameScene::GetUI()->removeAllChildrenWithCleanup(true);
	CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
	mIsFirstTimeLoading = true;
	*/
}

static void _LoadEnterGameState()
{
	/*
	GameScene::GetActorManager()->onGameStateEnter();
	Log::PrintAndroidErrorLog("GameScene::GetActorManager()->onGameStateEnter()");
	CGameMainUI::instance()->Load();
	Log::PrintAndroidErrorLog("CGameMainUI::instance()->Load()");
	ScenarioModule::instance().Initialize();
	Log::PrintAndroidErrorLog("ScenarioModule::instance().Initialize()");
	SceneInstance::instance().Initialize();
	Log::PrintAndroidErrorLog("SceneInstance::instance().Initialize()");
	GuideModule::instance().Initialize();
	Log::PrintAndroidErrorLog("GuideModule::instance().Initialize()");
	CShortPage::instance();
	CSystemSetUI::instance().load();
	UpdateMessage::instance().load();
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	CRechargeUI_IOS::instance().init();
#endif

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (updateGlobal::getInstance()->m_platformID == Platform_TW_ANDROID)
	{
		CRechargeUI_Android_TW::instance().init();
	}
#endif

	Log::PrintAndroidErrorLog("CGameMainUI::instance()->Load()");
	*/
}

void CGameState::EnterState()
{
	_LoadEnterGameState();

	/*
	CPlayingCardUI::instance().request_state();
	CShop::instance().ShowShopUI( false);
	//////////////////////////////////////////////////////////////////////////
	Variant::instance();
	SmallBag::instance();
	NpcStore::instance();
	TokenStore::instance();
	ItemBag::instance();
	CNpcItemStore::instance();
	CIconRemindPage::instance();
	CChampionMainUI::Instance();
	CChampionRankUI::Instance();
	CChampionRankGift::Instance();
	RankHistoryUI::Instance();
	CPlayerRankUI::Instance();
	CConSalesBank::instance();
	CChat::instance();
	XSMUI::instance();
	CBazzarItem::instance();
	CBoundPhone::instance();
	RankHistoryUI::Instance();
	CGameHangUp::GetInstance();
	CExppool::Instance();
	CFriendUI::instance();
	CGuildUI::instance()->show(false);
	ItemTipsUI::instance();
	BuffListUI::instance();
	CItemGetUI::instance();
	ConvoyUI::Instance();
	CTopUi::instance();
	CShenMiTianLaoUI::instance();
	CTargetHeadMenu::instance();
	CRechargeEditUI::instance();
	CSMCharacterFB::instance();

	TeamUI::Instance();
	CWipeoutUI::instance();

	OnlineSurveyUI::instance();
	CMagicSystemUI::instance();
	OnlineLotteryUI::shareInstance();
	CFriendTeamAdditionUI::instance();
	CSpecialSkillUI::instance();
	CGaoShouTopUi::instance();
	CGaoShouDuiZhanBiaoUI::instance();
	CBeaconMainUI::instance();
	CShenMiTianLaoGaoShouZhuZhen::instance();

	CJzfbUI::instance();
	CHorseGrowUI::instance();
	MFShareWeiboUI::shareInstance();
	CPlayerListUI::Instace();
	CItemGetWayPanel::Instace();

	CCopyProgressUI::instance();
	CCopyMapSAUI::instance();


	VIPXSMUI::Instance();

	CBattleUI::instance();

	CDirectHandleUI::instance();
	CTaskTeamTabUI::instance();

	CLevelGiftUI::instance();
	CPrayUI::instance();
	//CZhuXianTaUI::instance();
	//CGiftShortUI::instance();
	shouHuUI::Instance();
	CGrowUpUI::instance();
	CFlowersUI::instance();
	CSMCharacter::instance();
	CAcupointUI::instance();


	MFLevelPrompt::shareInstance();
	CMasterTilTleTip::instance();
	MFLoginQueue::shareInstance();
	*/
}

void CGameState::OnDraw()
{
	if ( mLoadingFrame > 0 ) {
		--mLoadingFrame;
		if ( mLoadingFrame == 0 ) {
			// mark: loading image just been presented
			mLoadingFrame = -1000;
		}
	}
}

void CGameState::decideIsToreloading()
{
	/*
	CGameState *mPgamestate = dynamic_cast<CGameState*>(GameScene::GetScene()->GetState());
	if (0 != mPgamestate->mBeKickOutedTime)
	{
		long long rebackLoadingTime = CCTime::getMSecond();
		if (rebackLoadingTime - mPgamestate->mBeKickOutedTime >= 500)
		{
			GameScene::GetScene()->ChangeState(GAME_STATE_LOGIN);
			mPgamestate->mBeKickOutedTime = 0;
		}
	}
	*/
}

void CGameState::OnUpdate(float dt)
{
	/*
	if ( mLoadingFrame != 0 ) {
		if ( mLoadingFrame == -1000 ) {
			// hold the loading image a little period
			if(mIsFirstTimeLoading)
			{
				if ( UpdateTool::AppUpdater::isEnabled() ) {
					UpdateTool::LocalResVersionInfo resVer = UpdateTool::AppUpdater::loadLocalResVersionInfo();
					int val = Variant::instance().getPlayerVariant(PlayerVariant_Index_Is_Update_Package);   
					if( val == 0
					   && UpdateMessage::instance().IsRequestUpdate() )
					{
						//pk::U2GS_StartUpdatePackage downloadResFinish;
						//downloadResFinish.Send();
						UpdateMessage::instance().UpdateRewardUse();
					}
				}
				else
				{
#if defined UPDATE_START
					int val = Variant::instance().getPlayerVariant(PlayerVariant_Index_Is_Update_Package);   
					if( val == 0
					   && UpdateMessage::instance().IsRequestUpdate()
					   && GameScene::GetScene()->m_cp->isFinishedUpdateFullResource() )
					{
						//pk::U2GS_StartUpdatePackage downloadResFinish;
						//downloadResFinish.Send();
						UpdateMessage::instance().UpdateRewardUse();
					}
#endif
				}
			}
			else
			{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
				Sleep(1000);
#else
				sleep(1);
#endif
			}
			endLoading();
			mLoadingFrame = 0;
			mIsFirstTimeLoading = false;
		}
		return;
	}

	PROFILE("CGameState::OnUpdate");

	CGameMainUI::instance()->update(dt);
	GameScene::GetScene()->GetCurMap()->update(dt);
	GameScene::GetActorManager()->update(dt);
	GameScene::GetScene()->GetHeroNavigation()->Update(dt);
	CombatModule::instance().Update(dt);
	ScenarioModule::instance().Update(dt);
	CNPCMissionUI::Instance()->update(dt);
	GuideModule::instance().Update(dt);
	OpenFunctionUi::instance().update(dt);
	CItemCD::instance().updateCD(dt);
	CDailyUI::instance().check_notify(dt);
	CChat::instance().onTrumpetUpdate(dt);
	CQuestionAndAnswerUI::instance()->update(dt);
	OnlineLotteryUI::shareInstance()->update(dt);
	//CPlayingCardUI::instance().update(dt);
	CCopyMapSAUI::instance().update(dt);
	CPrayUI::instance().update(dt);
	CChampionMainUI::Instance().OnUpdate(dt);
	CGameHangUp::GetInstance().update(dt);
	MFLevelPrompt::shareInstance()->update(dt);
	EquipmentPropup::instance().Update(dt);
	CPlayerEquipAtrUI::instance()->Update(dt);
	ShowKnigtIslandInfo::Instance().Update(dt);
	XSMUI::instance().UpdatePutOn(dt);
	CHorseGrowUI::instance().updatePutOn(dt);
	COnlineAwardUI::instance().update(dt);
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (updateGlobal::getInstance()->m_platformID == Platform_TW_ANDROID)
	{
		CRechargeUI_Android_TW::instance().update(dt);
	}
#endif

	ClientToGSOnHeart();
	*/

}


void CGameState::showInGameLoading()
{
	++mLoadingFrame;
	if ( mLoadingFrame == 1 ) {
		beginLoading();
	}
}

void CGameState::beginLoading()
{
	/*
	if ( !mLoadingUI ) {
		char imageName[ 256 ];
		int imageIdx = rand();
		imageIdx = imageIdx % 4 + 1;
		sprintf( imageName, "Origin/LoadImage%d.wen", imageIdx );
		if( !(ImageCenter::instance().LoadResource(imageName)) )
		{
			sprintf(imageName, "Origin/LoadImage%d.wen", 1);
			ImageCenter::instance().LoadResource(imageName);
		}
		mImageName = imageName;

		ImageCenter::instance().LoadResource("Origin/GameName.png");
		mLoadingUI = UIManager::Instance()->loadUI("LoadingUI.ui");
		if ( mLoadingUI ) {
			mLoadingUI->setVisible( true );
		}
		ImageCenter::instance().UnLocalLoadResource( "ImageCenter/Loading.bui" );
	}
	*/
}

void CGameState::endLoading()
{
	/*
	if ( mLoadingUI ) {
		mLoadingUI->setVisible( false );
		UIManager::Instance()->removeUI( "LoadingUI.ui" );
		mLoadingUI = NULL;

		ImageCenter::instance().UnLoadResource( mImageName.c_str() );
		ImageCenter::instance().UnLoadResource("Origin/GameName.png");
		mImageName.clear();
	}

	Map* pMap = GameScene::GetScene()->GetCurMap();
	if(pMap && pMap->isMapPackgeNeedUpdate())
    {
        if(!Variant::instance().getWorldVariantFlag(WorldVariant_Index_1, WorldVariant_Index_1_Active_Update_Resource ))
            UpdateMessage::instance().show(true);
    }
	*/
}



int CLoadingState::mType = -1;

CLoadingState::CLoadingState()
	//: mLoadingUI( NULL ),
//mFrameCount( 0 ), mExit( false )
{
}

CLoadingState::~CLoadingState()
{
	/*
	ImageCenter::instance().UnLoadResource( mImageName.c_str() );
	mImageName.clear();
	if ( mLoadingUI ) {
		mLoadingUI->setVisible( false );
		UIManager::Instance()->removeUI( "LoadingUI.ui" );
		mLoadingUI = NULL;
	}
	ImageCenter::instance().UnLoadResource("Origin/GameName.png");
	*/
}

void CLoadingState::EnterState()
{
	/*
	char imageName[ 256 ];
	int imageIdx = rand();
	imageIdx = imageIdx % 4 + 1;
	sprintf( imageName, "Origin/LoadImage%d.wen", imageIdx );
	if( !(ImageCenter::instance().LoadResource(imageName)) )
	{
		sprintf(imageName, "Origin/LoadImage%d.wen", 1);
		ImageCenter::instance().LoadResource(imageName);
	}
	mImageName = imageName;
		
	mLoadingUI = UIManager::Instance()->loadUI("LoadingUI.ui");
	if ( mLoadingUI ) {
		mLoadingUI->setVisible( true );
	}
	ImageCenter::instance().UnLocalLoadResource( "ImageCenter/Loading.bui" );
	*/
}

void CLoadingState::OnUpdate( float dt )
{
	ClientToGSOnHeart();
}

void CLoadingState::OnDraw()
{
}

void CLoadingState::OnDestroy()
{
}

//EOF

bool	CheckNeedUpdate()
{
	/*
	char path[128];
	sprintf(path, "Map/Map21/0_0.wen");
	return !CCFileUtils::sharedFileUtils()->isFileExist(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(path).c_str());
	*/
	return false;
}
