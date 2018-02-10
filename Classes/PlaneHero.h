#ifndef PLANEHERO_H
#define PLANEHERO_H

#include "cocos2d.h"

USING_NS_CC;

//�ҷ��ɻ���
class PlaneHero : public Sprite
{
public:
	//������������init������г�ʼ��
	CREATE_FUNC(PlaneHero);
	bool init();

	void onEnter();

public:
	void dead(); //�ɻ��ҵ�
    Node* findAnEnemy();//find an enemy plane
    bool isWillBeCrashEnemy(Node* enemy, Point position);//test whether hero will be crash enemy at position
    Node* getEnemyInFrontOfPosition(Point position);// get Enemy in front of position
    Node* getNearestEnemy();//get the nearest enemy
    Node* getNearestEnemy(Point position);//get the nearest enemy 

    void AdjustHeroPosition(Node* hero);
    void setHeroPlaneUnderPosition(Point _targetPosition);
    //m_isAI��ʾ�Ƿ�ʹ��AI
    bool m_isAI;
    void setAI(bool value);
    //ai����
    void AIAction(float level);
private:
	void beginShooting(float dt); //��ʼ�����ӵ������dt�뷢��һ��
	void removeBullet(float dt); //�Ƴ��䵽��Ļ������ӵ�
	void stopShooting(); //ֹͣ�����ӵ�

	void blowUp(); //�ɻ���ը
    
    DrawNode * draw;
};

#endif

