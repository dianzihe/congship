#include "WHero.h"
#include "WBullet.h"
#include "WFadeOutHurtLabel.h"
#include "WAnimationManager.h"
//#include "animation.h"
//#include "GameFrontLayer.h"
//#include "ddd_global.h"
//#include "WMusic.h"
//#include "CCAutoreleasePool.h"
#if OPEN_FIFTH
//#include "../battle_base/WSkillDialog.h"
#endif




//连发+1(2)   连发+2(3)  散射x3(4)
//医疗包(10) 医疗包(10) 暴怒(17)
const char AICombination1[][4]=
{
    //技能
    {2,3,4,-1},
    
    //道具
    {10,10,17,-1},
    
    //攻击四种组合
    {-2,4},//接下来是攻击组合,一共四种
    
    //连发+1 连发+2
    {2,3,-1},
    
    //连发+1 散射x3
    {2,4,-1},
    
    //连发+1 连发+2
    {2,2,-1},
    
    //连发+2 连发+2
    {3,3,-1},
    
    //辅助两种组合
    {-3,2},//接下来是辅助组合,一共2种
    
    //医疗包 医疗包
    {10,10,-1},
    
    //医疗包 
    {10,7,-1},
    
};

//攻击+30%(7)   连发+2(3)  散射x2(18)
//医疗包(10) 群体医疗(11) 追踪(13)
const char AICombination2[][4]=
{
    //技能
    {6,3,18,-1},
    
    //道具
    {10,11,13,-1},
    
    //攻击四种组合
    {-2,4},//接下来是攻击组合,一共四种
    
    //攻击+40% 连发+2
    {7,3,-1},
    
    //连发+1 散射x2
    {3,18,-1},
    
    //攻击+30% 散射x2
    {7,18,-1},
    
    //攻击+30% 攻击+30%
    {7,7,-1},
    
    //辅助两种组合
    {-3,2},//接下来是辅助组合,一共2种
    
    //医疗包 连发+2
    {10,3,-1},
    
    //医疗包 
    {11,13,-1},
    
};


//攻击+50%(5)   攻击+40%(6)  攻击+30%(7) 
//医疗包(10) 医疗包(10) 医疗包(10) 
const char AICombination3[][4]=
{
    //技能
    {5,6,7,-1},
    
    //道具
    {10,10,10,-1},
    
    //攻击四种组合
    {-2,4},//接下来是攻击组合,一共四种
    
    //攻击+50% 攻击+30%
    {5,7,-1},
    
    //攻击+40% 攻击+40%
    {4,4,-1},
    
    //攻击+50% 
    {5,-1},
    
    //攻击+50%
    {7,-1},
    
    //辅助两种组合
    {-3,3},//接下来是辅助组合,一共3种
    
    //医疗包 攻击+30%
    {10,7,-1},
    
    //医疗包 
    {4,10,-1},
    
    {10,-1},
    
};



WHero::WHero():
m_currentUsedItems(NULL),
//m_lpSCCharacter(NULL),
m_lpSpecialEffect(NULL),
m_pAngryFire(NULL),
m_BulletAni(NULL),
m_BulletAniAngry(NULL),
m_BulletAniExplode(NULL),
m_BulletAniRear(NULL),
m_BulletAniFreezeExplode(NULL),
m_BulletCilcleImage(NULL),
m_IsStandby(true),
m_newRunStatus(DEF_ST_NORMAL),
m_runStatus(DEF_ST_NORMAL),
m_face(1),
m_PointsUsedCount(0),
m_isShowPoint(false),
m_IsTouchControlStarted(false),
m_ctrlType(0),
m_IsInit(false),
m_fly(false),
m_bulletSpecialType(-1),
m_isFreeze(false),
m_currentWBEvent(NULL),
m_isDead(false),
m_HideRoundLast(0),
m_FreezeLastRound(0),
m_isHide(false),
m_loseNet(false),
m_FlyLockLastRound(0),
m_isCollsionPre(false),
m_needCheckCollsion(true),
m_aiCtrlId(0),
m_useItem(false),
m_preTargetHero(NULL),
m_BuffAttack(0),
m_BuffCriticalAttack(0),
m_BuffMovePFCostRate(1.0),
m_lpWeaponSkillEffect(NULL)
{
    setTag(DEF_OBJ_TYPE_MAN);
    PropertyRoundClear();
  //  m_SP=0;
    setSP(0);
    
    setScale(0.7f);
    
    //st_shoot_speed.Set(0, 0);
    
#if OPEN_FIFTH
    m_weaponSkills=CCArray::array();
    m_weaponSkills->retain();
    
     m_WSSpecial=NULL;
    clearWeaponSkill();
    
    clearWeaponSkill_s();

   
#endif
}


WHero::~WHero()
{
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
    stop();
  
    //CC_SAFE_RELEASE_NULL(m_lpSCCharacter); ///< 商城的角色形象
    CC_SAFE_RELEASE_NULL(m_lpPlayerIcon);
    CC_SAFE_RELEASE_NULL(m_BulletAni);                ///< 炮弹动画
    CC_SAFE_RELEASE_NULL(m_BulletAniAngry);      ///< 爆怒炮弹动画
    CC_SAFE_RELEASE_NULL(m_BulletAniExplode);  ///< 炮弹爆炸
    CC_SAFE_RELEASE_NULL(m_BulletAniFreezeExplode);
    CC_SAFE_RELEASE_NULL(m_BulletAniRear);        ///< 炮弹尾巴
    
#if OPEN_FIFTH
    CC_SAFE_RELEASE_NULL(m_weaponSkills);
#endif

    //DeleteObject(m_BulletCilcleImage);
	//DeleteObject(m_BulletCilcleImageMark);
}

void WHero::start()
{
    if(m_IsInit) scheduleUpdate();
}

void WHero::stop()
{
    unscheduleUpdate();
}

void WHero::onEnter()
{
    Sprite::onEnter();
    
    ClearEventQueue();
    
    PropertyRoundClear();
    
}

void WHero::buildAiCombination()
{
    const char (*pAiCombination)[4];
    
    setAiCtrlId(getAiCtrlId()%3);
    
    switch (getAiCtrlId())
    {
        default:
        case 0:
            pAiCombination=&AICombination1[0];
            break;
            
        case 1:
            pAiCombination=&AICombination2[0];
            break;
            
        case 2:
            pAiCombination=&AICombination3[0];
            break;
            
    }
	/*
    m_AICombination.skills.clear();
    for(int i=0; i<4; i++)
    {
        m_skills[i].setUsed(0);
        if(pAiCombination[0][i]==-1) break;
        
        m_AICombination.skills.push_back(pAiCombination[0][i]);  
        m_skills[i].setUsed(1);    
        m_skills[i].setId(pAiCombination[0][i]);
                                          
    }
    
    m_skills[3].setUsed(-1);
    
   m_AICombination.items.clear();
    for(int i=0; i<4; i++)
    {
        m_items[i].setUsed(0);
        if(pAiCombination[1][i]==-1) break;
        
        m_AICombination.items.push_back(pAiCombination[1][i]);   
        m_items[i].setUsed(1);      
        m_items[i].setId(pAiCombination[1][i]);                               
    }
    
    m_items[3].setUsed(-1);
    
    
    m_AICombination.attack_plan.clear();
    int k=pAiCombination[2][1];
    int l=3+k;
    for(int i=0; i<k; i++)
    {
        
        char *plan=new char[4];
        
        
        for(int j=0; j<4; j++)
        {
            plan[j]=pAiCombination[3+i][j];
            
            if(plan[j]==-1)
            {
                break;
            }
        }
        
        m_AICombination.attack_plan.push_back(plan);                                        
    }
    
    
   m_AICombination.assistant_plan.clear();
    int m=pAiCombination[l][1];
    l++;
    
    for(int i=0; i<m; i++)
    {
        
        char *plan=new char[4];
        
        
        for(int j=0; j<4; j++)
        {
            plan[j]=pAiCombination[l+i][j];
            
            if(plan[j]==-1)
            {
                break;
            }
        }
        
        m_AICombination.assistant_plan.push_back(plan);                                        
    }
    */
    
 
}





void WHero::getCircleImg(const string &path,Image **pCircle,Image **pCircleMark)
{
#if 0
    CCImage *pImg=new CCImage();
    if(!pImg->initWithImageFile(path.c_str(),pImg->kFmtPng,true))
    {
        *pCircle=NULL;
        *pCircleMark=NULL;
        
        pImg=NULL;//没有就让他闪吧
        
    }
    
    int *lpCircleBuf=  NULL;
    int *lpCircleMarkBuf=NULL;
   

    
    if(pImg->getWidth()>pImg->getHeight())
    {    
        int rectWidth=pImg->getWidth()/2;
        int rectHeight=pImg->getHeight();
        
        lpCircleBuf=new int[rectWidth*rectHeight];
        memset(lpCircleBuf, 0, rectWidth*rectHeight*4);
        Rect rect;

        rect.x=0;
        rect.y=0;
        rect.w=rectWidth;
        rect.h=rectHeight;
        
        Image::BitBlt32(lpCircleBuf, rectWidth, rectHeight, 0, 0, pImg->getData(), pImg->getWidth(), pImg->getHeight(), &rect);
        
        *pCircle = new Image();
        (*pCircle)->initWithBuf32((byte *)lpCircleBuf,rectWidth,rectHeight);
        
        lpCircleMarkBuf=new int[rectWidth*rectHeight];
        memset(lpCircleMarkBuf, 0, rectWidth*rectHeight*4);
           
        rect.x=rectWidth;
        rect.y=0;
        rect.w=rectWidth;
        rect.h=rectHeight;
        
        Image::BitBlt32(lpCircleMarkBuf, rectWidth, rectHeight, 0, 0, pImg->getData(), pImg->getWidth(), pImg->getHeight(), &rect);
        
        *pCircleMark = new Image();
        (*pCircleMark)->initWithBuf32((byte *)lpCircleMarkBuf,rectWidth,rectHeight);
        
    }
    else 
    {
    
        int rectWidth=pImg->getWidth();
        int rectHeight=pImg->getHeight()/2;
        
        lpCircleBuf=new int[rectWidth*rectHeight];
        memset(lpCircleBuf, 0, rectWidth*rectHeight*4);
        Image::Rect rect;
        
        rect.x=0;
        rect.y=0;
        rect.w=rectWidth;
        rect.h=rectHeight;
        
        Image::BitBlt32(lpCircleBuf, rectWidth, rectHeight, 0, 0, pImg->getData(), pImg->getWidth(), pImg->getHeight(), &rect);
        
        *pCircle = new Image();
        (*pCircle)->initWithBuf32((byte *)lpCircleBuf,rectWidth,rectHeight);
        
        lpCircleMarkBuf=new int[rectWidth*rectHeight];
        memset(lpCircleMarkBuf, 0, rectWidth*rectHeight*4);
        
        rect.x=0;
        rect.y=rectHeight;
        rect.w=rectWidth;
        rect.h=rectHeight;
        
        Image::BitBlt32(lpCircleMarkBuf, rectWidth, rectHeight, 0, 0, pImg->getData(), pImg->getWidth(), pImg->getHeight(), &rect);
        
        *pCircleMark = new Image();
        (*pCircleMark)->initWithBuf32((byte *)lpCircleMarkBuf,rectWidth,rectHeight);
    }
    
    DeleteObject(pImg);
#endif
}


WHero *WHero::BuildHero(const vector<string> &strList,int boyOrGirl, int weaponType)
{
    WHero *lpHero=new WHero();
    lpHero->autorelease();
    
    //map<string,string> desc=WDDD_GLOBAL.m_aniManager.TransToAnimationDesc(strList);
	map<string, string> desc;
    string iwco_name;
    
    lpHero->m_weaponType=weaponType;
    
    if(boyOrGirl==0)
    {
        iwco_name=WANI_IWCO_BATTLEBOY;
    }
    else
    {
         iwco_name=WANI_IWCO_BATTLEGIRL;
    }     
    
    //一般待机    
    WAnimationManager::addAnimationToCharater(iwco_name, "standby1", lpHero, WHero::DEF_NORMAL, desc,0.2,true);

    //待机2
    WAnimationManager::addAnimationToCharater(iwco_name, "standby2", lpHero, WHero::DEF_NORMAL_2, desc,0.2,true);

    //胜利手式
    WAnimationManager::addAnimationToCharater(iwco_name, "standby3", lpHero, WHero::DEF_SUREWIN, desc,0.2,true);
  
    //使用道具动画
     WAnimationManager::addAnimationToCharater(iwco_name, "itemskill", lpHero, WHero::DEF_ITEMSKILL, desc,0.2,true);
 
    //移动
    WAnimationManager::addAnimationToCharater(iwco_name, "move", lpHero, WHero::DEF_MOVE, desc,0.2,true);
    
    //开始射击动画 
    if(weaponType==0) { 
		WAnimationManager::addAnimationToCharater(iwco_name, 
			"attackstart1-t", 
			lpHero, 
			WHero::DEF_SHOOT_START, 
			desc,
			0.1,
			true);
	}else{ 
		WAnimationManager::addAnimationToCharater(iwco_name, "attackstart1-s", lpHero, WHero::DEF_SHOOT_START, desc,0.1,true);}
   
    
    //重复射击动画
    if(weaponType==0) { 
		WAnimationManager::addAnimationToCharater(iwco_name, "attackstart1-t2", lpHero, WHero::DEF_SHOOT_REPEAT, desc,0.1,true);}
    else{ 
		WAnimationManager::addAnimationToCharater(iwco_name, "attackstart1-s2", lpHero, WHero::DEF_SHOOT_REPEAT, desc,0.1,true);}
 
       
    //射击结束
    if(weaponType==0) { 
		WAnimationManager::addAnimationToCharater(iwco_name, "attack1-t", lpHero, WHero::DEF_SHOOT_END, desc,0.1,true);}
    else{ 
		WAnimationManager::addAnimationToCharater(iwco_name, "attack1-s", lpHero, WHero::DEF_SHOOT_END, desc,0.1,true);}
    
 

    //开始射击动画(大招)
    if(weaponType==0) { 
		WAnimationManager::addAnimationToCharater(iwco_name, "attackstart2-t", lpHero, WHero::DEF_SHOOT_BIG_START, desc,0.1,true);}
    else{ 
		WAnimationManager::addAnimationToCharater(iwco_name, "attackstart2-s", lpHero, WHero::DEF_SHOOT_BIG_START, desc,0.1,true);}
    

    //重复射击动画(大招)
    if(weaponType==0) { 
		WAnimationManager::addAnimationToCharater(iwco_name, "attackstart2-t2", lpHero, WHero::DEF_SHOOT_BIG_REPEAT, desc,0.1,true);}
    else{ 
		WAnimationManager::addAnimationToCharater(iwco_name, "attackstart2-s2", lpHero, WHero::DEF_SHOOT_BIG_REPEAT, desc,0.1,true);}
    
    //射击结束(大招)
    if(weaponType==0) { 
		WAnimationManager::addAnimationToCharater(iwco_name, "attack2-t", lpHero, WHero::DEF_SHOOT_BIG_END, desc,0.1,true);}
    else{ 
		WAnimationManager::addAnimationToCharater(iwco_name, "attack2-s", lpHero, WHero::DEF_SHOOT_BIG_END, desc,0.1,true);}
 
    //鬼魂
    WAnimationManager::addAnimationToCharater(iwco_name, "ghost", lpHero, WHero::DEF_GHOST, desc,0.2);
    
    bool dontHaveWing=false;
    
    if(desc.find("wing")==desc.end())
    {
        dontHaveWing=true;
    }
    
    if(dontHaveWing)
    {
        desc.insert(pair<string,string>("effects","fly1"));
    }
    //飞行
    WAnimationManager::addAnimationToCharater(iwco_name, "fly", lpHero, WHero::DEF_FLY, desc,0.1,true);

    iwco_name=WANI_IWCO_BATTLEEFFICIENTS;
    
    if(dontHaveWing)
    {
        desc.erase("effects");
    }
    //受到伤害
    WAnimationManager::addAnimationToCharater(iwco_name, "binjured", lpHero, WHero::DEF_HURT, desc,0.2);

    
    /**
     * @brief 找到武器对应的炮弹
     */
    string weapon=desc["weapon"];
    map<string,string> bulletDesc;
          
    bulletDesc.insert(pair<string,string>("weapon",weapon));
#if 0
    //使用的炮弹   
    lpHero->m_BulletAni=AnimationPool::sharedAnimationPool()->animation(iwco_name, "fly1", bulletDesc);
    lpHero->m_BulletAni->setDelay(0.1);
    lpHero->m_BulletAni->retain();   
  
    lpHero->m_BulletAniAngry=cwSngAnimationPool::sharedAnimationPool()->animation(iwco_name, "fly2", bulletDesc);
    lpHero->m_BulletAniAngry->setDelay(0.1);
    lpHero->m_BulletAniAngry->retain();   

  
    //爆炸后面的编号是'c'
    int pos=weapon.find_last_of('a');
    weapon.replace(pos, 1, 1,'c');
    bulletDesc["weapon"]=weapon;
    
    
    lpHero->m_BulletAniExplode=cwSngAnimationPool::sharedAnimationPool()->animation(iwco_name, "blasting", bulletDesc);
    lpHero->m_BulletAniExplode->setDelay(0.1);
    lpHero->m_BulletAniExplode->retain();  
    
    //爆炸尾巴后面的编号是'b'
    pos=weapon.find_last_of('c');
    weapon.replace(pos, 1, 1,'b');
    bulletDesc["weapon"]=weapon;
#endif   
//    pAniFrames=lpIwcoManager->GetAnimationFrames(lpIwcoManager->GetAnimation("locus"), bulletDesc, true);
//    lpHero->m_BulletAniRear=WCharacter::AnimationWithWAnimationFrames(pAniFrames,0.15);
//    lpHero->m_BulletAniRear->retain();   
//    DeleteObject(pAniFrames);
    
    
    //TODO TODO TODO
    //爆炸后使用的挖坑图
    weapon.append(".png");
    string circleImagePath=DEF_EXPLODE_IMAGE_PATH;
    circleImagePath.append(weapon);
  
    
    lpHero->getCircleImg(circleImagePath,&(lpHero->m_BulletCilcleImage),&(lpHero->m_BulletCilcleImageMark));
    
    if(lpHero->m_BulletCilcleImage==NULL || lpHero->m_BulletCilcleImageMark==NULL)//找不到默认一个
    {
        circleImagePath=DEF_EXPLODE_IMAGE_PATH;
        circleImagePath.append("weapon1b.png");
        lpHero->getCircleImg(circleImagePath,&(lpHero->m_BulletCilcleImage),&(lpHero->m_BulletCilcleImageMark));
    }
   // lpHero->m_BulletCilcleImage=NULL;
//   lpIwcoManager->GetFrameImage(lpIwcoManager->GetIwco_frameFromIwcoAnimation(lpIwcoManager->GetAnimation("bombrange"), 0), bulletDesc, false);
   // lpHero->m_BulletCilcleImageMark=NULL;
//    lpIwcoManager->GetFrameImage(lpIwcoManager->GetIwco_frameFromIwcoAnimation(lpIwcoManager->GetAnimation("bombpattern"), 0), bulletDesc, true);
    
    lpHero->setAnimation(WHero::DEF_NORMAL);
#if 0   
    WBRect collisionRect;
    
    collisionRect.m_LeftTop.x=0;
    collisionRect.m_LeftTop.y=lpHero->getContentSizeInPixels().height;
    collisionRect.m_RightBottom.x=lpHero->getContentSizeInPixels().width;
    collisionRect.m_RightBottom.y=0;
    

     //   collisionCircle.
    Vec2 achor(lpHero->getAnchorPointInPixels().x,lpHero->getAnchorPointInPixels().y);
    Vec2 center(0,20);//(lpHero->getContentSizeInPixels().width/2,lpHero->getContentSizeInPixels().height/2);
    
 //   center-=achor;

    lpHero->setMoverCenter(center);
    lpHero->setMoverRadius(10);//(lpHero->getContentSizeInPixels().width+lpHero->getContentSizeInPixels().height)/8);
   
    lpHero->setRadiusForHurtCheck(lpHero->getContentSizeInPixels().width/2*0.8);
    lpHero->setRadiusForBulletCollisionCheck(lpHero->getContentSizeInPixels().width/2*0.5);
#endif
    if(boyOrGirl==0)
    {
        iwco_name=WANI_IWCO_SHOPBOY;
    }else{
        iwco_name=WANI_IWCO_SHOPGIRL;
    }
    
    desc.erase("weapon");
    
    //创建商城形象,用于大招
    //lpHero->m_lpSCCharacter=WShopCharacter::shopCharaWithDesc(desc, boyOrGirl);
    //lpHero->m_lpSCCharacter->retain();
    
    
    lpHero->m_lpPlayerIcon=Sprite::create();
    lpHero->m_lpPlayerIcon->retain();
    desc.erase("weapon");
    desc.erase("bbody");
    desc.erase("wing");
    
    if(boyOrGirl==0)
    {
        iwco_name=WANI_IWCO_BATTLEBOY;
    }
    else
    {
        iwco_name=WANI_IWCO_BATTLEGIRL;
    }
    WAnimationManager::addAnimationToCharater(iwco_name, "standby1",lpHero->m_lpPlayerIcon, 0, desc,0.2,true);
  //  lpHero->m_lpPlayerIcon->setAnchorPoint(CCPointMake(0.5, 0.5));
    
    desc.clear();//不需要任何描述,都使用的默认
    
    //创建特效对象
#if 0
    lpHero->m_lpSpecialEffect=Sprite::node();
    //lpHero->m_lpSpecialEffect->retain();
    lpHero->addChild(lpHero->m_lpSpecialEffect);
    lpHero->m_lpSpecialEffect->setIsVisible(false);//开始不用显示
    lpHero->m_lpSpecialEffect->setPosition(CCPointMake(lpHero->getAnchorPoint().x*lpHero->getContentSize().width, lpHero->getAnchorPoint().y*lpHero->getContentSize().height));
#endif
    iwco_name=WANI_IWCO_BATTLEEFFECT;
 
    WAnimationManager::addAnimationToCharater(iwco_name, "frozen1",lpHero->m_lpSpecialEffect, WHero::DEF_SE_FROZEN_1, desc,0.1);
    WAnimationManager::addAnimationToCharater(iwco_name, "frozen3",lpHero->m_lpSpecialEffect, WHero::DEF_SE_FROZEN_2, desc,0.5);
    WAnimationManager::addAnimationToCharater(iwco_name, "use",lpHero->m_lpSpecialEffect, WHero::DEF_SE_USE_ITEM, desc,0.1);
    WAnimationManager::addAnimationToCharater(iwco_name, "blood",lpHero->m_lpSpecialEffect, WHero::DEF_SE_ADD_BLOOD, desc,0.1);
    WAnimationManager::addAnimationToCharater(iwco_name, "hide",lpHero->m_lpSpecialEffect, WHero::DEF_SE_HIDE, desc,0.1);
    WAnimationManager::addAnimationToCharater(iwco_name, "specialeffects1",lpHero->m_lpSpecialEffect, WHero::DEF_SE_BIGSKILL, desc,0.1);
    
#if 0
    lpHero->m_lpSpecialEffect->setAnimation(WHero::DEF_SE_USE_ITEM);
	lpHero->m_lpSpecialEffect->PlayRepeat();
    lpHero->m_lpSpecialEffect->setIsVisible(false);//开始不用显示
    
    lpHero->m_BulletAniFreezeExplode=cwSngAnimationPool::sharedAnimationPool()->animation(iwco_name, "frozen2", desc);
    lpHero->m_BulletAniFreezeExplode->setDelay(0.1);
    lpHero->m_BulletAniFreezeExplode->retain();
    
    lpHero->m_pAngryFire=Sprite::node();
   
    WAnimationManager::addAnimationToCharater(iwco_name, "anger1",lpHero->m_pAngryFire, 0, desc,0.1);
    lpHero->m_pAngryFire->setAnimation(0);
    lpHero->m_pAngryFire->setIsVisible(false);
    lpHero->m_pAngryFire->setPositionInPixels(lpHero->getAnchorPointInPixels());
	lpHero->addChild(lpHero->m_pAngryFire,-1);
#endif
    
  //   lpHero->addChild(CCSprite::node());
    lpHero->m_IsInit=true;
    
//    lpHero->m_emitter->retain();
//	lpHero->addChild(lpHero->m_emitter, -10);
//    
//    lpHero->m_emitter->setPosition(CCPointZero);
//	lpHero->m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("gameResources/battle/hud/fire.png") );
//    lpHero->m_emitter->setPositionType(kCCPositionTypeRelative);
    return lpHero;
}


#if 0
void WHero::draw()
{
    
    Sprite::draw();

#if 0//TARGET_IPHONE_SIMULATOR    
    CCPoint orignal=getAnchorPointInPixels();
    orignal.x/=2;
    orignal.y/=2;
   
    glLineWidth(5.0f);
    
    glColor4f(.0f, .0f, .0f, 1.0f);
    ccDrawLine(CCPointMake(-20+orignal.x, -18+orignal.y), CCPointMake(20+orignal.x, -18+orignal.y));
    glColor4f(0.0f, .0f, 0, 1.0f);
    ccDrawLine(CCPointMake(-20+orignal.x, -15+orignal.y), CCPointMake(20+orignal.x, -15+orignal.y));
    
    glColor4f(1.0f, 0, 0, 1.0f);  
    ccDrawLine(CCPointMake(-20+orignal.x, -18+orignal.y), CCPointMake(-20+40*m_HP/m_maxHP+orignal.x, -18+orignal.y));
    glColor4f(0.0f, 1.0f, 0, 1.0f);
    ccDrawLine(CCPointMake(-20+orignal.x, -15+orignal.y), CCPointMake(-20+40*m_PF/m_maxPF+orignal.x, -15+orignal.y));
    
   
    CCPoint anchor=getAnchorPointInPixels();
    
    anchor.x/=CC_CONTENT_SCALE_FACTOR();
    anchor.y/=CC_CONTENT_SCALE_FACTOR();

    CCPoint p(getMoverCenter().x+getAnchorPointInPixels().x,getMoverCenter().y+getAnchorPointInPixels().y);
    p.x/=CC_CONTENT_SCALE_FACTOR();
    p.y/=CC_CONTENT_SCALE_FACTOR();
        
    ccDrawCircle(p,getRadiusForBulletCollisionCheck()/(0.7*CC_CONTENT_SCALE_FACTOR()),360,20,false); 
    glColor4f(1.0, 0, 0, 1.0f);
    ccDrawCircle(p,getRadiusForHurtCheck()/(0.7*CC_CONTENT_SCALE_FACTOR()),360,20,false); 
#endif
    
    
    if( m_isShowPoint
    && getRunStatus() == DEF_ST_NORMAL
    && m_PointsUsedCount > 0 )
    {
        GLfloat oldColor[4];
        GLfloat oldPointSize;
        
        
        glGetFloatv(GL_CURRENT_COLOR, oldColor);
        glGetFloatv(GL_POINT_SIZE, &oldPointSize);
        GLfloat rate;
        GLfloat size;
        
        CCPoint anchor=getAnchorPointInPixels();
        anchor.x/=CC_CONTENT_SCALE_FACTOR();
        anchor.y/=CC_CONTENT_SCALE_FACTOR();
        
        if(CC_CONTENT_SCALE_FACTOR()==1)
        {
            size=2.5f;
        }
        else
        {
            size=5.0f;
        }
        
        ccColor3B c;
        if(WDDD_GLOBAL.m_lpBattleGlobal->getIsInTeach()==false)
        {
            c=getGameFrontLayer()->getPointColor();
        }
        else
        {
            c=getGameFrontTeachLayer()->getPointColor();
        }
        
        for(int i=0; i<m_PointsUsedCount; i++)
        {      
            rate=((float)(m_PointsUsedCount-i+1))/m_PointsUsedCount;
            
            glColor4f(c.r, c.g, c.b, rate);
            glPointSize(size*rate);
            ccDrawPoint(CCPointMake(m_Points[i].x+anchor.x,m_Points[i].y+anchor.y));
        }
        
        glColor4f(oldColor[0], oldColor[1], oldColor[2], oldColor[3]);
        glPointSize(oldPointSize);
        
        
    }
    
    
    
    
}
#endif

void WHero::PropertyRoundClear()
{

//    m_PF=m_maxPF;
    setPF(getMaxPF());
    m_isCriticalhit=false;
    m_AttackMultiple=1.0f;
    m_AttackTimes=1;
    m_AttackDivideNum=1;
    m_isBigSkill=false;
    m_bulletSpecialType=-1;
    
    m_isItemFly=false;
    
    m_fly=false;
    
#if OPEN_FIFTH
    clearWeaponSkill_s();
#endif

    if(m_currentUsedItems)
    {
        m_currentUsedItems->removeAllObjects();
        m_currentUsedItems->release();
        m_currentUsedItems=NULL;
    }
#if 0    
    if(m_pAngryFire)
    {
        if(m_pAngryFire->getIsVisible())
        {
            m_pAngryFire->setIsVisible(false);
            m_pAngryFire->stopPlay();
        }
    }
#endif
}

void WHero::SendMsgNormal()
{
    SendEventToQueue(new WBEvent(DEF_ST_NORMAL,0));
}


void WHero::SendMsgMove(const Vec2 &pos,int leftOrRight,int st_move_times)
{
    WBEvent *lpEvent;
    
    MOVE_STRUCT *pMove=new MOVE_STRUCT();
    pMove->startPos=pos;
    pMove->times=st_move_times;
    
    if(leftOrRight==1) 
    {
        lpEvent=new WBEvent(DEF_ST_MOVE_LEFT,0);
    }
    else
    {
        lpEvent=new WBEvent(DEF_ST_MOVE_RIGHT,0);
    }            
    
    lpEvent->setData(pMove);
    
    SendEventToQueue(lpEvent);
    
}

void WHero::SendMsgShoot(const CCPoint &startPos,const Vec2 &speed,int face)
{
    SHOOT_OR_FLY_STRUCT *lpShoot=new SHOOT_OR_FLY_STRUCT();
    lpShoot->startPos=startPos;
    lpShoot->speed=speed;
    lpShoot->face=face;
    
    WBEvent *lpEvent=new WBEvent(DEF_ST_SHOOT,0);
    lpEvent->setData(lpShoot);
    
    SendEventToQueue(lpEvent);

}

void WHero::SendMsgFly(const CCPoint &startPos,const Vec2 &speed,int face)
{
    SHOOT_OR_FLY_STRUCT *lpShoot=new SHOOT_OR_FLY_STRUCT();
    lpShoot->startPos=startPos;
    lpShoot->speed=speed;
    lpShoot->face=face;
    WBEvent *lpEvent=new WBEvent(DEF_ST_FLY,0);
    lpEvent->setData(lpShoot);
    
    SendEventToQueue(lpEvent);
}

void WHero::SendMsgUseItem(int type,int subtype)
{
    WBEvent *lpEvent;

    lpEvent=new WBEvent(DEF_ST_ITEMSKILL,0);
              
    int *p=new int[2];
    p[0]=type;
    p[1]=subtype;
    lpEvent->setData(p);
    
    SendEventToQueue(lpEvent);
}



void WHero::SendMsgDeath()
{
    
    SendEventToQueue(new WBEvent(DEF_ST_DEATH,0));
}

void WHero::SendMsgFreeze()
{
    SendEventToQueue(new WBEvent(DEF_ST_FREEZE,0));
}

void WHero::SendMsgHurt(int playerid,int hurtValue,int criticalType)
{
    WBEvent *lpEvent;
    
    lpEvent=new WBEvent(DEF_ST_HURT,0);
    
    HURT_STRUCT *lpHurt=new HURT_STRUCT();
    lpHurt->playerId=playerid;
    lpHurt->hurt=hurtValue;
    lpHurt->ciriticalType=criticalType;
    lpEvent->setData(lpHurt);
    
    SendEventToQueue(lpEvent);
}

void WHero::SendMsgBIGSKILL()
{

    SendEventToQueue(new WBEvent(DEF_ST_BIGSKILL,0));
}

#if OPEN_FIFTH
void WHero::CheckWeaponSkillTouchOff()
{
#if 0
    CCObject *pNode;
    WBWeaponSkill* pSkill;
    int index=0;
    
  //  WSkillDialog *pDialog=NULL;
    
    CCARRAY_FOREACH(m_weaponSkills, pNode)
    {
        pSkill=(WBWeaponSkill *)pNode;
        
       
        if(pSkill->isVailable(WDDD_GLOBAL.m_lpBattleGlobal->getBattleRandNum()[index]))
        {
//            if(pDialog==NULL) pDialog=WSkillDialog::node();
//            
//            pDialog->pushString(pSkill->getSkillName());

            CCLOG("%s",pSkill->getSkillName().c_str());
           // pSkill->setSkillType(11);
            WFadeOutLabel *pFade =WFadeOutLabel::LabelWithString(ccpAdd(getPositionInPixels(), CCPointMake(0, GET_RIGHT_TXT_SIZE(12))), pSkill->getSkillName());
            CCLayer *pLayer=(CCLayer *)getParent();
            pLayer->addChild(pFade);
            processWeaponSkill(pSkill);
            
            break;
           
        }
        
        index++;
        
        if(index>=WDDD_GLOBAL.m_lpBattleGlobal->getBattleRandNum().size()) index=0;
    }
    
//    if(pDialog)
//    {
//        getGameFrontLayer()->getBattleScene()->getHudLayer()->addChild(pDialog);
//    }
    
    
    
    if(getWSSkillType_s()==WBWeaponSkill::E_WEAPONSKILL_TYPE_CAROM
       || getWSSkillType_s() ==WBWeaponSkill::E_WEAPONSKILL_TYPE_FOLLOW
       || getWSSkillType_s() == WBWeaponSkill::E_WEAPONSKILL_TYPE_ATOM
       || getWSSkillType_s() == WBWeaponSkill::E_WEAPONSKILL_TYPE_ADDATTACK)
    {
        m_AttackTimes+=m_WSAttackTimesUp;
        m_AttackMultiple*=m_WSAttackLowdownRate*m_WSAttackRate;
            
    }
    
    if(getWSSkillType_s()==WBWeaponSkill::E_WEAPONSKILL_TYPE_FOLLOW)
    {
        setBulletSpecialType(1);
    }
    else if(getWSSkillType_s()==WBWeaponSkill::E_WEAPONSKILL_TYPE_ATOM)
    {
        setBulletSpecialType(2);
    }
#endif
}

void WHero::clearWeaponSkill_s()
{
    m_WSAttackRate=1; ///< 武器技能,攻击力增副
    m_WSHurt=0;///< 伤害增加
    m_WSIsCriticalAttack=0;///< 是不是暴击
    m_WSGetHurtToBloodRate=0; ///< 获取攻击百分之多少加血
    m_WSAttackLowdownRate=1; ///< 攻击力下降百分比
    m_WSAttackTimesUp=0;///< 攻击次数上升
    m_WSIsFollowAttack=0; ///< 是否跟跟踪
    m_WSIsAttom=0; ///< 是否原子弹
    
    m_WSSkillType_s=-1;
    m_WSLastHurt_s=0; ///< 持续伤害
    m_WSLastHurtRound_s=0;///< 持续伤害剩作回合数
    m_WSLastTired_s=0;///< 持续降低体力上限
    m_WSLastTiredRound_s=0;///< 持续降低体力上限回合数
    m_WSLastSeal_s=0;///< 持续封印
    m_WSLastSealRound_s=0;///<持续封印回合数
}
#if 0
void WHero::processWeaponSkill(const WBWeaponSkill *lpSkill)
{
    if(lpSkill==NULL) return;
    
     
    switch (lpSkill->getSkillType())
    {
        case WBWeaponSkill::E_WEAPONSKILL_TYPE_ADDATTACK:///< 增加攻击力
        {
            m_WSSkillType_s = lpSkill->getSkillType();
            m_WSAttackRate=1.0f+lpSkill->getSkillParam1()/10000.0f;
        }
        break;
        case WBWeaponSkill::E_WEAPONSKILL_TYPE_ADDHURT:///< 增加伤害
        {
            m_WSSkillType_s = lpSkill->getSkillType();
            m_WSHurt          = lpSkill->getSkillParam1();
        }
        break;
        case WBWeaponSkill::E_WEAPONSKILL_TYPE_ADDCRITICALRATE:///< 增加爆击率
        {
            if(WDDD_GLOBAL.m_lpBattleGlobal->getBattleRandNum().size()>=2
            &&lpSkill->getSkillParam1()>=WDDD_GLOBAL.m_lpBattleGlobal->getBattleRandNum()[1])
            {
                m_WSSkillType_s = lpSkill->getSkillType();
                m_WSIsCriticalAttack = 1;
            }
        }
        break;
        case WBWeaponSkill::E_WEAPONSKILL_TYPE_LASTHURT:///< 灼伤持续扣血
        {
            m_WSSkillType_s                = lpSkill->getSkillType();
            m_WSLastHurt_s              = lpSkill->getSkillParam1();
            m_WSLastHurtRound_s  =lpSkill->getSkillParam2();
        }
        break;
        case WBWeaponSkill::E_WEAPONSKILL_TYPE_LOSETIREDVALUE :///< 降低疲劳上限
        {
            m_WSSkillType_s                  = lpSkill->getSkillType();
            m_WSLastTired_s              = lpSkill->getSkillParam1();
            m_WSLastTiredRound_s  =lpSkill->getSkillParam2();
        }
        break;
        case WBWeaponSkill::E_WEAPONSKILL_TYPE_GRAVITY:///< 无法飞行
        {
            m_WSSkillType_s                = lpSkill->getSkillType();
            m_WSLockFlyRound_s   = lpSkill->getSkillParam1();
        }
        break;
        case WBWeaponSkill::E_WEAPONSKILL_TYPE_GETHURTTOBLOOD:///< 吸收伤害加血
        {
            m_WSSkillType_s                = lpSkill->getSkillType();
            m_WSGetHurtToBloodRate = lpSkill->getSkillParam1()/10000.0f;
        }
        break;
        case WBWeaponSkill::E_WEAPONSKILL_TYPE_SEAL:///< 封印
        {
            m_WSSkillType_s                       = lpSkill->getSkillType();
            m_WSLastSeal_s                     =1;
            m_WSLastSealRound_s = lpSkill->getSkillParam1();
        }
        break;
        case WBWeaponSkill::E_WEAPONSKILL_TYPE_CAROM:///< 连击
        {
            m_WSSkillType_s                       = lpSkill->getSkillType();
            m_WSAttackLowdownRate = lpSkill->getSkillParam1()/10000.0f;
            m_WSAttackTimesUp           = lpSkill->getSkillParam2();
        }
        break;
        case WBWeaponSkill::E_WEAPONSKILL_TYPE_FOLLOW:///< 追踪
        {
            m_WSSkillType_s                       = lpSkill->getSkillType();
            m_WSAttackLowdownRate = lpSkill->getSkillParam1()/10000.0f;
            m_WSIsFollowAttack             =1;
        }
        break;
        case WBWeaponSkill::E_WEAPONSKILL_TYPE_ATOM:///<原子弹
        {
            m_WSSkillType_s                       = lpSkill->getSkillType();
            m_WSAttackLowdownRate = lpSkill->getSkillParam1()/10000.0f;
            m_WSIsAttom                         =1;
        }
        break;
            
        default:
            break;
    }
}
#endif
void WHero::clearWeaponSkill()
{
    m_WSSkillType =-1;
    m_WSLastHurt=0; ///< 持续伤害
    m_WSLastHurtRound=0;///< 持续伤害剩作回合数
    m_WSLastTired=0;///< 持续降低体力上限
    m_WSLastTiredRound=0;///< 持续降低体力上限回合数
    m_WSLastSeal=0;///< 持续封印
    m_WSLastSealRound=0;///<持续封印回合数
    
    m_FlyLockLastRound=0;///<飞行清零
    m_WSLastFlyLockRound=0;///<持续锁定飞行
    m_WSLastFlyLock=0;///<持续锁定飞行
    
    //还要清除动画
    
    if(m_WSSpecial)
    {
        m_WSSpecial->removeFromParentAndCleanup(true);
        m_WSSpecial=NULL;
    }
}

void WHero::beShootedInWeaponSkill(const WHero *lpOwnerPlayer)
{
#if 0
    if(getPlayerId()==lpOwnerPlayer->getPlayerId()
    || getIsDead()) return;
    

    switch (lpOwnerPlayer->getWSSkillType_s())
    {
        case WBWeaponSkill::E_WEAPONSKILL_TYPE_LASTHURT:///< 灼伤持续扣血
        {
            clearWeaponSkill();
            
            m_WSSkillType              = lpOwnerPlayer->getWSSkillType_s();
            m_WSLastHurt               = lpOwnerPlayer->getWSLastHurt_s();
            m_WSLastHurtRound  =  lpOwnerPlayer->getWSLastHurtRound_s()+1;//到零就执行,所以要先加1
            
            m_WSSpecial=WAnimationManager::GetSampleAnimation(WANI_IWCO_BATTLEEFFECT, "butn");
            m_WSSpecial->setPositionInPixels(getAnchorPointInPixels());
            m_WSSpecial->playRepeat();
            addChild(m_WSSpecial,1);
        }
            break;
        case WBWeaponSkill::E_WEAPONSKILL_TYPE_LOSETIREDVALUE :///< 降低疲劳上限
        {
            clearWeaponSkill();
            
            m_WSSkillType                = lpOwnerPlayer->getWSSkillType_s();
            m_WSLastTired              = lpOwnerPlayer->getWSLastTired_s();
            m_WSLastTiredRound  =lpOwnerPlayer->getWSLastTiredRound_s()+1;
            
            m_WSSpecial=WAnimationManager::GetSampleAnimation(WANI_IWCO_BATTLEEFFECT, "fatigue");
            m_WSSpecial->setPositionInPixels(getAnchorPointInPixels());
            m_WSSpecial->playRepeat();
            addChild(m_WSSpecial,1);
        }
            break;
        case WBWeaponSkill::E_WEAPONSKILL_TYPE_GRAVITY:///< 无法飞行
        {
            clearWeaponSkill();
            
            m_WSSkillType                = lpOwnerPlayer->getWSSkillType_s();
            m_WSLastFlyLockRound    = lpOwnerPlayer->getWSLockFlyRound_s()+1;//这里不是到零执行是,负数执行
            
            m_WSSpecial=WAnimationManager::GetSampleAnimation(WANI_IWCO_BATTLEEFFECT, "gravity");
            m_WSSpecial->setPositionInPixels(getAnchorPointInPixels());
            m_WSSpecial->playRepeat();
            addChild(m_WSSpecial,1);
        }
            break;
            
        case WBWeaponSkill::E_WEAPONSKILL_TYPE_SEAL:///< 封印
        {
            clearWeaponSkill();
            
            m_WSSkillType            = lpOwnerPlayer->getWSSkillType_s();
            m_WSLastSeal              =lpOwnerPlayer->getWSLastSeal_s();
            m_WSLastSealRound = lpOwnerPlayer->getWSLastSealRound_s()+1;
            
            m_WSSpecial=WAnimationManager::GetSampleAnimation(WANI_IWCO_BATTLEEFFECT, "seal");
            m_WSSpecial->setPositionInPixels(getAnchorPointInPixels());
            m_WSSpecial->playRepeat();
            addChild(m_WSSpecial,1);
        }
        break;

            
        default:
            break;
    }
#endif
}

void WHero::updateWeaponSkillPerRound()
{
#if 0
    clearWeaponSkill_s();
    
    switch (getWSSkillType())
    {
        case WBWeaponSkill::E_WEAPONSKILL_TYPE_LASTHURT:///< 灼伤持续扣血
        {
            if(m_WSLastHurtRound>0)
            {
                m_WSLastHurtRound--;
                
                if(m_WSLastHurtRound<=0)
                {
                    clearWeaponSkill();
                }
            }
            
            if(m_WSLastHurtRound<0) m_WSLastHurtRound=0;
            
            if(m_WSLastHurtRound>0 && getCtrlType() != DEF_WB_CTRL_OTHER)
            {
                SendMsgHurt(0,m_WSLastHurt,WFadeOutHurtLabel::E_NORMAL);//发送对这个角色进行伤害
              
                BATTLE_Hurt *lpHurt=new BATTLE_Hurt();
                
                
                lpHurt->setBattleId(getBattleId());
                lpHurt->setPlayerId(getPlayerId());
                vector<int> hurtValue;
                vector<int> hurtPlayerIds;
                hurtValue.push_back(m_WSLastHurt);
                hurtPlayerIds.push_back(getPlayerId());
                lpHurt->sethurtcount(1);
                lpHurt->setPlayerIds(hurtPlayerIds);
                lpHurt->setHurtvalue(hurtValue);
                
                WBSendProtocol(lpHurt);
                 
            }
         
        
        }
            break;
        case WBWeaponSkill::E_WEAPONSKILL_TYPE_LOSETIREDVALUE :///< 降低疲劳上限
        {
            if(m_WSLastTiredRound>0)
            {
                m_WSLastTiredRound--;
                if(m_WSLastTiredRound<=0)
                {
                    clearWeaponSkill();
                }
            }
            
            if(m_WSLastTiredRound<0) m_WSLastTiredRound=0;
            
            if(m_WSLastTiredRound>0)
            {
                m_SP-=m_WSLastTired;
            }
        }
            break;
        case WBWeaponSkill::E_WEAPONSKILL_TYPE_GRAVITY:///< 无法飞行
        {
            if(m_WSLastFlyLockRound>0)
            {
                m_WSLastFlyLockRound--;
                
                if(m_WSLastFlyLockRound<=0)
                {
                    clearWeaponSkill();
                }
            }
            
            if(m_WSLastFlyLockRound<0) m_WSLastFlyLockRound=0;
            
            if(m_WSLastFlyLockRound>0)
            {
                m_WSLastFlyLock=1;
            }
            else
            {
                m_WSLastFlyLock=0;
            }
            
            if(m_WSLastFlyLock)
            {
                setFlyLockLastRound(1);
            }
        }
        break;
            
        case WBWeaponSkill::E_WEAPONSKILL_TYPE_SEAL:///< 封印
        {
            if(m_WSLastSealRound>0)
            {
                m_WSLastSealRound--;
                
                if(m_WSLastSealRound<=0)
                {
                    clearWeaponSkill();
                }
            }
            
            if(m_WSLastSealRound<0) m_WSLastSealRound=0;
            
            if(m_WSLastSealRound>0)
            {
                m_WSLastSeal=1;
            }
            else
            {
                m_WSLastSeal=0;
            }
        }
            break;
    }
#endif
}
#endif

void WHero::SendMsgSureWin()
{
    SendEventToQueue(new WBEvent(DEF_ST_SUREWIN,0));
}

void WHero::SendMsgFail()
{
    SendEventToQueue(new WBEvent(DEF_ST_FAIL,0));
}

void WHero::ProcessMessage()
{

#if 0
    while(m_EventManager.size()>0)
    {
        
        if(m_currentWBEvent!=NULL)
        {
          
            if(!m_currentWBEvent->isEnd())
            {
                WBEvent *pEvent=m_EventManager.front();
                if(pEvent->getType()==DEF_ST_REBORN)
                {
                    m_currentWBEvent->End();
                }
                else if(pEvent->getType()==DEF_ST_HURT
                && m_currentWBEvent->getType()==DEF_ST_HURT)
                {
                    m_currentWBEvent->End();
                }
                
                break;
            } 
            
//            if(m_currentWBEvent->getType()==DEF_ST_FREEZE) //冻结时会多显示特效
//            {
//                m_lpSpecialEffect->setIsVisible(false);
//            }
            
            DeleteObject(m_currentWBEvent);
        }
        
        m_currentWBEvent=m_EventManager.front();
        m_EventManager.pop();
        
        m_runStatus=m_currentWBEvent->getType();
        
    
        switch (m_currentWBEvent->getType()) {
            case DEF_ST_NORMAL://待机
                setAnimation(DEF_NORMAL);
                playRepeat();
                st_normal_timer=rand()%20+10;
               m_isShowPoint=false;
                m_currentWBEvent->End(); //可以直接被切换成别的状态
                m_needCheckCollsion=true;
                break;
                
            case DEF_ST_MOVE_LEFT:        //移动中
                if(getAnimationStatus()!=DEF_MOVE)
                {
                    setFlipX(true);
                    setAnimation(DEF_MOVE);
                    playRepeat();
                    
                    MOVE_STRUCT *pMove=(MOVE_STRUCT *)m_currentWBEvent->getData();
                    setMoverPosition(pMove->startPos);
                    setMoverPrePosition(pMove->startPos);
                    if(m_isCollsionPre)setMoverSpeed(Vec2(0,0));
                    st_move_times= pMove->times;
                    st_move_timer=0.5f;
                    
                    m_face=0;
                } 
                else
                {
                    if(m_face==1) { m_face=0;setFlipX(true);}
                    MOVE_STRUCT *pMove=(MOVE_STRUCT *)m_currentWBEvent->getData();
                    
                    if(m_isCollsionPre)
                    {
                        setMoverSpeed(Vec2(0,0));
                    }                    
                    st_move_times+=pMove->times;
                    st_move_timer=0.5f;
                    m_currentWBEvent->End();
                }   
                
                     
                break;
            case DEF_ST_MOVE_RIGHT:        //移动中
                if(getAnimationStatus()!=DEF_MOVE)
                {
                    setAnimation(DEF_MOVE);
                    playRepeat();
                    
                    MOVE_STRUCT *pMove=(MOVE_STRUCT *)m_currentWBEvent->getData();
                    setMoverPosition(pMove->startPos);
                    setMoverPrePosition(pMove->startPos);
                    if(m_isCollsionPre)setMoverSpeed(Vec2(0,0));
                    st_move_times= pMove->times;
                    st_move_timer=0.5f;
                    
                    SetLeftRight(DEF_FACE_RIGHT);
                }
                else
                {
                    if(m_face==0) { m_face=1;setFlipX(false);}
                    MOVE_STRUCT *pMove=(MOVE_STRUCT *)m_currentWBEvent->getData();
                    if(m_isCollsionPre)setMoverSpeed(Vec2(0,0));
                    st_move_times+=pMove->times;
                    st_move_timer=0.5f;
                    m_currentWBEvent->End();
                }       
               
                break;
            case DEF_ST_ITEMSKILL://使用道具
            {
                int *type=(int *)m_currentWBEvent->getData();
                
                WMusic::shareMusic()->PlaySound(WMusic::E_S_USE_ITEM);
                if(type[0]==WBItemSkill::E_TYPE_SKILL)
                {
                    ShowSpecialEffect(DEF_SE_USE_ITEM);
                    m_currentWBEvent->End();
                    SendMsgNormal();
                }
                else if(type[0]==WBItemSkill::E_TYPE_FUNC)
                {
                    switch (type[1]) {
                        case WBItemSkill::E_SUBTYPE_FUNC_FREEZE:
                            ShowSpecialEffect(DEF_SE_FROZEN_1);
                            m_currentWBEvent->End();
                            SendMsgNormal();
                            
                            break;
                            
                        case WBItemSkill::E_SUBTYPE_FUNC_HIDES:
                        case WBItemSkill::E_SUBTYPE_FUNC_HIDET:
                        {
                            
                            if(type[1]==WBItemSkill::E_SUBTYPE_FUNC_HIDES)
                            {
                                WBItemSkill *pItemSkill=(WBItemSkill *)WDDD_GLOBAL.m_lpBattleGlobal->getItemSkillWithId(14);
                                m_HideRoundLast=pItemSkill->getParam1();
                            }
                            else
                            {
                                WBItemSkill *pItemSkill=(WBItemSkill *)WDDD_GLOBAL.m_lpBattleGlobal->getItemSkillWithId(15);
                                m_HideRoundLast=pItemSkill->getParam1();
                            }
                            ShowSpecialEffect(DEF_SE_HIDE);
                            m_currentWBEvent->End();
                            SendMsgNormal();
                        }
                            break;
                            
                            
                        case WBItemSkill::E_SUBTYPE_FUNC_BLOODS:
                        case WBItemSkill::E_SUBTYPE_FUNC_BLOODT:
                            ShowSpecialEffect(DEF_SE_ADD_BLOOD);
                            m_currentWBEvent->End();
                            SendMsgNormal();
                            break;
                            
                            
                        default:
                        ShowSpecialEffect(DEF_SE_USE_ITEM);
                            m_currentWBEvent->End();
                            SendMsgNormal();
                            break;
                    }
                }
                else
                {
                    ShowSpecialEffect(DEF_SE_USE_ITEM);
                    m_currentWBEvent->End();
                    SendMsgNormal();
                }
            }
            break;
            
            case DEF_ST_FREEZE:
            {
#if 0
                ShowSpecialEffect(DEF_SE_FROZEN_2);
                m_currentWBEvent->End();
                setAnimation(DEF_NORMAL);
                m_isFreeze=true;
                WBItemSkill *pItemSkill=(WBItemSkill*)WDDD_GLOBAL.m_lpBattleGlobal->getItemSkillWithId(12);//冰冻id12
                m_FreezeLastRound=pItemSkill->getParam1();
#endif
            }
            break;
            
            case DEF_ST_SUREWIN:
            {
                setAnimation(DEF_SUREWIN);
                //playByTimes(3);
            }
            break;
            
            case DEF_ST_FAIL:
            {
                setAnimation(DEF_NORMAL_2);
                //playByTimes(3);
            }
            break;
            
            case DEF_ST_SHOOT://射击
            {
                m_shootAttackRateIndex=0;
                if(getIsBigSkill()==false)
                {
                    setAnimation(DEF_SHOOT_START);
                    //playOnce();
                    SHOOT_OR_FLY_STRUCT *lpS=(SHOOT_OR_FLY_STRUCT *)m_currentWBEvent->getData();
                    st_shoot_startPos=lpS->startPos;
                    st_shoot_speed    =lpS->speed;
                   
                    SetLeftRight(lpS->face);
                    
                    
#if OPEN_FIFTH
                    CheckWeaponSkillTouchOff();
            
#endif
                }
                else
                {
                    ShowSpecialEffect(DEF_SE_BIGSKILL);
                    SHOOT_OR_FLY_STRUCT *lpS=(SHOOT_OR_FLY_STRUCT *)m_currentWBEvent->getData();
                    st_shoot_startPos=lpS->startPos;
                    st_shoot_speed    =lpS->speed;
                 
                    SetLeftRight(lpS->face);
                    if(m_pAngryFire)
                    {
#if 0
                        if(m_pAngryFire->getIsVisible())
                        {
                            m_pAngryFire->setIsVisible(false);
                            m_pAngryFire->stopPlay();
                        }
#endif
                    }
                }
                
          
                
            }    
            break;
            
            case DEF_ST_FLY://飞行
            {
                m_oldPosBeforeFly=getMoverPosition();
                setAnimation(DEF_FLY);
                playRepeat();
                SHOOT_OR_FLY_STRUCT *lpS=(SHOOT_OR_FLY_STRUCT *)m_currentWBEvent->getData();
               
                st_shoot_startPos=lpS->startPos;
                st_shoot_speed    =lpS->speed;
                
                SetLeftRight(lpS->face);
                
                //WMusic::shareMusic()->PlaySound(WMusic::E_S_FLY);
                
//                CCPoint anchor=getAnchorPointInPixels();
//                
//    
//                CCAffineTransform tranf=nodeToParentTransform();
//                CCPoint startPos=CCPointMake(st_shoot_startPos.x+anchor.x, st_shoot_startPos.y+anchor.y);
//                startPos=CCPointApplyAffineTransform(startPos,tranf);
            
                setMoverPosition(Vec2(st_shoot_startPos.x,st_shoot_startPos.y));
                setRotation(0);
                setMoverSpeed(st_shoot_speed);
                
                m_flytime=0.05f;
            }
            break;
            
            case DEF_ST_DEATH://死亡
            {
                setAnimation(DEF_GHOST);
                playRepeat();
                m_isDead=true;
                
                setRotation(0);
                
#if OPEN_FIFTH
                clearWeaponSkill();
#endif
#if 0
                if(!getGameFrontLayer()->getIsGameOver())
                {
                    if(getPlayerId()==WDDD_GLOBAL.m_lpBattleGlobal->myHero->getPlayerId())
                    {
                        WMusic::shareMusic()->PlaySound(WMusic::E_S_PLAYERDIE);
                    }
                    else
                    {
                        WMusic::shareMusic()->PlaySound(WMusic::E_S_KILLPLAYER);
                    }
                }
                
          
                int mode=WDDD_GLOBAL.m_lpBattleGlobal->getBattleMode();
                if(mode==2
                   && getCtrlType()!=1)
                {
                    vector<int> posX;
                    vector<int> posY;
                    
                  
                    Vec2 pos=getGameFrontLayer()->getRebornPosition();
                    
                    posX.push_back(WBUtil::floatToInt(pos.x));
                    posY.push_back(WBUtil::floatToInt(pos.y));
                
                    
                    //TODO 还要检测位置是否重复,还没做
                    BATTLE_RebornPosition *lpRebornPos=new BATTLE_RebornPosition();
                    
                    lpRebornPos->setBattleId(WDDD_GLOBAL.m_lpBattleGlobal->getBattleId());
                    lpRebornPos->setPlayerCount(1);
                    lpRebornPos->setPlayerId(WDDD_GLOBAL.m_lpBattleGlobal->myHero->getPlayerId());
                    vector<int> playerids;
                    playerids.push_back(getPlayerId());
                    lpRebornPos->setPlayerIds(playerids);
                    lpRebornPos->setPositionX(posX);
                    lpRebornPos->setPositionY(posY);
                    
                    WBSendProtocol(lpRebornPos);
                }
#endif
            }
                break;
                
            case DEF_ST_HURT://伤害
            {                
                setAnimation(DEF_HURT);
                //playByTimes(2);
                m_needCheckCollsion=true;
                if(m_isFreeze)
                {
                    m_FreezeLastRound=0;
                    m_isFreeze=false;
		   							 if(m_lpSpecialEffect) m_lpSpecialEffect->setIsVisible(false);
                }
                
                if(m_isHide)
                {
                    m_isHide=false;
                    m_HideRoundLast=0;
                    setOpacity(255);
                }
                
                HURT_STRUCT *lpHurt=(HURT_STRUCT*)m_currentWBEvent->getData();
                
                
                WFadeOutHurtLabel *pFade =WFadeOutHurtLabel::LabelWithString(ccpAdd(getPositionInPixels(), CCPointMake(rand()%50-25, 12)), lpHurt->hurt,lpHurt->ciriticalType);
                CCLayer *pLayer=(CCLayer *)getParent();
             
                pLayer->addChild(pFade,1);
                

         
                if(WDDD_GLOBAL.m_lpBattleGlobal->getIsInTeach()==false)
                {
                    getGameFrontLayer()->getBattleScene()->getHudLayer()->updateHud();
                }
            }
            break;
            
            case DEF_ST_BIGSKILL://大招
            {
            
//                if(getSP()<getMaxSP())
//                {
//                    m_currentWBEvent->End();
//                    SendMsgNormal();
//                    break;
//                }
              
               m_fly=false;
               m_isItemFly=false;
               
               setIsBigSkill(true);
               
              
               
                switch (m_BigSkillType) {
                    case 0:
                    {
                        if(WDDD_GLOBAL.m_lpBattleGlobal->getIsInTeach()==false)
                        {
                            getGameFrontLayer()->getBattleScene()->getNotScaleLayer()->pushItemIcon(this, "attract_0_1.png");
                        }
                        setAttackDivideNum(1);
                        setAttackMultiple(0.3f);
                        setAttackTimes(7);
                    }
                    break;
                    
                    case 1:
                    {
                        if(WDDD_GLOBAL.m_lpBattleGlobal->getIsInTeach()==false)
                        {
                            getGameFrontLayer()->getBattleScene()->getNotScaleLayer()->pushItemIcon(this, "attract_1_1.png");
                        }
                        setAttackDivideNum(1);
                        setAttackMultiple(2.5f);
                        setAttackTimes(1);
                    }
                        break;
                        
                    case 2:
                    {
                    
                        if(WDDD_GLOBAL.m_lpBattleGlobal->getIsInTeach()==false)
                        {
                            getGameFrontLayer()->getBattleScene()->getNotScaleLayer()->pushItemIcon(this, "attract_2_1.png");
                        }
                        setAttackDivideNum(7);
                        setAttackMultiple(0.4f);
                        setAttackTimes(1);
                        setBulletSpecialType(1);
                    }
                        break;
                        
                    default:
                        break;
                }
             
               
               if(m_pAngryFire)
               {
                   if(!m_pAngryFire->getIsVisible())
                   {
                       m_pAngryFire->setIsVisible(true);
                       m_pAngryFire->setAnimation(0);
                       m_pAngryFire->playRepeat();
                   }
               }
               
               setSP(0);
                
                if(WDDD_GLOBAL.m_lpBattleGlobal->getIsInTeach()==false)
                {
                    m_lpGameFrontLayer->getBattleScene()->getHudLayer()->updateHud();
                    m_lpGameFrontLayer->getBattleScene()->getHudLayer()->disableHud();
                }
       
                m_currentWBEvent->End();
                
                WFadeOutLabel *pFade =WFadeOutLabel::LabelWithString(ccpAdd(getPositionInPixels(), CCPointMake(0, 12)), WDDD_GLOBAL.getClientText(E_BATTLE_USE_BIG_SKILL));
              
                getParent()->addChild(pFade);
                
                SendMsgNormal();
      
            }
            break;
            
            case DEF_ST_FLASH:
            {
                m_blink=CCBlink::actionWithDuration(1.0f, 6);
                m_blink->retain();
                runAction(m_blink);
            }
                break;
                
            case DEF_ST_REBORN:
            {
                Vec2 *lpRebornPos=(Vec2 *)m_currentWBEvent->getData();
                
                setMoverPosition(*lpRebornPos);
                setMoverPrePosition(*lpRebornPos);
                setMoverSpeed(Vec2(0,0));
                
                SendMsgNormal();
                
                m_currentWBEvent->End();
                
                setHP(getMaxHP());
                setPF(getMaxPF());
//                m_HP=m_maxHP;
//                m_PF=m_maxPF;
              //  m_SP=0;
                
                m_isDead=false;
                
                if(WDDD_GLOBAL.m_lpBattleGlobal->getIsInTeach()==false)
                {
                    getGameFrontLayer()->getBattleScene()->getHudLayer()->updateHud();
                }
            }
                break;
            default:
                break;
        }
    }
#endif
}


void WHero::SetLeftRight(int leftRight)
{
    if(leftRight!=m_face)
    {
        if(leftRight==DEF_FACE_RIGHT)
        {
            m_face=DEF_FACE_RIGHT;
            setFlipX(false);
        }
        else
        {
            m_face=DEF_FACE_LEFT;
            setFlipX(true);
        }
    }

}

void WHero::SendMsgReborn(const Vec2 &position)
{
    WBEvent *pEvent=new WBEvent(DEF_ST_REBORN,0);
    pEvent->setData(new Vec2(position.x,position.y));
  
    if(m_isDead==true)
    {
        ClearEventQueue();
    }
    SendEventToQueue(pEvent);
    
    
}
int WHero::getAnimationStatus(){
	return DEF_NORMAL;
}
void WHero::st_normal()
{
    if(getAnimationStatus()==DEF_NORMAL)
    {
            st_normal_timer-=m_dt;
            if(st_normal_timer<0)
            {
                int random=rand()%2;
                
                if(random==0)
                {
                    setAnimation(DEF_NORMAL_2);
                    playOnce();
                }
                else
                {
                    setAnimation(DEF_SUREWIN);
                    playOnce();
                }
            }
 
    }
    else
    {
        if(isCurrentAnimationDone())
        {
            st_normal_timer=rand()%20+10;
            setAnimation(DEF_NORMAL);
            //playRepeat();
        }
    }
    

    
    checkCollision();
}

void WHero::ShowSpecialEffect(int effect)
{
#if 0
    if(getIsFreeze()) return;//如果是在冻动状态下,不能播放其他特效
    
    switch (effect) 
    {
        case DEF_SE_FROZEN_1:
            m_lpSpecialEffect->setAnimation(DEF_SE_FROZEN_1);
            m_lpSpecialEffect->playOnce();
            m_lpSpecialEffect->setIsVisible(true);
            break;
            
        case DEF_SE_FROZEN_2:
            m_lpSpecialEffect->setAnimation(DEF_SE_FROZEN_2);
            m_lpSpecialEffect->playRepeat();
            m_lpSpecialEffect->setIsVisible(true);
            break;
            
        case DEF_SE_USE_ITEM:
            m_lpSpecialEffect->setAnimation(DEF_SE_USE_ITEM);
            m_lpSpecialEffect->playOnce();
            m_lpSpecialEffect->setIsVisible(true);
            break;
            
        case DEF_SE_ADD_BLOOD:
            m_lpSpecialEffect->setAnimation(DEF_SE_ADD_BLOOD);
            m_lpSpecialEffect->playOnce();
            m_lpSpecialEffect->setIsVisible(true);
            break;
            
        case DEF_SE_HIDE:
            m_lpSpecialEffect->setAnimation(DEF_SE_HIDE);
            m_lpSpecialEffect->playOnce();
            m_lpSpecialEffect->setIsVisible(true);
            if(WDDD_GLOBAL.m_lpBattleGlobal->myHero->getCamp()==getCamp())
            {
                setOpacity(0.5f*255);
            }
            else
            {
                //setIsVisible(false);
                setOpacity(0);
            }
            
          //  m_HideRoundLast=DEF_WB_HIDE_ROUND_MAX;
            m_isHide=true;
            break;
            
        case DEF_SE_BIGSKILL:
            m_lpSpecialEffect->setAnimation(DEF_SE_BIGSKILL);
            m_lpSpecialEffect->playOnce();
            m_lpSpecialEffect->setIsVisible(true);
            break;
            
        default:
            break;
    }
#endif
}
void WHero::setAnimation(int dwAniID){
}
void WHero::playRepeat(){}

void WHero::st_move()
{
    m_needCheckCollsion=true;
    
    if(st_move_times<=0)
    {
        assert(m_currentWBEvent);
        
        setAnimation(DEF_ST_NORMAL);
        playRepeat();
        
        st_move_timer-=m_dt;
        if(st_move_timer<=0.0f)
        {
            m_currentWBEvent->End();
            SendEventToQueue(new WBEvent(DEF_ST_NORMAL,0));
        }
        
         return;
    }
    else
    {
        st_move_times--;
        
    }
    
    m_currentWBEvent->End();
    
    if(getPF()>0)
    {
        //m_PF-=m_BuffMovePFCostRate;
        setPF(getPF()-m_BuffMovePFCostRate);
        
        if(getPF()<0) setPF(0);
#if 0
        if(WDDD_GLOBAL.m_lpBattleGlobal->getIsInTeach()==false)
        {
            getGameFrontLayer()->getBattleScene()->getHudLayer()->updateHud();
        }
#endif
    }
    else
    {
        return;
    }
    
    if(m_runStatus==DEF_ST_MOVE_LEFT)
    {

        setMoverAcceleration(getMoverAcceleration()+Vec2(-2.0,0.0));

//        setMoverAcceleration(getMoverAcceleration()+Vec2(-2.0,0.0));

//        CCLog("HeroMoverAcceleration%f,%f",getMoverAcceleration().x,getMoverAcceleration().y);
        
    }
    else 
    {

        setMoverAcceleration(getMoverAcceleration()+Vec2(2.0,0.0));

        

//        CCLog("HeroMoverAcceleration%f,%f",getMoverAcceleration().x,getMoverAcceleration().y);
    }
    

    
    checkCollision();
}


void WHero::ClearEventQueue()
{   
    WBEvent *pEvent;
    
    while(m_EventManager.size()>0)
    {
        pEvent=m_EventManager.front();
        m_EventManager.pop();
        
		DeleteObject(pEvent);
        
    }
    
    while(m_quickEventManager.size()>0)
    {
        pEvent=m_quickEventManager.front();
        m_quickEventManager.pop();
        
        DeleteObject(pEvent);
        
    }
}

void WHero::SendEventToQueue(WBEvent *pEvent)
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

int WHero::TouchCheckBeginMove(CCTouch *touch)
{
#if 0
    CCPoint heroPoint=getAnchorPointInPixels();
    heroPoint.y+=getContentSizeInPixels().height/2;
    heroPoint.x/=CC_CONTENT_SCALE_FACTOR();
    heroPoint.y/=CC_CONTENT_SCALE_FACTOR();
    heroPoint=convertToWorldSpaceAR(heroPoint);
    heroPoint=CCDirector::sharedDirector()->convertToUI(heroPoint);
    
    CCPoint tpoint=touch->locationInView(0);
    
    float distance=tpoint.x-heroPoint.x;
   
    
    if(abs(distance)<35/CC_CONTENT_SCALE_FACTOR()) return 0;
    
    if(distance<0) return -1;
#endif
    return 1;
}

bool WHero::TouchCheckBeginControl(CCTouch *touch)
{
    
    float checkRadius;
    float scale=getParent()->getScale()*getScale();
    if(scale!=0)
    {
        checkRadius=DEF_WB_TOUCH_RADIUS/scale;
    }
    else
    {
        checkRadius=DEF_WB_TOUCH_RADIUS;
        
    }  
    
    checkRadius/=CC_CONTENT_SCALE_FACTOR();
    
    
    
    CCPoint pos=convertTouchToNodeSpaceAR(touch);
    pos.y-=getContentSize().height/2;
    
//printf("rrrr:%f  LL::%f\n",checkRadius,ccpLength(pos));
    return (checkRadius>ccpLength(pos));
    
}

void WHero::TouchControlStart()
{
    m_IsTouchControlStarted=true;
    st_normal_oldTouchPoint=CCPointMake(-1, -1);
    m_isShowPoint=true;
    

}

void WHero::TouchControlEnd(bool shoot)
{
 
    m_IsTouchControlStarted=false;
    m_isShowPoint=false;
}

void WHero::TouchControl(CCTouch *touch)
{
#if 0
    if(!m_IsTouchControlStarted) return;
    
  //  GameFrontLayer *lpGameLayer=(GameFrontLayer *)getParent();
    
    CCPoint touchPoint=touch->locationInView(0);//getParent()->convertTouchToNodeSpace(touch);
 //   touchPoint=CCDirector::sharedDirector()->convertToGL(touchPoint);
    if(st_normal_oldTouchPoint.x!=touchPoint.x || st_normal_oldTouchPoint.y!=touchPoint.y)
    {
        //转换到父结点坐标系的矩阵
         CCAffineTransform toParentTranf=nodeToParentTransform();         
         
        //保留上一次点击坐标
        st_normal_oldTouchPoint=touchPoint;
        
        //中心点转换到世界坐标系
        CCPoint heroCenter=getAnchorPointInPixels();
        heroCenter.y+=getContentSizeInPixels().height/2;
        heroCenter.x/=CC_CONTENT_SCALE_FACTOR();
        heroCenter.y/=CC_CONTENT_SCALE_FACTOR();
        heroCenter=convertToWorldSpaceAR(heroCenter);
        heroCenter=CCDirector::sharedDirector()->convertToUI(heroCenter);
        //CCPointApplyAffineTransform(heroCenter,toParentTranf);
       
        heroCenter.x*=CC_CONTENT_SCALE_FACTOR();
        heroCenter.y*=CC_CONTENT_SCALE_FACTOR();
        //转换为角素坐标
        touchPoint.x*=CC_CONTENT_SCALE_FACTOR();
        touchPoint.y*=CC_CONTENT_SCALE_FACTOR();
        
        
        CCPoint speedDirector=ccpSub(heroCenter,touchPoint); //射击方向
        speedDirector.y=-speedDirector.y;
        CCPoint touchDirector(-speedDirector.x,-speedDirector.y); //点击的方向
        WLog("%f,%f",speedDirector.x,speedDirector.y);
        //离中心点的距离
        float touchLength=ccpLength(speedDirector);
        
        if(touchLength<5)  //过小时,加大
        {
            if(touchLength==0)
            {
                speedDirector.x=5;
                speedDirector.y=0;
            }
            touchLength=5;
        }
        
        //单位化
        speedDirector.x/=touchLength;
        speedDirector.y/=touchLength;
        
      //  WLog("speedDirector::%f %f",speedDirector.x,speedDirector.y);

        //对力度进行限制
        if(touchLength<DEF_WB_SHOOT_POWER_MIN) touchLength=DEF_WB_SHOOT_POWER_MIN;
        else if(touchLength>DEF_WB_SHOOT_POWER_MAX) touchLength=DEF_WB_SHOOT_POWER_MAX;
        
        float rate=(touchLength-DEF_WB_SHOOT_POWER_MIN)/(DEF_WB_SHOOT_POWER_MAX-DEF_WB_SHOOT_POWER_MIN);


        
        
        float st_shoot_power=rate*DEF_WB_SHOOT_POWER_BASE;
        
        //得到限制好的速度
        st_shoot_speed.x=speedDirector.x*st_shoot_power;
        st_shoot_speed.y=speedDirector.y*st_shoot_power;
        
        //判断人物的面向
                  if(touchDirector.x>  5)  SetLeftRight(DEF_FACE_LEFT);
         else  if(touchDirector.x<-5)  SetLeftRight(DEF_FACE_RIGHT);
        
        //转换速度的方向到人物的局部坐标系
        CCPoint speedDirectorInNode=speedDirector;
        
        CCAffineTransform toNodeTranf=parentToNodeTransform();
        toNodeTranf.tx=0; toNodeTranf.ty=0;//只旋转不平移
        
        speedDirectorInNode=CCPointApplyAffineTransform(speedDirectorInNode,toNodeTranf);
        
        CCPoint g;
        if(WDDD_GLOBAL.m_lpBattleGlobal->getIsInTeach()==false)
        {
            //转换外力的方向到人物的局部坐标系
            g=CCPointMake(m_lpGameFrontLayer->getGravityFly().x+m_lpGameFrontLayer->getWind().x, m_lpGameFrontLayer->getGravityFly().y+m_lpGameFrontLayer->getWind().y);
        }
        else
        {
            g=CCPointMake(m_lpGameFrontTeachLayer->getGravityFly().x+m_lpGameFrontTeachLayer->getWind().x, m_lpGameFrontTeachLayer->getGravityFly().y+m_lpGameFrontTeachLayer->getWind().y);
        }
        g=CCPointApplyAffineTransform(g,toNodeTranf);
        
        //不同方向发射点不同
        if(m_face==1)
        {
            st_shoot_startPos.x=40;
            st_shoot_startPos.y=60;
        }
        else
        {
            st_shoot_startPos.x=-40;
            st_shoot_startPos.y=60;
        }
        
        CCPoint p(st_shoot_startPos.x,st_shoot_startPos.y);
        
        
        
        //记录发射点
        st_shoot_startPos=ccpAdd(st_shoot_startPos, getAnchorPointInPixels());
        st_shoot_startPos=CCPointApplyAffineTransform(st_shoot_startPos,toParentTranf);
        
        
        //计算发射线的所有点
        CCPoint speed=speedDirectorInNode;
        
        speed.x*=st_shoot_power;
        speed.y*=st_shoot_power;
        
        
        float gameLayerScale;
        if(WDDD_GLOBAL.m_lpBattleGlobal->getIsInTeach()==false)
        {
            gameLayerScale=m_lpGameFrontLayer->getScale();
        }
        else
        {
            gameLayerScale=m_lpGameFrontTeachLayer->getScale();
        }
        
        m_PointsUsedCount=0;
        for(int i=0; i<DEF_EHERO_MAX_POINT; i++)
        {
            
            CCPoint tmp=CCPointMake((p.x)/CC_CONTENT_SCALE_FACTOR(), (p.y)/CC_CONTENT_SCALE_FACTOR());
            if(!(m_PointsUsedCount>0 && ccpLength(ccpSub(tmp, m_Points[m_PointsUsedCount-1]))*gameLayerScale*0.5<1.0f))
            {
                m_Points[m_PointsUsedCount]=tmp;
                m_PointsUsedCount++;
            }
            
            speed=ccpAdd(speed, g);
            p.x+=speed.x;
            p.y+=speed.y;
            
        }
        
    }
#endif 

}


void WHero::st_shoot_calc()
{
#if 0
    WBullet *lpBullet;
    
    int attack;
    
   
    if(m_isBigSkill)
    {
        attack=getAttack();
    }
    else
    {
        attack=getAttack();
    }
    
 
    if(m_isCriticalhit)
    {
        attack=attack*m_CriticalhitAttackRate/1000;
    }
    
    attack=(int)(m_AttackMultiple*attack);
    
    
 //   CCPoint anchor=getAnchorPointInPixels();
    
    GameFrontLayerInterFace *lpGameFrontLayer;
    
    if(WDDD_GLOBAL.m_lpBattleGlobal->getIsInTeach()==false)
    {
        lpGameFrontLayer=m_lpGameFrontLayer;
    }
    else 
    {
        lpGameFrontLayer=m_lpGameFrontTeachLayer;
    }
    
    if(m_AttackDivideNum>1)
    {
    
  
   
     
        Vec2 dy(0,2);
        Vec2 speed=st_shoot_speed;
        Vec2 sp;
        dy=speed;
  //      Vec2 speedDirector=st_shoot_speed;
       
   
        
        dy.Normalize();
        dy=Vec2(dy.y,dy.x);
        dy.y*=2;
        float power=speed.Length();
                
                
        b2Transform bTran;     
        
        
                
        if(speed.x>0)
        {
            bTran.Set(Vec2(0,0), CC_DEGREES_TO_RADIANS(-8*(m_AttackDivideNum/2-(m_AttackDivideNum&0x1))));
            speed=b2Mul(bTran, speed);
            bTran.Set(Vec2(0,0), CC_DEGREES_TO_RADIANS(8));
            //speed.y-=dy.y*;
        }   
        else 
        {
            bTran.Set(Vec2(0,0), CC_DEGREES_TO_RADIANS(8*(m_AttackDivideNum/2-(m_AttackDivideNum&0x1))));
            speed=b2Mul(bTran, speed);
            bTran.Set(Vec2(0,0), CC_DEGREES_TO_RADIANS(-8));
        }
        
        for(int i=0; i<m_AttackDivideNum; i++)
        {

            sp=speed;
            sp.Normalize();
            sp*=power;
            
            float attackRate;
            if(WDDD_GLOBAL.m_lpBattleGlobal->getAttackRate().size()<=0)
            {
                attackRate=1.0f;
            }
            else 
            {
                attackRate=WDDD_GLOBAL.m_lpBattleGlobal->getAttackRate()[m_shootAttackRateIndex]/1000.0f;
            }
            lpBullet=WBullet::buildBullet(Vec2(st_shoot_startPos.x,st_shoot_startPos.y), speed, lpGameFrontLayer, this, attack*attackRate, m_ExplodeRadius, getIsBigSkill());
            m_shootAttackRateIndex++;
            if(WDDD_GLOBAL.m_lpBattleGlobal->getAttackRate().size()<=m_shootAttackRateIndex)
            {
                m_shootAttackRateIndex=0;
            }
            
            if(lpBullet)
            {
                if(m_bulletSpecialType>=0)
                {
                    lpBullet->setSpecialType(m_bulletSpecialType);
                }
            }
            lpGameFrontLayer->addChild(lpBullet);
            
//            speed.x-=dy.x;
//            speed.y+=dy.y;
            speed=b2Mul(bTran, speed);
            
            WMusic::shareMusic()->PlaySound(WMusic::E_S_SHOOT);
        }
    }
    else
    {
        float attackRate;
        
        if(WDDD_GLOBAL.m_lpBattleGlobal->getAttackRate().size()<=0)
        {
            attackRate=1.0f;
        }
        else 
        {
            attackRate=WDDD_GLOBAL.m_lpBattleGlobal->getAttackRate()[m_shootAttackRateIndex]/1000.0f;
        }
       
        
        lpBullet=WBullet::buildBullet(Vec2(st_shoot_startPos.x,st_shoot_startPos.y), st_shoot_speed, lpGameFrontLayer, this, attack*attackRate, m_ExplodeRadius, getIsBigSkill());
        m_shootAttackRateIndex++;
        if(WDDD_GLOBAL.m_lpBattleGlobal->getAttackRate().size()<=m_shootAttackRateIndex)
        {
            m_shootAttackRateIndex=0;
        }
        
        if(lpBullet)
        {
            if(m_bulletSpecialType>=0)
            {
                lpBullet->setSpecialType(m_bulletSpecialType);
            }
        }
        
        lpGameFrontLayer->addChild(lpBullet);
        
        WMusic::shareMusic()->PlaySound(WMusic::E_S_SHOOT);
    }
    
    if(m_AttackTimes>1)
    {
        if(!getIsBigSkill())
        {
            setAnimation(DEF_SHOOT_REPEAT);
        }   
        else 
        {
            setAnimation(DEF_SHOOT_BIG_REPEAT);
        }
        playOnce();
        
    }
    else
    {

        if(!getIsBigSkill())
        {
            
            setAnimation(DEF_SHOOT_END);
        }   
        else 
        {
            setIsBigSkill(false);
            setAnimation(DEF_SHOOT_BIG_END);
        }
        playOnce();
        if(m_currentWBEvent) m_currentWBEvent->End();
    }
#endif
    m_AttackTimes--;
}
boolean WHero::isCurrentAnimationDone(){
	return 1;
}
void WHero::playOnce(){}
void WHero::st_shoot()
{
    if(getAnimationStatus()==DEF_SHOOT_START
|| getAnimationStatus()==DEF_SHOOT_BIG_START)
    {
        if(isCurrentAnimationDone())
        {
            st_shoot_calc();
        }
    }
    else if(getAnimationStatus()==DEF_SHOOT_REPEAT
    || getAnimationStatus()==DEF_SHOOT_BIG_REPEAT)
    {
        if(isCurrentAnimationDone())
        {
            st_shoot_calc();            
        }
    }
    else if(getAnimationStatus()==DEF_SHOOT_END
    || getAnimationStatus()==DEF_SHOOT_BIG_END)
    {
        if(isCurrentAnimationDone())
        {
            m_currentWBEvent->End();
            
            SendEventToQueue(new WBEvent(DEF_ST_NORMAL,0));
        }
    }
}


void WHero::st_freeze()
{
    checkCollision();
}


void WHero::st_hurt()
{
    
    if(isCurrentAnimationDone())
    {
        m_currentWBEvent->End();
        SendEventToQueue(new WBEvent(DEF_ST_NORMAL,0));
    }
    
    checkCollision();
}

void WHero::st_fly()
{
    checkCollisionInFly();
}

void WHero::st_flash()
{
#if 0
    if(m_blink && m_blink->isDone())
    {
        CC_SAFE_RELEASE_NULL(m_blink);
        m_currentWBEvent->End();
        SendMsgNormal();
        
        m_lpGameFrontLayer->SendMsgNextRound();
        m_lpGameFrontLayer->EndCurrentMsg();
    }      
#endif
}


void WHero::onStartBigSkillShoot()
{
#if 0
    setAnimation(DEF_SHOOT_BIG_START);
    playOnce();
    
    if(WDDD_GLOBAL.m_lpBattleGlobal->getIsInTeach()==false)
    {
        getGameFrontLayer()->getBattleScene()->getColorLayer()->setIsVisible(true);
    }
#endif
}


void WHero::ProcessStatus()
{
    
    switch (m_runStatus) {
        case DEF_ST_NORMAL://待机
            st_normal();
            break;
        case DEF_ST_MOVE_LEFT:        //移动中
        case DEF_ST_MOVE_RIGHT:        //移动中
            st_move();
            break;
        case DEF_ST_ITEMSKILL://使用道具
        
            break;
        case DEF_ST_SHOOT://射击
            st_shoot();
            break;
        case DEF_ST_FLY://飞行
            st_fly();
            break;
            
        case DEF_ST_FREEZE://冰冻
            st_freeze();
            break;
            
        case DEF_ST_DEATH://死亡
        
            break;
        case DEF_ST_HURT://伤害
            st_hurt();
            break;
        case DEF_ST_BIGSKILL://大招
        
            break;
            
        case DEF_ST_FAIL:
        case DEF_ST_SUREWIN:
            if(isCurrentAnimationDone())
            {
                m_currentWBEvent->End();
                SendEventToQueue(new WBEvent(DEF_ST_NORMAL,0));
            }
            break;
            
            
        case DEF_ST_FLASH:
            st_flash();
            break;
            
        default:
            break;
    }
#if OPEN_FIFTH    
    if(m_WSSpecial)
    {
        m_WSSpecial->setPositionInPixels(getAnchorPointInPixels());
    }
#endif
#if 0
    if(m_lpSpecialEffect)
    {
        if(m_lpSpecialEffect->getIsVisible() && m_lpSpecialEffect->isCurrentAnimationDone())
        {
            m_lpSpecialEffect->setIsVisible(false);
            
            if(m_runStatus==DEF_ST_SHOOT && getIsBigSkill())
            {
                
                WBigSkillCg *pCg=WBigSkillCg::initWithTarget(this, this,callfunc_selector(WHero::onStartBigSkillShoot));
                
                if(pCg)
                {
                    if(WDDD_GLOBAL.m_lpBattleGlobal->getIsInTeach()==false)
                    {
                        getGameFrontLayer()->getBattleScene()->getHudLayer()->addChild(pCg);
                    }
                    else
                    {
#if(OPEN_NEWTEACH)
                getGameFrontTeachLayer()->getBattleNewTeachScene()->getHudLayer()->addChild(pCg);
#else
                        getGameFrontTeachLayer()->getBattleTeachScene()->getHudLayer()->addChild(pCg);
#endif
                        
                    }
                }
            }
        }
    }
    
    if(WDDD_GLOBAL.m_lpBattleGlobal->getIsInTeach()==false
    &&m_runStatus!=DEF_ST_FLY
    && m_runStatus!=DEF_ST_DEATH
    && m_isDead==false)
    {
        CCSize sceneSize=getGameFrontLayer()->getContentSizeInPixels();
        if(getMoverPosition().x<-100 || getMoverPosition().x>(sceneSize.width+100)
           || getMoverPosition().y<-100)
        {
           
            if(getCtrlType()!=1)
            {
                BATTLE_OutOfScene *lpOut=new BATTLE_OutOfScene();
                lpOut->setBattleId(getBattleId());
                lpOut->setPlayerId(getPlayerId());
                lpOut->setCurrentPlayerId(getGameFrontLayer()->GetCurrentHero()->getPlayerId());
                
                WBSendProtocol(lpOut);
                
          
            }
            if(getGameFrontLayer()->GetCurrentHero()->getPlayerId()==getPlayerId())
            {
                getGameFrontLayer()->SendMsgNextRound();
            }
            m_isDead=true;
            
            if(WDDD_GLOBAL.m_lpBattleGlobal->getBattleMode()!=DEF_BATTLE_NORMAL_MODE_REBORN)
            {
                float x=getMoverPosition().x;
                float y=getMoverPosition().y;
                if(x<0) x=60;
                else if(x>=sceneSize.width) x=sceneSize.width-=60;
                
                if(y<0) y=100;
                
                setMoverPosition(Vec2(x, y));
                setMoverSpeed(Vec2(0,0));
            }
            
            
            
            if(m_currentWBEvent)m_currentWBEvent->End();
        }
    }
#endif
}

void WHero::checkCollisionInFly()
{
#if 0
    Vec2 tempPosition;
    Vec2 tempTangent;
    bool isInSide;
    Vec2 newPosition(0,0);
    Vec2 tangent(0,0);
    
    CCSize sceneSize;
    
    if(WDDD_GLOBAL.m_lpBattleGlobal->getIsInTeach()==false)
    {
        sceneSize=m_lpGameFrontLayer->getContentSizeInPixels();
        setMoverAcceleration(getMoverAcceleration()+m_lpGameFrontLayer->getWind()+m_lpGameFrontLayer->getGravityFly());
    }
    else
    {
        sceneSize=m_lpGameFrontTeachLayer->getContentSizeInPixels();
        setMoverAcceleration(getMoverAcceleration()+m_lpGameFrontTeachLayer->getWind()+m_lpGameFrontTeachLayer->getGravityFly());
    }
    
    
    
    
    updatePostion();
    
    int collsion=0;
    
    
//    if(m_flytime>0)
//    {
//        m_flytime-=m_dt;
//        if(m_flytime<0)
//        {
//            m_flytime=0;
//        }
//    }
//    
//    if(m_flytime==0)
//    {
    setMoverCollisionType(WMover::E_COLLISION_CIRCLE);
    
    if(WDDD_GLOBAL.m_lpBattleGlobal->getIsInTeach()==false)
    { 
        if(m_lpGameFrontLayer->getPixelByte()->CheckCollision(this,&tempPosition,&tempTangent,isInSide))
        {
            newPosition+=tempPosition;
            
            collsion++;
            
        }
    }
    else
    {
        if(m_lpGameFrontTeachLayer->getPixelByte()->CheckCollision(this,&tempPosition,&tempTangent,isInSide))
        {
            newPosition+=tempPosition;
            
            collsion++;
            
        }
    }
  //  }
    setMoverCollisionType(WMover::E_COLLISION_POINT);
    
    if(collsion>0)
    {
        newPosition.x/=collsion;
        newPosition.y/=collsion;
        
        
        setMoverPosition(newPosition);
        setMoverPrePosition(newPosition);
        setMoverSpeed(Vec2(0,0));
        
        SendMsgNormal();
       
            
            
            
            m_currentWBEvent->End();
        if(WDDD_GLOBAL.m_lpBattleGlobal->getIsInTeach()==false)
        {     
            m_lpGameFrontLayer->SendMsgNextRound();
            m_lpGameFrontLayer->EndCurrentMsg();
        }
        else
        {
#if(OPEN_NEWTEACH)
            m_lpGameFrontTeachLayer->m_teachStep=m_lpGameFrontTeachLayer->E_TEACH_S_TO_FLY_Zipper;
#else
            m_lpGameFrontTeachLayer->m_teachStep=m_lpGameFrontTeachLayer->E_TEACH_S_TO_FLY;
#endif
        }
    
    
        
    }
     
    else if(getMoverPosition().x<-100 || getMoverPosition().x>(sceneSize.width+100)
       || getMoverPosition().y<-100)
    {
    
        SendEventToQueue(new WBEvent(DEF_ST_FLASH,0));
        
        m_currentWBEvent->End();
        if(WDDD_GLOBAL.m_lpBattleGlobal->getIsInTeach()==false)
        {

            
            m_lpGameFrontLayer->SendMsgCenterToHero();
            m_lpGameFrontLayer->EndCurrentMsg();
            m_lpGameFrontLayer->_controller->centerOnPoint(CCPointMake(m_oldPosBeforeFly.x, m_oldPosBeforeFly.y),0,0.1);
        }
      
        
        setMoverPosition(m_oldPosBeforeFly);
        setMoverPrePosition(m_oldPosBeforeFly);
        setMoverSpeed(Vec2(0,0));
        
        setAnimation(DEF_NORMAL);
        playRepeat();
       
        
    }
    
    setPositionInPixels(CCPointMake(getMoverPosition().x, getMoverPosition().y));
  
    setMoverAcceleration(Vec2(0,0));
#endif
}


void WHero::checkCollision()
{
#if 0
    Vec2 tempPosition;
    Vec2 tempTangent;
    bool isInSide;
    Vec2 newPosition(0,0);
    Vec2 tangent(0,0);
    CCArray *lpPixelSprites;
    
    if(!m_needCheckCollsion) return;
    
    if(WDDD_GLOBAL.m_lpBattleGlobal->getIsInTeach()==false)
    {
        lpPixelSprites=m_lpGameFrontLayer->getPixelSprites();
        
        setMoverAcceleration(getMoverAcceleration()+m_lpGameFrontLayer->getGravity());
        
    }
    else
    {
        lpPixelSprites=m_lpGameFrontTeachLayer->getPixelSprites();
        
        setMoverAcceleration(getMoverAcceleration()+m_lpGameFrontTeachLayer->getGravity());
    }
    
    updatePostion();
    
    int collsion=0;
//    for(int i=0; i<lpPixelSprites->count(); i++)
//    {
//        WBPixelSprite *lpPixel=(WBPixelSprite *)lpPixelSprites->objectAtIndex(i);
//        
//        if(lpPixel->CheckCollision(this,&tempPosition,&tempTangent,isInSide))
//        {
//            newPosition+=tempPosition;
//            tangent+=tempTangent;
//            collsion++;
//            //break;
//        }
//        
//    } 

    if(WDDD_GLOBAL.m_lpBattleGlobal->getIsInTeach()==false)
    {
        if(m_lpGameFrontLayer->getPixelByte()->CheckCollision(this,&tempPosition,&tempTangent,isInSide))
        {
            newPosition+=tempPosition;
            tangent+=tempTangent;
            collsion++;
            
        }
    }
    else
    {
        if(m_lpGameFrontTeachLayer->getPixelByte()->CheckCollision(this,&tempPosition,&tempTangent,isInSide))
        {
            newPosition+=tempPosition;
            tangent+=tempTangent;
            collsion++;
            
        }
    }
    
  //  WLog("dffafdaf:%f,collsion%d",getMoverSpeed().y,collsion);
    if(collsion>0)
    {
        newPosition.x/=collsion;
        newPosition.y/=collsion;
     
        
        setMoverPosition(newPosition);
        setMoverPrePosition(newPosition);
        setMoverSpeed(Vec2(0,0));
        
  
        if(tangent.x!=0.0f || tangent.y!=0.0f)
        {
            tangent.x/=collsion;
            tangent.y/=collsion;
            float angle=ccpToAngle(CCPointMake(tangent.x, tangent.y));
            setMoverRotate(CC_RADIANS_TO_DEGREES(angle));
     

            if(abs(getMoverRotate()-getRotation())>0.5f)
            {
                setRotation(getMoverRotate());
            }
        }
        
        m_needCheckCollsion=false;
        m_isCollsionPre=true;
    }
    else
    {
        m_isCollsionPre=false;
        setMoverSpeed(Vec2(0,getMoverSpeed().y));
    }
    
    
    setPositionInPixels(CCPointMake(getMoverPosition().x, getMoverPosition().y));
    setMoverAcceleration(Vec2(0,0));
#endif
}


void WHero::setPlayerLose()
{
    m_loseNet=true;
    //setIsVisible(false);
}

void WHero::update(float dt)
{
    if(!m_IsInit) return;
    
    m_dt=dt;
    
 
    
    ProcessMessage();
    
    ProcessStatus();
    
   
    
}

int WHero::getCurCriticalType()
{
    if(m_isCriticalhit)
    {
            if(m_CriticalhitAttackRate>=1300)
            {
                return WFadeOutHurtLabel::E_SUPER;
            }
            else
            {
                return WFadeOutHurtLabel::E_CRIT;
            }
    }
#if OPEN_FIFTH
    else
    {
        if(getWSSkillType_s()==WBWeaponSkill::E_WEAPONSKILL_TYPE_ADDCRITICALRATE)
        {
            if (m_WSIsCriticalAttack)
            {
                if(m_CriticalhitAttackRate>=1300)
                {
                    return WFadeOutHurtLabel::E_SUPER;
                }
                else
                {
                    return WFadeOutHurtLabel::E_CRIT;
                }
            }
        }
    }
#endif
    
    return WFadeOutHurtLabel::E_NORMAL;
}

#if(OPEN_NEWTEACH)
void WHero::createHeroCould()
{
    smallCould = cwSngPlistSprite::spriteWithSpriteFrameName(DEF_TEACH_PATH"dialog_box_5.png");
    smallCould->setPositionInPixels(CCPointMake(80, 140));
    smallCould->setScale(2.5);
    smallCould->setIsVisible(false);
    addChild(smallCould);
    
    bigCould = cwSngPlistSprite::spriteWithSpriteFrameName(DEF_TEACH_PATH"dialog_box_4.png");
    bigCould->setPositionInPixels(CCPointMake(100, 250));
    bigCould->setScale(2.5);
    bigCould->setIsVisible(false);
    addChild(bigCould);
};
#endif
