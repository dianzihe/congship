#include "ASpriteManager.h"
//#include "Hero.h"
//#include "GameScene.h"
#include "ActorManager.h"

//#include "MountCfg.h"
//#include "HeroMount.h"
//#include "PlayerEquipAtrUI.h"

const char* OtherResName[] = 
{
	"NPCmission",
	"MiniMap",
	"click",
	"Pick",
	"Aoe",
	"Shadow",
	"PlayerHP",
	"transport",
	"expression",
	"LogoSFX",
	"eye"
};

AspriteManager::~AspriteManager()
{
}

void AspriteManager::RemoveSprite(ASprite* pSprite)
{
	SpriteContainer::iterator iter = gSprites.begin();
	for (;iter != gSprites.end(); ++iter)
	{
		if (iter->second == pSprite)
		{
			gSprites.erase(iter);
			break;
		}
	}
}

ASprite* AspriteManager::LoadSprite(SpriteInfo& nSpriteInfo, bool nIsMustLoad, bool isRecursiveCall)
{
	std::string spriteName = GetSpriteName(nSpriteInfo);
	std::string spriteFile = GetSpritePath(nSpriteInfo._ActorType) + spriteName;
	ASprite* sprite = GetSprite(spriteName);
	if ( sprite == NULL)
	{
		sprite = new ASprite();

		if( sprite->Load(spriteFile.c_str(), nSpriteInfo._ActorType, nIsMustLoad | isMustLoad(nSpriteInfo._ActorType)) )
		{
			sprite->setSpriteName(spriteName);
			gSprites[spriteName] = sprite;
		}
		else
		{
			//SAFE_DELETE(sprite);
			sprite->release();
			sprite = NULL;

			if(!isRecursiveCall) //防递归调用
				sprite = FindReplaceSpriteWhenResourceMiss(nSpriteInfo);
		}
	}
	else
	{
		if(nIsMustLoad)
			sprite->ForceLoadTexture();
		sprite->retain();
	}
	return sprite;
}

bool AspriteManager::IsSpriteLoaded(SpriteInfo& nSpriteInfo)
{
	std::string spriteName = GetSpriteName(nSpriteInfo);
	std::string spriteFile = GetSpritePath(nSpriteInfo._ActorType) + spriteName;
	ASprite* sprite = GetSprite(spriteName);

	if (sprite)
		return true;
	return false;
}


ASprite* AspriteManager::GetSprite( const std::string& nSpriteName )
{
	SpriteContainer::iterator it = gSprites.find(nSpriteName);
	if(it != gSprites.end())
	{
		return it->second;
	}
	return NULL;
}

bool AspriteManager::isMustLoad(ACTORTYPE actorType)
{
	if (actorType == ACTORTYPE_NPC || 
		actorType == ACTORTYPE_MONSTER || 
		actorType == ACTORTYPE_TRANSPORT ||
		actorType == ACTORTYPE_COLLECT ||
		actorType == ACTORTYPE_ANIMATION ||
		actorType == ACTORTYPE_FLAG)
		return true;

	return false;
}

const char* AspriteManager::GetSpritePath( ACTORTYPE actorType )
{
	return ResPath[actorType];
}

std::string AspriteManager::GetSpriteName( SpriteInfo& nSpriteInfo )
{
	const char* nameStart;
	char name[256];
	if(nSpriteInfo._ActorType == ACTORTYPE_ANIMATION)
	{
		nameStart = OtherResName[nSpriteInfo._ActorID];
	}
	else
	{
		nameStart = ResNameStart[nSpriteInfo._ActorType];
	}

	switch(nSpriteInfo._ActorType)
	{
	case ACTORTYPE_PLAYER:
	case ACTORTYPE_HERO:
	case ACTORTYPE_WEAPON:
		{
			sprintf(name, "%s%d_%d_%c", 
				nameStart,
				nSpriteInfo._ActorID + 1,
				nSpriteInfo._EquipLevel,
				nSpriteInfo._ActorGender ? 'f' : 'm');
		}
		break;
	case ACTORTYPE_WEAPONSFX: //涉及到换装
		{
			sprintf(name, "%s%d_%d", 
				nameStart,
				nSpriteInfo._ActorID,
				nSpriteInfo._EquipLevel);
		}
		break;
	case ACTORTYPE_TRANSPORT:
		{
			strcpy(name, nameStart);
		}
		break;
	case ACTORTYPE_ANIMATION:
	case ACTORTYPE_OBJECT_NORMAL:
		{
			strcpy(name, nameStart);
		}
		break;
	case ACTORTYPE_SKILLSFX:
		{
			if(nSpriteInfo._ActorID <= 4)
			{
				sprintf(name, "%s%s%d", "Sprite/playerSFX/", nameStart, nSpriteInfo._ActorID );
			}
			else
			{
				sprintf(name, "%s%s%d", "Sprite/monsterSFX/", nameStart, nSpriteInfo._ActorID );
			}
		}
		break;
	case ACTORTYPE_OTHERSFX:
		{
			strcpy(name, nameStart);
		}
		break;
	default:
		{
			sprintf(name, "%s%d",
				nameStart,
				nSpriteInfo._ActorID);
		}
		break;
	}
	return name;
}

AspriteManager::AspriteManager()
{
	ResPath[ACTORTYPE_ANIMATION] = "Sprite/object/";
	ResPath[ACTORTYPE_PLAYER] = "Sprite/player/";
	ResPath[ACTORTYPE_WEAPON] = "Sprite/weapon/";
	ResPath[ACTORTYPE_WEAPONSFX] = "Sprite/weaponSFX/";
	ResPath[ACTORTYPE_MOUNT] = "Sprite/mount/";
	ResPath[ACTORTYPE_WING] = "Sprite/wing/";
	ResPath[ACTORTYPE_NPC] = "Sprite/npc/";
	ResPath[ACTORTYPE_MONSTER] = "Sprite/monster/";
	ResPath[ACTORTYPE_HERO] = ResPath[ACTORTYPE_PLAYER];
	ResPath[ACTORTYPE_SKILLSFX] = "";
	ResPath[ACTORTYPE_OTHERSFX] = "Sprite/otherSFX/";
	//ResPath[ACTORTYPE_PETSFX] = "Sprite/object/";
	ResPath[ACTORTYPE_TRANSPORT] = ResPath[ACTORTYPE_ANIMATION];
	ResPath[ACTORTYPE_COLLECT] = "Sprite/Collection/";
	ResPath[ACTORTYPE_FLAG] = "Sprite/Collection/";
	ResPath[ACTORTYPE_PATHFIND_POINT] = ResPath[ACTORTYPE_ANIMATION];
	ResPath[ACTORTYPE_PET] = "Sprite/xsm/";
	ResPath[ACTORTYPE_OBJECT_NORMAL] = ResPath[ACTORTYPE_ANIMATION];
	ResPath[ACTORTYPE_SCENEOBJECT] = "Sprite/sceneObject/";
	ResPath[ACTORTYPE_CONVOY] = ResPath[ACTORTYPE_MONSTER];
	ResPath[ACTORTYPE_MAGICWEAPONSFX] = "Sprite/MagicWeaponSFX/";

	ResNameStart[ACTORTYPE_ANIMATION] = "";
	ResNameStart[ACTORTYPE_PLAYER] = "p";
	ResNameStart[ACTORTYPE_WEAPON] = "w";
	ResNameStart[ACTORTYPE_WEAPONSFX] = "d";
	ResNameStart[ACTORTYPE_MOUNT] = "mot";
	ResNameStart[ACTORTYPE_WING] = "w";
	ResNameStart[ACTORTYPE_NPC] = "n";
	ResNameStart[ACTORTYPE_MONSTER] = "m";
	ResNameStart[ACTORTYPE_HERO] = ResNameStart[ACTORTYPE_PLAYER];
	ResNameStart[ACTORTYPE_SKILLSFX] = "e";
	ResNameStart[ACTORTYPE_OTHERSFX] = "otherSFX";
	//ResNameStart[ACTORTYPE_PETSFX] = "eye";
	ResNameStart[ACTORTYPE_TRANSPORT] = "transport";
	ResNameStart[ACTORTYPE_COLLECT] = "c";
	ResNameStart[ACTORTYPE_FLAG] = "c";
	ResNameStart[ACTORTYPE_PATHFIND_POINT] = "";
	ResNameStart[ACTORTYPE_PET] = "xsm";
	ResNameStart[ACTORTYPE_OBJECT_NORMAL] = "tongyong";
	ResNameStart[ACTORTYPE_SCENEOBJECT] = "sceneObj";
	ResNameStart[ACTORTYPE_CONVOY] = ResNameStart[ACTORTYPE_MONSTER];
	ResNameStart[ACTORTYPE_MAGICWEAPONSFX] = "fb_";

	m_preLoad[0] = NULL;
	m_preLoad[1] = NULL;
	m_preLoad[2] = NULL;
	m_preLoad[3] = NULL;
	m_preLoad[4] = NULL;
	m_preLoad[5] = NULL;
}

void AspriteManager::initilize()
{
    if(m_preLoad[0] == NULL)
 	{
 		SpriteInfo _spriteInfo;
 		_spriteInfo._ActorType = ACTORTYPE_ANIMATION;
 		_spriteInfo._ActorID = SPRITE_EXPRESSION;
 		m_preLoad[0] = LoadSprite(_spriteInfo);
 	}
    
    if(m_preLoad[1] == NULL)
 	{
 		SpriteInfo _spriteInfo;
 		_spriteInfo._ActorType = ACTORTYPE_ANIMATION;
 		_spriteInfo._ActorID = SPRITE_HP;
 		m_preLoad[1] = LoadSprite(_spriteInfo);
 	}
    
    if(m_preLoad[2] == NULL)
 	{
 		SpriteInfo _spriteInfo;
 		_spriteInfo._ActorType = ACTORTYPE_ANIMATION;
 		_spriteInfo._ActorID = SPRITE_CLICK;
 		m_preLoad[2] = LoadSprite(_spriteInfo);
 	}

	if(m_preLoad[3] == NULL)
	{
		SpriteInfo _spriteInfo;
		_spriteInfo._ActorType = ACTORTYPE_OTHERSFX;
		m_preLoad[3] = LoadSprite(_spriteInfo, true);
	}
}

void AspriteManager::uninitilize()
{
	for (int n = 0; n <= 5; ++n)
	{
		if (m_preLoad[n])
			m_preLoad[n]->release();
	}
	mAnimationDelayLoadMap.clear();
}

void AspriteManager::tick(float deltaTime)
{
	SpriteContainer::iterator iter = gSprites.begin();
	SpriteContainer::iterator end = gSprites.end();
	for (; iter != end; ++iter)
	{
		ASprite* pSprite = iter->second;
		if(pSprite && !pSprite->IsTextureLoaded())
		{
			pSprite->tick(deltaTime);
		}
	}
}

ASprite* AspriteManager::FindReplaceSpriteWhenMemoryLack( SpriteInfo& nSpriteInfo )
{
	ASprite* replaceSprite = NULL;
	switch(nSpriteInfo._ActorType)
	{
	case ACTORTYPE_PLAYER:
	case ACTORTYPE_HERO:
	case ACTORTYPE_WEAPON:
	case ACTORTYPE_MOUNT:
		{
			/*
			CHero* pHero = GameScene::GetActorManager()->GetHero();
			if(pHero)
			{
				SpriteInfo _SpriteInfo;
				_SpriteInfo._ActorGender = pHero->getSex();
				_SpriteInfo._ActorID = pHero->getCamp();
				_SpriteInfo._ActorType = nSpriteInfo._ActorType;
				_SpriteInfo._EquipLevel = nSpriteInfo._EquipLevel;
				if(ACTORTYPE_PLAYER == nSpriteInfo._ActorType || ACTORTYPE_HERO == nSpriteInfo._ActorType)
				{
					////////////////////////装备模型修改：万佳////////////////////////////
					ClientItem* pCoatItem = CPlayerEquipAtrUI::instance()->GetPlayerEquipInfoByType(EquipTypeXSM_Coat);
					if(pCoatItem == NULL)
						_SpriteInfo._EquipLevel = 1;
					else
						_SpriteInfo._EquipLevel = pCoatItem->getItemData()->m_useSpriteID;
				}
				if(ACTORTYPE_WEAPON == nSpriteInfo._ActorType)
				{
					ClientItem* pWeaponItem = CPlayerEquipAtrUI::instance()->GetPlayerEquipInfoByType(EquipTypeXSM_Weapon);
					if(pWeaponItem == NULL)
						_SpriteInfo._EquipLevel = 1;
					else
						_SpriteInfo._EquipLevel = pWeaponItem->getItemData()->m_useSpriteID;
				}
				if(ACTORTYPE_MOUNT == nSpriteInfo._ActorType)
				{
					const PlayerMountData* pEquipMount = CHeroMount::instance().getEquipMountData();
					_SpriteInfo._ActorID = 1;
					if(pEquipMount)
					{
						const MountData* pMountData = MountCfg::instance().getMountCfgData(pEquipMount->mountDataID);
						if(pMountData)
							_SpriteInfo._ActorID = pMountData->MountModelID;
					}
				}
				std::string spriteName = GetSpriteName( _SpriteInfo );
				replaceSprite = GetSprite(spriteName);
			}
			*/
		}
		break;
	case ACTORTYPE_PET:
		{
			SpriteInfo _SpriteInfo;
			_SpriteInfo._ActorGender = 0;
			_SpriteInfo._ActorID = 0;//初始套装
			_SpriteInfo._ActorType = ACTORTYPE_PET;
			_SpriteInfo._EquipLevel = 1;
			replaceSprite = LoadSprite(_SpriteInfo, true);
			//replaceSprite->release();
		}
		break;
	}
	return replaceSprite;
}

ASprite* AspriteManager::FindReplaceSpriteWhenResourceMiss( SpriteInfo& nSpriteInfo )
{

	ASprite* replaceSprite = NULL;
	switch(nSpriteInfo._ActorType)
	{
	case ACTORTYPE_PLAYER:
	case ACTORTYPE_HERO:
	case ACTORTYPE_WEAPON:
		{
			/*
			CHero* pHero = GameScene::GetActorManager()->GetHero();
			if(pHero)
			{
				SpriteInfo _SpriteInfo;
				_SpriteInfo._ActorGender = nSpriteInfo._ActorGender;
				_SpriteInfo._ActorID = nSpriteInfo._ActorID;
				_SpriteInfo._ActorType = nSpriteInfo._ActorType;
				_SpriteInfo._EquipLevel = 2;
				replaceSprite = LoadSprite(_SpriteInfo, false, true);
			}
			*/
		}
		break;
	case ACTORTYPE_MONSTER:
	case ACTORTYPE_PET:
		{
			replaceSprite = gSprites["monster_null"];
			if( replaceSprite == NULL )
			{
				ASprite* pSprite = new ASprite();

				if( pSprite->Load("Sprite/monster/monster_null", nSpriteInfo._ActorType, false) )
				{
					gSprites["monster_null"] = pSprite;
					pSprite->setSpriteName("monster_null");
					replaceSprite = pSprite;
				}
				else
				{
					pSprite->release();
				}
			}
			else
			{
				replaceSprite->retain();
			}
		}
		break;
	case ACTORTYPE_NPC:
		{
			replaceSprite = gSprites["npc_null"];
			if( replaceSprite == NULL )
			{
				ASprite* pSprite = new ASprite();

				if( pSprite->Load("Sprite/npc/npc_null", nSpriteInfo._ActorType, false) )
				{
					gSprites["npc_null"] = pSprite;
					pSprite->setSpriteName("npc_null");
					replaceSprite = pSprite;
				}
				else
				{
					pSprite->release();
				}
			}
			else
			{
				replaceSprite->retain();
			}
		}
		break;
	}
	return replaceSprite;
}

void AspriteManager::AddAnimationDelayLoad( DQAnimation* pAnima, ASprite* delayLoad, ACTORTYPE type, GrayPart gPart )
{
	DelayAnimInfo _DelayAnimInfo;
	_DelayAnimInfo._HostAnimation = pAnima;
	_DelayAnimInfo._ActorType = type;
	_DelayAnimInfo._GrayPart = gPart;
	mAnimationDelayLoadMap[delayLoad] = _DelayAnimInfo;
}

void AspriteManager::RemoveAnimationDelayLoad( DQAnimation* pAnima )
{
	DelayAnimationMap::iterator it = mAnimationDelayLoadMap.begin();
	DelayAnimationMap::iterator end = mAnimationDelayLoadMap.end();
	while(it != end)
	{
		if(it->second._HostAnimation == pAnima)
		{
			it->first->release();
			mAnimationDelayLoadMap.erase(it++);
		}
		else
		{
			++it;
		}
	}
}

void AspriteManager::RemoveAnimationDelayLoad( ASprite* pSprite )
{
	DelayAnimationMap::iterator it = mAnimationDelayLoadMap.find(pSprite);
	if(it != mAnimationDelayLoadMap.end())
	{
		mAnimationDelayLoadMap.erase(it);
	}
}

void AspriteManager::AnimationDelayLoadCall( ASprite* pSprite )
{
	DelayAnimationMap::iterator it = mAnimationDelayLoadMap.find(pSprite);
	if(it != mAnimationDelayLoadMap.end())
	{
		it->second._HostAnimation->AddASprite(pSprite, it->second._ActorType);
		it->second._HostAnimation->m_pHostEventHandler->setGray(it->second._GrayPart, false);
		mAnimationDelayLoadMap.erase(it);
	}
}

