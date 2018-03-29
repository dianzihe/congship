#pragma once

#include "Actor.h"
#include "CharacterStateTransTable.h"
#include "GameCMDSystem.h"
#include "MotionManager.h"
#include "RoutingModule.h"
#include "DirectionModule.h"
#include <vector>

//#include "platform.h"
//#include "StateMachine.h"
//#include "AbnormalStateModule.h"

using namespace std;
struct	CharactorBuff 
{
	long	startTime;
	int		buff_id;
	long long 	casterID;
	int		allValidTime;
	int		remainTriggerCount;
	int		buffIcon;
};

enum CharactorCombatState
{
	eCharactorCombatState_Idle,
	eCharactorCombatState_Attack,
	eCharactorCombatState_CombatAccept,
	eCharactorCombatState_End,
};
class RoutingModule;
class GameCMDSystem;
class DirectionModule;
class TeleportModule;
//class MotionManager;
class Charactor : public Actor/*, public ITransationInfo*/
{
	
public:
	Charactor();
	virtual ~Charactor();

protected:
	CC_SYNTHESIZE(int, m_speed, Speed);			//移动速度 每秒移动多少像素
	CC_SYNTHESIZE(int, m_camp, Camp);			//职业：0 ，1， 2， 3
	CC_SYNTHESIZE(int, m_nLevel, Level);		//等级
	CC_SYNTHESIZE(int, m_nFaction, Faction);	//阵营
	CC_SYNTHESIZE(int, m_nSex, Sex);			//性别
	CC_SYNTHESIZE(int, m_nLife, Life);			//生命
	CC_SYNTHESIZE(int, m_nLifeMax, LifeMax);	//最大生命
	CC_SYNTHESIZE(int, m_percentage_Life, perlife);//生命百分比
	CC_SYNTHESIZE(int, m_head, Head);			//小头像id
	CC_SYNTHESIZE(int, m_CurCombatID, CurCombatID);

public:
	bool		 init( void );

	virtual void update(float dt);
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)override;
	virtual void onStateEnter(int stateToEnter, int stateParam = 0);


	DQMotionManager*	m_pMotionMananger;
	GameCMDSystem*		m_pGameCMDSystem;

	DQMotionManager*	GetMotionManager() { return m_pMotionMananger; }
	RoutingModule*		GetRoutingModule() { return (RoutingModule*)(m_pMotionMananger->GetMotionModule(eMotionType_Routing)); }
	DirectionModule*	GetDirectionModule() { return (DirectionModule*)m_pMotionMananger->GetMotionModule(eMotionType_Direction); }
	GameCMDSystem*		GetGameCMDSystem() { return m_pGameCMDSystem; }

	//inline TeleportModule* GetTeleportModule() { return (TeleportModule*)m_pMotionMananger->GetMotionModule(eMotionType_Teleport); }

	/*
	int                         getAttackSum( void )const       { return m_nAttackSum; }
	void                        setAttackSum( int n )           { m_nAttackSum = n; }

	int                         getSkillMac( void )const       { return m_nSkillMac; }
	void                        setSkillMac( int n )           { m_nSkillMac = n; }
	*/
public:
	/*
	virtual void				DrawHP();

	virtual	void				onDead( void );

	virtual	void				onRevive( int nLife, int nMaxLife );

	virtual void				AddBuff( CharactorBuff& buff );

	virtual void				DelBuff(int buff_id);

	virtual void				UpdateBuff( const CharactorBuff& buff );

	virtual CharactorBuff* FindBuff( int buff_id );

	virtual std::vector<CharactorBuff>& getBuffList(){ return m_BuffList; };
	virtual bool				ChangeBuffBecauseBuff(){return true;}

	//inline StateMachine* GetStateMachine() { return m_pStateMachine; }

	virtual void ProcessAnimaEvent( AnimaEvent* event );

	bool IsAbleToAttack( int skillId );

	bool IsAbleToBeenAttack();

	bool IsAbleToMove();
	

	
	//AbnormalStateModule* GetAbnormalStateModule() { return m_AbnormalStateModule; }
	// New State Machine, Old Discard
	//virtual bool getStateTransitionInfo( int src, int dest );
	virtual void onStateExit( int stateToExit, int stateParam = 0 );
	*/
	/*
	virtual float getStateAnimTime( CharactorState state, int stateParam = 0 );
	virtual void DelayASpriteLoadCallBack();



	CharactorCombatState GetCharactorCombatState() { return m_CharactorCombatState; }

	//设置打坐状态
	void setSitDownState(int sitDownType);
	const int getSitDownSate(){return m_sitDownType;}
	*/
private:
#if 0

	
	//StateMachine*		m_pStateMachine;

	int                 m_nAttackSum;
	int                 m_nSkillMac;
	std::vector<CharactorBuff>		m_BuffList;

	int					m_nNameColorType;
	CharactorCombatState m_CharactorCombatState;

	void checkCanBeenAttackByHero_DrawName( void );
	void drawPkKillOtherName();

	int m_sitDownType;				//打坐类型
#endif 
};