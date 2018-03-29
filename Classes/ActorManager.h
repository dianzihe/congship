#pragma once

#include "base.h"
//#include "Event.h"
//#include "CCNode.h"
#include "cocos2d.h"
#include "Actor.h"
#include "Map.h"
#include <map>
#include <vector>
/*
class Actor;
class CHero;
class Click;
class Pick;
class AOEpick;
class DealImage;
class LevelUp;
class Map;
*/
using namespace std;
typedef std::map< long, Actor* >	MAP_ACTORS;

using namespace cocos2d;

class ActorManager /*: public OneEventObject*/
{
public:
	long							m_clientActorID;

	//CHero*							m_hero;
	//Click*							m_click;
	//Pick*							m_pick;
	//AOEpick*						m_aoe;
	//LevelUp* m_level;
	//int Deltag[];
	std::map< long, Actor* >		m_mapActors;
	MAP_ACTORS						m_mapTransportActors;

	typedef list< long >			LIST_ACTORIDS;
	LIST_ACTORIDS					m_lstWaitToDelActorIDs;
	long							timeNonce;

	DQMap*							m_pMap;

	int								m_nDispPlayerNum;
public:
	ActorManager(void);
	~ActorManager(void);

	virtual void update(float dt);	

	//bool ccTouchBegan(CCTouch* touch, CCEvent* event);

	void AddActor(Actor* actor );
	void DelActor(long nActorID);
	void DelayDelActor( long nActorID );
	void cleartimeNonce(){timeNonce=0;}
	Actor* FindActor(long nActorID)
	{
		if (m_mapActors.empty())
			return NULL;
		MAP_ACTORS::iterator iterFind = m_mapActors.find( nActorID );
		return iterFind != m_mapActors.end() ? (iterFind->second) : NULL;
	}

	void getActors( int nActorType, int nDataID, vector<Actor*>& vOut );//获得指定Type与dataID的actor
	void getActors( int nActorType, vector<Actor*>& vOut );//获得指定Type的actor
	void getActors(MAP_ACTORS& vOut); //获得全部actor
	void onChangeMap( void );
	void onGameStateEnter( void );
	void onGameStateLeave( void );

	void  updateAllNpcIcon( void );

	/*
	CHero* GetHero(){return m_hero;};
	Click* GetClick(){return m_click;};
	Pick* Getpick(){return m_pick;};
	AOEpick* Getaoe(){return m_aoe;};

	void SetHero(CHero* hero){ m_hero = hero; };
	void SetClick(Click* click){m_click = click;};
	void setPick(Pick* pick){m_pick=pick;};
	void setAoe(AOEpick* aoe){m_aoe = aoe;};
	*/
	//void SetLevel(LevelUp*level){m_level = level;};
	MAP_ACTORS& GetMapActors(){return m_mapActors;};

	long incClientActorID( void );

	void  setMap(DQMap *p){ m_pMap = p;};


	//自动选择一个目标，在使用技能时无目标时调用
	Actor	*AutoSelectTarget();

	//选择目标，用于摇杆界面目标选择按钮
	Actor	*SelectTarget();

	// 主角每次坐标变化时，检测传送点
	void	onHeroPosSet( void );

	void	doReleaseMemory();

	void	setOtherChaFractionName(bool showFraction);


};
