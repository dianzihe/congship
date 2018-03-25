#ifndef _GAMECMD_H__
#define _GAMECMD_H__

#include "base.h"

enum GameCMDType
{
	eGameCMDType_NULL,
	eGameCMDType_Routing,
	eGameCMDType_Direction,
	eGameCMDType_CommonAtk,
	eGameCMDType_Combat,
	eGameCMDType_Teleport,
};

enum GameCMDState
{
	eGameCMDState_Undefined,
	eGameCMDState_Executing,
	eGameCMDState_Finished,
};

class Charactor;
class GameCMD
{
public:
	GameCMD( GameCMDType nGameCMDType, ActorID nHost );
	virtual ~GameCMD() {}

	GameCMDType GetGameCMDType() { return mGameCMDType; }

	GameCMDState GetGameCMDState() { return mGameCMDState; }

	bool IsHost() { return mIsHost; }

	void SetIsHost( bool isHost ) { mIsHost = isHost; }

public:
	virtual bool CanBeExecute() = 0;

	virtual void Enter() = 0;

	virtual void Execute() = 0;

	virtual void Exit(GameCMD* pNextCMD) = 0;

	Charactor* GetHost();

	virtual void SynchrToSever(Charactor* pHost) = 0;
protected:
	ActorID		mHostID;
	GameCMDType mGameCMDType;
	GameCMDState mGameCMDState;
	bool mIsHost;
};


#endif