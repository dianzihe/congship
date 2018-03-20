//
//  GameFrontLayerInterFace.h
//  dandandao
//
//  Created by haotao on 12-4-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef dandandao_GameFrontLayerInterFace_h
#define dandandao_GameFrontLayerInterFace_h

#include "WBEvent.h"
//#include "typedefine.h"
//#include "../battle_base/ECCPanZoomController.h"
//#include "WBPixelSpriteStencil.h"

#define DEF_GameFrontLayerInterFace_TAG 0xFF1312

class GameFrontLayerInterFace:public CCLayer
{
    CC_SYNTHESIZE(Vec2, m_gravityFly,GravityFly);  ///< 飞行时的重力加速度
    CC_SYNTHESIZE(Vec2, m_gravity,Gravity);           ///< 重力加速度
    CC_SYNTHESIZE(Vec2, m_wind,Wind);                  ///< 风力
    
    CC_SYNTHESIZE(CCArray *,m_heros,Heros);           //当前所有的角色
    CC_SYNTHESIZE(CCArray *,m_guais, Guais);          //当前所有的怪
#if (NOT_USE_STENCIL_SPRITE == 1)
    //CC_SYNTHESIZE(CCArray *,m_PixelSprites,PixelSprites); //当前所有的碰撞色块实图
    //CC_SYNTHESIZE(WBPixelByte *, m_PixelByte, PixelByte); //当前所有的碰撞色块模板
#else
    CC_SYNTHESIZE(WBPixelSpriteStencil*, m_stencilSprite, StencilSprite); //碰撞使用模板测试实现
#endif
    
    CC_SYNTHESIZE(ccColor3B, m_pointColor, PointColor) //射线点的颜色
    
    CC_SYNTHESIZE(bool, m_isGameOver, IsGameOver)
    
#if OPEN_FIFTH
    CC_SYNTHESIZE(WImage *, m_lpCircle, lpCircle);
    CC_SYNTHESIZE(WImage *, m_lpCircleMark, lpCircleMark);
#endif

public:
    virtual void updateHud();
    virtual void showBlackColorBackGround();
    
    virtual void SendMsgNextRound();
    virtual void EndCurrentMsg();
    
    void SendMsgCenterToChara();
    
    /**
     * @brief 清理事件队列
     */
    void ClearEventQueue();
    
    /**
     * @brief 发送事件到事件队列
     */
    void SendEventToQueue(WBEvent *pEvent); 
    
    //得到重生点
    Vec2 getRebornPosition();
    
protected:
    queue<WBEvent *> m_EventManager;
    
    queue<WBEvent *> m_quickEventManager;//立即执行的事件队列，一般会是一些只发数值的操作
    
    WBEvent *m_currentWBEvent; //当前正在执行的事件
    
    
    /**
     * @brief 处理事件
     */
    virtual void processEvent(); 


  
public:
    //CCPanZoomController *_controller;
    
    void resume();
    //void initMap(WMap *pMap);
  
    GameFrontLayerInterFace();
    ~GameFrontLayerInterFace();
};

#endif
