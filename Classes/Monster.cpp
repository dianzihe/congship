#include "Monster.h"
//#include "PlayerDefine.h"
#include "MonsterCfg.h"
#include "GameScene.h"
#include "ActorManager.h"
/*
#include "SkillCfg.h"
#include "Map.h"
#include "../BaseModule/Motion/RoutingModule.h"
#include "../InputSystem/GameCMDSystem.h"
#include "../BaseModule/SFX/SFXModule.h"
*/

float CMonster::sDeathFlySpeed = 1200;

float CMonster::sDeathFlyAcceleration = 10000;

#define		MonsterWild_Scale_Speed	4.0f

#define  MONSTER_FONT_SCALE 1.3f

CMonster::CMonster()
: mDeathFlyTime(0)
, mCurDecresSpeed(0)
, mHostAtkObjID(0)
//, m_cacheSkillSprite(NULL)
, m_eWildState(Monster_WildState_NotWilded)
, m_fCfgScale( 1.0f )
, m_fWildScale( 1.0f )
, m_eWildAinmationState( eMonsterWildAnimation_State_NotWilded )
{
	mDeathFlyDir.x = 0;
	mDeathFlyDir.y = 0;
}

CMonster::~CMonster()
{
	/*
	if (m_cacheSkillSprite)
	{
		m_cacheSkillSprite->release();
	}
	*/
}

CMonster* CMonster::node()
{
	CMonster* pRet = new CMonster();
	pRet->setActorType(ACTORTYPE_MONSTER);
	pRet->init();
	pRet->setSpeed(150);
	pRet->autorelease();

	return pRet;
}
/*
void CMonster::onLookInfoMonster( const pk::LookInfoMonster* pLookInfoMonster )
{
	const MonsterData* pMonsterData = MonsterCfg::instance().getMonsterCfgData( pLookInfoMonster->monster_data_id );
	if( !pMonsterData )
	{
		ERROR_LOG( "CMonster::onLookInfoMonster monster_data_id[%d] can not find ", pLookInfoMonster->monster_data_id  );
		return;
	}
	setActorID( pLookInfoMonster->id );

	setDataID( pLookInfoMonster->monster_data_id );
	setFaction(pMonsterData->faction);
	setLevel( pMonsterData->level );
	setperlife(float(pLookInfoMonster->lifePercent)/100.0f);
	setHead(pMonsterData->mobHead);
	setSpeed(pLookInfoMonster->move_speed);
	setStateFlag(pLookInfoMonster->charState);
	if(pMonsterData->monstertype == MonsterType_NormalBoss ||
		pMonsterData->monstertype == MonsterType_CopyMapBoss ||
		pMonsterData->monstertype == MonsterType_FieldBoss)
		setTargetIconSheild(false); // by wzq 2013.12.23 去掉屏蔽头像功能
	else
		setTargetIconSheild(true);
	m_animation.SetHostEventHandler(this);
	addAnimationSprite( pMonsterData->animation, ACTORTYPE_MONSTER, 0, 1, true );
	char str[128];
	sprintf(str, "%s(LV%d)", pMonsterData->name.c_str(), pMonsterData->level);
	SetName( str ); //必须放在模型设置完毕之后再显示  否则无法读取模型高度  会出现名字在脚下的BUG
	m_pStateMachine->setStateForce(eCharactorState_Idle, m_dir);

	GameScene::GetActorManager()->AddActor( this );
	SetNewPos(ccp(pLookInfoMonster->x, pLookInfoMonster->y));
	if( pLookInfoMonster->move_target_x > 0 || pLookInfoMonster->move_target_y > 0 )
	{
		RoutingCMD* newCMD = new RoutingCMD(getActorID());
		GetGameCMDSystem()->PushGameCMD(newCMD);
		GetRoutingModule()->AddTargetPath( ccp( pLookInfoMonster->move_target_x, pLookInfoMonster->move_target_y ) );
	}
	const SkillInfo* pBaseSkill = SkillCfg::instance().getSkillCfgData(pMonsterData->baseSkillID);
	if(pBaseSkill)
	{
		SpriteInfo _SpriteInfo;
		_SpriteInfo._ActorType = ACTORTYPE_SKILLSFX;
		_SpriteInfo._ActorID = pBaseSkill->EffectGroup;
		m_cacheSkillSprite = AspriteManager::instance().LoadSprite(_SpriteInfo);
	}
	else
	{
		SpriteInfo _SpriteInfo;
		_SpriteInfo._ActorType = ACTORTYPE_SKILLSFX;
		_SpriteInfo._ActorID = 5;
		m_cacheSkillSprite = AspriteManager::instance().LoadSprite(_SpriteInfo);
	}
	// 处理金银岛
	int mapID = GameScene::GetScene()->GetCurMap()->getMapID();
	if (mapID ==45||mapID==48)
	{
		SetShowName(pMonsterData->name);
	}

	//添加buff
	cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now,NULL);
	for( int i=0; i < (int)pLookInfoMonster->buffList.size(); ++i )
	{
		CharactorBuff buff;
		buff.buff_id =pLookInfoMonster->buffList[i].buff_id;
		buff.allValidTime = pLookInfoMonster->buffList[i].allValidTime;
		buff.casterID = 0;
		buff.remainTriggerCount = pLookInfoMonster->buffList[i].remainTriggerCount;
		buff.startTime = now.tv_sec+now.tv_usec/1000000;
		AddBuff(buff);
	}

	DEBUG_LOG( "onLookInfoMonster [%lld %s] pos[%d %d]", 
		getActorID(),
		GetName().c_str(),
		(int)getPosition().x,
		(int)getPosition().y );


	m_fCfgScale = pMonsterData->modelscale;
	m_fMaxWildScale = pMonsterData->wildMaxScale;
	m_fWildScale = pMonsterData->wildMaxScale;
	switch( pLookInfoMonster->wildState )
	{
	case Monster_WildState_NotWilded:
		m_eWildState = Monster_WildState_NotWilded;
		m_animation.setScale(m_fCfgScale);
		RemoveWildEffect();
		break;

	case Monster_WildState_Wilded:
		m_eWildState = Monster_WildState_Wilded;
		m_animation.setScale(m_fCfgScale*m_fWildScale);
		AddWildEffect();
		break;
	}
}

void CMonster::draw()
{
	Charactor::draw();
}
*/
void CMonster::onStateEnter( int stateToEnter, int stateParam /*= 0 */ )
{
	Charactor::onStateEnter(stateToEnter, stateParam);
	switch(stateToEnter)
	{
	case eCharactorState_Idle:
		{
			ChangeAnimation(ANIM_MONSTER_IDLE_DOWN, m_dir);		
		}
		break;
	case eCharactorState_Run:
		{
			int newDir = stateParam;
			ChangeAnimation(ANIM_MONSTER_MOVE_DOWN, newDir);		
		}
		break;
	case eCharactorState_Attack:
		{
			ChangeAnimation(ANIM_MONSTER_ATTACK_DOWN, m_dir, false);

		}
		break;
	case eCharactorState_UnderAttack:
		{
			//ChangeAnimation(ANIM_MONSTER_HURT_DOWN, m_dir);
		}
		break;
	case eCharactorState_Death:
		{
			/*
			addStateFlag(Actor_State_Flag_Dead);

			Actor* atkObj = GameScene::GetActorManager()->FindActor(mHostAtkObjID);
			if(atkObj)
			{
				mDeathFlyDir.x = getPositionX() - atkObj->getPositionX();
				mDeathFlyDir.y = getPositionY() - atkObj->getPositionY();
				float dis = sqrtf(mDeathFlyDir.x*mDeathFlyDir.x + mDeathFlyDir.y*mDeathFlyDir.y);
				if(dis == 0.0f)
				{
					mDeathFlyDir.x = 0;
					mDeathFlyDir.y = 1;
				}
				else
				{
					mDeathFlyDir.x = mDeathFlyDir.x / dis;
					mDeathFlyDir.y = mDeathFlyDir.y / dis;
				}
				//mCurDecresSpeed = sDeathFlySpeed;
				//mDeathFlyTime = 0.03f;
				mCurDecresSpeed = 0;
				mDeathFlyTime = 0;
			}
			ChangeAnimation(ANIM_MONSTER_DEAD_DOWN, m_dir, false);
			*/
		}
		break;
	default:
		break;
	}
}

/*
float CMonster::getStateAnimTime( CharactorState state, int stateParam )
{
	float time = 0.0f;
	switch(state)
	{
	case eCharactorState_Attack:
		{
			time = GetAnimationTime(ANIM_MONSTER_ATTACK_DOWN);
		}
		break;
	case eCharactorState_Death:
		{
			time = GetAnimationTime(ANIM_MONSTER_DEAD_DOWN);
		}
		break;
	default:
		break;
	}
	return time;
}
*/
void CMonster::update( float dt )
{
	Charactor::update(dt);

	/*
	switch ( m_eWildAinmationState )
	{
	case eMonsterWildAnimation_State_Enter:
		if( m_fWildScale < m_fMaxWildScale )
		{
			m_fWildScale += MonsterWild_Scale_Speed*dt;
			m_animation.setScale( m_fCfgScale*m_fWildScale );
		}
		else
		{
			ChangeWildAnimationState( eMonsterWildAnimation_State_Wilded );
		}
		break;

	case eMonsterWildAnimation_State_Leave:
		if( m_fWildScale > 1.0f )
		{
			m_fWildScale -= MonsterWild_Scale_Speed*dt;
			m_animation.setScale( m_fCfgScale*m_fWildScale );
		}
		else
		{
			ChangeWildAnimationState( eMonsterWildAnimation_State_NotWilded );
		}
		break;
	}
	*/
	updateDeathFly(dt);
}

void CMonster::updateDeathFly( float dt )
{
	/*
	if (m_pStateMachine->getCurrentState() == eCharactorState_Death)
	{
		if(mDeathFlyTime > 0)
		{
			if(dt > 0.02f)
				dt = 0.02f;
			mDeathFlyTime -= dt;
			float moveLen = mCurDecresSpeed * dt;
			setPosition(mDeathFlyDir.x * moveLen + getPositionX(), mDeathFlyDir.y * moveLen + getPositionY());
		}
		else if( mCurDecresSpeed > 0)
		{
			float moveLen = mCurDecresSpeed * dt + 0.5f * dt * dt * sDeathFlyAcceleration;
			setPosition(mDeathFlyDir.x * moveLen + getPositionX(), mDeathFlyDir.y * moveLen + getPositionY());
			mCurDecresSpeed -= sDeathFlyAcceleration * dt;
		}
		else if(m_animation.m_opacity > 0)
		{
			m_animation.m_opacity -= (int)(200 * dt);
			if(m_animation.m_opacity < 0)
				m_animation.m_opacity = 0;
			mHostAtkObjID = 0;
		}
	}
	*/
}

void	CMonster::SetUnShowName()
{
	/*
	int mapID = GameScene::GetScene()->GetCurMap()->getMapID();
	if (mapID ==45||mapID==48)
	{
		return ; // 金银岛退出
	}
	*/
	removeChildByTag(ACTORCHILD_NAME, true);
}

void	CMonster::SetShowName( const string& name)
{
	if( !name.size() )
		return;
	/*
	removeChildByTag(ACTORCHILD_NAME, true);
	CCLabelBMFont *pName = CCLabelBMFont::create(name.c_str(), FONT_BMP_24);
	pName->setScale(MONSTER_FONT_SCALE);
	pName->setAnchorPoint(ccp(0.5f, 0.0f));
	if(GetSprite() != NULL && GetSprite()->IsDataLoaded() == true)
	{
		CCRect rect = GetSprite()->getRectSelect();
		pName->setPosition(ccp(0, rect.size.height + 20));
	}
	addChild( pName, 0, ACTORCHILD_NAME );

	const MonsterData *pMonsterCfg = MonsterCfg::instance().getMonsterCfgData(getDataID());
	if( pMonsterCfg && pMonsterCfg->Active )
	{
		pName->setColor(ccc3( 255, 0, 0 ));
	}
	*/
}

void CMonster::DelayASpriteLoadCallBack()
{
	Actor::DelayASpriteLoadCallBack();
	// 处理金银岛
	/*
	int mapID = GameScene::GetScene()->GetCurMap()->getMapID();
	if (mapID ==45||mapID==48)
	{
		CCLabelBMFont *pName = dynamic_cast<CCLabelBMFont*>(getChildByTag(ACTORCHILD_NAME));
		if(GetSprite() != NULL && GetSprite()->IsDataLoaded() == true && pName )
		{
			CCRect rect = GetSprite()->getRectSelect();
			pName->setPosition(ccp(0, rect.size.height + 20));
		}
	}
	*/
}

void	CMonster::ChangeWildState( int state )
{
	switch( state )
	{
	case Monster_WildState_NotWilded:
		m_eWildState = Monster_WildState_NotWilded;
		ChangeWildAnimationState(eMonsterWildAnimation_State_Leave);
		break;

	case Monster_WildState_Wilded:
		m_eWildState = Monster_WildState_Wilded;
		ChangeWildAnimationState(eMonsterWildAnimation_State_Enter);
		break;
	}
}

void	CMonster::ChangeWildAnimationState( int state )
{
	/*
	switch( state )
	{
	case eMonsterWildAnimation_State_Enter:
		m_animation.setScale( m_fCfgScale );
		m_fWildScale = 1.0f;
		m_eWildAinmationState = eMonsterWildAnimation_State_Enter;
		break;

	case eMonsterWildAnimation_State_Wilded:
		m_animation.setScale( m_fCfgScale*m_fMaxWildScale );
		m_fWildScale = m_fMaxWildScale;
		m_eWildAinmationState = eMonsterWildAnimation_State_Wilded;
		AddWildEffect();
		break;

	case eMonsterWildAnimation_State_Leave:
		m_animation.setScale( m_fCfgScale*m_fMaxWildScale );
		m_fWildScale = m_fMaxWildScale;
		m_eWildAinmationState = eMonsterWildAnimation_State_Leave;
		break;

	case eMonsterWildAnimation_State_NotWilded:
		m_animation.setScale( m_fCfgScale );
		m_fWildScale = 1.0f;
		m_eWildAinmationState = eMonsterWildAnimation_State_NotWilded;
		RemoveWildEffect();
		break;
	}
	*/
}


void	CMonster::AddWildEffect()
{
	RemoveWildEffect();
	/*
	AnimSFX* pSFX = new AnimSFX;
	pSFX->Initialize();
	pSFX->GetAnimation()->LoadASprite(0, ACTORTYPE_OTHERSFX);
	pSFX->GetAnimation()->setAnim( 32 );
	pSFX->GetAnimation()->setScale(m_fCfgScale*m_fMaxWildScale);
	pSFX->SetSFXLocation(eSFXLocation_Back);
	pSFX->SetLifeStyle( eLife_Allways );
	pSFX->SetLifeTime( pSFX->GetAnimation()->getAnimTime( 32 ) );
	pSFX->SetSFXIdentify( 32 );
	m_SFXModule->AddSFX(pSFX);
	*/
}

void	CMonster::RemoveWildEffect()
{
	/*
	SFXModule::SFXContainer::iterator it = m_SFXModule->GetSFXContainer().begin();
	SFXModule::SFXContainer::iterator end = m_SFXModule->GetSFXContainer().end();
	while(it != end)
	{
		if((*it)->GetSFXIdentify() == 32 )
		{
			m_SFXModule->DelSFX(*it);
			break;
		}
		++it;
	}
	*/
}