//
//  GameFrontLayerInterFace.h
//  dandandao
//
//  Created by haotao on 12-4-13.
//  Copyright (c) 2012�� __MyCompanyName__. All rights reserved.
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
    CC_SYNTHESIZE(Vec2, m_gravityFly,GravityFly);  ///< ����ʱ���������ٶ�
    CC_SYNTHESIZE(Vec2, m_gravity,Gravity);           ///< �������ٶ�
    CC_SYNTHESIZE(Vec2, m_wind,Wind);                  ///< ����
    
    CC_SYNTHESIZE(CCArray *,m_heros,Heros);           //��ǰ���еĽ�ɫ
    CC_SYNTHESIZE(CCArray *,m_guais, Guais);          //��ǰ���еĹ�
#if (NOT_USE_STENCIL_SPRITE == 1)
    //CC_SYNTHESIZE(CCArray *,m_PixelSprites,PixelSprites); //��ǰ���е���ײɫ��ʵͼ
    //CC_SYNTHESIZE(WBPixelByte *, m_PixelByte, PixelByte); //��ǰ���е���ײɫ��ģ��
#else
    CC_SYNTHESIZE(WBPixelSpriteStencil*, m_stencilSprite, StencilSprite); //��ײʹ��ģ�����ʵ��
#endif
    
    CC_SYNTHESIZE(ccColor3B, m_pointColor, PointColor) //���ߵ����ɫ
    
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
     * @brief �����¼�����
     */
    void ClearEventQueue();
    
    /**
     * @brief �����¼����¼�����
     */
    void SendEventToQueue(WBEvent *pEvent); 
    
    //�õ�������
    Vec2 getRebornPosition();
    
protected:
    queue<WBEvent *> m_EventManager;
    
    queue<WBEvent *> m_quickEventManager;//����ִ�е��¼����У�һ�����һЩֻ����ֵ�Ĳ���
    
    WBEvent *m_currentWBEvent; //��ǰ����ִ�е��¼�
    
    
    /**
     * @brief �����¼�
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
