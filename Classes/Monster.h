#pragma once

#include "Charactor.h"
//#include "package.h"
#include "cocos2d.h"
using namespace cocos2d;
//��״̬
#define Monster_WildState_NotWilded	0	//δ��
#define Monster_WildState_Wilded 1		//�Ѿ���

enum
{
	eMonsterWildAnimation_State_Enter,
	eMonsterWildAnimation_State_Wilded,
	eMonsterWildAnimation_State_Leave,
	eMonsterWildAnimation_State_NotWilded,
};

struct LookInfoMonster
{
	INT32 id;
	INT16 move_target_x;
	INT16 move_target_y;
	INT16 move_speed;
	INT16 x;
	INT16 y;
	INT16 monster_data_id;
	INT8 lifePercent;
	INT8 faction;
	int charState;
	vector<ObjectBuff> buffList;
	INT8 wildState;
};

class CMonster : public Charactor
{
private:
	CMonster();
public:
	virtual ~CMonster();

	static CMonster* node(void);

	//virtual void draw();
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)override;
	virtual void update(float dt);

	void updateDeathFly(float dt);

	void onStateEnter( int stateToEnter, int stateParam /*= 0 */ );
	float getStateAnimTime( CharactorState state, int stateParam = 0 );
//////////////////////////////////////////////////////////////////////////
	void setHostAtkObjID( ActorID id ) { mHostAtkObjID = id; }

	virtual void	SetUnShowName();
	virtual void	SetShowName( const string& name);

	void	ChangeWildState( int state );

	void	ChangeWildAnimationState( int state );

	void	AddWildEffect();

	void	RemoveWildEffect();
	virtual void DelayASpriteLoadCallBack();

	//���ù��������ֵ
	void	setDeathFly( float speed, float time)
	{
		mCurDecresSpeed = speed;
		mDeathFlyTime = time;
	}
//Msg
public:
	void	onLookInfoMonster( LookInfoMonster* pLookInfoMonster );
	float	mDeathFlyTime;
	float	mCurDecresSpeed;
	Point	mDeathFlyDir;
	static float sDeathFlySpeed;
	static float sDeathFlyAcceleration;
	ActorID mHostAtkObjID;
	ASprite*		m_cacheSkillSprite;
	int		m_eWildState;
	int		m_eWildAinmationState;
	float	m_fCfgScale;
	float	m_fWildScale;
	float	m_fMaxWildScale;
};