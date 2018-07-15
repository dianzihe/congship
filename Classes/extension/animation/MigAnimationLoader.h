//
//  MigAnimationLoader.h
//  SanguoHeros
//
//  Created by 伟 李 on 12-10-12.
//  Copyright (c) 2012年 intelligame. All rights reserved.
//

#ifndef SanguoHeros_MigAnimationLoader_h
#define SanguoHeros_MigAnimationLoader_h

#include "cocos2d.h"
#include "MigAnimation.h"
#include "../xml/XmlResolver.h"
#include "MigAnimationCache.h"

USING_NS_CC;

class MigAnimationLoader :public Ref, public XmlResolverListener
{
public:
    MigAnimationLoader(const char* path);
    
    virtual ~ MigAnimationLoader();
    
    virtual bool load(MigSpriteNode* node,const char* pXmlFile,const char* plistFile,bool useBatchSprite);
    virtual bool loadBin(MigSpriteNode* node,const char* binFile,const char* plistFile,bool useBatchSprite);
    
    virtual void onResolveElement(const char* name);
    virtual void onResolveElementEnd(const char* name);
    virtual void onResolveAttribute(const char* name,const char* value);
    
    virtual void onResolveAnimationAttribute(const char* name,const char* value);
    virtual void onResolveSpriteAttribute(const char* name,const char* value);
    virtual void onResolveFrameAttribute(const char* name,const char* value);
    virtual void onResolveModuleAttribute(const char* name,const char* value);
    virtual void onResolveRectRedAttribute(const char* name,const char* value);
    virtual void onResolveRectGreenAttribute(const char* name,const char* value);
    
    static const char* readTextureNameFromPlist(const char* plist);
    
protected:
    MigSpriteNode* pAnimation;
    AnimationCache* pAnimationCache;
    SpriteCache* pSpriteCache;
    FrameCache* pFrameCache;
    ModuleCache* pModuleCache;
    CCRect bufRect;
    CCString* m_sPath;
    enum
    {
        ResolveNothing,ResolveAnimation,ResolveSprite,ResolveFrame,ResolveModule,ResolveRectRed,ResolveRectGreen
    } curResolveType;
};
#endif
