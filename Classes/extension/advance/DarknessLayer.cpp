//
//  DarknessLayer.cpp
//  SanguoHeros
//
//  Created by 伟 李 on 12-10-25.
//  Copyright (c) 2012年 intelligame. All rights reserved.
//

#include <iostream>
#include "DarknessLayer.h"
#include "MyHead.h"

DarknessLayer* DarknessLayer::create(ccColor4F color)
{
    DarknessLayer* pRef = create();
    pRef->m_c4fColor = color;
    return pRef;
}

DarknessLayer::DarknessLayer()
{
    
}

DarknessLayer::~ DarknessLayer()
{
    
}

bool DarknessLayer::init()
{
    if(!CCLayer::init())
        return false;
    m_pRender = CCRenderTexture::create(getContentSize().width, getContentSize().height);
    m_pRender->clear(m_c4fColor.r,m_c4fColor.g,m_c4fColor.b,m_c4fColor.a);
    m_pRender->setPosition(CCPointMake(getContentSize().width/2, getContentSize().height/2));
    addChild(m_pRender,99);
    return true;
}

CCRenderTexture* DarknessLayer::getRender()
{
    return m_pRender;
}

void DarknessLayer::draw()
{
    m_pRender->clear(m_c4fColor.r,m_c4fColor.g,m_c4fColor.b,m_c4fColor.a);
    CCLayer::draw();
}

Light* DarknessLayer::addLight(const cocos2d::CCPoint &position)
{
	//Light* light = Light::create(("zip::light.png"));
	Light* light = Light::create(CCString::createWithFormat("%slight.png", DATADECODE_HEAD)->getCString());
    light->setPosition(position);
    CCLog("add light x = %f,y = %f",light->getPositionX(),light->getPositionY());
    addChild(light);
    return light;
}

Light* DarknessLayer::addLightWithNode(cocos2d::CCNode *follow)
{
    assert(follow);
    Light* light = addLight(follow->getPosition());
    light->setFollowNode(follow);
    light->scheduleUpdate();
    return light;
}

void DarknessLayer::removeLight(Light *light)
{
    assert(light);
    assert(light->getParent() == this);
    CCLog("DarknessLayer:remove light@%d",light);
    removeChild(light, true);
}

void DarknessLayer::removeLightFollowWith(cocos2d::CCNode *follow)
{
    assert(follow);
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(getChildren(), pObj)
    {
        Light* light = dynamic_cast<Light*>(pObj);
        if(light && light->getFollowNode() == follow)
        {
            CCLog("DarknessLayer:remove light@%d",light);
            removeChild(light, true);
        }
    }
}

Light* Light::create(const char *pszFileName)
{
    Light *pobSprite = new Light();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void Light::draw()
{
    DarknessLayer* darkness = dynamic_cast<DarknessLayer*>(getParent());
    assert(darkness);
    darkness->getRender()->begin();
    CC_NODE_DRAW_SETUP();
    glBlendFunc(GL_ZERO ,GL_ONE_MINUS_SRC_ALPHA);
    glColorMask(0.0f, 0.0f, 0.0f, 1.0f);
#define kQuadSize sizeof(m_sQuad.bl)
    if (m_pobTexture)
    {
        glBindTexture(GL_TEXTURE_2D,  m_pobTexture->getName());
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
    long offset = (long)&m_sQuad;
    // vertex 
    int diff = offsetof(ccV3F_C4B_T2F, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Position,3, GL_FLOAT,GL_FALSE, kQuadSize, (void*)(offset +  diff));
    
    // color
    diff = offsetof( ccV3F_C4B_T2F,  colors);
    glVertexAttribPointer(kCCVertexAttrib_Color,4, GL_UNSIGNED_BYTE,GL_TRUE, kQuadSize, (void*)(offset  + diff));
    
    // tex coords
    diff = offsetof( ccV3F_C4B_T2F, texCoords);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords,2, GL_FLOAT,GL_FALSE, kQuadSize, (void*)(offset + diff));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glColorMask(1.0, 1.0, 1.0, 1.0);
    
    darkness->getRender()->end();
    
    CC_INCREMENT_GL_DRAWS(1);
}

void Light::setFollowNode(cocos2d::CCNode *var)
{
    m_pFollowNode = var;
}

CCNode* Light::getFollowNode()
{
    return m_pFollowNode;
}

void Light::update(float dt)
{
    if(!m_pFollowNode)
        return;
    CCPoint p = m_pFollowNode->getPosition();
    CCPoint wp = m_pFollowNode->getParent()->convertToWorldSpace(p);
    if(wp.x != getPositionX() || wp.y != getPositionY())
        setPosition(wp);
}