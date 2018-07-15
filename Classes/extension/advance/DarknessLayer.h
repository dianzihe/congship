#ifndef SanguoHeros_DarknessLayer_h
#define SanguoHeros_DarknessLayer_h

#include "cocos2d.h"
#include "CCGL.h"

USING_NS_CC;
class Light;

class DarknessLayer : public CCLayer
{
public:
    DarknessLayer();
    ~ DarknessLayer();
    
    CREATE_FUNC(DarknessLayer);
    
    static DarknessLayer* create(ccColor4F color);
    
    bool init();
    void draw();
    
    CCRenderTexture* getRender();
    
    Light* addLight(const CCPoint& position);
    Light* addLightWithNode(CCNode* follow);
    void removeLight(Light* light);
    void removeLightFollowWith(CCNode* follow);
protected:
    CCRenderTexture* m_pRender;
    ccColor4F m_c4fColor;
};

class Light : public CCSprite
{
public:
    static Light* create(const char *pszFileName);
    void draw();
    void update(float dt);
    CC_PROPERTY(CCNode*, m_pFollowNode, FollowNode);
};

#endif
