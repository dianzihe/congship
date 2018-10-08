//
//  MigAnimationLoader.cpp
//  SanguoHeros
//
//  Created by ��� ��� on 12-10-12.
//  Copyright (c) 2012��� intelligame. All rights reserved.
//

#include <iostream>
#include "MigAnimationLoader.h"
//#include "../io/UIFeiDiaoLayer.h"


MigAnimationLoader::MigAnimationLoader(const char* path) :pAnimation(NULL), pAnimationCache(NULL), pSpriteCache(NULL), pFrameCache(NULL), pModuleCache(NULL), bufRect(), m_sPath(NULL)
{
	m_sPath = new CCString(path ? path : "");
}

MigAnimationLoader::~MigAnimationLoader()
{
	//CC_SAFE_RELEASE_NULL(m_sPath);
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

bool MigAnimationLoader::load(MigSpriteNode* node, const char* pXmlFile, const char* plistFile, bool useBatchSprite)
{
	assert(pXmlFile && plistFile);
	CCString* xmlName = CCString::createWithFormat("%s%s", m_sPath->getCString(), pXmlFile);
	CCString* plistName = CCString::createWithFormat("%s%s", m_sPath->getCString(), plistFile);
	CCString* textureName = CCString::createWithFormat("%s%s", m_sPath->getCString(), getTextureNameFromPlist(plistName->getCString()));

	DQAnimationCache* cache = MigAnimationCache::getShared()->getAnimationCache(xmlName->getCString());
	if (cache){
		if (node) {
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
	if (node) {
		//MigAnimationCache::getShared()->createAnimationFromCache(node, xmlName->getCString(), useBatchSprite);
	}

	//CC_SAFE_RELEASE_NULL(pAnimationCache);
	return true;
}

const char* MigAnimationLoader::hel009(const char* path)
{
	std::string fullpath = FileUtils::getInstance()->fullPathForFilename(path);
	unsigned char* pData = NULL;
	ssize_t len = 0;
	pData = FileUtils::getInstance()->getFileData(fullpath.c_str(), "rb", &len);
	//std::string destpath = FileUtils::getInstance()->getWritablePath();
	std::string destpath = fullpath + "dq";
	//CCFileUtils::sharedFileUtils()->getWriteablePath();
	//;
	//std::string destpath = FileUtils::getInstance()->getWritablePath();
	std::string buf = path;
	{
		for (int i = 0; i < buf.size(); i++)
		{
			if (buf[i] == '/')
				buf[i] = '_';
		}
	}
	destpath += buf;
	log("copy data from [%s] to [%s].", fullpath.c_str()
		, destpath.c_str());
	FILE* fp = fopen(destpath.c_str(), "w");
	fwrite(pData, sizeof(char), len, fp);
	fclose(fp);
	delete pData;
	pData = NULL;
	return destpath.c_str();
}

bool MigAnimationLoader::loadBin(MigSpriteNode *node, const char *pBinFile, const char *plistFile, bool useBatchSprite)
{
	log("MigAnimationLoader::loadBin-start1");
	assert(pBinFile && plistFile);
	log("MigAnimationLoader::loadBin-start2");
	CCString* xmlName = CCString::createWithFormat("%s%s", m_sPath->getCString(), pBinFile);
	CCString* plistName = CCString::createWithFormat("%s%s", m_sPath->getCString(), plistFile);
	CCString* textureName = CCString::createWithFormat("%s%s", m_sPath->getCString(), getTextureNameFromPlist(plistName->getCString()));

	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile(plistName->getCString());

	//DQAnimationCache* cache = MigAnimationCache::getShared()->getAnimationCache(xmlName->getCString());
	/*
	if(cache){
	if(node) {
	MigAnimationCache::getShared()->createAnimationFromCache(node, xmlName->getCString(), useBatchSprite);
	}
	return true;
	}

	cache = new DQAnimationCache();
	cache->plistName = plistName;
	cache->xmlName = xmlName;
	cache->textureName = textureName;
	*/
	//CC_SAFE_RETAIN(plistName);
	//CC_SAFE_RETAIN(xmlName);
	//CC_SAFE_RETAIN(textureName);
	//load animation from bin
	{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		const char* full_name = UIFeiDiaoLayer::hel009(xmlName->getCString());
#else
		//const char* full_name = hel009(xmlName->getCString());
		//const char* full_name = FileUtils::getInstance()->fullPathForFilename(xmlName->getCString());
		auto fileUtiles = FileUtils::getInstance();
		auto fragmentFullPath = fileUtiles->fullPathForFilename(xmlName->getCString());
#endif
		FILE* pfile = fopen(fragmentFullPath.c_str(), "rb");
		//assert(pfile);
		if (NULL == pfile)
			log("=======================================%s", fragmentFullPath.c_str());
		log("MigAnimationLoader::loadBin-0");
		//bin info
		sdafwefc(pfile);
		//animation info
		string animationName = sdafwefc(pfile);
		log("cache-name=%s\n", animationName.c_str());
		//sprite count
		int spriteCount = hel001(pfile);
		log("spriteCount=%d", spriteCount);
		for (int i = 0; i < spriteCount; i++)
		{
#if 0
			Vector<SpriteFrame*> animFrames(15);
			char str[100] = { 0 };
			for (int i = 1; i < 15; i++)
			{
				sprintf(str, "grossini_dance_%02d.png", i);
				auto frame = frameCache->getSpriteFrameByName(str);

				animFrames.pushBack(frame);
			}

			auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);

			// Add an animation to the Cache
			AnimationCache::getInstance()->addAnimation(animation, "dance");
#endif			
			/////////////////////////////////////////////////////////////////
			//SpriteCache* spriteCache = new SpriteCache();
			//spriteCache->name = new CCString(sdafwefc(pfile));
			string actionName = sdafwefc(pfile);
			log("spriteCache->name=%s", actionName.c_str());
			//frame count
			int frameCount = hel001(pfile);
			log("frameCount=%d", frameCount);

			for (int j = 0; j < frameCount; j++)
			{
				//log("------1");
				//FrameCache* frameCache = new FrameCache();
				//frameCache->duration = hel001(pfile);
				//frameCache->flag = hel001(pfile);
				//tile count
				int duration = hel001(pfile);
				int flag = hel001(pfile);
				int tileCount = hel001(pfile);

				Vector<SpriteFrame*> animFrames(30);
				for (int k = 0; k < tileCount; k++)
				{
					/*
					ModuleCache* moduleCache = new ModuleCache();
					moduleCache->name = new CCString(sdafwefc(pfile));

					moduleCache->offsetX = hel001(pfile);
					moduleCache->offsetY = hel001(pfile);
					moduleCache->flip = hel001(pfile);
					moduleCache->rotate = hel001(pfile);
					*/
					string fileName = sdafwefc(pfile);
					int offsetX = hel001(pfile);
					int offsetY = hel001(pfile);
					int flip = hel001(pfile);
					int rotate = hel001(pfile);

					log("------2- X:[%3d] Y:[%3d] Flip:[%3d] Rotate:[%3d] Duration[%3d]-%s",
						offsetX,
						offsetY,
						flip,
						rotate,
						duration,
						fileName.c_str());

					//log("------2---%d", frameCache->modules.size());
					//frameCache->modules.push_back(moduleCache);
					//CC_SAFE_RELEASE_NULL(moduleCache);
					//auto frame = frameCache->getSpriteFrameByName(moduleCache->name->getCString());
					//animFrames.pushBack(frame);

					auto frame = frameCache->getSpriteFrameByName(fileName);
					frame->setOffset(Vec2(offsetX, offsetY));
					frame->setRotated(rotate);
					//frame->setOffset(Vec2(offsetX, offsetY));

					animFrames.pushBack(frame);

					//ModuleCache* moduleCache = (ModuleCache*)(pObj);
					Sprite* pModuleSprite = Sprite::createWithSpriteFrameName(fileName);
					Size size = pModuleSprite->getContentSize();
					pModuleSprite->setAnchorPoint(Point(0.5, 0.5));
					bool buf = true;
					switch (rotate) {
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
					switch (flip) {
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
					pModuleSprite->setPositionX(offsetX + (buf ? size.width / 2 : size.height / 2));
					pModuleSprite->setPositionY(-offsetY - (buf ? size.height / 2 : size.width / 2));
					//pFrame->addModuleSprite(pModuleSprite);
				}

				auto animation = Animation::createWithSpriteFrames(animFrames, duration);
				// Add an animation to the Cache
				log("add -----> %s", (animationName + actionName + to_string(j)).c_str());
				AnimationCache::getInstance()->addAnimation(animation, animationName + actionName + to_string(j));

				int rx = hel001(pfile);
				int ry = hel001(pfile);
				int rw = hel001(pfile);
				int rh = hel001(pfile);
				//log("------3");
				//frameCache->rectRed.setRect(rx, -ry-rh, rw, rh);
				int gx = hel001(pfile);
				int gy = hel001(pfile);
				int gw = hel001(pfile);
				int gh = hel001(pfile);
				//log("------4");
				//frameCache->rectGreen.setRect(gx, -gy-gh, gw, gh);
				//spriteCache->frames.push_back(frameCache);

				//CC_SAFE_RELEASE_NULL(frameCache);
			}
			//log("------6---%d", spriteCache->frames.size());
			//cache->sprites.push_back(spriteCache);
			//CC_SAFE_RELEASE_NULL(spriteCache);
		}
		//log("------7---%d", cache->sprites.size());
		fclose(pfile);
	}
	//MigAnimationCache::getShared()->addAnimationCache(cache);
	/*
	if(node) {
	MigAnimationCache::getShared()->createAnimationFromCache(node, xmlName->getCString(), useBatchSprite);
	}
	*/
	log("MigAnimationLoader::loadBin-end");
	//CC_SAFE_RELEASE_NULL(cache);
	return true;
}

void MigAnimationLoader::onResolveElement(const char *name)
{
	if (strcmp(name, "animation") == 0)
	{
		curResolveType = ResolveAnimation;
		pAnimationCache = new DQAnimationCache();
	}
	else if (strcmp(name, "sprite") == 0)
	{
		curResolveType = ResolveSprite;
		pSpriteCache = new SpriteCache();
		pAnimationCache->sprites.push_back(pSpriteCache);
		//pSpriteCache->release();
	}
	else if (strcmp(name, "frame") == 0)
	{
		curResolveType = ResolveFrame;
		pFrameCache = new FrameCache();
		pSpriteCache->frames.push_back(pFrameCache);
		//pFrameCache->release();
	}
	else if (strcmp(name, "module") == 0)
	{
		curResolveType = ResolveModule;
		pModuleCache = new ModuleCache();
		pFrameCache->modules.push_back(pModuleCache);
		//pModuleCache->release();
	}
	else if (strcmp(name, "red_rect") == 0)
	{
		curResolveType = ResolveRectRed;
		bufRect = CCRectMake(0, 0, 0, 0);
	}
	else if (strcmp(name, "green_rect") == 0)
	{
		curResolveType = ResolveRectGreen;
		bufRect = CCRectMake(0, 0, 0, 0);
	}
}

void MigAnimationLoader::onResolveElementEnd(const char *name)
{
	if (strcmp(name, "animation") == 0)
	{
		curResolveType = ResolveNothing;
	}
	else if (strcmp(name, "sprite") == 0)
	{
		curResolveType = ResolveNothing;
	}
	else if (strcmp(name, "frame") == 0)
	{
		curResolveType = ResolveNothing;
	}
	else if (strcmp(name, "module") == 0)
	{
		curResolveType = ResolveNothing;
	}
	else if (strcmp(name, "red_rect") == 0)
	{
		curResolveType = ResolveNothing;
		float bufy = bufRect.origin.y - bufRect.size.height;
		bufRect.origin.y = bufy;
		pFrameCache->rectRed = bufRect;
	}
	else if (strcmp(name, "green_rect") == 0)
	{
		curResolveType = ResolveNothing;
		float bufy = bufRect.origin.y - bufRect.size.height;
		bufRect.origin.y = bufy;
		pFrameCache->rectGreen = bufRect;
	}
}

void MigAnimationLoader::onResolveAnimationAttribute(const char *name, const char *value)
{
	if (strcmp(name, "name") == 0)
	{
		pAnimationCache->name = new CCString(value);
	}
}

void MigAnimationLoader::onResolveSpriteAttribute(const char *name, const char *value)
{
	if (strcmp(name, "name") == 0)
	{
		pSpriteCache->name = new CCString(value);
	}
}

void MigAnimationLoader::onResolveFrameAttribute(const char *name, const char *value)
{
	if (strcmp(name, "duration") == 0)
	{
		pFrameCache->duration = atoi(value);
	}
	else if (strcmp(name, "flag") == 0)
	{
		pFrameCache->flag = atoi(value);
	}
}

void MigAnimationLoader::onResolveModuleAttribute(const char *name, const char *value)
{
	if (strcmp(name, "name") == 0)
	{
		pModuleCache->name = new CCString(value);
	}
	else if (strcmp(name, "x") == 0)
	{
		pModuleCache->offsetX = atoi(value);
	}
	else if (strcmp(name, "y") == 0)
	{
		pModuleCache->offsetY = atoi(value);
	}
	else if (strcmp(name, "flip") == 0)
	{
		pModuleCache->flip = atoi(value);
	}
	else if (strcmp(name, "rotate") == 0)
	{
		pModuleCache->rotate = atoi(value);
	}
}

void MigAnimationLoader::onResolveRectRedAttribute(const char *name, const char *value)
{
	if (strcmp(name, "x") == 0)
	{
		bufRect.origin.x = atoi(value);
	}
	else if (strcmp(name, "y") == 0)
	{
		bufRect.origin.y = -atoi(value);
	}
	else if (strcmp(name, "width") == 0)
	{
		bufRect.size.width = atoi(value);
	}
	else if (strcmp(name, "height") == 0)
	{
		bufRect.size.height = atoi(value);
	}
}

void MigAnimationLoader::onResolveRectGreenAttribute(const char *name, const char *value)
{
	if (strcmp(name, "x") == 0)
	{
		bufRect.origin.x = atoi(value);
	}
	else if (strcmp(name, "y") == 0)
	{
		bufRect.origin.y = -atoi(value);
	}
	else if (strcmp(name, "width") == 0)
	{
		bufRect.size.width = atoi(value);
	}
	else if (strcmp(name, "height") == 0)
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

/*

bool MigAnimationLoader::loadBin(MigSpriteNode *node, const char *pBinFile, const char *plistFile, bool useBatchSprite)
{
log("MigAnimationLoader::loadBin-start1");
assert(pBinFile && plistFile);
log("MigAnimationLoader::loadBin-start2");
CCString* xmlName = CCString::createWithFormat("%s%s", m_sPath->getCString(), pBinFile);
CCString* plistName = CCString::createWithFormat("%s%s", m_sPath->getCString(), plistFile);
CCString* textureName = CCString::createWithFormat("%s%s", m_sPath->getCString(), getTextureNameFromPlist(plistName->getCString()));
DQAnimationCache* cache = MigAnimationCache::getShared()->getAnimationCache(xmlName->getCString());
if(cache){
if(node) {
MigAnimationCache::getShared()->createAnimationFromCache(node, xmlName->getCString(), useBatchSprite);
}
return true;
}
cache = new DQAnimationCache();
cache->plistName = plistName;
cache->xmlName = xmlName;
cache->textureName = textureName;
//CC_SAFE_RETAIN(plistName);
//CC_SAFE_RETAIN(xmlName);
//CC_SAFE_RETAIN(textureName);
//load animation from bin
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
const char* full_name = UIFeiDiaoLayer::hel009(xmlName->getCString());
#else
//const char* full_name = hel009(xmlName->getCString());
//const char* full_name = FileUtils::getInstance()->fullPathForFilename(xmlName->getCString());
auto fileUtiles = FileUtils::getInstance();
auto fragmentFullPath = fileUtiles->fullPathForFilename(xmlName->getCString());
#endif
FILE* pfile = fopen(fragmentFullPath.c_str(), "rb");
//assert(pfile);
if (NULL == pfile)
log("=======================================%s", fragmentFullPath.c_str());
log("MigAnimationLoader::loadBin-0");
//bin info
sdafwefc(pfile);
//animation info
cache->name = new CCString(sdafwefc(pfile));
log("cache-name=%s\n", cache->name->getCString());
//sprite count
int spriteCount = hel001(pfile);
log("spriteCount=%d", spriteCount);
for (int i = 0; i < spriteCount; i++)
{
SpriteCache* spriteCache = new SpriteCache();
spriteCache->name = new CCString(sdafwefc(pfile));
log("spriteCache->name=%s", spriteCache->name->getCString());
//frame count
int frameCount = hel001(pfile);
log("frameCount=%d", frameCount);
for (int j = 0; j < frameCount; j++)
{
//log("------1");
FrameCache* frameCache = new FrameCache();
frameCache->duration = hel001(pfile);
frameCache->flag = hel001(pfile);
//tile count
int tileCount = hel001(pfile);
for (int k = 0; k < tileCount; k++)
{
//log("------2");

ModuleCache* moduleCache = new ModuleCache();
moduleCache->name = new CCString(sdafwefc(pfile));
log("------2--%s", moduleCache->name->getCString());
moduleCache->offsetX = hel001(pfile);
moduleCache->offsetY = hel001(pfile);
moduleCache->flip = hel001(pfile);
moduleCache->rotate = hel001(pfile);
//log("------2---%d", frameCache->modules.size());
frameCache->modules.push_back(moduleCache);
//CC_SAFE_RELEASE_NULL(moduleCache);
}
int rx = hel001(pfile);
int ry = hel001(pfile);
int rw = hel001(pfile);
int rh = hel001(pfile);
//log("------3");
frameCache->rectRed.setRect(rx, -ry-rh, rw, rh);
int gx = hel001(pfile);
int gy = hel001(pfile);
int gw = hel001(pfile);
int gh = hel001(pfile);
//log("------4");
frameCache->rectGreen.setRect(gx, -gy-gh, gw, gh);
spriteCache->frames.push_back(frameCache);
log("--------------------------5");
//CC_SAFE_RELEASE_NULL(frameCache);
}
log("------6---%d", spriteCache->frames.size());
cache->sprites.push_back(spriteCache);
//CC_SAFE_RELEASE_NULL(spriteCache);
}
log("------7---%d", cache->sprites.size());
fclose(pfile);
}
log("------8");
MigAnimationCache::getShared()->addAnimationCache(cache);
log("------9");
if(node) {
MigAnimationCache::getShared()->createAnimationFromCache(node, xmlName->getCString(), useBatchSprite);
}
log("MigAnimationLoader::loadBin-end");
//CC_SAFE_RELEASE_NULL(cache);
return true;
}
*/