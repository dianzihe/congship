#ifndef _ROUTINCMD_H__
#define _ROUTINCMD_H__

#include "GameCMD.h"

class RoutingCMD : public GameCMD
{
public:
	RoutingCMD(ActorID nHost);
	virtual ~RoutingCMD();
public:
	virtual bool CanBeExecute();

	virtual void Enter();

	virtual void Execute();

	virtual void Exit(GameCMD* pNextCMD);

	void SynchrToSever(Charactor* pHost) {}
private:
};


#endif