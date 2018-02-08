#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "PlaneHero.h"
#include "PlaneEnemy.h"
#include "GameOverScene.h"
#include <2d/CCSprite.h>
#include "NPC.h"
#include "hero.h"

using namespace CocosDenshion;

GameScene* GameScene::m_gamelayer = nullptr;

const float GameScene::refresh_delay[] = { 2.0f, 1.5f, 1.0f, 0.5f, 0.2f }; //ս��ˢ�¼��
std::vector<behaviac::Agent*>  GameScene::m_bt_agent_delete_queue;
Scene* GameScene::createScene()
{
	//����һ��û����������������
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vect(0, 0));

	//������Ի�ͼ
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	m_gamelayer = GameScene::create();
	scene->addChild(m_gamelayer);

	return scene;
}

GameScene* GameScene::GetScene()
{
	return (GameScene*)(CCDirector::getInstance()->getRunningScene());
}

bool GameScene::init()
{
	Layer::init();
	log("---------------------------Game init!");

	//backtrace:
	//libcocos2dlua.so (behaviac::operator<(behaviac::CStringID const&, behaviac::CStringID const&)+28)
	//libcocos2dlua.so (std::less<behaviac::CStringID>::operator()(behaviac::CStringID const&, behaviac::CStringID const&) const+32)
	//libcocos2dlua.so (std::_Rb_tree<behaviac::CStringID, std::pair<behaviac::CStringID const, behaviac::Agent::MetaInfo_t>, std::_Select1st<std::pair<behaviac::CStringID const, behaviac::Agent::MetaInfo_t> >, std::less<behaviac::CStringID>, behaviac::stl_allocator<std::pair<behaviac::CStringID const, behaviac::Agent::MetaInfo_t> > >::_M_lower_bound(std::_Rb_tree_node<std::pair<behaviac::CStringID const, behaviac::Agent::MetaInfo_t> >*, std::_Rb_tree_n    #03 pc 0060b7f0  /data/app/mian.fm.cs2.online-1/lib/arm/libcocos2dlua.so (std::_Rb_tree<behaviac::CStringID, std::pair<behaviac::CStringID const, behaviac::Agent::MetaInfo_t>, std::_Select1st<std::pair<behaviac::CStringID const, behaviac::Agent::MetaInfo_t> >, std::less<behaviac::CStringID>, behaviac::stl_allocator<std::pair<behaviac::CStringID const, behaviac::Agent::MetaInfo_t> > >::find(behaviac::CStringID const&)+72)
	//libcocos2dlua.so (std::map<behaviac::CStringID, behaviac::Agent::MetaInfo_t, std::less<behaviac::CStringID>, behaviac::stl_allocator<std::pair<behaviac::CStringID const, behaviac::Agent::MetaInfo_t> > >::find(behaviac::CStringID const&)+28)
	//libcocos2dlua.so (void behaviac::Agent::RegisterTypeToMetas<behaviac::Agent>(bool)+68)
	//libcocos2dlua.so (behaviac::Agent::AgentSuperRegister<behaviac::Agent, true>::Register()+16)
	//libcocos2dlua.so (void behaviac::Agent::RegisterTypeToMetas<NPC>(bool)+20)
	//libcocos2dlua.so (bool behaviac::Agent::Register<NPC>()+20)
	//libcocos2dlua.so (AppDelegate::AppDelegate()+416)
	//libcocos2dlua.so (cocos_android_app_init(_JNIEnv*, _jobject*)+96)


	//m_isAI = false;

	auto winSize = Director::getInstance()->getWinSize();

	//����plist�ļ�
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot_background.plist");
	//�������֣����ű�������
	auto audioengine = SimpleAudioEngine::getInstance();
	audioengine->preloadBackgroundMusic("sound/bgmusic.mp3");
	audioengine->preloadEffect("sound/shoot.wav");
	audioengine->preloadEffect("sound/hero_down.mp3");
	audioengine->preloadEffect("sound/enemy3_down.wav");
	audioengine->preloadEffect("sound/enemy1_down.wav");
	audioengine->preloadEffect("sound/enemy2_down.wav");
	audioengine->preloadEffect("sound/big_spaceship_flying.mp3");

	audioengine->playBackgroundMusic("sound/bgmusic.mp3", true);

	log("load---------------------------Music!");

	//ws = behaviac::Agent::GetInstance<WorldState>(0);
	ws = behaviac::Agent::Create<WorldState>();
	//ws->setParent(this);
	ws->dq_parent = this;
	ws->level0_daly;
	//GameLogic* logic = BEHAVIAC_NEW framework::GameLogic();
	//framework::gl = logic;

	/*
	//create NPC and hero
	m_NPC = behaviac::Agent::Create<NPC>();

	log("load---------------------------Agent::Create<NPC>()");

	m_NPC->setParent(this);

	log("load---------------------------m_NPC->setParent(this)");

	bool bOk = m_NPC->btload("npc");

	log("load---------------------------m_NPC->btload(npc)");
	if (bOk)
	{
	m_NPC->btsetcurrent("npc");
	log("load---------------------------m_NPC->btsetcurrent");
	}
	else
	{
	log("loading error!\n");
	}
	*/

	//this->SetIdFlag(1);
	//m_Hero = behaviac::Agent::Create<Hero>();

	log("load---------------------------behaviac object!");
	//���ű���ͼ
	playBackground();

	//������ͣ��ť
	auto pause_sp1 = Sprite::createWithSpriteFrameName("game_pause_nor.png");
	auto pause_sp2 = Sprite::createWithSpriteFrameName("game_pause_pressed.png");
	auto resume_sp1 = Sprite::createWithSpriteFrameName("game_resume_nor.png");
	auto resume_sp2 = Sprite::createWithSpriteFrameName("game_resume_pressed.png");

	auto pauseitem = MenuItemSprite::create(pause_sp1, pause_sp2);
	auto resumeitem = MenuItemSprite::create(resume_sp1, resume_sp2);
	auto pauseButton = MenuItemToggle::createWithTarget(this, menu_selector(GameScene::pauseButtonCallBack), pauseitem, resumeitem, nullptr);
	pauseButton->setAnchorPoint(Vec2(0, 0));
	pauseButton->setPosition(Vec2(winSize.width / 2 - pauseButton->getContentSize().width, winSize.height / 2 - pauseButton->getContentSize().height)); //λ�����Ͻ�

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


	//����һ��������
	m_score = 0;
	auto scorelabel = Label::createWithSystemFont("Score: 0", "Arial", 36);
	scorelabel->setAnchorPoint(Vec2(0, 0));
	scorelabel->setColor(cocos2d::Color3B(255, 0, 0));
	scorelabel->setPosition(Vec2(0, winSize.height - scorelabel->getContentSize().height)); //λ�����Ͻ�
	addChild(scorelabel, 10, SCORE_LABEL);
	//Ĭ����������
	m_isAI = true;

#if 1	
	//�����ҷ�ս������ʼλ���趨���·��е�
	//Hero* hero = m_Hero->getPlane();
	//auto hero = m_Hero->getPlane();

	dq = PlaneHero::make();

	//dq->init();
	//auto dq = Sprite::createWithSpriteFrameName("hero2.png");

	//PlaneHero* hero = PlaneHero::create();
	//Sprite *dq = Sprite::createWithSpriteFrameName("hero2.png");
	//this->addChild(hero, 0, HERO_TAG);
	dq->root->setPosition(Vec2(200, 200));
	//dq->root->setPosition(Vec2(200, 200));
	addChild(dq->root, 0, HERO_TAG);
	log("----------00000000000");
	//addChild(bb);
	//addChild(dq, 0, HERO_TAG);

	//addChild(hero, 9, HERO_TAG);
	//hero->setPosition(Vec2(winSize.width / 2, hero->getContentSize().height / 2 + 10));
	//hero->setAI(m_isAI);
	//m_Hero->setAI(m_isAI);
	//ws->fdsafdsafd;
	ws->spawnEnemy(1);

	auto cache = SpriteFrameCache::getInstance();
	//auto sprite = Sprite::createWithSpriteFrameName("101-1.png");

	auto str = new char[50];// std::isstream << ""

	auto sprite = Sprite::create("101-1.png");
	// ����ê��
	//sprite->setAnchorPoint(Vec2(0.5f, 0.5f));

	// ��������
	sprite->setPosition(Vec2(200, 330));
	auto animation = Animation::create(); // ��������
	{
		for (int index = 0; index < 10; index++) {
			std::sprintf(str, "101-%d.png", index + 1);
			animation->addSpriteFrameWithFile(str); // �򶯻����ͼƬ
		}
		// should last 2.8 seconds. And there are 14 frames.
		animation->setDelayPerUnit(2.8f / 14.0f);
		animation->setRestoreOriginalFrame(true);

		// Add an animation to the Cache
		AnimationCache::getInstance()->addAnimation(animation, "explode-1");
	}
	animation = Animation::create(); // ��������
	{
		for (int index = 0; index < 8; index++) {
			std::sprintf(str, "102-%d.png", index + 1);
			animation->addSpriteFrameWithFile(str); // �򶯻����ͼƬ
		}
		// should last 2.8 seconds. And there are 14 frames.
		animation->setDelayPerUnit(2.8f / 14.0f);
		animation->setRestoreOriginalFrame(true);

		// Add an animation to the Cache
		AnimationCache::getInstance()->addAnimation(animation, "explode-2");
	}
	animation = Animation::create(); // ��������
	{
		for (int index = 0; index < 8; index++) {
			std::sprintf(str, "99-%d.png", index + 1);
			animation->addSpriteFrameWithFile(str); // �򶯻����ͼƬ
		}
		// should last 2.8 seconds. And there are 14 frames.
		animation->setDelayPerUnit(2.8f / 14.0f);
		animation->setRestoreOriginalFrame(true);

		// Add an animation to the Cache
		AnimationCache::getInstance()->addAnimation(animation, "shoot-2");
	}
	// ->addAnimation(anim, GemUtils::attackAnim(GemUtils::Fire));
	auto repeated = RepeatForever::create(Animate::create(animation));
	sprite->runAction(repeated);
	sprite->setOpacity(255);

	addChild(sprite, 10, 1000);
	//m_NPC = new NPC();
	//m_NPC->setParent(this);
	//m_NPC->spawnEnemy();
#endif

#if 1
	auto herobody = PhysicsBody::create();
	Vec2 verts[] = { Vec2(0, 55), Vec2(50, -30), Vec2(-50, -30) };  //���ݵ����һ�������
	herobody->addShape(PhysicsShapeEdgePolygon::create(verts, 3));
	herobody->setCollisionBitmask(0x0); //��������ײģ��
	herobody->setContactTestBitmask(HERO_CONTACTMASKBIT);
	dq->root->setPhysicsBody(herobody);

	//����һ�����������������ƶ��ҷ�ս��
	auto touchlistener = EventListenerTouchOneByOne::create();
	touchlistener->setSwallowTouches(true);
	touchlistener->onTouchBegan = [this](Touch *pTouch, Event*) {
		log("--->touch began");
		//�����ŷɻ��ƶ�
		auto hero = getChildByTag(HERO_TAG);
		if (hero->boundingBox().containsPoint(pTouch->getLocation()))
		{
			log("choose hero!");
			return true;
		}
		else return false;
	};
	touchlistener->onTouchMoved = [this](Touch* pTouch, Event*) {
		log("--->touch move");
		auto delta = pTouch->getDelta();
		//auto hero = this->m_Hero->getPlane();
		auto hero = getChildByTag(HERO_TAG);
		auto oldpos = hero->getPosition(); //�������ó�����λ��

		hero->setPosition(Vec2(hero->getPosition().x + delta.x, hero->getPosition().y + delta.y));

		//���ܳ���
		auto winSize = Director::getInstance()->getWinSize();
		if (hero->getPositionY() < hero->getContentSize().height / 2 || hero->getPositionY() > winSize.height - hero->getContentSize().height / 2
			|| hero->getPositionX() < hero->getContentSize().width / 2 || hero->getPositionX() > winSize.width - hero->getContentSize().width / 2)
		{
			hero->setPosition(oldpos);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, this);
#endif

#if 1
	//�����ӵ���Ⱦ����
	m_bulletBox = SpriteBatchNode::createWithTexture(dq->root->getTexture()); //�����õ���һ�������ͼ������png��
	addChild(m_bulletBox);

	//������ײ�¼�����
	auto contactlistener = EventListenerPhysicsContact::create();
	contactlistener->onContactBegin = CC_CALLBACK_1(GameScene::dealWithContact, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactlistener, this);

	//����Level��⣬���ݼ�����Level����ս����ˢ���ٶ�
	m_level = LEVEL1;
	//schedule(schedule_selector(GameScene::testLevel), 1.0f);
	schedule(schedule_selector(GameScene::Update), .1f);
	//����󣬿�ʼ�����ӵ�
	//schedule(schedule_selector(GameScene::beginShooting), 0.5f);
	//����ӵ��Ƿ���磬�����������bulletBox
	//schedule(schedule_selector(GameScene::removeBullet), 0.1f);

	//ÿ��5�����ˢ��һ��bossս��
	//schedule(schedule_selector(GameScene::resetBoss), 5.0f);
#endif
	
	
#if 1
	// ��ʼ������
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
	{
		log("Key with keycode %d pressed", keyCode);
		if (keyCode == EventKeyboard::KeyCode::KEY_S)
		{
			//������Ի�ͼ��
			this->getScene()->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
			//this->m_Hero->getPlane()->enableShowScreenDebugInfo(false);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_D)
		{
			//������Ի�ͼ�� 
			this->getScene()->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
			//this->m_Hero->getPlane()->enableShowScreenDebugInfo(true);
		}

	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif	
	log("load---------------------------end!");
	return true;
}
void GameScene::beginShooting(float dt){
	dq->beginShooting(.1);
}
void GameScene::removeBullet(float dt){
	dq->removeBullet(.1);
}
void GameScene::playBackground()
{

	auto winSize = Director::getInstance()->getWinSize();

	int delta = 10; //�����õģ����������������ƶ����ܳ��ַ�϶

	//���ű���������������ͼƬ��һ���ģ�������ѭ������
	//ע��㣺1.�ֲ�ͼ�����ظ�Ӧ�ñ��豸�Ĵ�һ�� 2.�����ͼӦ����΢��ǰ��һ�� �����Ͳ����з�϶��
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

	//�鿴·����������
	//log(userdefault->getXMLFilePath().c_str()); 

	//�洢������Ϸ����
	char score_str[100] = { 0 };
	sprintf(score_str, "%d", m_score);
	userdefault->setStringForKey("LastScore", score_str);

	//�洢�����Ϸ����
	auto bestscore = userdefault->getStringForKey("BestScore");
	if (m_score > atoi(bestscore.c_str()))
		userdefault->setStringForKey("BestScore", score_str);
}

void GameScene::gameover()
{
	unschedule(schedule_selector(GameScene::Update));
	unschedule(schedule_selector(GameScene::testLevel));
	publishScore(); //�洢��Ϸ����
	cleanBehaviacAgentDeleteQueue();
	//behaviac::Agent::Destroy(m_NPC);
	behaviac::Agent::Destroy(m_Hero);
	auto scene = TransitionFade::create(2.0, GameOverScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void GameScene::AIButtonCallBack(Ref* pSender)//���AI��ť�ص�����
{
	m_isAI = !m_isAI;
	m_Hero->setAI(m_isAI);
	//PlaneHero* hero = m_Hero->getPlane();
	//hero->setAI(m_isAI);

}

void GameScene::pauseButtonCallBack(Ref* pSender)
{
	//log("press pause button!");

	/*
	 *  ��ͣ/���� ���裺
	 *1.�ر�/���� ��������
	 *2.�����ӽڵ㣬�ѳ�����ͣ��ť�� �ر�/���� ��Ⱦ(onExit)
	 *3.�ر�/���� �л���ˢ��schedule
	 *4.�ر�/���� ���������ģ��
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

		unschedule(schedule_selector(GameScene::Update));

		((Scene*)this->getParent())->getPhysicsWorld()->setAutoStep(false);

	}
	else
	{
		i = 0;

		_eventDispatcher->resumeEventListenersForTarget(this);

		auto vec = this->getChildren();
		for (auto &child : vec)
		{
			if (child->getTag() != PAUSE_MENU)
				child->onEnter();
		}

		schedule(schedule_selector(GameScene::Update), 0.1f);


		((Scene*)this->getParent())->getPhysicsWorld()->setAutoStep(true);
	}
}

bool GameScene::dealWithContact(PhysicsContact& contact)
{
	//log("contact begin!");
	//��ȡ������ײ�Ľڵ�
	auto node1 = contact.getShapeA()->getBody()->getNode();
	auto node2 = contact.getShapeB()->getBody()->getNode();

	if (!node1 || !node2)
		return false;

	auto tag1 = node1->getTag();
	auto tag2 = node2->getTag();

	//�����ײ�����ӵ��͵з��ɻ�
	if ((tag1 == HERO_BULLET_TAG && tag2 == ENEMY_TAG) || (tag2 == HERO_BULLET_TAG && tag1 == ENEMY_TAG))
	{
		PlaneEnemy* enemy = nullptr;
		if (tag1 == HERO_BULLET_TAG)
		{
			node1->removeFromParent();
			enemy = ((PlaneEnemy*)node2);
		}
		else
		{
			node2->removeFromParent();
			enemy = ((PlaneEnemy*)node1);
		}

		hitEnemy(enemy);
	}

	//�����ײ�����ҷ�ս���͵л�
	if ((tag1 == HERO_TAG && tag2 == ENEMY_TAG) || (tag2 == HERO_TAG && tag1 == ENEMY_TAG))
	{
		_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE); //���ٽ��ܴ����¼�

		PlaneHero *hero = nullptr;
		PlaneEnemy *enemy = nullptr;
		if (tag1 == HERO_TAG)
		{
			hero = ((PlaneHero*)node1);
			enemy = ((PlaneEnemy*)node2);
		}
		else
		{
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

	//����з��ɻ����ˣ����ӷ���
	if (!enemy->isLive())
	{
		m_score += enemy->getPoints();
		char buf[100] = { 0 };
		sprintf(buf, "Score: %d", m_score);
		auto scorelabel = (Label*)this->getChildByTag(SCORE_LABEL);
		scorelabel->setString(buf);
	}
}

void GameScene::hitHero(PlaneHero* hero)
{
	//�һ�ֱ������
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
	//���ݵ���ķ�������õȼ�
	oldlevel = m_NPC->getLevel(m_score);

	//���levelû�仯������Ҫ����ˢ���ٶ�
	if (oldlevel == m_level)
	return;
	m_level = oldlevel;
	levelUp((Level)m_level);//����
	*/
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

//create Update for behaviac
void GameScene::Update(float dt)
{
	log("gamescene update---------------------------");

	const GameObjectList* objects = ws->getAllGameObjects();

	//float dt = ws->timeElapsed / 1000.0f;
	//behaviac::Workspace::GetInstance()->SetDeltaFrameTime(dt);

	//behaviac::Workspace::GetInstance()->Update();

	for (ConstGameObjectIter itr = objects->begin(); itr != objects->end(); ++itr)
	{
		GameObject* g = *itr;
		g->age += ws->timeElapsed;
		g->doActions(dt);
	}

	//behaviac::Workspace::GetInstance()->LogFrames();
	//behaviac::Workspace::GetInstance()->HandleRequests();
	//m_NPC->btexec();

	//behaviac::Workspace::GetInstance()->Update();
	//cleanBehaviacAgentDeleteQueue();
}

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
