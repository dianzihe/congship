#include "GameCMDSystem.h"


GameCMDSystem::GameCMDSystem( )
: mCurGameCMD(NULL)
{

}

GameCMDSystem::~GameCMDSystem()
{
	CleanGameCMD();
}

void GameCMDSystem::PushGameCMD( GameCMD* pGameCMD )
{
	mGameCMDList.push_back(pGameCMD);
}

void GameCMDSystem::CleanGameCMD()
{
	SAFE_DELETE(mCurGameCMD);
	GameCMDList::iterator it = mGameCMDList.begin();
	GameCMDList::iterator end = mGameCMDList.end();
	while(it != end) {
		GameCMD* pCMD = (*it);
		SAFE_DELETE(pCMD);
		++it;
	}
	mGameCMDList.clear();
}

void GameCMDSystem::UpdateCMDSystem()
{
	GameCMD* oldCMD = mCurGameCMD;
	GameCMDList::iterator it = mGameCMDList.begin();
	GameCMDList::iterator end = mGameCMDList.end();
	while(it != end) {
		GameCMD* pNextCMD = *it;
		
		if(pNextCMD->CanBeExecute()) {
			if(mCurGameCMD) {
				mCurGameCMD->Exit(pNextCMD);
				SAFE_DELETE(mCurGameCMD);
			}
			pNextCMD->Enter();
			pNextCMD->Execute();
			mCurGameCMD = pNextCMD;
		} else {
			SAFE_DELETE(pNextCMD);
		}

		++it;
	}
	mGameCMDList.clear();

	if(mCurGameCMD) {
		if(mCurGameCMD == oldCMD) {
			mCurGameCMD->Execute();
		}

		if(mCurGameCMD->GetGameCMDState() == eGameCMDState_Finished) {
			SAFE_DELETE(mCurGameCMD);
		}
	}
}
