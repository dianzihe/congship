//
//  MigAnimationLoader.cpp
//  SanguoHeros
//
//  Created by ��� ��� on 12-10-12.
//  Copyright (c) 2012��� intelligame. All rights reserved.
//

#include <iostream>
#include "MigAnimationLoader.h"
#include "../io/UIFeiDiaoLayer.h"


MigAnimationLoader::MigAnimationLoader(const char* path):pAnimation(NULL),pAnimationCache(NULL),pSpriteCache(NULL),pFrameCache(NULL),pModuleCache(NULL),bufRect(),m_sPath(NULL)
{
    m_sPath = new CCString(path ? path : "");
}

MigAnimationLoader::~ MigAnimationLoader()
{
    CC_SAFE_RELEASE_NULL(m_sPath);
}

const char* getTextureNameFromPlist(const char* plist)
{
	std::string pszPath = FileUtils::getInstance()->fullPathForFilename(plist);
    //const char *pszPath = FileUtils::getInstance()->fullPathFromRelativePath(plist);
    CCDictionary *dict = CCDictionary::createWithContentsOfFileThreadSafe(pszPath.c_str());
    CCDictionary* metadataDict = (CCDictionary*)dict->objectForKey("metadata");
    dict->autorelease();
    if (metadataDict)
    {
        // try to read  texture file name from meta data
        return metadataDict->valueForKey("textureFileName")->getCString();
    }
    return NULL;
}

bool MigAnimationLoader::load(MigSpriteNode* node,const char* pXmlFile,const char* plistFile,bool useBatchSprite)
{
    assert(pXmlFile && plistFile);
    CCString* xmlName = CCString::createWithFormat("%s%s",m_sPath->getCString(),pXmlFile);
    CCString* plistName = CCString::createWithFormat("%s%s",m_sPath->getCString(),plistFile);
    CCString* textureName = CCString::createWithFormat("%s%s",m_sPath->getCString(),getTextureNameFromPlist(plistName->getCString()));
    AnimationCache* cache = MigAnimationCache::getShared()->getAnimationCache(xmlName->getCString());
    if(cache){
        if(node)
        {
            MigAnimationCache::getShared()->createAnimationFromCache(node, xmlName->getCString(), useBatchSprite);
        }
        return true;
    }
    curResolveType = ResolveNothing;
    XmlResolver* resolver = new XmlResolver();
    resolver->loadXml(xmlName->getCString(), this);
    delete resolver;
    textureName->retain();
    xmlName->retain();
    plistName->retain();
    pAnimationCache->textureName = textureName;
    pAnimationCache->xmlName = xmlName;
    pAnimationCache->plistName = plistName;
    MigAnimationCache::getShared()->addAnimationCache(pAnimationCache);
    if(node)
    {
        MigAnimationCache::getShared()->createAnimationFromCache(node, xmlName->getCString(), useBatchSprite);
    }
    CC_SAFE_RELEASE_NULL(pAnimationCache);
    return true;
}

bool MigAnimationLoader::loadBin(MigSpriteNode *node, const char *pBinFile, const char *plistFile, bool useBatchSprite)
{
	CCLog("MigAnimationLoader::loadBin-start1");
    assert(pBinFile && plistFile);
	CCLog("MigAnimationLoader::loadBin-start2");
    CCString* xmlName = CCString::createWithFormat("%s%s",m_sPath->getCString(),pBinFile);
    CCString* plistName = CCString::createWithFormat("%s%s",m_sPath->getCString(),plistFile);
    CCString* textureName = CCString::createWithFormat("%s%s",m_sPath->getCString(),getTextureNameFromPlist(plistName->getCString()));
    AnimationCache* cache = MigAnimationCache::getShared()->getAnimationCache(xmlName->getCString());
    if(cache){
        if(node)
        {
            MigAnimationCache::getShared()->createAnimationFromCache(node, xmlName->getCString(), useBatchSprite);
        }
        return true;
    }
    cache = new AnimationCache();
    cache->plistName = plistName;
    cache->xmlName = xmlName;
    cache->textureName = textureName;
    CC_SAFE_RETAIN(plistName);
    CC_SAFE_RETAIN(xmlName);
    CC_SAFE_RETAIN(textureName);
    //load animation from bin
    {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        const char* full_name = UIFeiDiaoLayer::hel009(xmlName->getCString());
#else
        const char* full_name = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(xmlName->getCString());
#endif
        FILE* pfile = fopen(full_name, "rb");
        assert(pfile);
        CCLog("MigAnimationLoader::loadBin-0");
        //bin info
        UIFeiDiaoLayer::sdafwefc(pfile);
        //animation info
        cache->name = new CCString(UIFeiDiaoLayer::sdafwefc(pfile));
        //sprite count
        int spriteCount = UIFeiDiaoLayer::hel001(pfile);
        for (int i = 0; i < spriteCount; i++)
        {
            SpriteCache* spriteCache = new SpriteCache();
            spriteCache->name = new CCString(UIFeiDiaoLayer::sdafwefc(pfile));
            //frame count
            int frameCount = UIFeiDiaoLayer::hel001(pfile);
            for (int j = 0; j < frameCount; j++)
            {
                FrameCache* frameCache = new FrameCache();
                frameCache->duration = UIFeiDiaoLayer::hel001(pfile);
                frameCache->flag = UIFeiDiaoLayer::hel001(pfile);
                //tile count
                int tileCount = UIFeiDiaoLayer::hel001(pfile);
                for (int k = 0; k < tileCount; k++)
                {
                    ModuleCache* moduleCache = new ModuleCache();
                    moduleCache->name = new CCString(UIFeiDiaoLayer::sdafwefc(pfile));
                    moduleCache->offsetX = UIFeiDiaoLayer::hel001(pfile);
                    moduleCache->offsetY = UIFeiDiaoLayer::hel001(pfile);
                    moduleCache->flip = UIFeiDiaoLayer::hel001(pfile);
                    moduleCache->rotate = UIFeiDiaoLayer::hel001(pfile);
                    frameCache->modules->addObject(moduleCache);
                    CC_SAFE_RELEASE_NULL(moduleCache);
                }
                int rx = UIFeiDiaoLayer::hel001(pfile);
                int ry = UIFeiDiaoLayer::hel001(pfile);
                int rw = UIFeiDiaoLayer::hel001(pfile);
                int rh = UIFeiDiaoLayer::hel001(pfile);
                frameCache->rectRed.setRect(rx, -ry-rh, rw, rh);
                int gx = UIFeiDiaoLayer::hel001(pfile);
                int gy = UIFeiDiaoLayer::hel001(pfile);
                int gw = UIFeiDiaoLayer::hel001(pfile);
                int gh = UIFeiDiaoLayer::hel001(pfile);
                frameCache->rectGreen.setRect(gx, -gy-gh, gw, gh);
                spriteCache->frames->addObject(frameCache);
                CC_SAFE_RELEASE_NULL(frameCache);
            }
            cache->sprites->addObject(spriteCache);
            CC_SAFE_RELEASE_NULL(spriteCache);
        }
        fclose(pfile);
    }
    MigAnimationCache::getShared()->addAnimationCache(cache);
    if(node)
    {
        MigAnimationCache::getShared()->createAnimationFromCache(node, xmlName->getCString(), useBatchSprite);
    }
	CCLog("MigAnimationLoader::loadBin-end");
    CC_SAFE_RELEASE_NULL(cache);
    return true;
}

void MigAnimationLoader::onResolveElement(const char *name)
{
    if(strcmp(name, "animation") == 0)
    {
        curResolveType = ResolveAnimation;
        pAnimationCache = new AnimationCache();
    }
    else if(strcmp(name, "sprite") == 0)
    {
        curResolveType = ResolveSprite;
        pSpriteCache = new SpriteCache();
        pAnimationCache->sprites->addObject(pSpriteCache);
        pSpriteCache->release();
    }
    else if(strcmp(name, "frame") == 0)
    {
        curResolveType = ResolveFrame;
        pFrameCache = new FrameCache();
        pSpriteCache->frames->addObject(pFrameCache);
        pFrameCache->release();
    }
    else if(strcmp(name, "module") == 0)
    {
        curResolveType = ResolveModule;
        pModuleCache = new ModuleCache();
        pFrameCache->modules->addObject(pModuleCache);
        pModuleCache->release();
    }
    else if(strcmp(name, "red_rect") == 0)
    {
        curResolveType = ResolveRectRed;
        bufRect = CCRectMake(0, 0, 0, 0);
    }
    else if(strcmp(name, "green_rect") == 0)
    {
        curResolveType = ResolveRectGreen;
        bufRect = CCRectMake(0, 0, 0, 0);
    }
}

void MigAnimationLoader::onResolveElementEnd(const char *name)
{
    if(strcmp(name, "animation") == 0)
    {
        curResolveType = ResolveNothing;
    }
    else if(strcmp(name, "sprite") == 0)
    {
        curResolveType = ResolveNothing;
    }
    else if(strcmp(name, "frame") == 0)
    {
        curResolveType = ResolveNothing;
    }
    else if(strcmp(name, "module") == 0)
    {
        curResolveType = ResolveNothing;
    }
    else if(strcmp(name, "red_rect") == 0)
    {
        curResolveType = ResolveNothing;
        float bufy = bufRect.origin.y - bufRect.size.height;
        bufRect.origin.y = bufy;
        pFrameCache->rectRed = bufRect;
    }
    else if(strcmp(name, "green_rect") == 0)
    {
        curResolveType = ResolveNothing;
        float bufy = bufRect.origin.y - bufRect.size.height;
        bufRect.origin.y = bufy;
        pFrameCache->rectGreen = bufRect;
    }
}

void MigAnimationLoader::onResolveAnimationAttribute(const char *name, const char *value)
{
    if(strcmp(name, "name") == 0)
    {
        pAnimationCache->name = new CCString(value);
    }
}

void MigAnimationLoader::onResolveSpriteAttribute(const char *name, const char *value)
{
    if(strcmp(name, "name") == 0)
    {
        pSpriteCache->name = new CCString(value);
    }
}

void MigAnimationLoader::onResolveFrameAttribute(const char *name, const char *value)
{
    if(strcmp(name, "duration") == 0)
    {
        pFrameCache->duration = atoi(value);
    }
    else if(strcmp(name, "flag") == 0)
    {
        pFrameCache->flag = atoi(value);
    }
}

void MigAnimationLoader::onResolveModuleAttribute(const char *name, const char *value)
{
    if(strcmp(name, "name") == 0)
    {
        pModuleCache->name = new CCString(value);
    }
    else if(strcmp(name, "x") == 0)
    {
        pModuleCache->offsetX = atoi(value);
    }
    else if(strcmp(name, "y") == 0)
    {
        pModuleCache->offsetY = atoi(value);
    }
    else if(strcmp(name, "flip") == 0)
    {
        pModuleCache->flip = atoi(value);
    }
    else if(strcmp(name, "rotate") == 0)
    {
        pModuleCache->rotate = atoi(value);
    }
}

void MigAnimationLoader::onResolveRectRedAttribute(const char *name, const char *value)
{
    if(strcmp(name, "x") == 0)
    {
        bufRect.origin.x = atoi(value);
    }
    else if(strcmp(name, "y") == 0)
    {
        bufRect.origin.y = -atoi(value);
    }
    else if(strcmp(name, "width") == 0)
    {
        bufRect.size.width = atoi(value);
    }
    else if(strcmp(name, "height") == 0)
    {
        bufRect.size.height = atoi(value);
    }
}

void MigAnimationLoader::onResolveRectGreenAttribute(const char *name, const char *value)
{
    if(strcmp(name, "x") == 0)
    {
        bufRect.origin.x = atoi(value);
    }
    else if(strcmp(name, "y") == 0)
    {
        bufRect.origin.y = -atoi(value);
    }
    else if(strcmp(name, "width") == 0)
    {
        bufRect.size.width = atoi(value);
    }
    else if(strcmp(name, "height") == 0)
    {
        bufRect.size.height = atoi(value);
    }
}

void MigAnimationLoader::onResolveAttribute(const char *name, const char *value)
{
    switch (curResolveType) {
        case ResolveAnimation:
            onResolveAnimationAttribute(name, value);
            break;
        case ResolveSprite:
            onResolveSpriteAttribute(name, value);
            break;
        case ResolveFrame:
            onResolveFrameAttribute(name, value);
            break;
        case ResolveModule:
            onResolveModuleAttribute(name, value);
            break;
        case ResolveRectRed:
            onResolveRectRedAttribute(name, value);
            break;
        case ResolveRectGreen:
            onResolveRectGreenAttribute(name, value);
        default:
            break;
    }
}
