//
//  MigAnimation.h
//  SanguoHeros
//
//  Created by 伟 李 on 12-10-12.
//  Copyright (c) 2012年 intelligame. All rights reserved.
//

#ifndef SanguoHeros_MigAnimation_h
#define SanguoHeros_MigAnimation_h

#include "cocos2d.h"

USING_NS_CC;

class MigSpriteNode;
class MigSprite;
class MigFrame;

using namespace std;

struct KeyFrameEventParameter
{
public:
    int param1;
    int param2;
    int param3;
    int param4;
};

class KeyFrameEventProtocol
{
public:
    virtual void KeyFrameEvent(const MigSpriteNode* sender,const KeyFrameEventParameter& params) = 0;
    virtual void animationDone(const MigSpriteNode* sender) = 0;
};

const ccBlendFunc DEFAULT_BLEND_FUNC = {GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA};


const float DEFAULT_DELAY_PER_FRAME = 0.01666666666667;

class MigSpriteNode : public Node/*, public BlendProtocol*/
{
public:
    MigSpriteNode();
    virtual ~ MigSpriteNode();
    virtual bool init();
    
    CREATE_FUNC(MigSpriteNode);
    
    static MigSpriteNode* create(String* migXml, String* plistFile,const char* root=NULL,bool useBatchSprite = true,const char* defaultSpriteName = NULL,float delayPerUnit = DEFAULT_DELAY_PER_FRAME);
    static MigSpriteNode* create(const char* migXml,const char* plistFile,const char* root=NULL,bool useBatchSprite = true,const char* defaultSpriteName = NULL,float delayPerUnit = DEFAULT_DELAY_PER_FRAME);
    
    void initWithFile(const char* migXmlFile,const char* plistFile,const char* root,bool useBatchSprite,const char* defaultSpriteName,float delayPerUnit);
    
    //CC_PROPERTY(const char*, m_sName, Name);
	CC_SYNTHESIZE(MigSprite*, pDefaultSprite, DefaultSprite);
	CC_SYNTHESIZE(float, m_delayPerUnit, DelayPerUnit);
	CC_SYNTHESIZE(const char*, m_sXmlName, XmlName);
	CC_SYNTHESIZE(const char*, m_sPlistName, PlistName);
	CC_SYNTHESIZE(const char*, m_sTextureName, TextureName);
	CC_SYNTHESIZE(unsigned int, _heroID, HeroID);
	
	//CC_SYNTHESIZE(ccBlendFunc, m_blendFunc, BlendFunc);
	ccBlendFunc m_blendFunc;
	void setBlendFunc(ccBlendFunc var);
	ccBlendFunc getBlendFunc();

	CC_SYNTHESIZE(bool, m_bFlipX, FlipX);
	CC_SYNTHESIZE(bool, m_bFlipY, FlipY);
	//CC_SYNTHESIZE_PASS_BY_REF(Color3B, m_sColor, Color);

    bool runAnimation(const char* name,unsigned int loop = 0,bool backToDefault = true);
    bool runAnimation(int index,unsigned int loop = 0,bool backToDefault = true);
    
    virtual void update(float dt);
    
    int getLoopCount();
    int getExcutedLoopCount();

	GLubyte  m_nOpacity;
	GLubyte getOpacity(void);
	void setOpacity(GLubyte opacity);

	Color3B m_sColor;
	//const Color3B& getColor();
	void setColor(const Color3B& color3);

    virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB(void) { return false;}
    
    void setKeyFrameEventHandle(KeyFrameEventProtocol* handle);
    
    MigFrame* getCurrentFrame() const;
    MigSprite* getCurrentSprite() const;
    
    bool isAnimationDone();
    
    void addSprite(MigSprite* sprite);
    
    int indexOfSprite(MigSprite* pSprite);
    int indexOfCurrentSprite();
    int getSpriteCount();
    
    MigSprite* getSpriteChildByName(const char* name);
    MigSprite* getSpriteChildByIndex(int index);
    void runAnimation(MigSprite* sprite,unsigned int loop,bool backToDefault);
    
    virtual void retain();
    virtual void release();
protected:
    MigSprite* m_pCurSprite;
    MigFrame* m_pCurFrame;
    float m_elapsed;
    float m_spriteTotalDuration;
    unsigned int m_loop;
    unsigned int m_excutedLoop;
    bool m_bOnSpriteEndSkipToDefault;
    bool m_bNewFrame;
    CCNode* m_pDrawNode;
    
    void setCurrentSprite(MigSprite* pSprite);
    void displayFrame(MigFrame* frame);
    
    KeyFrameEventParameter m_keyFrameEventParameter;
    KeyFrameEventProtocol* m_pKeyFrameEventHandle;
    
    virtual void onKeyFrame();
    virtual void onAnimationDone();

    CCNode* getDrawNode();
    
    bool m_bAnimationDone;
    
    CCArray* m_pSprites;
    
    void updateAnimation(float dt);
    void updateSprite(float ratio);
};

class MigSprite : public Ref
{
    friend class MigSpriteNode;
public:
    MigSprite();
    virtual ~MigSprite();
    
    virtual bool init();
    
    CREATE_FUNC(MigSprite);
	CC_SYNTHESIZE(const char*, name, Name);

    void addFrame(MigFrame* frame);
    Array* getAllFrames();
    int getFrameCount();
    void refreshFrameInfo();
    
    float getTotalDelayUnits();
protected:
    int m_frameCount;//动画帧个数
    int m_fTotalDelayUnits;//动画帧长度，因为个别帧会播放多次，所以m_frameDuration>=m_frameCount
    std::vector<int>* m_frameSplitTimes;
    Array* m_pFrames;
};

class MigFrame : public Ref
{
    friend class MigSpriteNode;
public:
    MigFrame();
    virtual ~MigFrame();
    virtual bool init();
    CREATE_FUNC(MigFrame);

	CC_SYNTHESIZE(int, duration, Duration);
	CC_SYNTHESIZE(int, flag, Flag);
	CC_SYNTHESIZE_PASS_BY_REF(CCRect, rectRed, RectRed);
	CC_SYNTHESIZE_PASS_BY_REF(CCRect, rectGreen, RectGreen);
    
	void addModuleSprite(CCSprite* sprite);
    CCArray* getAllModuleSprite();
protected:
    CCArray* m_pModules;
};

class RunMigAnimation : public ActionInstant
{
public:
    RunMigAnimation() : m_pTarget(NULL),m_pSprite(NULL)
    {
    }
    
    virtual ~ RunMigAnimation(){}
    
    bool init() {return true;}
    
    CREATE_FUNC(RunMigAnimation);
    
    static RunMigAnimation* create(MigSpriteNode* target,const char* name,int loop,bool backToDefault)
    {
        assert(target);
        assert(name);
        RunMigAnimation* pRet = create();
        pRet->m_pTarget = target;
        pRet->m_pSprite = target->getSpriteChildByName(name);
        assert(pRet->m_pSprite);
        pRet->m_iLoop = loop;
        pRet->m_bBackToDefault = backToDefault;
        return pRet;
    }
    
    static RunMigAnimation* create(MigSpriteNode* target,int index,int loop,bool backToDefault)
    {
        assert(target);
        assert(index >= 0);
        RunMigAnimation* pRet = create();
        pRet->m_pTarget = target;
        pRet->m_pSprite = target->getSpriteChildByIndex(index);
        assert(pRet->m_pSprite);
        pRet->m_iLoop = loop;
        pRet->m_bBackToDefault = backToDefault;
        return pRet;
    }
    
    virtual bool isDone(void) 
    {
        return true;
    }
    
    virtual void update(float time)
    {
        CC_UNUSED_PARAM(time);
        m_pTarget->runAnimation(m_pSprite,m_iLoop,m_bBackToDefault);
    }
    
    virtual CCFiniteTimeAction * reverse(void)
    {
        return create();
    }
protected:
    MigSpriteNode* m_pTarget;
    int m_iLoop;
    bool m_bBackToDefault;
    MigSprite* m_pSprite;
};
#endif
