#ifndef _ASPRITEMANAGER_H__
#define _ASPRITEMANAGER_H__

#include "ASprite.h"
#include "ActorType.h"
#include "Singleton.h"
#include "Animation.h"
#include <map>
#include <string>

struct SpriteInfo
{
	ACTORTYPE	_ActorType;
	int			_ActorID;
	int			_ActorGender; // 0 : female, 1: male
	int			_EquipLevel;

	SpriteInfo(): _ActorID(0), _EquipLevel(1), _ActorGender(0), _ActorType(ACTORTYPE_ANIMATION) {}
};

class Animation;
struct DelayAnimInfo
{
	DQAnimation* _HostAnimation;
	ACTORTYPE _ActorType;
	GrayPart _GrayPart;

	DelayAnimInfo() : _HostAnimation(NULL){}
};

class AspriteManager : public Singleton<AspriteManager,Tag_Singleton_Auto>
{
private:
	friend class ASprite;
	friend class Singleton<AspriteManager,Tag_Singleton_Auto>;
	
	AspriteManager();
	~AspriteManager();
public:
	ASprite*		LoadSprite( SpriteInfo& nSpriteInfo, bool nIsMustLoad = false, bool isRecursiveCall = false );
	bool            IsSpriteLoaded(SpriteInfo& nSpriteInfo);
	std::string		GetSpriteName( SpriteInfo& nSpriteInfo );
	ASprite*		GetSprite( const std::string& nSpriteName );
	void			initilize();
	void			uninitilize();
	void			tick(float deltaTime);
	bool			isMustLoad(ACTORTYPE actorType);
	ASprite*		FindReplaceSpriteWhenMemoryLack(SpriteInfo& nSpriteInfo);
	ASprite*		FindReplaceSpriteWhenResourceMiss( SpriteInfo& nSpriteInfo );

	void			AddAnimationDelayLoad(DQAnimation* pAnima, ASprite* delayLoad, ACTORTYPE type, GrayPart gPart);
	void			RemoveAnimationDelayLoad(DQAnimation* pAnima);
	void			RemoveAnimationDelayLoad(ASprite* pSprite);
	void			AnimationDelayLoadCall(ASprite* pSprite);
protected:
	const char*		GetSpritePath( ACTORTYPE actorType );
	void			RemoveSprite(ASprite* pSprite);
private:
	typedef std::map<std::string, ASprite*> SpriteContainer;
	SpriteContainer gSprites;
	char* ResPath[ACTORTYPE_Count];
	char* ResNameStart[ACTORTYPE_Count];
	ASprite* m_preLoad[6];
	typedef std::map<ASprite*, DelayAnimInfo> DelayAnimationMap;
	DelayAnimationMap mAnimationDelayLoadMap;
};


#endif
