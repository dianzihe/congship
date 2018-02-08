//
//  WBullet.cpp
//  dandandao
//
//  Created by haotao on 12-3-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "WBullet.h"
//#include "../battle_base/WBUtil.h"
//#include "ddd_global.h"
//#include "WMusic.h"
#include <vector>


WBullet::WBullet():
m_emitter(NULL),
m_flyTime(0),
m_SpecialType(-1),
m_currentPositionIndex(0),
m_flyMode(E_FLYMODE_NORMAL)
//,
//m_lpHero(NULL)
{
    setTag(DEF_OBJ_TYPE_BULLET);
    setMoverCollisionType(WMover::E_COLLISION_CIRCLE);
    setScale(0.7f);
    m_TrackRadius=200;
    //m_targetHero=NULL;
    m_target=NULL;
    //m_targetHero=NULL;
    m_trackTime=0.0f;
}

void WBullet::onEnter()
{
    scheduleUpdate();  
#if 0
    cwSngSprite::onEnter();
      
    
    if(WBattleGlobal::isOpenMidLayer())
    {
        m_emitter=WParticleSun::node();
        //ARCH_OPTIMAL_PARTICLE_SYSTEM::particleWithFile("gameResources/battle/myfire.plist");
        //WParticleSun::node();
        //    m_emitter->setLife(1.0f);
        //   m_emitter->initWithTotalParticles(100);
        m_emitter->retain();
        m_emitter->setPosition(getPosition());
        
        m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("gameResources/battle/hud/battle_hud_fire2.png") );
        m_emitter->setPositionType(kCCPositionTypeRelative);
        m_emitter->setIsAutoRemoveOnFinish(true);
        
        m_lpGameFrontLayer->addChild(m_emitter,-1);
    }
    else
    {
        m_emitter=NULL;
    }
#endif 
}

void WBullet::onExit()
{
    unscheduleUpdate();
#if 0
    if(m_emitter)
    {
        if(m_emitter->getParent())
        {
            m_emitter->removeFromParentAndCleanup(true);
        }
        m_emitter->release();
        m_emitter=NULL;
    }
    cwSngSprite::onExit();
#endif
}

WBullet::~WBullet()
{
    CC_SAFE_RELEASE_NULL(m_emitter);
    
    if(m_target)
    {
        m_target->removeFromParentAndCleanup(true);
        m_target=NULL;
    }
}

//void WBullet::draw(void)
//{
//    cwSngSprite::draw();  
//    CCPoint p(getAnchorPointInPixels().x,getAnchorPointInPixels().y);
//    p.x/=CC_CONTENT_SCALE_FACTOR();
//    p.y/=CC_CONTENT_SCALE_FACTOR();
//    
//     ccDrawCircle(p,getMoverRadius()/(0.7*CC_CONTENT_SCALE_FACTOR()),360,20,false); 
//    glColor4f(1.0f, 0, 0, 1.0f);
//    ccDrawCircle(p,getExplodeRadius()/(0.7*CC_CONTENT_SCALE_FACTOR()),360,20,false); 
//}

WBullet *WBullet::buildGuaiBullet(Vec2 Position,Vec2 speed,/*GameFrontLayerInterFace *lpGameFrontLayer,WGuai *lpGuai,*/int m_attack,int m_radius,bool isBigSkill)
{
    WBullet *lpBullet=new WBullet();
    lpBullet->autorelease();
    
    //lpBullet->setGameFrontLayer(lpGameFrontLayer);
    //lpBullet->setHero(NULL);
    //lpBullet->setGuai(lpGuai);
    
    lpBullet->m_attack              =m_attack;
    lpBullet->m_ExplodeRadius=300;    
    
    lpBullet->m_shootType=0;
    
    //动画
	/*
    if(!isBigSkill){
        lpBullet->addAnimationToDict(WBullet::DEF_NORMAL, lpGuai->getBulletAni());
    }else{
        lpBullet->addAnimationToDict(WBullet::DEF_NORMAL, lpGuai->getBulletAniAngry());
    }
    */

    //lpBullet->addAnimationToDict(WBullet::DEF_EXPLODE, lpGuai->getBulletAniExplode());
	std::string iwco_name = "battleEfficients";
	/**
	* @brief 找到武器对应的炮弹
	*/
	string weapon = "weapon20a";
	map<string, string> bulletDesc;

	bulletDesc.insert(pair<string, string>("weapon", weapon));

	// 文件创建动画  
	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("weapon20c.wco", "weapon20c0.png");  // 增加动画plist和png文件  
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;
	for (int i = 1; i <= 8; i++){
		frame = frameCache->getSpriteFrameByName(StringUtils::format("s_%d.png", i));
		frameVec.pushBack(frame);
	}
	/*
	//使用的炮弹   
	lpHero->m_BulletAni = cwSngAnimationPool::sharedAnimationPool()->animation(iwco_name, "fly1", bulletDesc);
	lpHero->m_BulletAni->setDelay(0.1);
	lpHero->m_BulletAni->retain();

	Animation* anim;
	anim = createAttackAnimFromColor(GemUtils::Fire, 20);
	anim->setDelayPerUnit(0.05);
	CCAnimationCache::sharedAnimationCache()->addAnimation(anim, GemUtils::attackAnim(GemUtils::Fire));

    lpBullet->setAnimation(WBullet::DEF_NORMAL);
    lpBullet->playRepeat();
    
    //   collisionCircle.
    Vec2 achor(lpBullet->getAnchorPointInPixels().x,lpBullet->getAnchorPointInPixels().y);
    Vec2 center(lpBullet->getContentSizeInPixels().width/2,lpBullet->getContentSizeInPixels().height/2);
    
    center-=achor;
    
    lpBullet->setMoverCenter(center);
    lpBullet->setMoverRadius((lpBullet->getContentSizeInPixels().width)/2*0.5);
  
    //重置开始位置
    lpBullet->setMoverPosition(Position);
    lpBullet->setMoverSpeed(speed);
    lpBullet->setPositionInPixels(CCPointMake(Position.x, Position.y));
    
    */
    return lpBullet;
}

WBullet *WBullet::buildBullet(Vec2 Position,Vec2 speed,/*GameFrontLayerInterFace *lpGameFrontLayer,WHero *lpHero,*/int m_attack,int ExplodeRadius,bool isBigSkill)
{
    WBullet *lpBullet=new WBullet();
    lpBullet->autorelease();
    
    //lpBullet->setGameFrontLayer(lpGameFrontLayer);
    //lpBullet->setHero(lpHero);
    
    lpBullet->m_attack              =m_attack;
    lpBullet->m_ExplodeRadius=ExplodeRadius;    
    
    //lpBullet->m_shootType=lpHero->getWeaponType();
    
    
    //动画
	/*
    if(!isBigSkill){
        lpBullet->addAnimationToDict(WBullet::DEF_NORMAL, lpHero->getBulletAni());
    }else{
        lpBullet->addAnimationToDict(WBullet::DEF_NORMAL, lpHero->getBulletAniAngry());
    }
    
#if OPEN_FIFTH
    if(lpHero->getWSSkillType()==WBWeaponSkill::E_WEAPONSKILL_TYPE_ATOM)
    {
        map<string,string> bulletDesc;
        bulletDesc["weapon"]="weapon42c";
        cwSngAnimation *pSngAnimation=cwSngAnimationPool::sharedAnimationPool()->animation(WANI_IWCO_BATTLEEFFICIENTS, "blasting", bulletDesc);
        
        lpBullet->addAnimationToDict(WBullet::DEF_EXPLODE, pSngAnimation);
    }
    else
    {
         lpBullet->addAnimationToDict(WBullet::DEF_EXPLODE, lpHero->getBulletAniExplode());
    }
#else
    lpBullet->addAnimationToDict(WBullet::DEF_EXPLODE, lpHero->getBulletAniExplode());

#endif
    lpBullet->addAnimationToDict(WBullet::DEF_FREEZE, lpHero->getBulletAniFreezeExplode());
    
    lpBullet->setAnimation(WBullet::DEF_NORMAL);
    lpBullet->playRepeat();
    
    //   collisionCircle.
    Vec2 achor(lpBullet->getAnchorPointInPixels().x,lpBullet->getAnchorPointInPixels().y);
    Vec2 center(lpBullet->getContentSizeInPixels().width/2,lpBullet->getContentSizeInPixels().height/2);
    
    center-=achor;
    
    lpBullet->setMoverCenter(center);
    lpBullet->setMoverRadius((lpBullet->getContentSizeInPixels().width)/2*0.5);
    
    
    
    //重置开始位置
    lpBullet->setMoverPosition(Position);
    lpBullet->setMoverSpeed(speed);
    lpBullet->setPositionInPixels(CCPointMake(Position.x, Position.y));
    
    */
    return lpBullet;
}


int WBullet::getHurt(int radiusm/*,WHero *pHero*/)
{
    int hurt=0;
#if 0
    int defend=pHero->getDefence()/2;
    
    if(m_attack<0) m_attack=0;
    if(defend<0) defend=0;
    
     hurt=m_attack-defend;
    
    if(hurt <= m_attack*0.1f)
    {
        hurt=(int)(m_attack*0.1f);
    }
    
    if(radiusm < m_ExplodeRadius*0.3)
    {
    
    }
    else if(radiusm < m_ExplodeRadius*0.6)
    {
        hurt*=0.7;
    }
    else
    {
        hurt*=0.3;
    }
#endif    
#if OPEN_STRONGLEN
    if(m_lpHero)
    {
        hurt+=m_lpHero->getBuffAttack();
        
        if(m_lpHero->getCurCriticalType()!=WFadeOutHurtLabel::E_NORMAL)
        {
            hurt+=m_lpHero->getBuffCriticalAttack();
        }
    }
    
 
#endif

#if OPEN_FIFTH
    if(m_lpHero)
    {
        if(m_lpHero->getWSSkillType_s()==WBWeaponSkill::E_WEAPONSKILL_TYPE_ADDHURT)
        {
            hurt+=m_lpHero->getWSHurt();
        }
        
    }
#endif

    ///TODO
#if TARGET_IPHONE_SIMULATOR
//  hurt=10000;
#endif
  
    return hurt;
}

void WBullet::calcHurt(Vec2 lastPositon)
{
    vector<int> hurtPlayerIds;
    vector<int> hurtValue;
    
    int hurtcount=0;
#if 0    
    CCArray *pHeros=m_lpGameFrontLayer->getHeros();
  //  WHero *lpMyHero=WDDD_GLOBAL.m_lpBattleGlobal->myHero;
    
    for(int i=0; i<pHeros->count(); i++)
    {
        WHero *lpHero=(WHero *)pHeros->objectAtIndex(i);
        
        if(lpHero->getLoseNet() || lpHero->getIsDead()) continue;
        
        CCPoint heroCenter(lpHero->getMoverCenter().x+lpHero->getAnchorPointInPixels().x,lpHero->getMoverCenter().y+lpHero->getAnchorPointInPixels().y);
        CCAffineTransform toParentTranf=lpHero->nodeToParentTransform();
        heroCenter=CCPointApplyAffineTransform(heroCenter,toParentTranf);
        
        Vec2 center(heroCenter.x,heroCenter.y);
          
        
        if(WBUtil::CircleOverlap(lastPositon, m_ExplodeRadius, center,lpHero->getRadiusForHurtCheck()))
        {
        
            
            Vec2 s(lastPositon.x-center.x,lastPositon.y-center.y);
          
            
            float distance=s.Length();
            distance-=lpHero->getRadiusForHurtCheck();
            if(distance<0) distance=0.0f;
            
            int hurt=getHurt(distance,lpHero);
            
      
            if(m_SpecialType==0)//冰冻无伤害
            {
                hurt=0;
            }
            
            
            if(m_lpHero)
            {
                if(m_lpHero->getCtrlType()!=1)
                {
                    hurtValue.push_back(hurt);
                    hurtPlayerIds.push_back(lpHero->getPlayerId());
                    hurtcount++;
                    
                }         
            }
            
            
            
            WDDD_GLOBAL.m_lpBattleGlobal->m_beShootedHero.push_back(lpHero);
            
            if(m_SpecialType==-1 || m_SpecialType==2)
            {
                if(m_lpHero)
                {
                    lpHero->SendMsgHurt(m_lpHero->getPlayerId(),hurt,m_lpHero->getCurCriticalType());//发送对这个角色进行伤害
                    
                    if(lpHero->getCamp()!=m_lpHero->getCamp())m_lpHero->setPreTargetHero(lpHero);
                }
                else
                {
                    lpHero->SendMsgHurt(0,hurt,WFadeOutHurtLabel::E_NORMAL);//发送对这个角色进行伤害
                }
            }
            else if(m_SpecialType==0)//冰冻弹
            {
                lpHero->SendMsgFreeze();//不需要伤害
                if(lpHero->getCamp()!=m_lpHero->getCamp())m_lpHero->setPreTargetHero(lpHero);
            }
            else if(m_SpecialType==1)
            {
                if(m_lpHero)
                {
                    lpHero->SendMsgHurt(m_lpHero->getPlayerId(),hurt,m_lpHero->getCurCriticalType());
                    if(lpHero->getCamp()!=m_lpHero->getCamp())m_lpHero->setPreTargetHero(lpHero);
                }
                else
                {
                    lpHero->SendMsgHurt(0,hurt,WFadeOutHurtLabel::E_NORMAL);//发送对这个角色进行伤害
                }
              }
    
            else 
            {
                assert(0);//没有实现的类型
            }
            
        }
    }
    
    

    
    
    if(hurtcount>0)
    {
        if(m_lpHero)
        {
            BATTLE_Hurt *lpHurt=new BATTLE_Hurt();
            
            
            lpHurt->setBattleId(m_lpHero->getBattleId());
            lpHurt->setPlayerId(m_lpHero->getPlayerId());
            
            
            lpHurt->sethurtcount(hurtcount);
            lpHurt->setPlayerIds(hurtPlayerIds);
            lpHurt->setHurtvalue(hurtValue);
            
            WBSendProtocol(lpHurt);
        }
        
    }
#endif
}


//bool WBullet::preCollisionPostion(int prePositionIndex,int currentPositionIndex,Vec2 &position)
//{
//    assert(currentPositionIndex>=0 && currentPositionIndex<m_positionCollection.size());
//    assert(prePositionIndex<=currentPositionIndex);
//    bool collisioned=false;
//  
// //   position=m_positionCollection[currentPositionIndex];
//    
////    while(currentPositionIndex>=0)
////    {
////        Vec2 pos=m_positionCollection[currentPositionIndex];
////        
////        if(m_currentPositionIndex>0) setMoverPrePosition(m_positionCollection[currentPositionIndex-1]);
////        else                                           setMoverPrePosition(pos);
////        
////        
////        setMoverPosition(position);
////        
////        Vec2 tempTangent;
////        Vec2 newPosition(0,0);
////        bool isInSide;
////        CCArray *lpPixels=m_lpGameFrontLayer->getPixelSprites();
////        
////        int collsion=0;
////        
////        for(int i=0; i<lpPixels->count(); i++)
////        {
////            WBPixelSprite *lpPixel=(WBPixelSprite *)lpPixels->objectAtIndex(i);
////            
////            if(lpPixel->CheckCollision(this,&newPosition,&tempTangent,isInSide))
////            {
////                
////                collsion=1;
////                collisioned=true;
////                break;
////            }
////            
////        } 
////        
////        if(collsion==0)
////        {
////            break;
////        }
////        
////        position=pos;
////        
////        currentPositionIndex--;
////    }
//
//    position=m_positionCollection[currentPositionIndex];
//    
//    for(int i=prePositionIndex; i<=currentPositionIndex; i++)
//    {
//        Vec2 pos=m_positionCollection[i];
//        
//        if(i>0) setMoverPrePosition(m_positionCollection[i-1]);
//        else                                           setMoverPrePosition(pos);
//        
//        
//        setMoverPosition(position);
//        
//        Vec2 tempTangent;
//        Vec2 newPosition(0,0);
//        bool isInSide;
//        CCArray *lpPixels=m_lpGameFrontLayer->getPixelSprites();
//        
//        int collsion=0;
//        
//        for(int j=0; j<lpPixels->count(); j++)
//        {
//            WBPixelSprite *lpPixel=(WBPixelSprite *)lpPixels->objectAtIndex(j);
//            
//            if(lpPixel->CheckCollision(this,&newPosition,&tempTangent,isInSide))
//            {
//                
//                collsion=1;
//                collisioned=true;
//                break;
//            }
//            
//        } 
//        
//
//        
//        if(collsion)
//        {
//            position=newPosition;
//            break;
//        }
//        
//    }
//    
//    return collisioned;
//}

void WBullet::checkChangeToTrack()
{
    if(m_SpecialType!=1 || m_flyMode!=E_FLYMODE_NORMAL || m_trackTime<DEF_WB_BEGIN_TRACK_TIME) //追踪弹弹
    {
        return;
    }
#if 0
    float distanceMIN=INT32_MAX;
    float distance;
    WHero *nearHero=NULL;
    Vec2 normal;
    Vec2 nearNormal;
    
    for(int i=0;i<WDDD_GLOBAL.m_lpBattleGlobal->heros->count(); i++)
    {
        WHero *pHero=(WHero *)WDDD_GLOBAL.m_lpBattleGlobal->heros->objectAtIndex(i);
        
        if(pHero->getCamp()!=m_lpHero->getCamp())
        {
            normal.x=pHero->getMoverPosition().x-getMoverPosition().x;
            normal.y=pHero->getMoverPosition().y-getMoverPosition().y;
            
            
            distance=normal.Normalize();
            
            
            if(distance < DEF_WB_TRACK_DISTANCE && distance<distanceMIN
            && !pHero->getIsDead() && !pHero->getLoseNet())
            {
                distanceMIN=distance;
                nearHero=pHero;
                nearNormal=normal;
            }
            
        }
    }
    
    
    if(nearHero)
    {
        m_flyMode=E_FLYMODE_TRACK;
        
        float speed=20;//getMoverSpeed().Length();
        
        nearNormal*=speed;
        setMoverSpeed(nearNormal);
        
        m_targetHero=nearHero;
    
        m_target=WDDD_GLOBAL.m_aniManager.GetSampleAnimation(WANI_IWCO_BATTLEEFFECT, "follow");
        m_target->playRepeat();
        getParent()->addChild(m_target);
    }
#endif
}

bool WBullet::checkCollisionHero()
{
#if 0
    if(m_trackTime<DEF_WB_BEGIN_HERO_COLLSION_TIME) return false;
    
    CCArray *pHeros=m_lpGameFrontLayer->getHeros();
    //  WHero *lpMyHero=WDDD_GLOBAL.m_lpBattleGlobal->myHero;
    
    for(int i=0; i<pHeros->count(); i++)
    {
        WHero *lpHero=(WHero *)pHeros->objectAtIndex(i);
        
        CCPoint heroCenter(lpHero->getMoverCenter().x+lpHero->getAnchorPointInPixels().x,lpHero->getMoverCenter().y+lpHero->getAnchorPointInPixels().y);
        CCAffineTransform toParentTranf=lpHero->nodeToParentTransform();
        heroCenter=CCPointApplyAffineTransform(heroCenter,toParentTranf);
        
        Vec2 center(heroCenter.x,heroCenter.y);
        
        if(WBUtil::CircleOverlap(getMoverPosition(),2, center,lpHero->getRadiusForBulletCollisionCheck())
           && !lpHero->getIsDead() && !lpHero->getLoseNet())
        {
            if(m_lpHero && m_lpHero->getPlayerId()==lpHero->getPlayerId())
            {
                if(m_trackTime>DEF_WB_BEGIN_TRACK_TIME)
                {
                    return true;
                }
            }
            else
            {
                return true;
            }
        }
    }
#endif  
    return false;
}

void WBullet::checkCollision()
{
    Vec2 tempPosition;
    Vec2 tempTangent;
    bool isInSide;
    Vec2 newPosition(0,0);
    Vec2 tangent(0,0);
#if 0
    CCSize sceneSize=m_lpGameFrontLayer->getContentSizeInPixels();
   
   
    checkChangeToTrack();
    
    if(m_flyMode==E_FLYMODE_NORMAL)
    {
        setMoverAcceleration(getMoverAcceleration()+m_lpGameFrontLayer->getWind()+m_lpGameFrontLayer->getGravityFly());
    }
    else if(m_flyMode==E_FLYMODE_TRACK)
    {
        
    }
    
    updatePostion();
    
    int collsion=0;

    if(m_lpGameFrontLayer->getStencilSprite()->CheckCollision(this,&tempPosition,&tempTangent,isInSide))
    {
        newPosition+=tempPosition;
        
        collsion++;
        
    }
    
    if(collsion<=0)
    {
        if(checkCollisionHero())
        {
            newPosition=getMoverPosition();
            collsion++;
        }
    }
    
    
    if(WDDD_GLOBAL.m_lpBattleGlobal->getIsInTeach()==true)
    {
        if(collsion<=0)
        {
            GameFrontTeachLayer *pLayer=(GameFrontTeachLayer *)getGameFrontLayer();
            
            WGuai *pGuai=pLayer->getGuai();
            
            CCPoint heroCenter(pGuai->getMoverCenter().x+pGuai->getAnchorPointInPixels().x,pGuai->getMoverCenter().y+pGuai->getAnchorPointInPixels().y);
            CCAffineTransform toParentTranf=pGuai->nodeToParentTransform();
            heroCenter=CCPointApplyAffineTransform(heroCenter,toParentTranf);
            
            Vec2 center(heroCenter.x,heroCenter.y);
            
            if(WBUtil::CircleOverlap(getMoverPosition(),2, center,pGuai->getRadiusForBulletCollisionCheck()))
            {
                 pGuai->SendMsgHurt(0, 20);
                newPosition=getMoverPosition();
                collsion++;
            }
             
        }
    }
    
    if(collsion>0)
    {
        newPosition.x/=collsion;
        newPosition.y/=collsion;
        
        
        setMoverPosition(newPosition);
        setMoverPrePosition(newPosition);
        setMoverSpeed(Vec2(0,0));
        
        //WMusic::shareMusic()->PlaySound(WMusic::E_S_EXPLODE);
        
        if(m_SpecialType!=0)
        {
        
            
#if (NOT_USE_STENCIL_SPRITE == 1)
            if(m_lpHero)
            {
                m_lpGameFrontLayer->getPixelByte()->setBreakCircleImage(m_lpHero->getBulletCilcleImage(), m_lpHero->getBulletCilcleImageMark());
            }
            else if(m_lpGuai)
            {
                m_lpGameFrontLayer->getPixelByte()->setBreakCircleImage(m_lpGuai->getBulletCilcleImage(), m_lpGuai->getBulletCilcleImageMark());
            }
#if OPEN_FIFTH
            if(m_lpHero && m_lpHero->getWSSkillType_s()==WBWeaponSkill::E_WEAPONSKILL_TYPE_ATOM)
            {
                m_lpGameFrontLayer->getPixelByte()->setBreakCircleImage(m_lpGameFrontLayer->getlpCircle(), m_lpGameFrontLayer->getlpCircleMark());
            }
            
#endif //end OPEN_FIFTH
            m_lpGameFrontLayer->getPixelByte()->drawBreaken(newPosition.x, newPosition.y, m_ExplodeRadius);
            
            CCArray *lpPixelSprites=m_lpGameFrontLayer->getPixelSprites();
            
            for(int i=0; i<lpPixelSprites->count(); i++)
            {
                WBPixelSprite *lpPixel=(WBPixelSprite *)lpPixelSprites->objectAtIndex(i);
                
                if(m_lpHero)
                {
                    lpPixel->setBreakCircleImage(m_lpHero->getBulletCilcleImage(), m_lpHero->getBulletCilcleImageMark());
                }
                else if(m_lpGuai)
                {
                    lpPixel->setBreakCircleImage(m_lpGuai->getBulletCilcleImage(), m_lpGuai->getBulletCilcleImageMark());
                }
#if OPEN_FIFTH
                if(m_lpHero && m_lpHero->getWSSkillType_s()==WBWeaponSkill::E_WEAPONSKILL_TYPE_ATOM)
                {
                    lpPixel->setBreakCircleImage(m_lpGameFrontLayer->getlpCircle(), m_lpGameFrontLayer->getlpCircleMark());
                }
                
#endif
                if(lpPixel->drawBreaken(newPosition.x, newPosition.y, m_ExplodeRadius))
                {
                    lpPixel->UpdateImgToTexture();
                }
                
            }
#else
            if(m_lpHero)
            {
                m_lpGameFrontLayer->getStencilSprite()->setBreakCircleImage(m_lpHero->getBulletCilcleImage(), m_lpHero->getBulletCilcleImageMark());
            }
            else if(m_lpGuai)
            {
                m_lpGameFrontLayer->getStencilSprite()->setBreakCircleImage(m_lpGuai->getBulletCilcleImage(), m_lpGuai->getBulletCilcleImageMark());
            }
#if OPEN_FIFTH
            if(m_lpHero && m_lpHero->getWSSkillType_s()==WBWeaponSkill::E_WEAPONSKILL_TYPE_ATOM)
            {
                m_lpGameFrontLayer->getStencilSprite()->setBreakCircleImage(m_lpGameFrontLayer->getlpCircle(), m_lpGameFrontLayer->getlpCircleMark());
            }
            
#endif  //end OPEN_FIFTH
                m_lpGameFrontLayer->getStencilSprite()->drawBreaken(newPosition.x, newPosition.y, m_ExplodeRadius);
#endif //end NOT_USE_STENCIL_SPRITE
            

            
            
        }
        
        calcHurt(newPosition);
        
        if(m_emitter) m_emitter->stopSystem();
        
        
        if(m_lpHero && m_lpHero->getWSSkillType_s()==WBWeaponSkill::E_WEAPONSKILL_TYPE_ATOM)
        {
            setScale(3);
        }
        else
        {
            setScale(1.2);
        }


        if(getSpecialType()!=0)
            setAnimation(DEF_EXPLODE);
        else
            setAnimation(DEF_FREEZE);
            
        setRotation(0);
        playOnce();
        
        if(m_target)
        {
            m_target->removeFromParentAndCleanup(true);
            m_target=NULL;
            m_targetHero=NULL;
        }
        
        return;
    
    }
  
    if(m_shootType==0)
    {
        if(m_speed.x>0)
            setRotation(getRotation()+14);
        else 
            setRotation(getRotation()-14);
    }
    else
    {
        if(m_speed.x<0)
        {
            setRotation(-CC_RADIANS_TO_DEGREES(ccpToAngle(CCPointMake(getMoverSpeed().x, getMoverSpeed().y)))-3.14159265359f);
        }
        else if(m_speed.x>0)
        {
            setRotation(-CC_RADIANS_TO_DEGREES(ccpToAngle(CCPointMake(getMoverSpeed().x, getMoverSpeed().y))));
        }
        else if(m_speed.y!=0.0f)
        {
            setRotation(m_speed.y>0?-90:90);
        }
    }
    
    if(getMoverPosition().x<-100 || getMoverPosition().x>(sceneSize.width+100)
       || getMoverPosition().y<-100)
    {
        removeFromParentAndCleanup(true);
    }
    
    setPositionInPixels(CCPointMake(getMoverPosition().x, getMoverPosition().y));
    if(m_emitter) m_emitter->setPosition(getPosition());
    setMoverAcceleration(Vec2(0,0));
#endif
}


void WBullet::update(float dt)
{
 
    m_flyTime+=dt;
    
    if(m_trackTime<DEF_WB_BEGIN_TRACK_TIME)
    {
        m_trackTime++;
    }
    
#if 0
    if(getAnimationStatus()==DEF_NORMAL)
    {
     
        checkCollision();
        
        if(m_targetHero && m_target)
        {
            m_target->setPosition(m_targetHero->getPosition());
            m_target->setRotation(m_targetHero->getRotation());
        }
        
    }
    else
    {
        if(isCurrentAnimationDone()) //爆炸完了
        {
            removeFromParentAndCleanup(true);
        }
    }
#endif
}
