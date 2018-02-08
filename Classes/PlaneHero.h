#ifndef PLANEHERO_H
#define PLANEHERO_H

#include "cocos2d.h"
#include "NPC.h"

USING_NS_CC;

class PlaneHero;
//�ҷ��ɻ���
typedef std::shared_ptr<PlaneHero> PlaneHeroPtr;
class PlaneHero : public std::enable_shared_from_this<PlaneHero>
{
public:
	//������������init������г�ʼ��
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
	void dead(); //�ɻ��ҵ�

	/*
    Node* findAnEnemy();//find an enemy plane
    bool isWillBeCrashEnemy(Node* enemy, Point position);//test whether hero will be crash enemy at position
    Node* getEnemyInFrontOfPosition(Point position);// get Enemy in front of position
    Node* getNearestEnemy();//get the nearest enemy
    Node* getNearestEnemy(Point position);//get the nearest enemy 
	*/
    void AdjustHeroPosition(Node* hero);
    void setHeroPlaneUnderPosition(Point _targetPosition);
    //m_isAI��ʾ�Ƿ�ʹ��AI
    bool m_isAI;
    void setAI(bool value);
    //ai����
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
	void beginShooting(float dt); //��ʼ�����ӵ������dt�뷢��һ��
	void removeBullet(float dt); //�Ƴ��䵽��Ļ������ӵ�
	void stopShooting(); //ֹͣ�����ӵ�

	void blowUp(); //�ɻ���ը
    
private:
    DrawNode*   draw;
    Node*       nearestEnemy;//store the nearest enemy
    //Node        frontEnemy;//enemy in front of hero plane
    bool        showDebugInfo;//show debug info on screen
	Sprite *spritepig;
};

#endif

