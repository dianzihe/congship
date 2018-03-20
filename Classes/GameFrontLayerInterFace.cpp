//
//  GameFrontLayerInterFace.cpp
//  dandandao
//
//  Created by haotao on 12-4-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//



#include "GameFrontLayerInterFace.h"
//#include "../map/WMap.h"


/*
_controller(NULL),
#if (NOT_USE_STENCIL_SPRITE == 1)
m_PixelSprites(NULL),
m_PixelByte(NULL)
#else
m_stencilSprite(NULL)
#endif
*/
GameFrontLayerInterFace::GameFrontLayerInterFace():
m_currentWBEvent(NULL),
m_heros(NULL),
m_guais(NULL)
{

#if OPEN_FIFTH
    m_lpCircle=NULL;
    m_lpCircleMark=NULL;
#endif
    m_gravity=Vec2(0, -1); ///< 重力加速度
    
    m_gravityFly=Vec2(0.0f,-0.16f);
    
    m_wind =Vec2(0, 0);
    
    setTag(DEF_GameFrontLayerInterFace_TAG);
//    m_cilcleImage=NULL;
 //   m_cilcleImageMark=NULL;
}
GameFrontLayerInterFace::~GameFrontLayerInterFace()
{
    //CC_SAFE_RELEASE_NULL(_controller);
 
    while(m_EventManager.size())
    {
        WBEvent *pEvent=m_EventManager.front();
        m_EventManager.pop();
        CC_SAFE_DELETE(pEvent);
    }
    
    while(m_quickEventManager.size())
    {
        WBEvent *pEvent=m_quickEventManager.front();
        m_quickEventManager.pop();
        CC_SAFE_DELETE(pEvent);
    }
    
    CC_SAFE_RELEASE_NULL(m_heros);
    CC_SAFE_RELEASE_NULL(m_guais);
#if (NOT_USE_STENCIL_SPRITE == 1)
    //CC_SAFE_RELEASE_NULL(m_PixelSprites);
    //CC_SAFE_DELETE(m_PixelByte);
#else
    CC_SAFE_RELEASE_NULL(m_stencilSprite);
#endif
    
#if OPEN_FIFTH
    CC_SAFE_DELETE(m_lpCircle);
    CC_SAFE_DELETE(m_lpCircleMark);
#endif
}

void GameFrontLayerInterFace::resume()
{
    CCObject *thisObj =NULL;
   
#if (NOT_USE_STENCIL_SPRITE == 1)
#else
    //TODO
#endif
}
/*
void GameFrontLayerInterFace::initMap(WMap *pMap)
{

#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
	float fBeforeFactor	= CCTexture2D::cwSngGetScaleFactor();
	CCTexture2D::cwSngSetScaleFactor(1.0f);
#endif

    setContentSizeInPixels(pMap->m_size);
    
    _controller = CCPanZoomController::controllerWithNode(this);
    _controller->retain();
    
    _controller->_zoomOutLimit =_controller->getOptimalZoomOutLimit();
    //float scale=WUtil::getSceneScale();
    
   // if(scale>1.0)        _controller->_zoomOutLimit=_controller->_zoomOutLimit*scale;
    //  else if(scale<1.0) _controller->_zoomOutLimit=_controller->_zoomOutLimit/scale;
    
    // if(_controller->_zoomOutLimit<0.65) _controller->_zoomOutLimit=0.65;
    _controller->_zoomInLimit = 1.2;
    
    m_pointColor=pMap->m_pointColor;
    
#if OPEN_FIFTH
    string circleImagePath=DEF_EXPLODE_IMAGE_PATH;
    circleImagePath.append("weapon42b.png");
    WHero::getCircleImg(circleImagePath,&m_lpCircle,&m_lpCircleMark);
#endif
    
    
    assert(pMap && pMap->m_PixelImg.size()>0);
    
    
#if (NOT_USE_STENCIL_SPRITE == 1)
    m_PixelSprites=CCArray::array();
    m_PixelSprites->retain();
    
    for(int i=0; i<pMap->m_PixelImg.size(); i++)
    {
        
        WBPixelSprite *sprite = new WBPixelSprite(pMap->m_PixelImg[i].imgPath.c_str());
        
        sprite->setAnchorPoint(CCPointMake(0, 0));
        sprite->setPositionInPixels(pMap->m_PixelImg[i].position);
        //     sprite->setBreakCircleImage(m_cilcleImage, m_cilcleImageMark);
        //testtest
        //  sprite->setScale(2);
        if(pMap->m_PixelImg[i].breaktype==WMap::E_BREAKEN_TYPE_BREAK)
        {
            sprite->setCouldBeBroken(true);
        }
        else
        {
            sprite->setCouldBeBroken(false);
        }
        
        m_PixelSprites->addObject(sprite);
        addChild(sprite);
    }
    
    m_PixelByte=new WBPixelByte();
    m_PixelByte->init(m_PixelSprites);
#else
    m_stencilSprite = new WBPixelSpriteStencil(pMap);
    addChild(m_stencilSprite);
    m_stencilSprite->retain();
#endif
    
    
    
    
#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
	CCTexture2D::cwSngSetScaleFactor(fBeforeFactor);
#endif
  //  m_PixelByte->setBreakCircleImage(m_cilcleImage, m_cilcleImageMark);
}
*/
void GameFrontLayerInterFace::showBlackColorBackGround()
{
    
}

void GameFrontLayerInterFace::ClearEventQueue()
{   
    WBEvent *pEvent;
    
    while(m_EventManager.size()>0)
    {
        pEvent=m_EventManager.front();
        m_EventManager.pop();
        
		CC_SAFE_DELETE(pEvent);
        
    }
    
    while(m_quickEventManager.size()>0)
    {
        pEvent=m_quickEventManager.front();
        m_quickEventManager.pop();
        
		CC_SAFE_DELETE(pEvent);
        
    }
}

void GameFrontLayerInterFace::SendEventToQueue(WBEvent *pEvent)
{
    assert(pEvent);
    
    if(pEvent->getProcesstype()==0)
    {
        m_EventManager.push(pEvent);
    }
    else
    {
        m_quickEventManager.push(pEvent);
    }
}

void GameFrontLayerInterFace::EndCurrentMsg()
{
    //if(m_currentWBEvent) m_currentWBEvent->End();
}

void GameFrontLayerInterFace::SendMsgNextRound()
{
    
}

void GameFrontLayerInterFace::processEvent()
{
    
}

void GameFrontLayerInterFace::updateHud()
{
    
}

void GameFrontLayerInterFace::SendMsgCenterToChara()
{
    
}

Vec2 GameFrontLayerInterFace::getRebornPosition()
{
    Vec2 pos;
    Vec2 pos2;
    bool flag=false;
	/*
    WMover player;
    bool inSide;
    player.setMoverCollisionType(WMover::E_COLLISION_POINT);
    player.setMoverRadius(50);
    
    
    
    
    do
    {
        
        pos=Vec2(rand()%1300+250,getContentSizeInPixels().height-100);
        
        player.setMoverPosition(pos);
        player.setMoverPrePosition(pos);
        
        
#if (NOT_USE_STENCIL_SPRITE == 1)
        flag=getPixelByte()->CheckCollision(&player,NULL,NULL,inSide);
#else
        flag = getStencilSprite()->CheckCollision(&player, NULL, NULL, inSide);
#endif
        if(flag)
        {
            flag=false;
            continue;
        }
        
        for(int i=pos.y; i>0; i--)
        {
            pos2=pos;
            pos2.y=i;
            player.setMoverPosition(pos2);
            player.setMoverPrePosition(pos2);
            
#if (NOT_USE_STENCIL_SPRITE == 1)
            flag=getPixelByte()->CheckCollision(&player,NULL,NULL,inSide);
#else
            flag = getStencilSprite()->CheckCollision(&player, NULL, NULL, inSide);
#endif
            
            if(flag)
            {
                break;
            }
        }
        
        if(flag)
        {
            break;
        }
        
        
        
    }while (flag==false);
    */
    return pos;
}





