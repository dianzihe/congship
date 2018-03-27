#include "RoutingCMD.h"
#include "GameScene.h"
#include "Charactor.h"
#include "DirectionModule.h"

RoutingCMD::RoutingCMD(ActorID nHost)
: GameCMD(eGameCMDType_Direction, nHost)
{

}

RoutingCMD::~RoutingCMD()
{

}

bool RoutingCMD::CanBeExecute()
{
	Charactor* m_pHost = GetHost();
	//if(m_pHost == NULL || !m_pHost->IsAbleToMove() )
	//	return false;
	return true;
}

void RoutingCMD::Enter()
{
	Charactor* m_pHost = GetHost();
	m_pHost->GetMotionManager()->ChangeToMotion(eMotionType_Routing);
	mGameCMDState = eGameCMDState_Finished;
}

void RoutingCMD::Execute()
{

}

void RoutingCMD::Exit(GameCMD* pNextCMD)
{

}
