#include "DelayASpriteLoadManager.h"
#include "ASprite.h"
#include "GameScene.h"
#include "ActorManager.h"
#include "Actor.h"

DelayASpriteLoadManager::DelayASpriteLoadManager()
{
	mDelayASpriteContainer.clear();
}

DelayASpriteLoadManager::~DelayASpriteLoadManager()
{
	mDelayASpriteContainer.clear();
}

void DelayASpriteLoadManager::AddDelayASpriteAndCallBack( ASprite* pDelayASprite, long nHost )
{
	DelayASpriteContainer::iterator it = mDelayASpriteContainer.find(pDelayASprite);
	if(it != mDelayASpriteContainer.end())
	{
		it->second.insert(nHost);
	}
	else
	{
		CallBackContainer newCallBackContainer;
		newCallBackContainer.insert(nHost);
		mDelayASpriteContainer[pDelayASprite] = newCallBackContainer; 
	}
}

void DelayASpriteLoadManager::RemoveDelayASprite( ASprite* pDelayASprite )
{
	DelayASpriteContainer::iterator it = mDelayASpriteContainer.find(pDelayASprite);
	if(it != mDelayASpriteContainer.end())
	{
		mDelayASpriteContainer.erase(it);
	}
}

void DelayASpriteLoadManager::DelayASpriteLoadedCallBack( ASprite* pDelayASprite )
{
	DelayASpriteContainer::iterator it = mDelayASpriteContainer.find(pDelayASprite);
	if(it != mDelayASpriteContainer.end())
	{
		CallBackContainer::iterator itCB = it->second.begin();
		CallBackContainer::iterator itCBEnd = it->second.end();
		while(itCB != itCBEnd)
		{
			Actor* pCallBack = GameScene::GetActorManager()->FindActor(*itCB);
			/*
			if(pCallBack)
				pCallBack->DelayASpriteLoadCallBack();
			*/
			++itCB;
		}
		RemoveDelayASprite(pDelayASprite);
	}
}