//
//  WAnimationManager.cpp
//  dandandao
//
//  Created by haotao on 12-2-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


#include "WAnimationManager.h"


const char WanimationFileNameList[][32]=
{
    WANI_IWCO_BATTLEBOY,  
    WANI_IWCO_BATTLEGIRL,    
    WANI_IWCO_BATTLEEFFECT,
    WANI_IWCO_BATTLEEFFICIENTS,
    WANI_IWCO_SHOPEFFICIENTS,
    WANI_IWCO_SHOPBOY,
    WANI_IWCO_SHOPGIRL, 
    WANI_IWCO_ISLAND,    
    WANI_IWCO_BATTLEFACE,  
    WANI_IWCO_TEACH,
    WANI_IWCO_NEWTEACH,
    WANI_IWCO_BOSS,
    WANI_IWCO_MONSTER1,
    WANI_IWCO_MONSTER2,
    WANI_IWCO_BOSS21,
    WANI_IWCO_BOSS22,
    WANI_IWCO_MONSTER3,
    WANI_IWCO_EGG,
    WANI_IWCO_STRENGTHEN,
    WANI_IWCO_WING,
    WANI_IWCO_MONSTEREFFICIENTS, 
    WANI_IWCO_BOSS31,
    WANI_IWCO_BOSS32,
    WANI_IWCO_BOSS4
};

const char WanimationFileNameListInloading[][32]=
{
    WANI_IWCO_BATTLEEFFICIENTS,
    WANI_IWCO_NEWTEACH,
    WANI_IWCO_MONSTER2,
};




void WAnimationManager::BuildIWcoManagerList()
{
    int count=sizeof(WanimationFileNameList)/sizeof(WanimationFileNameList[0]);
    
    for(int i=0; i<count; i++)
    {
        //cwSngAnimationPool::sharedAnimationPool()->loadIWCO("gameResources/sng_animation/", WanimationFileNameList[i]);
   }
}

void WAnimationManager::BuildIWcoManagerListInLoading()
{
    int count=sizeof(WanimationFileNameListInloading)/sizeof(WanimationFileNameListInloading[0]);
    
    for(int i=0; i<count; i++)
    {
        //cwSngAnimationPool::sharedAnimationPool()->loadIWCO("gameResources/sng_animation/", WanimationFileNameListInloading[i]);
    }
    
    
}
/*
WAnimationManager::addAnimationToCharater(iwco_name,
	"attackstart1-t",
	lpHero,
	WHero::DEF_SHOOT_START,
	desc,
	0.1,
	true);
	
void WAnimationManager::addAnimationToCharater(const string &iwconame,
	const string &animationName,
	Sprite *pChara,
	int animationId,
	map<string, string> desc,
	float aniDelay = 0.2,
	bool filter = false)
{

	//开始射击动画
	//1,获取动画	
	//2,将动画加入pool
	//3,根据animationId，进行相关索引
	//创建一个全局的结构，通过ID来获取相应的animation
#if 0
	Animation *animation = Animation::create();
	animation->setDelayPerUnit(0.08);
	for (int i = 1; i <= 11; i++){
		CCSprite *tex = GetSprite("gameui/qiu1_" + toStr(i) + ".png");
		animation->addSpriteFrameWithTexture(tex->getTexture(), tex->getTextureRect());
	}

	Animate *anim = Animate::create(animation);
	return anim;

	directions = [(0, 1), (-1, 1), (-1, 0), (-1, -1), (0, -1), (1, -1), (1, 0), (1, 1)]
		for dc in xrange(len(directions)) :
			d = directions[dc]
			for i in xrange(11) :
				if i == 10 :
					key = ("idle", d)
				else :
				key = (i, d)
				t = self.bigtexture.sub(32 * i, (256 - 32) - 32 * dc, 32, 32)
				#print 32 * i, (512 - 32) - 32 * dc
				self.images[key] = t
#endif
}
*/


/************************************************************************/
/* 使用方法                                                                     */
/************************************************************************/
// 
// cwSngAnimationPool * cAni = cwSngAnimationPool::sharedAnimationPool();
////装载一个iwco（人物）
// cAni->loadIWCO("", "tt3");			
// {
////创建装备描述
// 	map<string, string>	equipMap;
// 	equipMap.insert(pair<string,string>("tt","tt"));
////创建带有指定装备的动画
// 	cwSngAnimation *	thisNewAnimation = cAni->animation("tt3", "wrong1", equipMap);
// 	//
// 	thisNewAnimation->setDelay(0.3f);
// 
// 	cwSngSprite *	thisNewSprite = new cwSngSprite();
// 	thisNewSprite->addAnimationToDict(0, thisNewAnimation);
// 
// 	thisNewSprite->setAnimation(0);
// 	thisNewSprite->playRepeat();
// 
// 	thisNewSprite->setAnchorPoint(ccp(0, 0));
// 	thisNewSprite->setPosition(ccp(100, 100));
// }