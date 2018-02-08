//附近玩家列表
#pragma once

#include "UI.h"
#include "ActorType.h"
//#include "UIScrollView.h"
#include <map>
using namespace std;
enum Actor_Type_Tab
{
	Actor_Player = 0,
	Actor_Other,
};

struct ActorInfo
{
	int actorID;
	string actroName;
	string level;
	ACTORTYPE actorType;
	string guildName;
};

//typedef map<int, ActorInfo> ActorInfoMap;
typedef vector<ActorInfo> ActorInfoVector;

class CPlayerItem
{
public:
	CPlayerItem();
	~CPlayerItem();

private:
	void init();

public:
	UI* m_pUI;
	UI* m_pSelectUI;

public:
	void setData(int index, ActorInfo* data);
};

class CPlayerListUI
{
public:
	CPlayerListUI();
	~CPlayerListUI();

	static CPlayerListUI& Instace()
	{
		static CPlayerListUI s;
		if( !s.m_bIsInit )
		{
			s.init();
		}
		return s;
	}

	void init();
	void unInit();

	void Show();

	//附近玩家
	void updatePlayer();
	void addPlayerToUI();

	//附近怪物
	void updateOther();
	void addOtherToUI();

	void switchPage(int type);

	int getSelectID(int index);

	void setSelectState(int index);

private:
	bool m_bIsInit;

	UI* m_pMain;
	UIScrollView* m_pPlayerPanel;
	UIScrollView* m_pOtherPanel;
	UI* m_pPlayerBtn;
	UI* m_pOtherBtn;

	int m_pageType;//选中的标签页

	ActorInfoVector m_playerInfoVec;
	ActorInfoVector m_otherInfoVec;

	vector<CPlayerItem*> m_pPlayerItem;
	vector<CPlayerItem*> m_pOtherItem;

	map<int, int> m_playerIDMap;
	map<int, int> m_otherIDMap;
};