#include "GameCMD.h"
#include "GameScene.h"
#include "Charactor.h"
#include "ActorManager.h"

GameCMD::GameCMD( GameCMDType nGameCMDType, long nHost )
: mGameCMDType(nGameCMDType)
, mHostID(nHost)
, mIsHost(false)
, mGameCMDState(eGameCMDState_Undefined)
{

}

Charactor* GameCMD::GetHost()
{
	Actor* pHost = GameScene::GetActorManager()->FindActor(mHostID);
	if(pHost)
	{
		assert(dynamic_cast<Charactor*>(pHost) != NULL);
		return (Charactor*)(pHost);
	}
	return NULL;
}

