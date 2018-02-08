#include "PlayerListUI.h"
//#include "GameScene.h"
#include "Monster.h"
#include "MonsterCfg.h"
#include "ActorManager.h"
/*
#include "Player.h"
#include "Friend.h"
#include "Text.h"
#include "TextDef.h"
#include "Object.h"
#include "Routing.h"
#include "Target.h"
#include "../BaseModule/Navigation/NavigationModule.h"
*/
#define ENEMY_COLOR	1	//敌对势力颜色
#define FRIEND_COLOR 4	//好友颜色
#define GUILD_COLOR 6	//同帮会颜色
#define OTHER_COLOR 3	//其他颜色

CPlayerListUI::CPlayerListUI():
m_bIsInit(false)
{

}

CPlayerListUI::~CPlayerListUI()
{

}

void OnClosePlayerList(UI* ui, void* data)
{
	CPlayerListUI::Instace().Show();
	return;
}

void OnSwitchTab(UI* ui, void* data)
{
	int type = (int)data;
	CPlayerListUI::Instace().switchPage( (Actor_Type_Tab)type);
	return;
}

void OnSelectActor(UI* ui, void* data)
{
	/*
	int64 id = CPlayerListUI::Instace().getSelectID( (int)data);
	CPlayerListUI::Instace().setSelectState( (int)data);
	Actor* pActor = GameScene::GetActorManager()->FindActor( id);
	if(pActor)
	{
		if(pActor->getActorType() == ACTORTYPE_FLAG)
		{
			NavigationModule *heroNavigation = GameScene::GetHeroNavigation();
			heroNavigation->CancelNavigation();
			FixCollectTask* newTask = new FixCollectTask(heroNavigation);
			newTask->SetTargetID(pActor->getActorID());
			heroNavigation->AddTask(newTask);
		}
		else
		{
			Target::instance().clearTarget();
			Target::instance().SetCurTargetID(pActor->getActorID());
			Target::instance().update();
			NavigationModule* heroNavigation = GameScene::GetHeroNavigation();
			heroNavigation->CancelNavigation();
			FixFightTask* newTask = new FixFightTask(heroNavigation);
			newTask->SetTargetID(pActor->getActorID());
			heroNavigation->AddTask(newTask);
		}
	}
	*/
	return;
}

void CPlayerListUI::init()
{
	m_pMain = UIManager::Instance()->loadUI("lingdizhengduo_player.ui", false);
	m_pMain->Top();
	m_pMain->setVisible(false);
	m_pMain->findUI("CloseButton1")->setEvent(EVENT_UP, OnClosePlayerList);
	m_pPlayerBtn = m_pMain->findUI("PageButton1");
	m_pOtherBtn = m_pMain->findUI("PageButton2");
	m_pPlayerBtn->setEvent(EVENT_UP, OnSwitchTab, (void*)Actor_Player);
	m_pOtherBtn->setEvent(EVENT_UP, OnSwitchTab, (void*)Actor_Other);
	/*
	m_pPlayerPanel = dynamic_cast<UIScrollView*>(m_pMain->findUI("PanelBase21"));
	m_pOtherPanel = dynamic_cast<UIScrollView*>(m_pMain->findUI("PanelBase22"));
	m_pPlayerPanel->SetScrollType( ScrollType_Y);
	m_pOtherPanel->SetScrollType( ScrollType_Y);
	*/

	m_bIsInit = true;

	OnSwitchTab(NULL, (void*)Actor_Player);
}

void CPlayerListUI::unInit()
{
	for(unsigned int i=0; i<m_pPlayerItem.size(); i++)
	{
		delete m_pPlayerItem[i];
	}
	m_pPlayerItem.clear();

	for(unsigned int i=0; i<m_pOtherItem.size(); i++)
	{
		delete m_pOtherItem[i];
	}
	m_pOtherItem.clear();
	m_bIsInit = false;
}

void CPlayerListUI::Show()
{
	//m_pMain->setVisible( !m_pMain->isVisible());
	m_pMain->Top();
	switchPage( m_pageType);
}

void CPlayerListUI::switchPage(int type)
{
	m_pageType = type;

	if(type == Actor_Player)
	{
		updatePlayer();
		//m_pPlayerPanel->setVisible(true);
		//m_pOtherPanel->setVisible(false);
		m_pPlayerBtn->m_down = true;
		m_pOtherBtn->m_down = false;
	}
	else
	{
		updateOther();
		//m_pPlayerPanel->setVisible(false);
		//m_pOtherPanel->setVisible(true);
		m_pPlayerBtn->m_down = false;
		m_pOtherBtn->m_down = true;
	}
}

void CPlayerListUI::updateOther()
{
	vector<ActorInfo>flags;
	vector<ActorInfo>boss;
	vector<ActorInfo>elite;//精英怪
	vector<ActorInfo>normal;//普通怪

	vector<Actor*>object;
	/*
	GameScene::GetActorManager()->getActors(ACTORTYPE_FLAG, object);
	for(unsigned int i=0; i<object.size(); i++)
	{
		CObject* pObj = dynamic_cast<CObject*>(object[i]);
		if(pObj && pObj->getActorType() == ACTORTYPE_FLAG)
		{
			char str[256];
			int color = FRIEND_COLOR;
			ActorInfo data;
			data.actorID = pObj->getActorID();
			data.actorType = ACTORTYPE_FLAG;
			sprintf(str, "<O=%d>%d%s</O>", color, 1, CText::GetText(CTextDef::LEVEL_JI).c_str());
			data.level = str;
			sprintf(str, "<O=%d>%s</O>", color, pObj->GetName().c_str());
			data.actroName = str;
			if(pObj->GetShowName() == pObj->GetName())
				sprintf(str, "<O=%d>%s</O>", color, CText::GetText(CTextDef::NoGuild_Text).c_str());
			else
				sprintf(str, "<O=%d>%s</O>", color, pObj->getBelongName().c_str());
			data.guildName = str;

			flags.push_back( data);
		}
	}

	vector<Actor*> monster;
	GameScene::GetActorManager()->getActors(ACTORTYPE_MONSTER, monster);
	for(unsigned int i=0; i<monster.size(); i++)
	{
		CMonster* pObj = dynamic_cast<CMonster*>(monster[i]);
		if(!pObj)
			continue;
		const MonsterData *pMonsterCfg = MonsterCfg::instance().getMonsterCfgData(pObj->getDataID());
		if(!pMonsterCfg)
			continue;

		char str[256];
		ActorInfo data;
		int color = ENEMY_COLOR;
		data.actorType = ACTORTYPE_MONSTER;
		data.actorID = pObj->getActorID();
		sprintf(str, "<O=%d>%d%s</O>", color, pObj->getLevel(), CText::GetText(CTextDef::LEVEL_JI).c_str());
		data.level = str;
		sprintf(str, "<O=%d>%s</O>", color, pMonsterCfg->name.c_str());
		data.actroName = str;
		if(pMonsterCfg->monstertype >= MonsterType_NormalBoss)
		{
			sprintf(str, "<O=%d>%s</O>", color, CText::GetText(CTextDef::Monster_Type_BOSS).c_str());
			data.guildName = str;
			boss.push_back( data);
		}
		else if(pMonsterCfg->monstertype == MonsterType_Elite)
		{
			sprintf(str, "<O=%d>%s</O>", color, CText::GetText(CTextDef::Monster_Type_Elite).c_str());
			data.guildName = str;
			elite.push_back( data);
		}
		else
		{
			sprintf(str, "<O=%d>%s</O>", color, CText::GetText(CTextDef::Monster_Type_Normal).c_str());
			data.guildName = str;
			normal.push_back( data);
		}
	}
	m_otherInfoVec.clear();
	m_otherInfoVec.insert(m_otherInfoVec.end(), flags.begin(), flags.end());
	m_otherInfoVec.insert(m_otherInfoVec.end(), boss.begin(), boss.end());
	m_otherInfoVec.insert(m_otherInfoVec.end(), elite.begin(), elite.end());
	//m_otherInfoVec.insert(m_otherInfoVec.end(), normal.begin(), normal.end());
	*/
	addOtherToUI();

	return;
}

void CPlayerListUI::addOtherToUI()
{
	for(unsigned int i=0; i<m_pOtherItem.size(); i++)
	{
		delete m_pOtherItem[i];
	}
	m_pOtherItem.clear();

	//m_pOtherPanel->removeAllChildrenWithCleanup(true);
	//m_pOtherPanel->resetStartPos();

	m_otherIDMap.clear();
	CCPoint pos(0, 0);
	for(unsigned int i=0; i<m_otherInfoVec.size(); i++)
	{
		CPlayerItem* pItem = new CPlayerItem;
		pItem->setData( i, &m_otherInfoVec[i]);
		m_otherIDMap.insert( make_pair(i, m_otherInfoVec[i].actorID));
		pos.x = 2;
		//pos.y = m_pOtherPanel->m_height - (float)(pItem->m_pUI->m_height+2)*i - pItem->m_pUI->m_height;
		//pItem->m_pUI->setPosition( pos);
		//m_pOtherPanel->addChild( pItem->m_pUI);
		m_pOtherItem.push_back(pItem);
	}
	return;
}

void CPlayerListUI::updatePlayer()
{
	vector<Actor*> actors;
	vector<ActorInfo>top;//武林盟主
	vector<ActorInfo>secend;//四大高手
	vector<ActorInfo>topTen;//十大高手
	vector<ActorInfo>enemies;//仇人
	vector<ActorInfo>friends;//朋友
	vector<ActorInfo>guildSelf;//本帮派成员
	vector<ActorInfo>guildOther;//其他帮会成员
	vector<ActorInfo>normal;//普通成员
	
	/*
	CHero* hero = 	GameScene::GetScene()->GetActorManager()->GetHero();
	GameScene::GetActorManager()->getActors(ACTORTYPE_PLAYER, actors);
	for(unsigned int i=0; i<actors.size();i++)
	{
		int color = OTHER_COLOR;
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(actors[i]);
		if(!pPlayer)
			continue;

		//颜色
		if(CFriend::Instance()->IsFriend(pPlayer->getActorID()))//好友
			color = FRIEND_COLOR;
		else if(pPlayer->getGuildID()>0 && (pPlayer->getGuildID()==hero->getGuildID()||pPlayer->getGuildID() == hero->getParnterID()))//同帮派
			color = GUILD_COLOR;
		else if(pPlayer->getGuildID()>0 && pPlayer->getGuildID()!=hero->getGuildID() && pPlayer->getGuildID() != hero->getParnterID())//敌对帮派
			color = ENEMY_COLOR;
		else if(pPlayer->IsEnemy())//仇人
			color = ENEMY_COLOR;
		else//其他
			color = OTHER_COLOR;

		char str[256];
		ActorInfo actorData;
		actorData.actorID = pPlayer->getActorID();
		actorData.actorType = ACTORTYPE_PLAYER;
		sprintf(str, "<O=%d>%d%s</O>", color, pPlayer->getLevel(), CText::GetText(CTextDef::LEVEL_JI).c_str());
		actorData.level = str;
		if(pPlayer->getGuildID()>0)
			sprintf(str, "<O=%d>%s</O>", color, pPlayer->getguildName().c_str());
		else
			sprintf(str, "<O=%d>%s</O>", color, CText::GetText(CTextDef::NoGuild_Text).c_str());
		actorData.guildName = str;

		if(pPlayer->IsEnemy())//仇人
		{
			sprintf(str, "<O=%d>[%s]%s</O>", color, CText::GetText(CTextDef::Enemy_Text).c_str(), pPlayer->GetName().c_str());
			actorData.actroName = str;
			enemies.push_back(actorData);
		}
		else if(CFriend::Instance()->IsFriend(pPlayer->getActorID()))//朋友
		{
			sprintf(str, "<O=%d>[%s]%s</O>", color, CText::GetText(CTextDef::Friend_Text).c_str(), pPlayer->GetName().c_str());
			actorData.actroName = str;
			friends.push_back(actorData);
		}
		else if(pPlayer->getGuildID()>0 && pPlayer->getGuildID()==hero->getGuildID())//有帮会，并和自己同帮会
		{
			sprintf(str, "<O=%d>[%s]%s</O>", color, CText::GetText(CTextDef::Guild_Self_Text).c_str(), pPlayer->GetName().c_str());
			actorData.actroName = str;
			guildSelf.push_back(actorData);
		}
		else if(pPlayer->getGuildID()>0 && pPlayer->getGuildID()!=hero->getGuildID())//有帮会，和自己不同帮
		{
			sprintf(str, "<O=%d>[%s]%s</O>", color, CText::GetText(CTextDef::Guild_Other_Text).c_str(), pPlayer->GetName().c_str());
			actorData.actroName = str;
			guildOther.push_back(actorData);
		}
		else
		{
			sprintf(str, "<O=%d>[%s]%s</O>", color, CText::GetText(CTextDef::Normal_Player_Text).c_str(), pPlayer->GetName().c_str());
			actorData.actroName = str;
			normal.push_back(actorData);
		}
	}
	m_playerInfoVec.clear();
	m_playerInfoVec.insert(m_playerInfoVec.end(), top.begin(), top.end());
	m_playerInfoVec.insert(m_playerInfoVec.end(), secend.begin(), secend.end());
	m_playerInfoVec.insert(m_playerInfoVec.end(), topTen.begin(), topTen.end());
	m_playerInfoVec.insert(m_playerInfoVec.end(), enemies.begin(), enemies.end());
	m_playerInfoVec.insert(m_playerInfoVec.end(), friends.begin(), friends.end());
	m_playerInfoVec.insert(m_playerInfoVec.end(), guildSelf.begin(), guildSelf.end());
	m_playerInfoVec.insert(m_playerInfoVec.end(), guildOther.begin(), guildOther.end());
	m_playerInfoVec.insert(m_playerInfoVec.end(), normal.begin(), normal.end());

	addPlayerToUI();
	*/
	return;
}

void CPlayerListUI::addPlayerToUI()
{
	for(unsigned int i=0; i<m_pPlayerItem.size(); i++)
	{
		delete m_pPlayerItem[i];
	}
	m_pPlayerItem.clear();

	//m_pPlayerPanel->removeAllChildrenWithCleanup(true);
	//m_pPlayerPanel->resetStartPos();

	m_playerIDMap.clear();
	CCPoint pos(0, 0);
	for(unsigned int i=0; i<m_playerInfoVec.size(); i++)
	{
		CPlayerItem* pItem = new CPlayerItem;
		pItem->setData( i, &m_playerInfoVec[i]);
		m_playerIDMap.insert( make_pair(i, m_playerInfoVec[i].actorID));
		pos.x = 2;
		//pos.y = m_pPlayerPanel->m_height - (float)(pItem->m_pUI->m_height+2)*i - pItem->m_pUI->m_height;
		//pItem->m_pUI->setPosition( pos);
		//m_pPlayerPanel->addChild( pItem->m_pUI);
		//m_pPlayerItem.push_back(pItem);
	}
}

/*
int64 CPlayerListUI::getSelectID(int index)
{
	if(m_pageType == Actor_Player)
	{
		map<int, int64>::iterator it = m_playerIDMap.find( index);
		if(it!=m_playerIDMap.end())
			return it->second;
		else
			return 0;
	}
	else
	{
		map<int, int64>::iterator it = m_otherIDMap.find( index);
		if(it!=m_otherIDMap.end())
			return it->second;
		else
			return 0;
	}
}
*/
void CPlayerListUI::setSelectState(int index)
{
	if(m_pageType == Actor_Player)
	{
		for(unsigned int i=0; i<m_pPlayerItem.size(); i++)
		{
			if( i == index)
				m_pPlayerItem[i]->m_pSelectUI->setVisible( true);
			else
				m_pPlayerItem[i]->m_pSelectUI->setVisible( false);
		}
	}
	else
	{
		for(unsigned int i=0; i<m_pOtherItem.size(); i++)
		{
			if( i == index)
				m_pOtherItem[i]->m_pSelectUI->setVisible( true);
			else
				m_pOtherItem[i]->m_pSelectUI->setVisible( false);
		}
	}
}

CPlayerItem::CPlayerItem()
{
	init();
}

CPlayerItem::~CPlayerItem()
{

}

void CPlayerItem::init()
{
	UI* ui = new UI();

	UIDataGroup group;
	group.Load("lingdizhengduo_playerList.ui");

	//ui->autorelease();
	ui->m_name = group.name;
	ui->m_align = group.align;

	for (int i = 0; i < group.count; i++ )
	{
		UI* pChild = group.data[i].createUI();
		//ui->addChild(pChild);
	}
	ui->init();
	m_pUI = ui;
	if(m_pUI)
	{
		m_pUI->findUI("level")->setIgnoreTouch(true);
		m_pUI->findUI("playername")->setIgnoreTouch(true);
		m_pUI->findUI("banghui")->setIgnoreTouch(true);

		m_pUI->m_width = m_pUI->findUI("PanelBase31")->m_width;
		m_pUI->m_height = m_pUI->findUI("PanelBase31")->m_height;
		m_pSelectUI = m_pUI->findUI("ItemSelect01");
		m_pSelectUI->setIgnoreTouch(true);
		m_pSelectUI->setVisible( false);
	}
}

void CPlayerItem::setData(int index, ActorInfo* data)
{
	if(data)
	{
		//m_pUI->findUI("playername")->setText(data->actroName.c_str());
		//m_pUI->findUI("banghui")->setText(data->guildName.c_str());
		//m_pUI->findUI("level")->setText(data->level.c_str());
		//m_pUI->findUI("PanelBase31")->setEvent(EVENT_UP, OnSelectActor, (void*)index);
	}
}