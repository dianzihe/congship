#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "PlaneHero.h"
#include "PlaneEnemy.h"
#include "GameOverScene.h"
#include <2d/CCSprite.h>
#include "NPC.h"
#include "hero.h"
#include "ASpriteManager.h"
#include "Monster.h"
#include "MonsterCfg.h"
#include "ZhongGaoState.h"
#include "base.h"
#include "UIBatchRenderer.h"
#include "PlayerLayerCfg.h"
#include "BossGameFrontLayer.h"
#include "extension\animation\MigAnimation.h"
#include <array>
using namespace CocosDenshion;

//GameScene* GameScene::m_gamelayer = nullptr;

const float GameScene::refresh_delay[] = { 2.0f, 1.5f, 1.0f, 0.5f, 0.2f }; //战机刷新间隔
//behaviac::vector<behaviac::Agent*>  GameScene::m_bt_agent_delete_queue;

// Initialize static members;
GameScene* GameScene::inst = NULL;

bool GameScene::init()
{
	if (!Scene::init())
		return false;
	
	log("-->%d", DQ_SET_DIR_BY_TWOPOINT(Point(1, 1), Point(2, 1)));
	log("-->%d", DQ_SET_DIR_BY_TWOPOINT(Point(1, 1), Point(2, 2)));
	log("-->%d", DQ_SET_DIR_BY_TWOPOINT(Point(1, 1), Point(1, 2)));
	log("-->%d", DQ_SET_DIR_BY_TWOPOINT(Point(1, 1), Point(0, 2)));
	log("-->%d", DQ_SET_DIR_BY_TWOPOINT(Point(1, 1), Point(0, 1)));
	log("-->%d", DQ_SET_DIR_BY_TWOPOINT(Point(1, 1), Point(0, 0)));
	log("-->%d", DQ_SET_DIR_BY_TWOPOINT(Point(1, 1), Point(1, 0)));
	log("-->%d", DQ_SET_DIR_BY_TWOPOINT(Point(1, 1), Point(2, 0)));
	
	//加载plist文件
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");
	auto s = Director::getInstance()->getWinSize();
	// launch network thread.
	//PuzzleRPC::getInstance()->launch();

	// create UI elements
	AspriteManager::instance().initilize();
	//PlayerLayerCfg::instance().init("playerlayer");

	m_actorManager = new ActorManager();
	log("GameScene---m_actorManager---->%x", m_actorManager);
	m_map = new DQMap();
	m_map->autorelease();
	m_map->setActorManager(m_actorManager);
	m_actorManager->setMap(m_map);
	addChild(m_map, GAME_LAYER_MAP);
	
	auto winSize = Director::getInstance()->getWinSize();
	log("winSize---->%d, %d", winSize.width, winSize.height);

	//MigSpriteNode::create("zhizhu.dat", "zhizhu.plist", "anim/", true, "walk_up", 0.1);

#if 1
	//monster测试
	//MonsterCfg::instance().init("monster");
#endif

	setGameLayer(new BossGameFrontLayer());
	getGameLayer()->setBattleScene(this);
	getGameLayer()->setPosition(Vec2(0, 0));
	getGameLayer()->setContentSize(Size(winSize.width, winSize.height) );
	getGameLayer()->setAnchorPoint(Point(0.5, 0.5));
	//getGameLayer()->LoadMap(pMap);

	addChild(getGameLayer(), 0);

#if 0
	auto _sprite1 = MySprite::create("gem_dark.png");
	addChild(_sprite1);
	_sprite1->setPosition(Vec2(1 * s.width / 4, s.height / 2));
	_sprite1->setScale(0.5);
#endif

	//WBossGuai *lpGuai = NULL;
	//lpGuai = WBoss4::BuildGuai();
#if 1
	CMonster * pMonster = CMonster::node();
	LookInfoMonster *monsterInfo = new LookInfoMonster();
	monsterInfo->monster_data_id = 13;
	monsterInfo->id = 17750;
	monsterInfo->move_target_x = 88;
	monsterInfo->move_target_y = 94;
	monsterInfo->move_speed = 10;
	monsterInfo->x = 50;
	monsterInfo->y = 50;
	monsterInfo->lifePercent = 80;
	monsterInfo->faction = 0;
	monsterInfo->charState = 0;
	monsterInfo->wildState = 0;

	pMonster->onLookInfoMonster(monsterInfo);
#endif	
	return true;
}

//create Update for behaviac
void GameScene::update(float dt)
{
	//behaviac::Workspace::GetInstance()->LogFrames();
	//behaviac::Workspace::GetInstance()->HandleRequests();
	//m_NPC->btexec();
	//log("UpdateLoop--->[%d, %d]\n", m_uiSprite->getPosition().x, m_uiSprite->getPosition().y);
	log("GameScene::Update-->%f", dt);
	{
		//处理未加载的图片
		//AspriteManager::instance().tick(dt);
		GameScene::GetActorManager()->update(dt);
	}
#if 0
	int frames = 0;
	behaviac::EBTStatus status = behaviac::BT_RUNNING;

	while (status == behaviac::BT_RUNNING)
	{
		printf("frame %d\n", ++frames);
		status = g_SecondAgent->btexec();
	}
#endif
	behaviac::Workspace::GetInstance()->Update();
	cleanBehaviacAgentDeleteQueue();
}

ActorManager* GameScene::GetActorManager()
{
	//return m_actorManager;
	return GameScene::GetScene()->m_actorManager;
}

GameScene::GameScene(void)
{
	//UIBatchRenderer::instance()->initilize();
	m_pRunState = NULL;
	schedule(schedule_selector(GameScene::update), .2f);
}
GameScene::~GameScene(void){
	//log("=======>release gamescene");
}

GameScene* GameScene::GetScene()
{
	//return (GameScene*)(Director::getInstance()->getRunningScene());
	if (!inst){
		assert(inst == NULL && "GameScene is not initialized.");
		return NULL;
	}

	return inst;
}
DQMap* GameScene::GetMap()
{
	return GameScene::GetScene()->m_map;
}
/*
void GameScene::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags){
	UIBatchRenderer::instance()->flush();
	if (m_pRunState)
		m_pRunState->OnDraw();

}
*/
/*
void GameScene::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	_blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
	setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_COLOR));
	_customCommand.init(_globalZOrder, transform, flags);
	_customCommand.func = CC_CALLBACK_0(GameScene::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
	
}

void GameScene::onDraw(const Mat4 &transform, uint32_t flags)
{
	//getGLProgram()->use();
	//getGLProgram()->setUniformsForBuiltins(transform);

	//GL::blendFunc(_blendFunc.src, _blendFunc.dst);

	Texture2D *_texture = Director::getInstance()->getTextureCache()->addImage("gem_wood.png");
	//_texture->retain();

	//GL::bindTexture2D(_texture->getName());
	GL::bindTexture2D(_texture->getName());
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);

	V3F_C4B_T2F_Quad quad;
	//reset to custome 
	quad.bl.vertices = Vec3(0, 0, 0);
	quad.br.vertices = Vec3(53, 0, 0);
	quad.tl.vertices = Vec3(0, 53, 0);
	quad.tr.vertices = Vec3(53, 53, 0);

	quad.bl.colors =
		quad.br.colors =
		quad.tl.colors =
		quad.tr.colors = Color4B(255, 255, 255, 255);

	quad.bl.texCoords = Tex2F(0.0f, 1.0f);
	quad.br.texCoords = Tex2F(1.0f, 1.0f);
	quad.tl.texCoords = Tex2F(0.0f, 0.0f);
	quad.tr.texCoords = Tex2F(1.0f, 0.0f);


#define kQuadSize sizeof(quad.bl) 
	size_t offset = (size_t)&quad;
	offset = (size_t)&quad;
	// vertex
	int diff = offsetof(V3F_C4B_T2F, vertices);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	// texCoords
	diff = offsetof(V3F_C4B_T2F, texCoords);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	// color
	diff = offsetof(V3F_C4B_T2F, colors);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, quadIndices);

	CHECK_GL_ERROR_DEBUG();
	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 4);
}
*/
/*
Node* GameScene::GetUI()
{
	return GameScene::GetScene()->m_uiNode;
}
*/
void GameScene::ReadLookInfoMonster(char*& buf, LookInfoMonster& value)
{
	Readint64(buf, value.id);
	Readint16(buf, value.move_target_x);
	Readint16(buf, value.move_target_y);
	Readint16(buf, value.move_speed);
	Readint16(buf, value.x);
	Readint16(buf, value.y);
	Readint16(buf, value.monster_data_id);
	Readint8(buf, value.lifePercent);
	Readint8(buf, value.faction);
	Readint(buf, value.charState);

//#define ReadArray(buf,t,data) {int len; Readint16(buf,len); data.resize(len); for(int i=0;i<len;i++){Read##t(buf,data[i]);}  }
	//ReadArray(buf, ObjectBuff, value.buffList);
	{
		int len; 
		Readint16(buf, len); 
		value.buffList.resize(len);
		for (int i = 0; i<len; i++){ 
			ReadObjectBuff(buf, value.buffList[i]);
		}  
	}
	Readint8(buf, value.wildState);
}
/*
DQCamera* GameScene::GetCamera()
{
	return m_map->GetCamera();
}
*/

void GameScene::initBG()
{
	//加载plist文件
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot_background.plist");

	auto winSize = Director::getInstance()->getWinSize();
	auto pause_sp1 = Sprite::createWithSpriteFrameName("game_pause_nor.png");
	auto pause_sp2 = Sprite::createWithSpriteFrameName("game_pause_pressed.png");
	auto resume_sp1 = Sprite::createWithSpriteFrameName("game_resume_nor.png");
	auto resume_sp2 = Sprite::createWithSpriteFrameName("game_resume_pressed.png");

	auto pauseitem = MenuItemSprite::create(pause_sp1, pause_sp2);
	auto resumeitem = MenuItemSprite::create(resume_sp1, resume_sp2);
	auto pauseButton = MenuItemToggle::createWithTarget(this, menu_selector(GameScene::pauseButtonCallBack), pauseitem, resumeitem, nullptr);
	pauseButton->setAnchorPoint(Vec2(0, 0));
	pauseButton->setPosition(Vec2(winSize.width / 2 - pauseButton->getContentSize().width, winSize.height / 2 - pauseButton->getContentSize().height)); //位于左上角

	auto menu = Menu::create(pauseButton, nullptr);
	addChild(menu, 10, PAUSE_MENU);
}

void GameScene::playBackground()
{
    auto winSize = Director::getInstance()->getWinSize();

    int delta = 10; //补缝用的，两个背景紧挨着移动可能出现缝隙

    //播放背景，两个背景的图片是一样的，紧挨着循环播放
    //注意点：1.轮播图的像素高应该比设备的大一点 2.后面的图应该稍微往前靠一点 这样就不会有缝隙了
    auto bg1 = Sprite::createWithSpriteFrameName("background.png");
    bg1->setScaleX(winSize.width / bg1->getContentSize().width);
    bg1->setScaleY(winSize.height / bg1->getContentSize().height + 0.01);
    bg1->setAnchorPoint(Vec2(0, 0));
    addChild(bg1);

    auto move1 = MoveBy::create(30, Vec2(0, -winSize.height));
    auto callfunc1 = CallFunc::create([bg1](){
        bg1->setPosition(Vec2(0, 0));
    });
    auto action1 = Sequence::create(move1, callfunc1, nullptr);
    bg1->runAction(RepeatForever::create(action1));

    auto bg2 = Sprite::createWithSpriteFrameName("background.png");
    bg2->setScaleX(winSize.width / bg2->getContentSize().width);
    bg2->setScaleY(winSize.height / bg2->getContentSize().height + 0.01);
    bg2->setAnchorPoint(Vec2(0, 0));
    bg2->setPosition(Vec2(0, bg1->getPositionY() + winSize.height - delta));
    addChild(bg2);

    auto move2 = MoveTo::create(30, Vec2(0, 0));
    auto callfunc2 = CallFunc::create([bg2, bg1, winSize, delta](){
        bg2->setPosition(Vec2(0, bg1->getPositionY() + winSize.height - delta));
    });
    auto action2 = Sequence::create(move2, callfunc2, nullptr);
    bg2->runAction(RepeatForever::create(action2));
}

void GameScene::publishScore()
{
    auto userdefault = UserDefault::getInstance();

    //查看路径，测试用
    //log(userdefault->getXMLFilePath().c_str()); 

    //存储本次游戏分数
    char score_str[100] = { 0 };
    sprintf(score_str, "%d", m_score);
    userdefault->setStringForKey("LastScore", score_str);

    //存储最佳游戏分数
    auto bestscore = userdefault->getStringForKey("BestScore");
    if (m_score > atoi(bestscore.c_str()))
        userdefault->setStringForKey("BestScore", score_str);
}

void GameScene::gameover()
{
    unschedule(schedule_selector(GameScene::update));
    unschedule(schedule_selector(GameScene::testLevel));
    publishScore(); //存储游戏分数
    cleanBehaviacAgentDeleteQueue();
    //behaviac::Agent::Destroy(m_NPC);
    auto scene = TransitionFade::create(2.0, GameOverScene::createScene());
    Director::getInstance()->replaceScene(scene);
}

void GameScene::AIButtonCallBack(Ref* pSender)//点击AI按钮回调函数
{
    m_isAI = !m_isAI;
    //PlaneHero* hero = m_Hero->getPlane();
    //hero->setAI(m_isAI);

}

void GameScene::pauseButtonCallBack(Ref* pSender)
{
    //log("press pause button!");

    /*
     *  暂停/开启 步骤：
     *1.关闭/开启 触摸监听
     *2.遍历子节点，把除了暂停按钮的 关闭/开启 渲染(onExit)
     *3.关闭/开启 敌机的刷新schedule
     *4.关闭/开启 物理引擎的模拟
     */
    static int i = 0;
    if (0 == i)
    {
        i = 1;

        _eventDispatcher->pauseEventListenersForTarget(this);

        auto vec = this->getChildren();
        for (auto &child : vec)
        {
            if (child->getTag() != PAUSE_MENU)
                child->onExit();
        }

        unschedule(schedule_selector(GameScene::update));

        ((Scene*)this->getParent())->getPhysicsWorld()->setAutoStep(false);

    }else{
        i = 0;

        _eventDispatcher->resumeEventListenersForTarget(this);

        auto vec = this->getChildren();
        for (auto &child : vec){
            if (child->getTag() != PAUSE_MENU)
                child->onEnter();
        }

        schedule(schedule_selector(GameScene::update), 0.1f);


        ((Scene*)this->getParent())->getPhysicsWorld()->setAutoStep(true);
    }
}

bool GameScene::dealWithContact(PhysicsContact& contact)
{
    //log("contact begin!");
    //获取两个碰撞的节点
    auto node1 = contact.getShapeA()->getBody()->getNode();
    auto node2 = contact.getShapeB()->getBody()->getNode();

    if (!node1 || !node2)
        return false;

    auto tag1 = node1->getTag();
    auto tag2 = node2->getTag();

    //如果碰撞的是子弹和敌方飞机
    if ((tag1 == HERO_BULLET_TAG && tag2 == ENEMY_TAG) || (tag2 == HERO_BULLET_TAG && tag1 == ENEMY_TAG))
    {
        PlaneEnemy* enemy = nullptr;
        if (tag1 == HERO_BULLET_TAG){
            node1->removeFromParent();
            enemy = ((PlaneEnemy*)node2);
        }else{
            node2->removeFromParent();
            enemy = ((PlaneEnemy*)node1);
        }

        hitEnemy(enemy);
    }

    //如果碰撞的是我方战机和敌机
    if ((tag1 == HERO_TAG && tag2 == ENEMY_TAG) || (tag2 == HERO_TAG && tag1 == ENEMY_TAG))
    {
        _eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE); //不再接受触摸事件

        PlaneHero *hero = nullptr;
        PlaneEnemy *enemy = nullptr;
        if (tag1 == HERO_TAG){
            hero = ((PlaneHero*)node1);
            enemy = ((PlaneEnemy*)node2);
        }else{
            hero = ((PlaneHero*)node2);
            enemy = ((PlaneEnemy*)node1);
        }

        hitEnemy(enemy);
        hitHero(hero);
    }

    return true;
}

void GameScene::hitEnemy(PlaneEnemy* enemy)
{
    enemy->getHurt();

    //如果敌方飞机挂了，增加分数
    if (!enemy->isLive()){
        m_score += enemy->getPoints();
        char buf[100] = { 0 };
        sprintf(buf, "Score: %d", m_score);
        auto scorelabel = (Label*)this->getChildByTag(SCORE_LABEL);
        scorelabel->setString(buf);
    }
}

void GameScene::hitHero(PlaneHero* hero)
{
    //我机直接死亡
    hero->dead();
}

void GameScene::levelUp(Level level)
{
    Label* label;
    int flontSize = 36;
    switch (level)
    {
    case LEVEL2:
        label = Label::createWithTTF("Good ! Level Up 2.", "fonts/Marker Felt.ttf", flontSize);

        break;
    case LEVEL3:
        label = Label::createWithTTF("Great ! Level Up 3.", "fonts/Marker Felt.ttf", flontSize);

        break;
    case LEVEL4:
        label = Label::createWithTTF("Awesome ! Level Up 4.", "fonts/Marker Felt.ttf", flontSize);

        break;
    case LEVEL5:
        label = Label::createWithTTF("Unbelievable ! Level Up 5.", "fonts/Marker Felt.ttf", flontSize);

        break;
    default:
        break;
    }

    auto s = Director::getInstance()->getWinSize();
    label->setPosition(Vec2(s.width / 2, s.height*0.6));

    this->addChild(label);
    label->setColor(Color3B::RED);

    //label->runAction(CCBlink::create(2, 10));
    label->runAction(
        Repeat::create(
        Sequence::create(
        CCBlink::create(2, 3),
        CCFadeTo::create(1, 0),
        nullptr), 1));
    //this->removeChild(label, true);
    //label->autorelease();
}

void GameScene::testLevel(float dt)
{
    int oldlevel = m_level;
	/*
    //根据到达的分数，获得等级
    oldlevel = m_NPC->getLevel(m_score);

    //如果level没变化，不需要更改刷新速度
    if (oldlevel == m_level)
        return;
    m_level = oldlevel;
    levelUp((Level)m_level);//升级
	*/
#if 0
	m_uiNode = Node::create();
	m_uiNode->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	//addChild(m_uiNode, GAME_LAYER_UI);

	m_uiSprite = Sprite::create();
	m_uiSprite->setPosition(Vec2(winSize.with / 2, winSize.height / 2));
	addChild(m_uiSprite, GAME_LAYER_UI);

	//图片堆叠测试代码
	auto sprite = MultiSprite::create("gem_light.png", "guangquan_lan.png");
	addChild(sprite);
	sprite->setPosition(100, 100);
#endif

#if 0
	auto animCache = AnimationCache::getInstance();
	auto test_animation0 = animCache->getAnimation("zhizhuhurt_up0");
	auto anim0 = Animate::create(test_animation0);
	auto seq = Sequence::create(anim0, nullptr);

	// create an sprite without texture
	auto grossini = Sprite::create();

	grossini->setPosition(Vec2(1 * s.width / 4, s.height / 2));
	addChild(grossini);
	auto pRepeatScale = RepeatForever::create(seq);
	grossini->runAction(pRepeatScale);
#endif	

#if 0
	Sprite *sprite;
	char str[100] = { 0 };
	std::array<int, 15> arr = { 0, 19, 8, 25, 12, 23, 24, 21, 26, 12, 20, 13, 20, 15, 31 };
	std::array<int, 15> offX = { -40, 11, 19, 11, 17, -19, -13, -11, -30, 30, -28, -33, -53, 26, -51 };
	std::array<int, 15> offY = { -23, -28, -56, -21, -43, -42, -33, -5, -26, -23, -11, -29, -45, -36, -58 };
	std::array<int, 15> flip = { 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0 };
	std::array<int, 15> rotate = { 0, 270, 0, 270, 0, 0, 0, 0, 270, 0, 0, 0, 0, 0, 0 };

	for (int i = 0; i < 15; i++)
	{
		sprintf(str, "zhizhu_%d.png", arr[i]);
		sprite = Sprite::createWithSpriteFrameName(str);
		if (NULL == sprite)
			continue;
		//sprite->setPosition(Vec2(s.width/6*(i%5+1), s.height*2/3 - s.height*(i/5)/3));
		sprite->setRotation(rotate[i]);
		sprite->setPosition(Vec2(300 + offX[i], 400 + offY[i]));
		//sprite->setScaleX(flip[i]);
		addChild(sprite, i);
	}
#endif

#if 0
	{
		string monsterName = "zhizhu";
		string xmlName = "anim/" + monsterName + ".xml";
		string plistName = "anim/" + monsterName + ".plist";
		string textureName = "anim/" + monsterName + ".dat";

		auto frameCache = SpriteFrameCache::getInstance();
		frameCache->addSpriteFramesWithFile(plistName->getCString());

		//DQAnimationCache* cache = MigAnimationCache::getShared()->getAnimationCache(xmlName->getCString());
		/*
		if(cache){
		if(node) {
		MigAnimationCache::getShared()->createAnimationFromCache(node, xmlName->getCString(), useBatchSprite);
		}
		return true;
		}

		cache = new DQAnimationCache();
		cache->plistName = plistName;
		cache->xmlName = xmlName;
		cache->textureName = textureName;
		*/
		//CC_SAFE_RETAIN(plistName);
		//CC_SAFE_RETAIN(xmlName);
		//CC_SAFE_RETAIN(textureName);
		//load animation from bin
		{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			const char* full_name = UIFeiDiaoLayer::hel009(xmlName->getCString());
#else
			//const char* full_name = hel009(xmlName->getCString());
			//const char* full_name = FileUtils::getInstance()->fullPathForFilename(xmlName->getCString());
			auto fileUtiles = FileUtils::getInstance();
			auto fragmentFullPath = fileUtiles->fullPathForFilename(xmlName->getCString());
#endif
			FILE* pfile = fopen(fragmentFullPath.c_str(), "rb");
			//assert(pfile);
			if (NULL == pfile)
				log("=======================================%s", fragmentFullPath.c_str());
			log("MigAnimationLoader::loadBin-0");
			//bin info
			sdafwefc(pfile);
			//animation info
			string animationName = sdafwefc(pfile);
			log("cache-name=%s\n", animationName.c_str());
			//sprite count
			int spriteCount = hel001(pfile);
			log("spriteCount=%d", spriteCount);
			for (int i = 0; i < spriteCount; i++)
			{
#if 0
				Vector<SpriteFrame*> animFrames(15);
				char str[100] = { 0 };
				for (int i = 1; i < 15; i++)
				{
					sprintf(str, "grossini_dance_%02d.png", i);
					auto frame = frameCache->getSpriteFrameByName(str);

					animFrames.pushBack(frame);
				}

				auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);

				// Add an animation to the Cache
				AnimationCache::getInstance()->addAnimation(animation, "dance");
#endif			
				/////////////////////////////////////////////////////////////////
				//SpriteCache* spriteCache = new SpriteCache();
				//spriteCache->name = new CCString(sdafwefc(pfile));
				string actionName = sdafwefc(pfile);
				log("spriteCache->name=%s", actionName.c_str());
				//frame count
				int frameCount = hel001(pfile);
				log("frameCount=%d", frameCount);

				for (int j = 0; j < frameCount; j++)
				{
					//log("------1");
					//FrameCache* frameCache = new FrameCache();
					//frameCache->duration = hel001(pfile);
					//frameCache->flag = hel001(pfile);
					//tile count
					int duration = hel001(pfile);
					int flag = hel001(pfile);
					int tileCount = hel001(pfile);

					Vector<SpriteFrame*> animFrames(30);
					for (int k = 0; k < tileCount; k++)
					{
						/*
						ModuleCache* moduleCache = new ModuleCache();
						moduleCache->name = new CCString(sdafwefc(pfile));

						moduleCache->offsetX = hel001(pfile);
						moduleCache->offsetY = hel001(pfile);
						moduleCache->flip = hel001(pfile);
						moduleCache->rotate = hel001(pfile);
						*/
						string fileName = sdafwefc(pfile);
						int offsetX = hel001(pfile);
						int offsetY = hel001(pfile);
						int flip = hel001(pfile);
						int rotate = hel001(pfile);

						log("------2- X:[%3d] Y:[%3d] Flip:[%3d] Rotate:[%3d] Duration[%3d]-%s",
							offsetX,
							offsetY,
							flip,
							rotate,
							duration,
							fileName.c_str());

						//log("------2---%d", frameCache->modules.size());
						//frameCache->modules.push_back(moduleCache);
						//CC_SAFE_RELEASE_NULL(moduleCache);
						//auto frame = frameCache->getSpriteFrameByName(moduleCache->name->getCString());
						//animFrames.pushBack(frame);

						auto frame = frameCache->getSpriteFrameByName(fileName);
						frame->setOffset(Vec2(offsetX, offsetY));
						frame->setRotated(rotate);
						//frame->setOffset(Vec2(offsetX, offsetY));

						animFrames.pushBack(frame);

						//ModuleCache* moduleCache = (ModuleCache*)(pObj);
						Sprite* pModuleSprite = Sprite::createWithSpriteFrameName(fileName);
						Size size = pModuleSprite->getContentSize();
						pModuleSprite->setAnchorPoint(Point(0.5, 0.5));
						bool buf = true;
						switch (rotate) {
						case 0:
							break;
						case 90:
							buf = false;
							pModuleSprite->setRotation(90);
							break;
						case 180:
							pModuleSprite->setRotation(180);
							break;
						case 270:
							buf = false;
							pModuleSprite->setRotation(270);
							break;
						default:
							break;
						}
						switch (flip) {
						case 0:
							break;
						case 1:
							pModuleSprite->setScaleX(-1);
							break;
						case 2:
							pModuleSprite->setScaleY(-1);
							break;
						default:
							break;
						}
						pModuleSprite->setPositionX(offsetX + (buf ? size.width / 2 : size.height / 2));
						pModuleSprite->setPositionY(-offsetY - (buf ? size.height / 2 : size.width / 2));
						//pFrame->addModuleSprite(pModuleSprite);
					}

					auto animation = Animation::createWithSpriteFrames(animFrames, duration);
					// Add an animation to the Cache
					log("add -----> %s", (animationName + actionName + to_string(j)).c_str());
					AnimationCache::getInstance()->addAnimation(animation, animationName + actionName + to_string(j));

					int rx = hel001(pfile);
					int ry = hel001(pfile);
					int rw = hel001(pfile);
					int rh = hel001(pfile);
					//log("------3");
					//frameCache->rectRed.setRect(rx, -ry-rh, rw, rh);
					int gx = hel001(pfile);
					int gy = hel001(pfile);
					int gw = hel001(pfile);
					int gh = hel001(pfile);
					//log("------4");
					//frameCache->rectGreen.setRect(gx, -gy-gh, gw, gh);
					//spriteCache->frames.push_back(frameCache);

					//CC_SAFE_RELEASE_NULL(frameCache);
				}
				//log("------6---%d", spriteCache->frames.size());
				//cache->sprites.push_back(spriteCache);
				//CC_SAFE_RELEASE_NULL(spriteCache);
			}
			//log("------7---%d", cache->sprites.size());
			fclose(pfile);
		}
		//MigAnimationCache::getShared()->addAnimationCache(cache);
		/*
		if(node) {
		MigAnimationCache::getShared()->createAnimationFromCache(node, xmlName->getCString(), useBatchSprite);
		}
		*/
		log("MigAnimationLoader::loadBin-end");
		//CC_SAFE_RELEASE_NULL(cache);
		return true;
	}
#endif

#if 0
	//integrate zhonggao
	m_pRunState = new CZhongGaoState();

	if (m_pRunState){
		//m_pRunState->autorelease();
		addChild(m_pRunState);
		m_pRunState->EnterState();
	}
#endif

#if 0
	//test flush correct
	auto bbsprite = DQTestFlushSprite::create();
	addChild(bbsprite);
	//bbsprite->setPosition(100, 100);
#endif

#if 1
	auto s = Director::getInstance()->getWinSize();

	auto _sprite1 = MySprite::create("gem_dark.png");
	addChild(_sprite1);
	_sprite1->setPosition(Vec2(1 * s.width / 4, s.height / 2));
	_sprite1->setScale(0.5);
#endif

#if 1
	std::string plist_content = FileUtils::getInstance()->getStringFromFile("Sprite/monster/m16.plist");

	Data image_content = FileUtils::getInstance()->getDataFromFile("Sprite/monster/m16.png");

	Image* image = new (std::nothrow) Image();
	image->initWithImageData((const uint8_t*)image_content.getBytes(), image_content.getSize());
	Texture2D* texture = new (std::nothrow) Texture2D();
	texture->initWithImage(image);
	texture->autorelease();

	CC_SAFE_RELEASE(image);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFileContent(plist_content, texture);
	Vector<SpriteFrame*> animFrames(15);

	char str[100] = { 0 };
	for (int j = 1; j < 50; j++) {
		sprintf(str, "%s_%04d.png", "attack/attack_up", j);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		log("--add to frame cache-->%s", str);
		if (NULL != frame)
			animFrames.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
#endif

#if 0
	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("grossini.plist");

	Vector<SpriteFrame*> animFrames(15);
	char str[100] = { 0 };
	for (int i = 1; i < 15; i++) {
		sprintf(str, "grossini_dance_%02d.png", i);
		auto frame = frameCache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);

	// Add an animation to the Cache
	AnimationCache::getInstance()->addAnimation(animation, "dance");
	// create an sprite without texture
	auto grossini = Sprite::create();
	//auto frame = frameCache->getSpriteFrameByName("grossini_dance_01.png");
	//grossini->setSpriteFrame(frame);
	/*
	auto winSize = Director::getInstance()->getWinSize();
	grossini->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	addChild(grossini);
	*/
	// run the animation
	//grossini->runAction(RepeatForever::create(Animate::create(animation)));
	m_uiSprite->runAction(RepeatForever::create(Animate::create(animation)));
#endif

}

void GameScene::resetBoss(float dt)
{ 
	/*
    if (!m_NPC->m_canBossRefresh)
    {
        m_NPC->m_canBossRefresh = true;
    }
	*/
}

/*
bool GameScene::initilize()
{
log("Game init!");
//m_actorManager = new ActorManager();

//m_isAI = false;
auto winSize = Director::getInstance()->getWinSize();

//加载plist文件
SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");
SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot_background.plist");
//加载音乐，播放背景音乐
auto audioengine = SimpleAudioEngine::getInstance();
audioengine->preloadBackgroundMusic("sound/bgmusic.mp3");
audioengine->preloadEffect("sound/shoot.wav");
audioengine->preloadEffect("sound/hero_down.mp3");
audioengine->preloadEffect("sound/enemy3_down.wav");
audioengine->preloadEffect("sound/enemy1_down.wav");
audioengine->preloadEffect("sound/enemy2_down.wav");
audioengine->preloadEffect("sound/big_spaceship_flying.mp3");

audioengine->playBackgroundMusic("sound/bgmusic.mp3", true);

//播放背景图
playBackground();

//加入暂停按钮
auto pause_sp1 = Sprite::createWithSpriteFrameName("game_pause_nor.png");
auto pause_sp2 = Sprite::createWithSpriteFrameName("game_pause_pressed.png");
auto resume_sp1 = Sprite::createWithSpriteFrameName("game_resume_nor.png");
auto resume_sp2 = Sprite::createWithSpriteFrameName("game_resume_pressed.png");

auto pauseitem = MenuItemSprite::create(pause_sp1, pause_sp2);
auto resumeitem = MenuItemSprite::create(resume_sp1, resume_sp2);
auto pauseButton = MenuItemToggle::createWithTarget(this, menu_selector(GameScene::pauseButtonCallBack), pauseitem, resumeitem, nullptr);
pauseButton->setAnchorPoint(Vec2(0, 0));
pauseButton->setPosition(Vec2(winSize.width / 2 - pauseButton->getContentSize().width, winSize.height / 2 - pauseButton->getContentSize().height)); //位于左上角

auto menu = Menu::create(pauseButton, nullptr);
addChild(menu, 10, PAUSE_MENU);

//create  AI  control button
auto ai_enable1 = Sprite::create("img/check_box_active.png");
auto ai_enable2 = Sprite::create("img/check_box_active_press.png");
auto ai_enable3 = Sprite::create("img/check_box_normal.png");
auto ai_enable4 = Sprite::create("img/check_box_normal_press.png");

auto pause_ai_item = MenuItemSprite::create(ai_enable1, ai_enable2);
auto resume_ai_item = MenuItemSprite::create(ai_enable3, ai_enable4);

auto AIButton = MenuItemToggle::createWithTarget(this, menu_selector(GameScene::AIButtonCallBack), pause_ai_item, resume_ai_item, nullptr);
AIButton->setAnchorPoint(Vec2(0, 0));
AIButton->setPosition(Vec2(winSize.width / 3 - AIButton->getContentSize().width, winSize.height / 2 - AIButton->getContentSize().height));
auto menu1 = Menu::create(AIButton, nullptr);
addChild(menu1, 10, AI_TAG);

//加入一个分数栏
m_score = 0;
auto scorelabel = Label::createWithSystemFont("Score: 0", "Arial", 36);
scorelabel->setAnchorPoint(Vec2(0, 0));
scorelabel->setColor(cocos2d::Color3B(255, 0, 0));
scorelabel->setPosition(Vec2(0, winSize.height - scorelabel->getContentSize().height)); //位于右上角
addChild(scorelabel, 10, SCORE_LABEL);
//默认启动ＡＩ
m_isAI = true;

g_SecondAgent = behaviac::Agent::Create<SecondAgent>();
bool bRet = g_SecondAgent->btload("fish");
if (!bRet){
log("==================");
}
g_SecondAgent->btsetcurrent("fish");
//g_SecondAgent->btexec();
//schedule(schedule_selector(GameScene::Update), 1.f);

AspriteManager::instance().initilize();
MonsterCfg::instance().init("monster");

CMonster * pMonster = CMonster::node();
LookInfoMonster *monsterInfo = new LookInfoMonster();
monsterInfo->monster_data_id = 13;
monsterInfo->id = 0;
monsterInfo->move_target_x = 300;
monsterInfo->move_target_y = 600;
monsterInfo->move_speed = 2;
monsterInfo->x = 50;
monsterInfo->y = 100;
monsterInfo->lifePercent = 80;
monsterInfo->faction = 0;
monsterInfo->charState = 0;
monsterInfo->wildState = 0;
m_actorManager->AddActor(pMonster);

pMonster->onLookInfoMonster(monsterInfo);

ASprite* m_cacheSkillSprite;
SpriteInfo _SpriteInfo;
_SpriteInfo._ActorType = ACTORTYPE_SKILLSFX;
_SpriteInfo._ActorID = 5;
m_cacheSkillSprite = AspriteManager::instance().LoadSprite(_SpriteInfo);

#if 0
//create NPC and hero
m_NPC = behaviac::Agent::Create<NPC>();
m_NPC->setParent(this);

bool bOk = m_NPC->btload("npc");

if (bOk)
{
m_NPC->btsetcurrent("npc");
}
else
{
printf("loading error!\n");
}

//this->SetIdFlag(1);
m_Hero = behaviac::Agent::Create<Hero>();

//加入我方战机，初始位置设定在下方中点
auto hero = m_Hero->getPlane();
addChild(hero, 0, HERO_TAG);
hero->setPosition(Vec2(winSize.width / 2, hero->getContentSize().height / 2 + 10));
hero->setAI(m_isAI);

//auto herobody = PhysicsBody::createBox(hero->getContentSize()); //这样设置不太精准
auto herobody = PhysicsBody::create();
Vec2 verts[] = { Vec2(0, 55), Vec2(50, -30), Vec2(-50, -30) };  //根据点组成一个多边形
herobody->addShape(PhysicsShapeEdgePolygon::create(verts, 3));
herobody->setCollisionBitmask(0x0); //不进行碰撞模拟
herobody->setContactTestBitmask(HERO_CONTACTMASKBIT);
hero->setPhysicsBody(herobody);

//加入一个触摸监听，用来移动我方战机
auto touchlistener = EventListenerTouchOneByOne::create();
touchlistener->setSwallowTouches(true);
touchlistener->onTouchBegan = [this](Touch *pTouch, Event*) {
//触摸着飞机移动
auto hero = (PlaneHero*)getChildByTag(HERO_TAG);
if (hero->boundingBox().containsPoint(pTouch->getLocation()))
{
//log("choose hero!");
return true;
}
else return false;
};
touchlistener->onTouchMoved = [this](Touch* pTouch, Event*) {
auto delta = pTouch->getDelta();
auto hero = this->m_Hero->getPlane();
auto oldpos = hero->getPosition(); //用来重置出界后的位置

hero->setPosition(Vec2(hero->getPosition().x + delta.x, hero->getPosition().y + delta.y));

//不能出界
auto winSize = Director::getInstance()->getWinSize();
if (hero->getPositionY() < hero->getContentSize().height / 2 || hero->getPositionY() > winSize.height - hero->getContentSize().height / 2
|| hero->getPositionX() < hero->getContentSize().width / 2 || hero->getPositionX() > winSize.width - hero->getContentSize().width / 2)
{
hero->setPosition(oldpos);
}
};
_eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, this);

//加入子弹渲染集合
m_bulletBox = SpriteBatchNode::createWithTexture(hero->getTexture()); //这里获得的是一张纹理大图（整张png）
addChild(m_bulletBox);

//加入碰撞事件监听
auto contactlistener = EventListenerPhysicsContact::create();
contactlistener->onContactBegin = CC_CALLBACK_1(GameScene::dealWithContact, this);
_eventDispatcher->addEventListenerWithSceneGraphPriority(contactlistener, this);

//开启Level检测，根据检测出的Level调整战机的刷新速度
m_level = LEVEL1;
schedule(schedule_selector(GameScene::testLevel), 1.0f);


schedule(schedule_selector(GameScene::Update), 0.1f);

//每隔5秒可以刷新一次boss战机
//schedule(schedule_selector(GameScene::resetBoss), 5.0f);

// 初始化并绑定
auto listener = EventListenerKeyboard::create();
//listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
//listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
{
log("Key with keycode %d pressed", keyCode);
if (keyCode == EventKeyboard::KeyCode::KEY_S)
{
//物理调试绘图关
this->getScene()->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
}
if (keyCode == EventKeyboard::KeyCode::KEY_D)
{
//物理调试绘图开
this->getScene()->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
}

};

_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

#endif
return true;
}
*/
/******************************************************************
Function    : void GameScene::addBehaviacDeleteQueue(behaviac::Agent* pAgent)
Date        : 2015-11-13 16:42:24
Author      : Quinn Pan
Parameter   : 
Return      : 
Desc        : add agent to the delete queue and delete it after Update 
******************************************************************/
void GameScene::addBehaviacAgentDeleteQueue(behaviac::Agent* pAgent)
{
    //m_bt_agent_delete_queue.push_back(pAgent);
}

/******************************************************************
Function    : void GameScene::cleanBehaviacAgentDeleteQueue()
Date        : 2015-11-13 16:46:25
Author      : Quinn Pan
Parameter   : 
Return      : 
Desc        : remove all elements in the m_bt_agent_delete_queue
******************************************************************/
void GameScene::cleanBehaviacAgentDeleteQueue()
{
	/*
    for (auto &p : m_bt_agent_delete_queue)
    {
        p->SetActive(false);
        behaviac::Agent::Destroy(p);
    }
    m_bt_agent_delete_queue.clear();
	*/
}
/*
GameScene* GameScene::create()
{
//创建一个没有重力的物理世界
//auto scene = Scene::createWithPhysics();
GameScene* scene = new GameScene();
//auto scene = Scene::create();
//auto scene = new Scene();
//	auto layer = LoginScene::create();
//scene->addChild(layer);

//scene->getPhysicsWorld()->setGravity(Vect(0, 0));

//物理调试绘图
//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
//m_gamelayer = GameScene::create();
//scene->addChild(m_gamelayer);

if (scene && scene->init()){
scene->autorelease();
//TODO: CCDirector::sharedDirector()->replaceScene(p);
//scene->addChild(SceneTestLayer1::create());
Director::getInstance()->runWithScene(scene);
}else{
delete scene;
scene = nullptr;
}
return scene;
//	Director::getInstance()->setProjection(kCCDirectorProjection3D);
}
*/
DQScreen::DQScreen(void){
	log("=======new GameScene");
}
DQScreen::~DQScreen(void){
	log("=======>release gamescene");
}
bool DQScreen::init()
{
	if (!Scene::init())
		return false;

	// launch network thread.
	//PuzzleRPC::getInstance()->launch();

	// create UI elements
	Sprite* background = GetSprite("loading_bg.jpg");
	background->setPosition(Point(320, 480));
	this->addChild(background);
	return true;
}
