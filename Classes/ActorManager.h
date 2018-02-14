#pragma once

#include "base.h"
//#include "Event.h"
//#include "CCNode.h"
#include "cocos2d.h"
#include "Actor.h"
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
typedef std::map< ActorID, Actor* >	MAP_ACTORS;

using namespace cocos2d;

class ActorManager /*: public OneEventObject*/
{
public:
	ActorManager(void);
	~ActorManager(void);

	virtual void update(float dt);	

	//bool ccTouchBegan(CCTouch* touch, CCEvent* event);

	void AddActor(Actor* actor );
	void DelActor(ActorID nActorID);
	void DelayDelActor( ActorID nActorID );
	void cleartimeNonce(){timeNonce=0;}
	Actor* FindActor(ActorID nActorID)
	{
		MAP_ACTORS::iterator iterFind = m_mapActors.find( nActorID );
		return iterFind != m_mapActors.end() ? (iterFind->second) : NULL;
	}

	void	getActors( int nActorType, int nDataID, vector<Actor*>& vOut );//���ָ��Type��dataID��actor
	void	getActors( int nActorType, vector<Actor*>& vOut );//���ָ��Type��actor
	void    getActors(MAP_ACTORS& vOut); //���ȫ��actor
	void	onChangeMap( void );
	void	onGameStateEnter( void );
	void	onGameStateLeave( void );

	void	updateAllNpcIcon( void );

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

	ActorID							incClientActorID( void );

	//void  setMap(Map *p){ m_pMap = p;};


	//�Զ�ѡ��һ��Ŀ�꣬��ʹ�ü���ʱ��Ŀ��ʱ����
	Actor	*AutoSelectTarget();

	//ѡ��Ŀ�꣬����ҡ�˽���Ŀ��ѡ��ť
	Actor	*SelectTarget();

	// ����ÿ������仯ʱ����⴫�͵�
	void	onHeroPosSet( void );

	void	doReleaseMemory();

	void	setOtherChaFractionName(bool showFraction);

private:
	ActorID							m_clientActorID;

	//CHero*							m_hero;
	//Click*							m_click;
	//Pick*							m_pick;
	//AOEpick*						m_aoe;
	//LevelUp* m_level;
	//int Deltag[];
	MAP_ACTORS						m_mapActors;

	MAP_ACTORS						m_mapTransportActors;

	typedef list< ActorID >			LIST_ACTORIDS;
	LIST_ACTORIDS					m_lstWaitToDelActorIDs;
	long							timeNonce;

	//Map*							m_pMap;

	int								m_nDispPlayerNum;
};
