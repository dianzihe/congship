#include "hero.h"
#include "PlaneHero.h"
#include "GameScene.h"
#include "enemy.h"
#include "PlaneEnemy.h"
USING_NS_CC;

Hero::Hero()
{
    //m_plane = PlaneHero::create();
	m_plane = PlaneHero::make();
    this->btload("hero");
    this->btsetcurrent("hero");
    waitTime = 20;
    m_isAI = true;
}

Hero::~Hero()
{

}

void Hero::findAnNearestEnemy()
{
	/*
	if (draw)
	{
		draw->clear();
	}
	assert(this->getTag() == GameScene::HERO_TAG);
	//auto hero = (PlaneHero*)this->getParent()->getChildByTag(GameScene::HERO_TAG);
	auto hero = this;

	nearestEnemy = getNearestEnemy();//get the nearest enemy {findAnNearestEnemy}
	*/
}

bool Hero::isWillBeCrashOnNearestEnemy()
{
	/*
	if (nearestEnemy != NULL && isWillBeCrashEnemy(nearestEnemy))//the enemy is not null and will be crash on the hero plane {isWillbeCrashEnemy }
	{
		return true;
	}
	*/
	return false;
}

void Hero::EscapeEnemyCrash()
{
	/*
	//{EscapeEnemyCrash}
	auto hero = this;
	auto enemyPosition = nearestEnemy->getPosition();
	auto heroPosition = hero->getPosition();

	//左右调整
	if (enemyPosition.x > heroPosition.x)
	{
		heroPosition.x = enemyPosition.x - (nearestEnemy->getBoundingBox().size.width + hero->getBoundingBox().size.width) / 2 - 6;
		hero->setPosition(heroPosition);
	}
	else if (enemyPosition.x < heroPosition.x)
	{
		heroPosition.x = enemyPosition.x + (nearestEnemy->getBoundingBox().size.width + hero->getBoundingBox().size.width) / 2 + 6;
		hero->setPosition(heroPosition);
	}
	else //hero 和 enemy处于同一垂直的直线上
	{
		//如果敌人在前面来的，且有后路可以退
		if (heroPosition.y > 0 && enemyPosition.y > heroPosition.y)
		{
			heroPosition.y = heroPosition.y - 10;
			hero->setPosition(heroPosition);
		}
		else //重新查找新的位置
		{
			setHeroPlaneUnderPosition(heroPosition);
		}

	}
	*/
}


bool Hero::hasEnemyInFrontCanAttack()
{
	/*
	if (getEnemyInFrontOfPosition(this->getPosition()) == NULL)
	{
		return false;
	}
	*/
	return true;
}

void Hero::findAnEnemyAndAttack()
{
	/*
	//find an enemy and set the hero plane under the enemey{findAnEnemeyAndAttack}
	auto enemy = findAnEnemy();
	if (enemy)
	{
		setHeroPlaneUnderPosition(enemy->getPosition());
	}
	*/
}

bool Hero::wait20Frame(){
    waitTime--;
    if (waitTime == 0)
    {
        waitTime = 20;
        return true;
    }
    return false;

}

void  Hero::setAI(bool value)
{
    //this->m_plane->clearScreenDebugInfo();
    m_isAI = value;
    this->SetActive(value);
    //return m_plane->setAI(value);
}

//AI action
void  Hero::AIAction(float level)
{
    return m_plane->AIAction(level);
}

//PlaneHeroPtr Hero::getPlane()
PlaneHeroPtr Hero::getPlane()
{
    //assert(this->m_plane->getTag() == GameScene::HERO_TAG);
    return m_plane;
}

void Hero::setPlane(PlaneHeroPtr heroPlane)
{
    //assert(heroPlane->getTag() == GameScene::HERO_TAG);
    this->m_plane = heroPlane;
}


/**
get first enemy in front of position
*/
cocos2d::Node* Hero::getEnemyInFrontOfPosition(Point position)
{
	/*
	////use Raycast to check if enemy in front of hero

	auto children = this->getParent()->getChildren();
	//创建一个屏幕高度，0.2宽的矩形，当做一条直线进行碰撞检测.
	//位置放在(position.x-0.1,0)处
	Point placePoint = Point(position.x - 0.001f, 0);
	Rect detectRect = Rect(placePoint.x, placePoint.y,
		0.002f, CCDirector::getInstance()->getOpenGLView()->getFrameSize().height);
	if (showDebugInfo)
	{
		draw->drawRect(placePoint, Size(0.002f, CCDirector::getInstance()->getOpenGLView()->getFrameSize().height), Color4F().GREEN);
	}
	for (auto it = children.begin(); it != children.end(); ++it)
	{
		if ((*it)->getTag() == GameScene::ENEMY_TAG)
		{
			//检测当前物体会否发生碰撞来检测前面是否有物体
			bool isInFront = (*it)->getBoundingBox().intersectsRect(detectRect);
			if (isInFront){
				//set enemy in front of heroPlane yellow color
				(*it)->setColor(Color3B(255, 255, 0));
				return (*it);
			}
		}
	}
	*/
	//if no enemy in front of position then return NULL 
	return NULL;
}

/*
seek for an enemy
*/
Node* Hero::findAnEnemy()
{
	/*
	auto children = this->getParent()->getChildren();
	for (auto it = children.begin(); it != children.end(); ++it)
	{
		if ((*it)->getTag() == GameScene::ENEMY_TAG)
		{
			return (*it);
		}
	}
	*/
	//if don't find an enemy, return null
	return NULL;
}

/*
*test whether hero will be crash enemy at position
*/
bool Hero::isWillBeCrashEnemy(Node* enemy, Point position)//whether will be crash enemy on position
{
	/*
	//Point::ZERO;
	assert(this->getTag() == GameScene::HERO_TAG);
	auto hero = this;
	//auto hero = this->getParent()->getChildByTag(GameScene::HERO_TAG);
	Size heroSize = hero->getBoundingBox().size;
	if (position == Vec2(-1, 0))
	{
		position = hero->getPosition();
	}
	float width = heroSize.width + 10;
	float heigth = heroSize.height + 60;
	//构建检测碰撞矩阵
	auto p = position - Vec2(width / 2, heroSize.height / 2);
	Rect detectRect = Rect(p.x, p.y, width, heigth);
	if (showDebugInfo)
	{
		//画出碰撞矩阵
		draw->drawRect(detectRect.origin, Vec2(detectRect.getMaxX(), detectRect.getMaxY()), Color4F().GREEN);
	}

	//获得最近的敌人
	auto nearestEnemy = getNearestEnemy(position);
	if (nearestEnemy != NULL)
	{
		return nearestEnemy->getBoundingBox().intersectsRect(detectRect);
	}
	*/
	return false;
}

/*
* get the nearest enemy
*/
Node* Hero::getNearestEnemy()
{
	/*
	auto children = this->getParent()->getChildren();
	auto hero = this->getParent()->getChildByTag(GameScene::HERO_TAG);
	Point heroPosition = hero->getPosition();
	
	return getNearestEnemy(heroPosition);
	*/
	return NULL;
}

Node* Hero::getNearestEnemy(Point position)//get the nearest enemy
{
	/*
	auto children = this->getParent()->getChildren();
	Node* nearestEnemy = NULL;
	float minDistance = 81000000;
	float distance = 0.0;

	for (auto it = children.begin(); it != children.end(); ++it)
	{
		if ((*it)->getTag() == GameScene::ENEMY_TAG)
		{
			distance = position.distanceSquared((*it)->getPosition());
			if (distance < minDistance)
			{
				minDistance = distance;
				nearestEnemy = (*it);
			}
		}

	}
	//set the nearest Enemy red color.
	if (nearestEnemy){
		nearestEnemy->setColor(Color3B(255, 0, 0));
	}
	return nearestEnemy;
	*/
	return NULL;
}

void Hero::AdjustHeroPosition(Node* hero )
{
	/*
	if (hero == NULL)
	{
		//hero = getChildByTag(GameScene::HERO_TAG);
		assert(this->getTag() == GameScene::HERO_TAG);
		hero = this;
	}
	auto enemy = getEnemyInFrontOfPosition(hero->getPosition());
	auto winHeight = CCDirector::getInstance()->getWinSize().height;
	if (enemy && enemy->getPosition().y > winHeight*0.4 && hero->getPosition().y < winHeight*0.1)
	{
		auto nearEnemy = getNearestEnemy(Vec2(hero->getPosition().x, winHeight*0.1));
		if (isWillBeCrashEnemy(nearEnemy))
		{
			return;
		}
		hero->setPosition(Vec2(hero->getPosition().x, winHeight*0.1));
	}
	*/
}