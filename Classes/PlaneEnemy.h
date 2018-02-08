#ifndef PLANEENEMY_H
#define PLANEENEMY_H

#include "cocos2d.h"
#include "behaviac/agent/agent.h"
#include "behaviac/agent/registermacros.h"

#include "GameObject.h"
#include "enemy.h"
USING_NS_CC;
class PlaneEnemy;
//�з��ɻ���
typedef std::shared_ptr<PlaneEnemy> PlaneEnemyPtr;

const double MAX_SPEED = 3;
const double MAX_FORCE = 3;
const double SEPARATION_RANGE = 30;
const double LOOK_RANGE = 100;
const double SMELL_RANGE = 300;
const double LENGTH = 20;
const double FERTILITY = .1;
const double BITE = .1;

//const static int kCOL_WIDTH = 540;
//const static int kCOL_HEIGHT = 960;

class PlaneEnemy : public Sprite
{
public:
	//DECLARE_BEHAVIAC_OBJECT(PlaneEnemy, GameObject);

	enum EnemyPlaneType
	{
		Enemy1,
		Enemy2,
		Enemy3,
		Enemy4
	}; //ս������

	enum EnemyPlaneVec
	{
		Enemy1_Vec = 150,
		Enemy2_Vec = 100,
		Enemy3_Vec = 50,
		Enemy4_Vec = 50
	}; //ս���ٶ�

	enum EnemyLife
	{
		Enemy1_Life = 1,
		Enemy2_Life = 2,
		Enemy3_Life = 5,
		Enemy4_Life = 8
	}; //ս������

	enum Enemy_Points
	{
		Enemy1_Points = 10,
		Enemy2_Points = 20,
		Enemy3_Points = 50,
		Enemy4_Points = 80
	}; //ս������

    Enemy* myAgent;
	Sprite* root;
public:
	//�Զ��幤������������enemy�кܶ��֣�����enemy�����ͳ�ʼ������init������г�ʼ��
	PlaneEnemy();
	static PlaneEnemy* createWithEnemyType(int planetype);
	
	bool init(int planetype);

	void moveToDirection(Point p);
	void applyForce(Vec2 v);
	void updatePosition();

	void eat();
	void shoal();
	void wander();
	void avoid();
	void mate();
	void boundaries();
	int randomRotate();

	void onEnter();

	void getHurt(); //�ɻ�������һ��
	bool isLive() { return m_live; }; 
	int getPoints() { return m_points; }
	int getType() { return m_planeType; }
    //void setSpeed(float speed);
    //float getSpeed();

	double m_lookRange = 20;
	double m_smellRange = 40;
	double m_length = 20;
	double m_rotate = .1;
	Vec2 m_velocity;
	Vec2 m_location;
	Vec2 m_acceleration;
	Vec2 m_wandering;

private:
	void initEnemyBlowUpFrames(int planetype); //���ر�ը����ͼ��
	void moveOn(float dt); //schedule�ص���ÿdt���ƶ�һ�ξ���
	void blowUp(); //�ɻ���ը
	void shoot();
private:
	//int m_velocity; //ս���ٶ�
	int m_life; //ս����ǰ����
	int m_points; //ս����ֵ
	int m_planeType; //�л�����
	bool m_live; //�ɻ��Ƿ���ŵı�־

	Vector<SpriteFrame*> m_blowframes; //��ű�ը������֡
};

#endif

