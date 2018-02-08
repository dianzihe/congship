#pragma once

#include "Charactor.h"
//#include "package.h"
#include "cocos2d.h"
using namespace cocos2d;
//¿ñ±©×´Ì¬
#define Monster_WildState_NotWilded			0		//Î´¿ñ±©
#define Monster_WildState_Wilded				1		//ÒÑ¾­¿ñ±©

enum
{
	eMonsterWildAnimation_State_Enter,
	eMonsterWildAnimation_State_Wilded,
	eMonsterWildAnimation_State_Leave,
	eMonsterWildAnimation_State_NotWilded,
};

class CMonster : public Charactor
{
private:
	CMonster();
public:
	virtual ~CMonster();

	static CMonster* node(void);

	//virtual void draw();
	virtual void update(float dt);

	void updateDeathFly(float dt);

	void onStateEnter( int stateToEnter, int stateParam /*= 0 */ );
	//float getStateAnimTime( CharactorState state, int stateParam = 0 );
//////////////////////////////////////////////////////////////////////////
	void setHostAtkObjID( ActorID id ) { mHostAtkObjID = id; }

	virtual void	SetUnShowName();
	virtual void	SetShowName( const string& name);

	void	ChangeWildState( int state );

	void	ChangeWildAnimationState( int state );

	void	AddWildEffect();

	void	RemoveWildEffect();
	virtual void DelayASpriteLoadCallBack();

	//ÉèÖÃ¹ÖÎï»÷·ÉÊýÖµ
	void	setDeathFly( float speed, float time)
	{
		mCurDecresSpeed = speed;
		mDeathFlyTime = time;
	}
//Msg
public:
	//void			onLookInfoMonster( const pk::LookInfoMonster* pLookInfoMonster );
	float mDeathFlyTime;
	float mCurDecresSpeed;
	Point mDeathFlyDir;
	static float sDeathFlySpeed;
	static float sDeathFlyAcceleration;
	ActorID mHostAtkObjID;
	//ASprite*		m_cacheSkillSprite;
	int	m_eWildState;
	int	m_eWildAinmationState;
	float	m_fCfgScale;
	float	m_fWildScale;
	float	m_fMaxWildScale;
};