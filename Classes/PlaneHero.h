#ifndef PLANEHERO_H
#define PLANEHERO_H

#include "cocos2d.h"
#include "NPC.h"

USING_NS_CC;

class PlaneHero;
//我方飞机类
typedef std::shared_ptr<PlaneHero> PlaneHeroPtr;
class PlaneHero : public std::enable_shared_from_this<PlaneHero>
{
public:
	//工厂方法，在init里面进行初始化
	//CREATE_FUNC(PlaneHero);
	Sprite* root;
	Vec2	position;
	virtual bool init();
	static PlaneHeroPtr make()
	{
		PlaneHeroPtr ret(new PlaneHero);
		//if (ret && !ret->init(col, turn))
		if (!ret->init())
			ret.reset();
		return ret;
	}

	//virtual void onEnter();
public:
	PlaneHero() : root(NULL){}
	Sprite* GetSprite(const std::string& filename);
	void dead(); //飞机挂掉

	/*
    Node* findAnEnemy();//find an enemy plane
    bool isWillBeCrashEnemy(Node* enemy, Point position);//test whether hero will be crash enemy at position
    Node* getEnemyInFrontOfPosition(Point position);// get Enemy in front of position
    Node* getNearestEnemy();//get the nearest enemy
    Node* getNearestEnemy(Point position);//get the nearest enemy 
	*/
    void AdjustHeroPosition(Node* hero);
    void setHeroPlaneUnderPosition(Point _targetPosition);
    //m_isAI表示是否使用AI
    bool m_isAI;
    void setAI(bool value);
    //ai动作
    void AIAction(float level);
    //the below method will be exoport for behaviac
    void findAnNearestEnemy();
    bool isWillBeCrashOnNearestEnemy();
    void EscapeEnemyCrash();
    bool hasEnemyInFrontCanAttack();
    void findAnEnemyAndAttack();
    //void clearScreenDebugInfo();
    void enableShowScreenDebugInfo(bool value);
public:
	void beginShooting(float dt); //开始发射子弹，间隔dt秒发射一发
	void removeBullet(float dt); //移除射到屏幕外面的子弹
	void stopShooting(); //停止发射子弹

	void blowUp(); //飞机爆炸
    
private:
    DrawNode*   draw;
    Node*       nearestEnemy;//store the nearest enemy
    //Node        frontEnemy;//enemy in front of hero plane
    bool        showDebugInfo;//show debug info on screen
	Sprite *spritepig;
};

#endif

