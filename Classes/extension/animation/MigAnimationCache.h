//
//  MigAnimationCache.h
//  SanguoHeros
//
//  Created by 伟 李 on 12-10-22.
//  Copyright (c) 2012年 intelligame. All rights reserved.
//

#ifndef SanguoHeros_MigAnimationCache_h
#define SanguoHeros_MigAnimationCache_h

#include "cocos2d.h"
#include "MigAnimation.h"

USING_NS_CC;

class DQAnimationCache;
class SpriteCache;
class FrameCache;
class ModuleCache;

class MigAnimationCache
{
public:
    static MigAnimationCache* getShared();
	bool init();
	static void purgeAll();
    DQAnimationCache* getAnimationCache(const char* xmlName);
    void addAnimationCache(DQAnimationCache* pCache);
    void removeAnimationCache(const char* xmlName);
    void removeAllCache();
    void createAnimationFromCache(MigSpriteNode* pRoot,const char* xmlName,bool useBatchSprite);
//private:
    MigAnimationCache();
    ~ MigAnimationCache();
    
    //CCArray* m_animationCaches;
	std::vector<DQAnimationCache*> m_animationCaches;
	//CCArray* enemy3sToDelete;
	//std::vector<std::string> enemy3sToDelete;
    //static MigAnimationCache* m_pSingleInstance;
    
    void createSpriteFromCache(MigSpriteNode* pRoot,SpriteCache* pCache);
    void createFrameFromCache(MigSpriteNode* pRoot,MigSprite* pSprite,FrameCache* pCache);
    
    //DQAnimationCache* m_pCurAnimationCache;
    bool m_bUseBatchSprite;
};

class DQAnimationCache : Ref
{
public:
    CCString* name;
    CCString* xmlName;
    CCString* plistName;
    CCString* textureName;
    //CCArray* sprites;
	std::vector<SpriteCache*> sprites;

    DQAnimationCache() : name(NULL),xmlName(NULL),plistName(NULL),textureName(NULL)
    {
		//sprites = CCArray::create();
    }
    
    ~ DQAnimationCache()
    {
		//sprites->autorelease();
        //CC_SAFE_RELEASE_NULL(sprites);
		/*
        CC_SAFE_RELEASE_NULL(name);
        CC_SAFE_RELEASE_NULL(xmlName);
        CC_SAFE_RELEASE_NULL(plistName);
        CC_SAFE_RELEASE_NULL(textureName);
		*/
    }
};

class SpriteCache : Ref
{
public:

    SpriteCache(): name(NULL)
    {
		//frames = CCArray::create();
    }
    
    ~ SpriteCache()
    {
        //CC_SAFE_RELEASE_NULL(frames);
        //CC_SAFE_RELEASE_NULL(name);
    }
    
    CCString* name;
	std::vector<FrameCache*> frames;
};

class FrameCache : Ref
{
public:

    FrameCache() : flag(0),duration(1),rectRed(),rectGreen()
    {
		//modules = CCArray::create();
    }
    
    ~ FrameCache()
    {
        //CC_SAFE_RELEASE_NULL(modules);
//        rectRed.release();
//        rectGreen.release();
    }
    
    int flag;
    int duration;
    CCRect rectRed;
    CCRect rectGreen;
	std::vector<ModuleCache*> modules;
};

class ModuleCache : Ref
{
public:

    ModuleCache():name(NULL),offsetX(0),offsetY(0),flip(0),rotate(0)
    {
        
    }
    
    ~ ModuleCache()
    {
        //CC_SAFE_RELEASE_NULL(name);
    }
    
    CCString* name;
    int offsetX;
    int offsetY;
    int flip;
    int rotate;
};

#endif
