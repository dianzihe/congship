#include "GameOverScene.h"
#include "GameScene.h"


SceneTestLayer1::SceneTestLayer1()
{
	auto item1 = MenuItemFont::create("Test pushScene", CC_CALLBACK_1(SceneTestLayer1::onPushScene, this));
	auto item2 = MenuItemFont::create("Test pushScene w/transition", CC_CALLBACK_1(SceneTestLayer1::onPushSceneTran, this));
	auto item3 = MenuItemFont::create("Quit", CC_CALLBACK_1(SceneTestLayer1::onQuit, this));

	auto menu = Menu::create(item1, item2, item3, nullptr);
	menu->alignItemsVertically();

	addChild(menu);

	auto s = Director::getInstance()->getWinSize();
	auto sprite = Sprite::create("Origin/chouqian.png");
	addChild(sprite);
	sprite->setPosition(Vec2(s.width - 40, s.height / 2));
	auto rotate = RotateBy::create(2, 360);
	auto repeat = RepeatForever::create(rotate);
	sprite->runAction(repeat);

	schedule(CC_SCHEDULE_SELECTOR(SceneTestLayer1::testDealloc));
}

void SceneTestLayer1::testDealloc(float dt)
{
	//CCLOG("SceneTestLayer1:testDealloc");
}

void SceneTestLayer1::onEnter()
{
	CCLOG("SceneTestLayer1#onEnter");
	Layer::onEnter();
}

void SceneTestLayer1::onEnterTransitionDidFinish()
{
	CCLOG("SceneTestLayer1#onEnterTransitionDidFinish");
	Layer::onEnterTransitionDidFinish();
}

SceneTestLayer1::~SceneTestLayer1()
{
	//NSLog(@"SceneTestLayer1 - dealloc");
}

void SceneTestLayer1::onPushScene(Ref* sender)
{
	//auto scene = SceneTestScene::create(2);
	//Director::getInstance()->pushScene(scene);
}

void SceneTestLayer1::onPushSceneTran(Ref* sender)
{
	//auto scene = SceneTestScene::create(2);
	//Director::getInstance()->pushScene(TransitionSlideInT::create(1, scene));
}


void SceneTestLayer1::onQuit(Ref* sender)
{
	//getCocosApp()->exit();
	//CCDirector::getInstance()->poscene();

	//// HA HA... no more terminate on sdk v3.0
	//// http://developer.apple.com/iphone/library/qa/qa2008/qa1561.html
	//if( [[UIApplication sharedApplication] respondsToSelector:@selector(terminate)] )
	//    [[UIApplication sharedApplication] performSelector:@selector(terminate)];
}

Scene* GameOverScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameOverScene::init()
{
	Layer::init();

	log("game over!");

	auto winSize = Director::getInstance()->getWinSize();

	//添加背景
	auto bg = Sprite::createWithSpriteFrameName("gameover.png");
	bg->setScaleX(winSize.width / bg->getContentSize().width);
	bg->setScaleY(winSize.height / bg->getContentSize().height);
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(Vec2(0, 0));
	addChild(bg);

	//返回游戏按钮
	auto backlabel = Label::createWithTTF("Try again", "fonts/Marker Felt.ttf", 36);
	backlabel->setColor(Color3B::BLACK);
	auto backItem = MenuItemLabel::create(backlabel);
	backItem->setTarget(this, menu_selector(GameOverScene::onBackItemCallback));
	backItem->setPosition(Vec2(winSize.width / 2 - backItem->getContentSize().width / 2 - 15, -winSize.height / 2 + backItem->getContentSize().height / 2 + 10)); //位于左下角
	auto menu = Menu::create(backItem, nullptr);
	addChild(menu);

	//显示本次分数，位于中间
	auto score = UserDefault::getInstance()->getStringForKey("LastScore");

	auto labelscore = Label::createWithTTF(score, "fonts/Marker Felt.ttf", 36);
	labelscore->setColor(Color3B::BLACK);
	labelscore->setPosition(Vec2(winSize.width / 2, winSize.height / 2 + 50));
	addChild(labelscore);
	
	//显示最佳分数，位于左上
	auto bestscore = UserDefault::getInstance()->getStringForKey("BestScore");

	auto labelbestscore = Label::createWithSystemFont(bestscore, "Arial", 36);
	labelbestscore->setColor(Color3B::BLACK);
	labelbestscore->setPosition(Vec2(labelbestscore->getContentSize().width / 2 + 50, winSize.height - labelbestscore->getContentSize().height / 2 - 80));
	addChild(labelbestscore);

	return true;
}

void GameOverScene::onBackItemCallback(Ref*)
{
	//返回游戏
	/*
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
	*/
}
