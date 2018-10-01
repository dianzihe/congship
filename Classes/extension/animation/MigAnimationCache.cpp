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
static MigAnimationCache* _sharedSingleInstance = nullptr;

MigAnimationCache* MigAnimationCache::getShared()
{
	if (!_sharedSingleInstance) {
		_sharedSingleInstance = new MigAnimationCache();
		//_sharedSingleInstance->init();
    }
	return _sharedSingleInstance;
}

MigAnimationCache::MigAnimationCache()
{
	
	//m_animationCaches = CCArray::create();
	
	//m_animationCaches->count();
}

bool MigAnimationCache::init()
{
	m_animationCaches.reserve(20);
	return true;
}

MigAnimationCache::~ MigAnimationCache()
{
	log("9999999999999999999999999999999999");
    //CC_SAFE_RELEASE_NULL(m_animationCaches);
}

DQAnimationCache* MigAnimationCache::getAnimationCache(const char *xmlName)
{
    CCObject* pObj = NULL;
	//if (NULL == m_animationCaches || 0 == m_animationCaches->count())
	//	return NULL;
    //CCARRAY_FOREACH(m_animationCaches, pObj)
	for (auto& pObj : m_animationCaches) {
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
    m_animationCaches.push_back(pCache);
}

void MigAnimationCache::removeAnimationCache(const char *xmlName)
{
    //CCObject* pObj = NULL;
	vector<DQAnimationCache*>::iterator it = m_animationCaches.begin();
	for (; it != m_animationCaches.end(); ++it){
		DQAnimationCache* animCache = (DQAnimationCache*)(*it);
		if (strcmp(animCache->xmlName->getCString(), xmlName) == 0)
		{
			it = m_animationCaches.erase(it);
			break;
		}
	}
	/*
	for (auto& pObj : m_animationCaches) {
        DQAnimationCache* animCache = (DQAnimationCache*)(pObj);
        if(strcmp(animCache->xmlName->getCString(), xmlName) == 0)
        {
			m_animationCaches.erase()
			m_animationCaches.erase(2);
			//m_animationCaches.erase();
            break;
        }
    }
	*/
}

void MigAnimationCache::removeAllCache()
{
    CCObject* pObj = NULL;
	for (auto& pObj : m_animationCaches) {
        DQAnimationCache* animCache = (DQAnimationCache*)(pObj);
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(animCache->plistName->getCString());
    }
    m_animationCaches.clear();
}

void MigAnimationCache::createAnimationFromCache(MigSpriteNode *pRoot, const char *xmlName,bool useBatchSprite)
{
	log("---1");
    DQAnimationCache* cache = getAnimationCache(xmlName);
    assert(cache);
	log("---2");

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(cache->plistName->getCString());//载入素材
	log("---3");

	//m_pCurAnimationCache = cache;
    m_bUseBatchSprite = useBatchSprite;
    pRoot->setName(cache->name->getCString());
    pRoot->setXmlName(cache->xmlName->getCString());
    pRoot->setPlistName(cache->plistName->getCString());
    pRoot->setTextureName(cache->textureName->getCString());
	log("---4");

	//CCObject* pObj = NULL;
	for (auto& pObj : m_animationCaches) {
        createSpriteFromCache(pRoot, (SpriteCache*)(pObj));
    }
}

void MigAnimationCache::createSpriteFromCache(MigSpriteNode *pRoot, SpriteCache *pCache)
{
	log("----------1");

    MigSprite* pSprite = MigSprite::create();
    pSprite->setName(pCache->name->getCString());
	log("----------2");

	pRoot->addSprite(pSprite);

	CCObject* pObj = NULL;
	log("----------3");

    //CCARRAY_FOREACH(pCache->frames, pObj)
	for (auto& pObj : pCache->frames) {
		log("----------3---1");
        createFrameFromCache(pRoot, pSprite, (FrameCache*)(pObj));
    }
	log("----------4");

    pSprite->refreshFrameInfo();
}

void MigAnimationCache::createFrameFromCache(MigSpriteNode* root,MigSprite *pSprite, FrameCache *pCache)
{
    MigFrame* pFrame = NULL;
	log("===============1");
    pFrame = MigFrame::create();
    pFrame->setRectRed(pCache->rectRed);
    pFrame->setRectGreen(pCache->rectGreen);
    pFrame->setDuration(pCache->duration);
    pFrame->setFlag(pCache->flag);
	log("===============2-->%d", pSprite->getAllFrames()->count());
	pSprite->getAllFrames()->count();
    pSprite->addFrame(pFrame);
    CCObject* pObj = NULL;
	log("===============3");
	for (auto& pObj : pCache->modules) {
//    CCARRAY_FOREACH(pCache->modules, pObj)
//    {
		log("===============4");
        ModuleCache* moduleCache = (ModuleCache*)(pObj);
        CCSprite* pModuleSprite = CCSprite::createWithSpriteFrameName(moduleCache->name->getCString());
        CCSize size = pModuleSprite->getContentSize();
		log("===============5");
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
		log("===============6");
        pModuleSprite->setPositionX(moduleCache->offsetX + (buf ? size.width/2 : size.height/2));
        pModuleSprite->setPositionY(-moduleCache->offsetY - (buf ? size.height/2 : size.width/2));
		log("===============7");
        pFrame->addModuleSprite(pModuleSprite);
		log("===============8");
    }
}

void MigAnimationCache::purgeAll()
{
	/*
	if (!m_pSingleInstance)
	{
		return;
	}
	*/
	//m_pSingleInstance->removeAllCache();
	//delete m_pSingleInstance;
}
