
#include "enemy.h"
#include "PlaneEnemy.h"
#include "GameScene.h"
USING_NS_CC;

Enemy::Enemy()
{
    //this->btload("enemy_fsm");
    //this->btsetcurrent("enemy_fsm");
    this->btload("enemy");
    this->btsetcurrent("enemy");
	speed = 20.0f;
	m_init_speed[0] = 50;
	m_init_speed[1] = 50;
	m_init_speed[2] = 100;
	m_init_speed[3] = 150;
}

Enemy::~Enemy()
{
}

//create an enemy with type
void Enemy::createAnEnemyWithType(int type)
{
    m_plane = PlaneEnemy::createWithEnemyType(type);
    m_plane->myAgent = this;
}

PlaneEnemy* Enemy::getPlane()
{
    return m_plane;
}

void Enemy::setPlane(Node* plane)
{
    this->m_plane = (PlaneEnemy*)plane;
}

void Enemy::setSpeed(float speed)
{
	this->speed = speed;//fix crash bug
    
    //if (this->m_plane)
    //{
    //    this->m_plane->setSpeed(speed);//this code will cause crash. but if use the code before this line will  be not
    //}
    //this->m_plane->setSpeed(speed);
}

float Enemy::getSpeed()
{
    if (this->m_plane){
        //return this->m_plane->getSpeed();
		return 0.0f;
    }
    else{
        return 0.0f;
    }
   
}

int Enemy::getEnemyType()
{
    return this->m_plane->getType();
}


float Enemy::getRandomSpeedByInitSpeed(float initSpeed)
{
    return  random(0.5, 1.3)*initSpeed;
}

void Enemy::init()
{

}

bool Enemy::isAlive()
{
    if (this->m_plane){
        return true;
    }else{
        //if the enemy is dead, then add this agent's behaviac to GanmeScene's agent delete queue.
        GameScene::addBehaviacAgentDeleteQueue((behaviac::Agent*)this);
        return false;
    }
}
