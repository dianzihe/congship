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
	int							m_speed;				//移动速度 每秒移动多少像素
	int							m_camp;					//职业：0 ，1， 2， 3
	int							m_nLevel;				//等级
	int							m_nFaction;				//阵营
	int							m_nSex;					//性别
	int							m_nLife;				//生命
	int							m_nLifeMax;				//最大生命
	float                       m_percentage_Life;      //生命百分比
	int							m_head;					//小头像id


public:
	bool						init( void );

	int							getSpeed( void )const			{ return	m_speed; }
	void						setSpeed( int n )				{ m_speed = n; }

	float                       getperlife(void)const           {return m_percentage_Life;}
	void				       setperlife(float n)             {m_percentage_Life = n;}

	int							getLevel( void )const			{ return m_nLevel; }
	void						setLevel( int n )				{ m_nLevel = n; }

	int							getFaction( void )const			{ return m_nFaction; }
	void						setFaction( int n )				{ m_nFaction = n; }

	int							getSex( void )const				{ return m_nSex; }
	void						setSex( int n )					{ m_nSex = n; }

	int							getLife( void )const			{ return m_nLife; }
	void						setLife( int n )				{ m_nLife = n;}

	int							getLifeMax( void )const			{ return m_nLifeMax; }
	void						setLifeMax( int n )				{ m_nLifeMax = n; }

	int							getCamp( void )const			{ return m_camp; }
	void						setCamp( int n )				{ m_camp = n; }

	int							getHead( void )const			{ return m_head; }
	void						setHead( int n )				{ m_head = n; }

	virtual void				update(float dt);
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)override;

	/*
	int							getCurCombatID()				{ return m_CurCombatID; }
	void						setCurCombatID( int n )			{ m_CurCombatID = n; }

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
	
	DQMotionManager*		m_pMotionMananger;
	DQMotionManager* GetMotionManager() { return m_pMotionMananger; }
	
	//AbnormalStateModule* GetAbnormalStateModule() { return m_AbnormalStateModule; }
	// New State Machine, Old Discard
	//virtual bool getStateTransitionInfo( int src, int dest );
	virtual void onStateExit( int stateToExit, int stateParam = 0 );
	virtual void onStateEnter( int stateToEnter, int stateParam = 0 );
	*/
	/*
	virtual float getStateAnimTime( CharactorState state, int stateParam = 0 );
	virtual void DelayASpriteLoadCallBack();

	RoutingModule* GetRoutingModule() { return (RoutingModule*)(m_pMotionMananger->GetMotionModule(eMotionType_Routing)); }

	DirectionModule* GetDirectionModule() { return (DirectionModule*)m_pMotionMananger->GetMotionModule(eMotionType_Direction); }

	//inline TeleportModule* GetTeleportModule() { return (TeleportModule*)m_pMotionMananger->GetMotionModule(eMotionType_Teleport); }

	GameCMDSystem* GetGameCMDSystem() { return m_pGameCMDSystem; }

	CharactorCombatState GetCharactorCombatState() { return m_CharactorCombatState; }

	//设置打坐状态
	void setSitDownState(int sitDownType);
	const int getSitDownSate(){return m_sitDownType;}
	*/
private:
#if 0
	GameCMDSystem*		m_pGameCMDSystem;
	
	//StateMachine*		m_pStateMachine;
	int					m_CurCombatID;
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