//
//  MigAnimation.cpp
//  SanguoHeros
//
//  Created by 伟 李 on 12-10-12.
//  Copyright (c) 2012年 intelligame. All rights reserved.
//

#include <iostream>
#include "MigAnimation.h"
#include "MigAnimationLoader.h"

MigSpriteNode::MigSpriteNode() : m_pCurSprite(NULL),m_pCurFrame(NULL),pDefaultSprite(NULL),m_delayPerUnit(DEFAULT_DELAY_PER_FRAME),m_elapsed(0),m_spriteTotalDuration(0),m_loop(0),m_excutedLoop(0),m_bOnSpriteEndSkipToDefault(true),m_nOpacity(255),m_sColor(ccWHITE),m_pKeyFrameEventHandle(NULL),m_keyFrameEventParameter(),m_bAnimationDone(false),m_pSprites(new CCArray()),m_bFlipX(false),m_bFlipY(false),m_bNewFrame(false),m_pDrawNode(NULL),m_sTextureName(NULL)
{
    m_blendFunc = DEFAULT_BLEND_FUNC;
}

MigSpriteNode::~ MigSpriteNode()
{
    CC_SAFE_RELEASE_NULL(m_pSprites);
}

void MigSpriteNode::retain()
{
    CCNode::retain();
//    CCLog("MigSpriteNode::retain()-ref=%d.",retainCount());
}

void MigSpriteNode::release()
{
//    CCLog("MigSpriteNode::release()-ref=%d.",retainCount()-1);
    CCNode::release();
}

bool MigSpriteNode::init()
{
    scheduleUpdate();
    return true;
}

MigSpriteNode* MigSpriteNode::create(cocos2d::CCString *migXml, cocos2d::CCString *plistFile,const char* root,bool useBatchSprite,const char* defaultSpriteName,float delayPerUnit)
{
    return create(migXml->getCString(), plistFile->getCString(),root,useBatchSprite,defaultSpriteName,delayPerUnit);
}

MigSpriteNode* MigSpriteNode::create(const char* migXmlFile,const char* plistFile,const char* root,bool useBatchSprite,const char* defaultSpriteName,float delayPerUnit)
{
    MigSpriteNode* node = create();
    node->initWithFile(migXmlFile, plistFile,root,useBatchSprite,defaultSpriteName,delayPerUnit);
    return node;
}

void MigSpriteNode::initWithFile(const char *migXmlFile, const char *plistFile,const char* root,bool useBatchSprite,const char* defaultSpriteName,float delayPerUnit)
{
	CCLog("MigSpriteNode::initWithFile:start");
	CCLog("MigSpriteNode::initWithFile:migXmlFile=%s.",migXmlFile);
    assert(migXmlFile && plistFile);
	CCLog("MigSpriteNode::initWithFile:plistFile=%s.",plistFile);
    MigAnimationLoader* loader = new MigAnimationLoader(root);
    std::string str = migXmlFile;
    if (str.compare(str.size()-4, 4, ".dat") == 0)
    {
        //assert(loader->loadBin(this, migXmlFile, plistFile, useBatchSprite));
        loader->loadBin(this, migXmlFile, plistFile, useBatchSprite);
    }
    else if(str.compare(str.size()-4,4,".xml") == 0)
    {
        //assert(loader->load(this,migXmlFile, plistFile,useBatchSprite));
		loader->load(this,migXmlFile, plistFile,useBatchSprite);
    }
    delete loader;
    //init draw node
    {
        if(useBatchSprite)
		{
			if (m_sTextureName != NULL)
			{
				CCLog("MigSpriteNode::initWithFile:m_sTextureName=%s.",m_sTextureName);
        		m_pDrawNode = CCSpriteBatchNode::create(m_sTextureName);
			}
			else
			{
				CCLog("MigSpriteNode::initWithFile:m_sTextureName=%s.",m_sTextureName);
			}
        }
        else
    	{
    		
        	m_pDrawNode = CCNode::create();
    	}
		CCLog("MigSpriteNode::initWithFile:0");
		if(m_pDrawNode != NULL)
		{
			
    		addChild(m_pDrawNode);
		}
		CCLog("MigSpriteNode::initWithFile:1");
    }
	CCLog("MigSpriteNode::initWithFile:2");
    if(defaultSpriteName)
    {
        MigSprite* pSprite = getSpriteChildByName(defaultSpriteName);
        setDefaultSprite(pSprite);
    }
    if(getDefaultSprite() == NULL)
    {
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(m_pSprites, pObj)
        {
            MigSprite* pSprite = dynamic_cast<MigSprite*>(pObj);
            if(pSprite)//第一个sprite节点为默认动作
            {
                setDefaultSprite(pSprite);
                break;
            }
        }
    }
	CCLog("MigSpriteNode::initWithFile:end");
    setCurrentSprite(pDefaultSprite);
    setDelayPerUnit(delayPerUnit);
    setBlendFunc(m_blendFunc);
}

MigSprite* MigSpriteNode::getCurrentSprite() const
{
    return m_pCurSprite;
}

MigFrame* MigSpriteNode::getCurrentFrame() const
{
    return m_pCurFrame;
}

void MigSpriteNode::setKeyFrameEventHandle(KeyFrameEventProtocol *handle)
{
    m_pKeyFrameEventHandle = handle;
}

void MigSpriteNode::onKeyFrame()
{
    int var = m_pCurFrame->getFlag();
    m_keyFrameEventParameter.param1 = (unsigned int)(var & 0x000f);
    m_keyFrameEventParameter.param2 = (unsigned int)((var >> 4) & 0x00f);
    m_keyFrameEventParameter.param3 = (unsigned int)((var >> 8) & 0x0f);
    m_keyFrameEventParameter.param4 = (unsigned int)(var >> 12);
    if(m_pKeyFrameEventHandle){
        m_pKeyFrameEventHandle->KeyFrameEvent(this, m_keyFrameEventParameter);
    }
}

void MigSpriteNode::onAnimationDone()
{
    m_bAnimationDone = true;
    if(m_pKeyFrameEventHandle)
        m_pKeyFrameEventHandle->animationDone(this);
}

bool MigSpriteNode::isAnimationDone()
{
    return m_bAnimationDone;
}

const char* MigSpriteNode::getName()
{
    return m_sName;
}

void MigSpriteNode::setName(const char *var)
{
    assert(var);
    m_sName = var;
}

const char* MigSpriteNode::getXmlName()
{
    return m_sXmlName;
}

void MigSpriteNode::setXmlName(const char *var)
{
    m_sXmlName = var;
}

const char* MigSpriteNode::getPlistName()
{
    return m_sPlistName;
}

void MigSpriteNode::setPlistName(const char *var)
{
    m_sPlistName = var;
}

const char* MigSpriteNode::getTextureName()
{
    return m_sTextureName;
}

void MigSpriteNode::setTextureName(const char *var)
{
    m_sTextureName = var;
}

void MigSpriteNode::setFlipX(bool var)
{
    m_bFlipX = var;
    float scale = getScaleX();
    if(!m_bFlipX)
    {
        setScaleX(scale>=0?scale:-scale);
    }
    else 
    {
        setScaleX(scale>=0?-scale:scale);
    }
}

bool MigSpriteNode::getFlipX()
{
    return m_bFlipX;
}

bool MigSpriteNode::getFlipY()
{
    return m_bFlipY;
}

void MigSpriteNode::setFlipY(bool var)
{
    m_bFlipY = var;
    float scale = getScaleY();
    if(!m_bFlipY)
    {
        setScaleY(scale>=0?scale:-scale);
    }
    else 
    {
        setScaleY(scale>=0?-scale:scale);
    }
}

void MigSpriteNode::update(float dt)
{
    updateAnimation(dt);
}

void MigSpriteNode::updateSprite(float d)
{
    if(!m_pCurSprite)
        return;
    assert(d >= 0 && d <= 1);//d总是在0~1之间
    float p = d * m_pCurSprite->getTotalDelayUnits();
    MigFrame* newFrame = NULL;
    CCArray* array = m_pCurSprite->getAllFrames();
    for (int i = 0; i < array->count(); i++)
    {
        MigFrame* pFrame = (MigFrame*)(array->objectAtIndex(i));
        if(p >= m_pCurSprite->m_frameSplitTimes->at(i) && p < m_pCurSprite->m_frameSplitTimes->at(i+1))
        {
            newFrame = pFrame;
            break;
        }
    }
    if(newFrame != m_pCurFrame)
    {
        m_pCurFrame = newFrame;
        displayFrame(m_pCurFrame);
    }
}

void MigSpriteNode::updateAnimation(float dt)
{
    if(!m_pCurSprite)
        return;
    bool done = false;
    m_elapsed += dt;
    float buf = m_elapsed / m_spriteTotalDuration;
    unsigned int loopCount = (unsigned int)(buf);
    MigFrame* tempFrame = m_pCurFrame;
    if(m_excutedLoop < loopCount)
    {
        if(m_excutedLoop == m_loop - 1)
        {
            done = true;
        }
        m_excutedLoop++;
        if(m_excutedLoop >= m_loop && m_loop > 0)
        {
            if(m_bOnSpriteEndSkipToDefault)
            {
                setCurrentSprite(pDefaultSprite);
                m_loop = 0;
                buf = 0;
            }
            else 
            {
                m_excutedLoop = m_loop;
            }
        }
    }
    if(m_excutedLoop >= m_loop && m_loop > 0)
    {
        buf = 1 - 0.000001;
    }
    updateSprite(fmodf(buf, 1.0));
    if((m_bNewFrame || tempFrame != m_pCurFrame) && m_pCurFrame->getFlag() > 0)
    {
        onKeyFrame();
        m_bNewFrame = false;
    }
    if(done)
    {
        onAnimationDone();
    }
}

bool MigSpriteNode::runAnimation(const char *name, unsigned int loop, bool backToDefault)
{
    MigSprite* pSprite = getSpriteChildByName(name);
    if(!pSprite)
    {
        CCLog("MigAnimation-runAnimation:cannot find animation by name=%s.",name);
        return false;
    }
    runAnimation(pSprite, loop, backToDefault);
    return true;
}

bool MigSpriteNode::runAnimation(int index,unsigned int loop,bool backToDefault)
{
    assert(index >= 0 && index < m_pSprites->count());
    MigSprite* pSprite = getSpriteChildByIndex(index);
    runAnimation(pSprite, loop, backToDefault);
    return true;
}

void MigSpriteNode::runAnimation(MigSprite *pSprite, unsigned int loop, bool backToDefault)
{
    setCurrentSprite(pSprite);
    m_loop = loop;
    m_excutedLoop = 0;
    m_bOnSpriteEndSkipToDefault = backToDefault;
}

MigSprite* MigSpriteNode::getSpriteChildByName(const char *name)
{
    CCObject* pCur = NULL;
    CCARRAY_FOREACH(m_pSprites, pCur)
    {
        MigSprite* pSprite = dynamic_cast<MigSprite*>(pCur);
        if(pSprite && strcmp(pSprite->getName(), name) == 0)
            return pSprite;
    }
    return NULL;
}

MigSprite* MigSpriteNode::getSpriteChildByIndex(int index)
{
    MigSprite* pSprite = dynamic_cast<MigSprite*>(m_pSprites->objectAtIndex(index));
    return pSprite;
}

void MigSpriteNode::setCurrentSprite(MigSprite *pSprite)
{
    assert(pSprite);
    m_elapsed = 0;
    m_excutedLoop = 0;
    m_bAnimationDone = false;
    if (pSprite == m_pCurSprite)
    {
        return;
    }
    m_pCurSprite = pSprite;
    m_spriteTotalDuration = m_pCurSprite->getTotalDelayUnits()*m_delayPerUnit;
    updateSprite(0);
    m_bNewFrame = true;
}

void MigSpriteNode::displayFrame(MigFrame *frame)
{
    assert(frame);
    CCArray* modules = frame->getAllModuleSprite();
    m_pDrawNode->removeAllChildrenWithCleanup(true);
    for (int i = 0; i < modules->count(); i++)
    {
        CCSprite* module = dynamic_cast<CCSprite*>(modules->objectAtIndex(i));
        m_pDrawNode->addChild(module);
		module->setColor(m_sColor);
		module->setOpacity(m_nOpacity);
    }
}

MigSprite* MigSpriteNode::getDefaultSprite()
{
    return pDefaultSprite;
}

void MigSpriteNode::setDefaultSprite(MigSprite* pSprite)
{
    assert(pSprite);
    pDefaultSprite = pSprite;
}

void MigSpriteNode::setDelayPerUnit(float var)
{
    assert(var);
    m_delayPerUnit = var;
    if(m_pCurSprite)
        m_spriteTotalDuration = m_pCurSprite->getTotalDelayUnits()*m_delayPerUnit;
}

float MigSpriteNode::getDelayPerUnit()
{
    return m_delayPerUnit;
}

int MigSpriteNode::getLoopCount()
{
    return m_loop;
}

int MigSpriteNode::getExcutedLoopCount()
{
    return m_excutedLoop;
}

GLubyte MigSpriteNode::getOpacity(void)
{
    return m_nOpacity;
}

void MigSpriteNode::setOpacity(GLubyte opacity)
{
    m_nOpacity = opacity;
    CCObject* pObj = NULL;
    CCArray* array = getChildren();
    CCARRAY_FOREACH(array, pObj)
    {
        CCRGBAProtocol* rgba = dynamic_cast<CCRGBAProtocol*>(pObj);
        if(rgba)
        {
            rgba->setOpacity(opacity);
        }
    }
    array = m_pDrawNode->getChildren();
    CCARRAY_FOREACH(array, pObj)
    {
        CCRGBAProtocol* rgba = dynamic_cast<CCRGBAProtocol*>(pObj);
        if(rgba)
        {
            rgba->setOpacity(opacity);
        }
    }
}

const ccColor3B& MigSpriteNode::getColor()
{
    return m_sColor;
}

void MigSpriteNode::setColor(const ccColor3B& color3)
{
    m_sColor = color3;
    CCObject* pObj = NULL;
    CCArray* array = getChildren();
    CCARRAY_FOREACH(array, pObj)
    {
        CCRGBAProtocol* rgba = dynamic_cast<CCRGBAProtocol*>(pObj);
        if(rgba)
        {
            rgba->setColor(color3);
        }
    }
    array = m_pDrawNode->getChildren();
    CCARRAY_FOREACH(array, pObj)
    {
        CCRGBAProtocol* rgba = dynamic_cast<CCRGBAProtocol*>(pObj);
        if(rgba)
        {
            rgba->setColor(color3);
        }
    }
}

void MigSpriteNode::setBlendFunc(ccBlendFunc var)
{
    m_blendFunc = var;
    CCObject* pObj = NULL;
    CCArray* array = getChildren();
    CCARRAY_FOREACH(array, pObj)
    {
        CCBlendProtocol* blend = dynamic_cast<CCBlendProtocol*>(pObj);
        if(blend)
        {
            blend->setBlendFunc(var);
        }
    }
    array = m_pDrawNode->getChildren();
    CCARRAY_FOREACH(array, pObj)
    {
        CCBlendProtocol* blend = dynamic_cast<CCBlendProtocol*>(pObj);
        if(blend)
        {
            blend->setBlendFunc(var);
        }
    }
}

ccBlendFunc MigSpriteNode::getBlendFunc()
{
    return m_blendFunc;
}

void MigSpriteNode::addSprite(MigSprite *sprite)
{
    m_pSprites->addObject(sprite);
}

int MigSpriteNode::indexOfSprite(MigSprite *pSprite)
{
    return m_pSprites->indexOfObject(pSprite);
}

int MigSpriteNode::indexOfCurrentSprite()
{
    if(m_pCurSprite)
        return m_pSprites->indexOfObject(m_pCurSprite);
    return -1;
}

int MigSpriteNode::getSpriteCount()
{
    return m_pSprites->count();
}

CCNode* MigSpriteNode::getDrawNode()
{
    return m_pDrawNode;
}

MigSprite::MigSprite() : m_frameCount(0),m_fTotalDelayUnits(0),m_frameSplitTimes(new std::vector<int>()),m_pFrames(NULL)
{
    m_pFrames = new CCArray();
}

MigSprite::~ MigSprite()
{
    CC_SAFE_DELETE(m_frameSplitTimes);
    CC_SAFE_DELETE(m_pFrames);
}

bool MigSprite::init()
{
    return true;
}

void MigSprite::addFrame(MigFrame *frame)
{
    m_pFrames->addObject(frame);
}

CCArray* MigSprite::getAllFrames()
{
    return m_pFrames;
}

const char* MigSprite::getName()
{
    return name;
}

void MigSprite::setName(const char *var)
{
    assert(var);
    name = var;
}

void MigSprite::refreshFrameInfo()
{
    m_frameSplitTimes->clear();
    m_frameCount = m_pFrames->count();
    m_frameSplitTimes->reserve(m_frameCount+1);
    CCObject* pObj = NULL;
    int i = 0;
    CCARRAY_FOREACH(m_pFrames, pObj)
    {
        MigFrame* pFrame = (MigFrame*)(pObj);
        m_frameSplitTimes->push_back(i);
        i+=pFrame->getDuration();
    }
    m_frameSplitTimes->push_back(i);
    m_fTotalDelayUnits = i;
}

int MigSprite::getFrameCount()
{
    return m_frameCount;
}


float MigSprite::getTotalDelayUnits()
{
    return m_fTotalDelayUnits;
}

MigFrame::MigFrame():rectRed(),rectGreen(),m_pModules(NULL)
{
    m_pModules = new CCArray();
}

MigFrame::~MigFrame()
{
    delete m_pModules;
}

bool MigFrame::init()
{
    return true;
}

void MigFrame::setDuration(int var)
{
    assert(var > 0);
    duration = var;
}

int MigFrame::getDuration()
{
    return duration;
}

void MigFrame::setFlag(int var)
{
    flag = var;
}

int MigFrame::getFlag()
{
    return flag;
}

void MigFrame::setRectRed(const CCRect& var)
{
    rectRed = CCRectMake(var.origin.x, var.origin.y, var.size.width, var.size.height);
}

const CCRect& MigFrame::getRectRed()
{
    return rectRed;
}

void MigFrame::setRectGreen(const CCRect& var)
{
    rectGreen = CCRectMake(var.origin.x, var.origin.y, var.size.width, var.size.height);
}

const CCRect& MigFrame::getRectGreen()
{
    return rectGreen;
}

void MigFrame::addModuleSprite(cocos2d::CCSprite *sprite)
{
    assert(sprite);
    m_pModules->addObject(sprite);
}

CCArray* MigFrame::getAllModuleSprite()
{
    return m_pModules;
}