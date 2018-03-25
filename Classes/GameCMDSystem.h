#ifndef _GAMECMDSYSTEM_H__
#define _GAMECMDSYSTEM_H__

#include "GameCMD.h"
#include "RoutingCMD.h"
//#include "DirectionCMD.h"
//#include "TeleportCMD.h"
//#include "CommonAtkCMD.h"
//#include "CombatCMD.h"

class GameCMDSystem
{
public:
	typedef std::list<GameCMD*> GameCMDList;
	GameCMDSystem();
	~GameCMDSystem();

public:
	void PushGameCMD(GameCMD* pGameCMD);

	void CleanGameCMD();

	void UpdateCMDSystem();

	GameCMD* GetCurGameCMD() { return mCurGameCMD; }

private:
	GameCMDList mGameCMDList;
	GameCMD* mCurGameCMD;
};

#endif
