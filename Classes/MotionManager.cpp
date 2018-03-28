#include "base.h"
#include "MotionManager.h"
//#include "Hero.h"
//#include "Charactor.h"
#include "RoutingModule.h"
#include "DirectionModule.h"
//#include "HeroRoutingModule.h"
//#include "TeleportModule.h"


DQMotionManager::DQMotionManager(Charactor* pHost)
: m_pHost(pHost)
, mNewMotion(eMotionType_NULL)
, mCurMotion(eMotionType_NULL)
{
	memset(mMotionModule, 0, sizeof(mMotionModule));
	mMotionModule[eMotionType_Routing] = new RoutingModule(m_pHost);
	mMotionModule[eMotionType_Direction] = new DirectionModule(m_pHost);
	//mMotionModule[eMotionType_Teleport] = new TeleportModule(m_pHost);
#if 0
	if(pHost->getActorType() == ACTORTYPE_HERO)
	{
		CHero* pHero = (CHero*)(pHost);
		mMotionModule[eMotionType_Routing] = new HeroRoutingModule(pHero);
		mMotionModule[eMotionType_Direction] = new DirectionModule(pHero);
		mMotionModule[eMotionType_Teleport] = new TeleportModule(pHero);
	}
	else
	{
		mMotionModule[eMotionType_Routing] = new RoutingModule(m_pHost);
		mMotionModule[eMotionType_Direction] = new DirectionModule(m_pHost);
		mMotionModule[eMotionType_Teleport] = new TeleportModule(m_pHost);
	}
#endif
}

DQMotionManager::~DQMotionManager()
{
	SAFE_DELETE(mMotionModule[eMotionType_Routing]);
	SAFE_DELETE(mMotionModule[eMotionType_Direction]);
	SAFE_DELETE(mMotionModule[eMotionType_Teleport]);
}

void DQMotionManager::Update(float dt)
{
	if(mNewMotion != mCurMotion){
		if(mMotionModule[mCurMotion])
			mMotionModule[mCurMotion]->ExitMotion();
		if(mMotionModule[mNewMotion])
			mMotionModule[mNewMotion]->EnterMotion();

		mCurMotion = mNewMotion;
	}

	if (mMotionModule[mCurMotion]){
		mMotionModule[mCurMotion]->UpdateMotion(dt);
	}
}

void DQMotionManager::ChangeToMotion(MotionType nMotion)
{
	if(IsCurMotionCanExit())
	{
		mNewMotion = nMotion;
	}
}

bool DQMotionManager::IsCurMotionCanExit()
{
	if( mMotionModule[mCurMotion] == NULL || mMotionModule[mCurMotion]->CanBeCancel() )
	{
		return true;
	}
	return false;
}

void DQMotionManager::StopMotion()
{
	if(mMotionModule[mCurMotion])
	{
		mMotionModule[mCurMotion]->ExitMotion();
	}
	mCurMotion = mNewMotion = eMotionType_NULL;
}

