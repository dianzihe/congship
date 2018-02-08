#include "PlaneHero.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Sprite * PlaneHero::GetSprite(const std::string& filename)
{
	Sprite *psprite = Sprite::create();

	// Search in the cache, first
	SpriteFrameCache *sfc = SpriteFrameCache::sharedSpriteFrameCache();
	SpriteFrame *psf = sfc->spriteFrameByName(filename.c_str());

	std::string::size_type pos;
	if (!psf && (pos = filename.find_last_of('/')) != filename.npos)
	{
		std::string lastPart(filename.begin() + pos + 1, filename.end());
		psf = sfc->spriteFrameByName(lastPart.c_str());
	}

	if (psf){
		psprite->initWithSpriteFrame(psf);
	}
	else{
		CCLOG("WARNING : %s not in a PACK!", filename.c_str());
		if (!psprite->initWithFile(filename.c_str()))
		{
			CCLOG("ERROR: %s is not in resources", filename.c_str());
			return NULL;
		}
	}
	return psprite;
}

bool PlaneHero::init()
{
	/*
	if (!Sprite::init()) {
		CCLOG("-------plane hero init exit");
		return false;
	}
    */
	CCLOG("-------plane hero init exit");
    //set ai action false
    m_isAI = false;
    //初始化纹理图
	//this->initWithSpriteFrameName("hero2.png");
	//this->addChild(spritepig);

	//this->btload("enemy_fsm");
	//this->btsetcurrent("enemy_fsm");
	
	this->root = GetSprite("hero2.png");
	this->root->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->root->retain();
	
    draw = nullptr;
    showDebugInfo = true;
    return true;
}

/*
void PlaneHero::onEnter()
{
    //Sprite::onEnter();
	Node::onEnter();
	CCLOG("000000000000000000000");
    draw = DrawNode::create();
    this->getParent()->addChild(draw, 10);

    //进入后，开始发射子弹
    schedule(schedule_selector(PlaneHero::beginShooting), 0.5f);
    //检查子弹是否出界，出界则清除出bulletBox
    schedule(schedule_selector(PlaneHero::removeBullet), 0.1f);
    if (m_isAI){
        //schedule(schedule_selector(PlaneHero::AIAction), 0.3f);
    }
}
*/

void PlaneHero::setHeroPlaneUnderPosition(Point targetPosition)
{
	/*
    //auto hero = (PlaneHero*)(this->getParent()->getChildByTag(GameScene::HERO_TAG));
    assert(this->getTag() == GameScene::HERO_TAG);
    auto hero = this;
    if (hero == nullptr) return;
    Point point = Vec2(targetPosition.x, hero->getPosition().y);
    auto enemy = getNearestEnemy(point);

    if (isWillBeCrashEnemy(enemy, point))
    {
        //如果新位置将会发生碰撞，就不设置
        return;
    }
    //set hero's position
    hero->setPosition(point);
	*/
}

void PlaneHero::setAI(bool value){
    m_isAI = value;
    if (draw != nullptr)
    {
        draw->clear();
    }
    //if (m_isAI){
    //    schedule(schedule_selector(PlaneHero::AIAction), 0.3f);
    //}
    //else{
    //    unschedule(schedule_selector(PlaneHero::AIAction));
    //}
}

void PlaneHero::AIAction(float level)
{
}


/**
*@desc: the dead method
*/
void PlaneHero::dead()
{
    //getPhysicsBody()->setContactTestBitmask(0x0); ////设置碰撞标志位，不再发生碰撞事件
    blowUp();
}

/**
*@desc: blowup hero plane
*/
void PlaneHero::blowUp()
{
    this->stopShooting();
    SimpleAudioEngine::getInstance()->playEffect("sound/hero_down.mp3");

    //加载死亡动画
    auto animation = Animation::create();
    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n1.png"));
    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n2.png"));
    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n3.png"));
    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n4.png"));
    animation->setDelayPerUnit(0.2f);
    animation->setRestoreOriginalFrame(true);

    auto blowUp = Animate::create(animation);

    //爆炸完后结束游戏
	/*
    auto gameoverCall = CallFunc::create([this]() {
        //log("call gameover!");
        removeFromParent();
        GameScene::sharedGameLayer()->gameover();
    });

    this->runAction(Sequence::create(blowUp, gameoverCall, nullptr));
	*/
}

/**
* begin shooting
* @param dt not used
*/
void PlaneHero::beginShooting(float dt)
{
	CCLOG("begin shooting ------>");
    SimpleAudioEngine::getInstance()->playEffect("sound/shoot.wav");

    //log("a bullet shoot!");
    //创建一颗子弹，加入到GameLayer的子弹渲染器中
    auto bullet = Sprite::createWithSpriteFrameName("bullet1.png");
    bullet->setPosition(Vec2(root->getPositionX(), root->getPositionY() + root->getContentSize().height / 2));
    auto bulletBox = GameScene::sharedGameLayer()->getBulletBox();

    bulletBox->addChild(bullet, 0, GameScene::HERO_BULLET_TAG);

    //给子弹套一个body，加一个初始速度，让其射到物理世界中
    auto body = PhysicsBody::createBox(bullet->getContentSize(), PhysicsMaterial(0, 0, 0));
    body->setVelocity(Vect(0, 500));
    body->setContactTestBitmask(GameScene::ContactMaskBit::HERO_BULLET_CONTACTMASKBIT);
    body->setCollisionBitmask(0x0); //不进行碰撞模拟，因为不需要。

    bullet->setPhysicsBody(body);
	
}

/**
* @desc: remove bullet which out of scene
* @param: dt unused
*/
void PlaneHero::removeBullet(float dt)
{
    //遍历每一颗子弹，把出界的删除
    auto bulletBox = GameScene::sharedGameLayer()->getBulletBox();
    auto vec = bulletBox->getChildren();
    for (auto &bullet : vec)
    {
        auto posInNode = bullet->getPosition();
        //由于bullet处于bulletBox的模型坐标系，因此要转化成世界坐标系，不过如果子弹渲染器在原点则不是必要
        auto posInWorld = bulletBox->convertToWorldSpace(posInNode);
        if (posInWorld.y > Director::getInstance()->getVisibleSize().height)
        {
            bulletBox->removeChild(bullet, true);
            //log("a bullet remove!");
        }
    }
}

/**
* @desc stop shooting
*/
void PlaneHero::stopShooting()
{
    //unschedule(schedule_selector(PlaneHero::beginShooting));
}
