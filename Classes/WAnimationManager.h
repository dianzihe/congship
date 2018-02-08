//
//  WAnimationManager.h
//  dandandao
//
//  Created by haotao on 12-2-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef dandandao_WAnimationManager_h
#define dandandao_WAnimationManager_h
#include <string>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
#define WANI_IWCO_BATTLEBOY        "battleBoy"
#define WANI_IWCO_BATTLEGIRL       "battleGirl"
#define WANI_IWCO_BATTLEEFFECT  "battleEffect"
#define WANI_IWCO_BATTLEFACE      "face"
#define WANI_IWCO_BATTLEEFFICIENTS "battleEfficients"
#define WANI_IWCO_SHOPEFFICIENTS "shopEfficients"
#define WANI_IWCO_SHOPBOY             "shopBoy"
#define WANI_IWCO_SHOPGIRL            "shopGirl"
#define WANI_IWCO_ISLAND                "island"
#define WANI_IWCO_TEACH                 "teach"
#define WANI_IWCO_NEWTEACH                 "teach2"
#define WANI_IWCO_BOSS                    "boss"
#define WANI_IWCO_MONSTER1          "monster1"
#define WANI_IWCO_MONSTER2          "monster2"
#define WANI_IWCO_BOSS21                "boss2-1"
#define WANI_IWCO_BOSS22                "boss2-2"
#define WANI_IWCO_MONSTER3          "monster3"
#define WANI_IWCO_EGG               "egg"
#define WANI_IWCO_STRENGTHEN        "strengthen"
#define WANI_IWCO_WING              "Wing"
#define WANI_IWCO_MONSTEREFFICIENTS "monsterEfficient"

#define WANI_IWCO_BOSS31                "boss3-1"
#define WANI_IWCO_BOSS32                "boss3-2"
#define WANI_IWCO_BOSS4                 "boss4"
#define WANI_IWCO_BOSS4_TORNADO         "tornado"

class WAnimationManager
{
    
public:
    /**
     * @brief 根据数据表生成管理列表
     */
	static void BuildIWcoManagerList();
    
    static void BuildIWcoManagerListInLoading();
	static void addAnimationToCharater(const string &iwconame,
		const string &animationName,
		Sprite *pChara,
		int animationId,
		map<string, string> desc,
		float aniDelay = 0.2,
		bool filter = false){};

};

#endif
