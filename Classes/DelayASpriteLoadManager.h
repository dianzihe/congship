#ifndef _DELAYASPRITELOADMANAGER_H__
#define _DELAYASPRITELOADMANAGER_H__

#include <map>
#include <set>
#include "Singleton.h"
#include "base.h"

class ASprite;
class DelayASpriteLoadManager : public Singleton<DelayASpriteLoadManager ,Tag_Singleton_Auto>
{
protected:
	friend class Singleton<DelayASpriteLoadManager, Tag_Singleton_Auto>;
	typedef std::set<ActorID> CallBackContainer;
	typedef std::map<ASprite*, CallBackContainer> DelayASpriteContainer;
	DelayASpriteLoadManager();

public:
	virtual ~DelayASpriteLoadManager();

	void AddDelayASpriteAndCallBack( ASprite* pDelayASprite, ActorID nHost );

	void RemoveDelayASprite( ASprite* pDelayASprite );

	void DelayASpriteLoadedCallBack(ASprite* pDelayASprite);

protected:
	DelayASpriteContainer mDelayASpriteContainer;
};

#endif
