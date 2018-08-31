//
//  MigAnimationCache.cpp
//  SanguoHeros
//
//  Created by 伟 李 on 12-10-22.
//  Copyright (c) 2012年 intelligame. All rights reserved.
//

#include <iostream>
#include "MigAnimationCache.h"

//MigAnimationCache* MigAnimationCache::m_pSingleInstance = NULL;
//static SpriteFrameCache *_sharedSpriteFrameCache = nullptr;
static MigAnimationCache* m_pSingleInstance = NULL;

MigAnimationCache* MigAnimationCache::getShared()
{
    if(!m_pSingleInstance)
    {
        m_pSingleInstance = new MigAnimationCache();
    }
    return m_pSingleInstance;
}

MigAnimationCache::MigAnimationCache()
{
	m_animationCaches = CCArray::create();
	
	m_animationCaches->count();
}

MigAnimationCache::~ MigAnimationCache()
{
    CC_SAFE_RELEASE_NULL(m_animationCaches);
}

DQAnimationCache* MigAnimationCache::getAnimationCache(const char *xmlName)
{
    CCObject* pObj = NULL;
	if (NULL == m_animationCaches || 0 == m_animationCaches->count())
		return NULL;
    CCARRAY_FOREACH(m_animationCaches, pObj)
    {
        DQAnimationCache* animCache = (DQAnimationCache*)(pObj);
        if(strcmp(animCache->xmlName->getCString(), xmlName) == 0)
            return animCache;
    }
    return NULL;
}

void MigAnimationCache::addAnimationCache(DQAnimationCache *pCache)
{
    assert(pCache);
    assert(getAnimationCache(pCache->xmlName->getCString()) == NULL);
    m_animationCaches->addObject(pCache);
}

void MigAnimationCache::removeAnimationCache(const char *xmlName)
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_animationCaches, pObj)
    {
        DQAnimationCache* animCache = (DQAnimationCache*)(pObj);
        if(strcmp(animCache->xmlName->getCString(), xmlName) == 0)
        {
            m_animationCaches->removeObject(animCache);
            break;
        }
    }
}

void MigAnimationCache::removeAllCache()
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_animationCaches, pObj)
    {
        DQAnimationCache* animCache = (DQAnimationCache*)(pObj);
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(animCache->plistName->getCString());
    }
    m_animationCaches->removeAllObjects();
}

void MigAnimationCache::createAnimationFromCache(MigSpriteNode *pRoot, const char *xmlName,bool useBatchSprite)
{
    DQAnimationCache* cache = getAnimationCache(xmlName);
    assert(cache);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(cache->plistName->getCString());//载入素材
    m_pCurAnimationCache = cache;
    m_bUseBatchSprite = useBatchSprite;
    pRoot->setName(cache->name->getCString());
    pRoot->setXmlName(cache->xmlName->getCString());
    pRoot->setPlistName(cache->plistName->getCString());
    pRoot->setTextureName(cache->textureName->getCString());
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(cache->sprites, pObj)
    {
        createSpriteFromCache(pRoot, (SpriteCache*)(pObj));
    }
}

void MigAnimationCache::createSpriteFromCache(MigSpriteNode *pRoot, SpriteCache *pCache)
{
    MigSprite* pSprite = MigSprite::create();
    pSprite->setName(pCache->name->getCString());
    pRoot->addSprite(pSprite);
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(pCache->frames, pObj)
    {
        createFrameFromCache(pRoot,pSprite, (FrameCache*)(pObj));
    }
    pSprite->refreshFrameInfo();
}

void MigAnimationCache::createFrameFromCache(MigSpriteNode* root,MigSprite *pSprite, FrameCache *pCache)
{
    MigFrame* pFrame = NULL;
    pFrame = MigFrame::create();
    pFrame->setRectRed(pCache->rectRed);
    pFrame->setRectGreen(pCache->rectGreen);
    pFrame->setDuration(pCache->duration);
    pFrame->setFlag(pCache->flag);
    pSprite->addFrame(pFrame);
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(pCache->modules, pObj)
    {
        ModuleCache* moduleCache = (ModuleCache*)(pObj);
        CCSprite* pModuleSprite = CCSprite::createWithSpriteFrameName(moduleCache->name->getCString());
        CCSize size = pModuleSprite->getContentSize();
        pModuleSprite->setAnchorPoint(CCPointMake(0.5, 0.5));
        bool buf = true;
        switch (moduleCache->rotate) {
            case 0:
                break;
            case 90:
                buf = false;
                pModuleSprite->setRotation(90);
                break;
            case 180:
                pModuleSprite->setRotation(180);
                break;
            case 270:
                buf = false;
                pModuleSprite->setRotation(270);
                break;
            default:
                break;
        }
        switch (moduleCache->flip) {
            case 0:
                break;
            case 1:
                pModuleSprite->setScaleX(-1);
                break;
            case 2:
                pModuleSprite->setScaleY(-1);
                break;
            default:
                break;
        }
        pModuleSprite->setPositionX(moduleCache->offsetX + (buf ? size.width/2 : size.height/2));
        pModuleSprite->setPositionY(-moduleCache->offsetY - (buf ? size.height/2 : size.width/2));
        pFrame->addModuleSprite(pModuleSprite);
    }
}

void MigAnimationCache::purgeAll()
{
	if (!m_pSingleInstance)
	{
		return;
	}
	m_pSingleInstance->removeAllCache();
	delete m_pSingleInstance;
}
