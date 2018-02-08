#include "PlaneEnemy.h" 
#include "SimpleAudioEngine.h"
#include "enemy.h"
using namespace CocosDenshion;



PlaneEnemy::PlaneEnemy(){
}

PlaneEnemy* PlaneEnemy::createWithEnemyType(int planetype)
{
	/*
	//�Զ���һ���������������ݴ����ս�����ͣ���ʼ���з�ս��
	PlaneEnemy *a = new PlaneEnemy();
	PlaneEnemyPtr plane(new PlaneEnemy());
	if (plane && plane->init(planetype))
	{
		//plane->autorelease();
		return plane;
	}
	return plane;
	*/
	//�Զ���һ���������������ݴ����ս�����ͣ���ʼ���з�ս��
	auto plane = new PlaneEnemy();
	if (plane && plane->init(planetype))
	{
		plane->autorelease();
		return plane;
	}
	else
	{
		CC_SAFE_DELETE(plane);
		return nullptr;
	}
}

/*
�л����ݳ�ʼ��
*/
bool PlaneEnemy::init(int planetype)
{
	Sprite::init();
	m_planeType = planetype;
	m_live = true;
	
	//��ʼ������ͼ��ս���ٶȣ���������ֵ
	String framename;
	switch (planetype)
	{
	case EnemyPlaneType::Enemy1:
		framename = "enemy1.png";
		m_velocity = Vec2(random(0.5, 1.5), random(0.5, 1.5)) * Enemy1_Vec; //����һ������ٶ�
		m_life = Enemy1_Life;
		m_points = Enemy1_Points;
		break;
	case EnemyPlaneType::Enemy2:
		framename = "enemy2.png";
		m_velocity = Vec2(random(0.5, 1.5), random(0.5, 1.5)) * Enemy2_Vec;
		m_life = Enemy2_Life;
		m_points = Enemy2_Points;
		break;
	case EnemyPlaneType::Enemy3:
		framename = "enemy3_n1.png";
		m_velocity = Vec2(random(0.5, 1.5), random(0.5, 1.5)) * Enemy3_Vec;
		m_life = Enemy3_Life;
		m_points = Enemy3_Points;
		break;
	case EnemyPlaneType::Enemy4:
		framename = "enemy3_n2.png";
		m_velocity = Vec2(random(0.5, 1.5), random(0.5, 1.5)) * Enemy4_Vec;
		m_life = Enemy4_Life;
		m_points = Enemy4_Points;
		break;
	}
	
	//this->root = setSprite(framename.getCString());
	this->root->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->root->retain();

	//���ص��˱�ը����֡����
	initEnemyBlowUpFrames(planetype);

	return true;
}


/*
��ӱ�ը���¼�
*/
void PlaneEnemy::blowUp()
{
	//����ս�����Ͳ�����Ч
	switch (m_planeType)
	{
	case Enemy1:
		SimpleAudioEngine::getInstance()->playEffect("sound/enemy1_down.wav");
		break;
	case Enemy2:
		SimpleAudioEngine::getInstance()->playEffect("sound/enemy2_down.wav");
		break;
	case Enemy3:
		SimpleAudioEngine::getInstance()->playEffect("sound/enemy3_down.wav");
		break;
	case Enemy4:
		SimpleAudioEngine::getInstance()->playEffect("sound/enemy3_down.wav");
		break;
	}

	//������������
	auto animation = Animation::createWithSpriteFrames(m_blowframes);
	animation->setDelayPerUnit(0.2f);
	animation->setRestoreOriginalFrame(true);
	auto blowUp = Animate::create(animation);

	//��ը������
	auto clear = CallFunc::create([this]() {
        //set the agent's m_plane is null
        
		this->root->removeFromParent();
		//log("enemy cleared!");
	});
    //���������ָ���Լ���ָ��ȥ��
    //this->myAgent->setPlane(nullptr);

	this->root->runAction(Sequence::create(blowUp, clear, nullptr));
}

void PlaneEnemy::getHurt()
{
	m_life--;
	if (m_life <= 0)
	{
		m_live = false;
		root->getPhysicsBody()->setContactTestBitmask(0x0); ////������ײ��־λ�����ٷ�����ײ�¼�
		blowUp(); //���ű�ը����
		return;
	}
	else if (m_planeType != Enemy1) //����ս��û�����˶���
	{
		//�������˶���
		SpriteFrame *hurt = nullptr;
		SpriteFrame *old = nullptr;
		switch (m_planeType)
		{
		case Enemy2:
			hurt = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_hit.png");
			old = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2.png");
			break;
		case Enemy3:
			hurt = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_hit.png");
			old = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png");
			break;
		case Enemy4:
			hurt = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_hit.png");
			old = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png");
			break;
		}

		auto setHurtImg = CallFunc::create([this, hurt](){
			this->root->setSpriteFrame(hurt);
		});

		auto setOldImg = CallFunc::create([this, old](){
			this->root->setSpriteFrame(old);
		});

		auto hurtAction = Sequence::create(setHurtImg, DelayTime::create(0.2f), setOldImg, nullptr);

		//this->stopAllActions();
		//this->runAction(hurtAction);
	}
}
/*
��ʼ��ÿһ��ս����ը��Ч��
*/
void PlaneEnemy::initEnemyBlowUpFrames(int planetype)
{
	if (planetype == EnemyPlaneType::Enemy1)
	{
		m_blowframes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down1.png"));
		m_blowframes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down2.png"));
		m_blowframes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down3.png"));
		m_blowframes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down4.png"));
	}
	
	else if (planetype == EnemyPlaneType::Enemy2)
	{
		m_blowframes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down1.png"));
		m_blowframes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down2.png"));
		m_blowframes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down3.png"));
		m_blowframes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down4.png"));
	}

	else
	{
		m_blowframes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down1.png"));
		m_blowframes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down2.png"));
		m_blowframes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down3.png"));
		m_blowframes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down4.png"));
		m_blowframes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down5.png"));
		m_blowframes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down6.png"));
	}
}

void PlaneEnemy::moveOn(float dt)
{
	/*
	//log("enemy moveon!");
	m_velocity = (int) this->myAgent->initSpeed;
	//�����н��ٶȣ������ƶ���һ�����磬�����ȥ
	this->root->setPositionY(getPositionY() - dt * m_velocity);
	if (getPositionY() < -this->getContentSize().height / 2)
	{
		removeFromParent();
		//log("enemy out!");
	}
	*/
}

int  PlaneEnemy::randomRotate(){
	return 1;
}

void PlaneEnemy::moveToDirection(Vec2 p){
	printf("moveToDirection position:[%f, %f]\n", p.x, p.y);
	//./ws->moveObject(this, p);
	root->setPosition(p);
}

// apply all the force vectors to the fish's acceleration
void PlaneEnemy::applyForce(Vec2 v)
{
	printf("applyforce acceleration:[%f,%f]\n", v.x, v.y);
	m_acceleration += v;
}
void PlaneEnemy::onEnter()
{
	Sprite::onEnter();

	schedule(schedule_selector(PlaneEnemy::moveOn)); //ս������󣬿�ʼ�ƶ�
}
void PlaneEnemy::updatePosition(){

	// move the fish
	m_velocity += (m_acceleration);
	
	if (m_velocity.getLength() > MAX_SPEED){
		m_velocity.normalize();
		m_velocity.scale(MAX_SPEED);
	}

	//if (m_velocity.mag() < 3)
	//	m_velocity.setMag(5);

	m_location += (m_velocity);
	if (m_acceleration.getLength() > MAX_FORCE){
		m_acceleration.normalize();
		m_acceleration.scale(MAX_FORCE);
	}

	printf("updatePosition--velocity[%f,%f]\n", m_velocity.x, m_velocity.y);

	moveToDirection(Vec2(m_location.x + m_velocity.x, m_location.y + m_velocity.y));
	// spend energy
	//this.energy -= ((this.acceleration.mag() * this.mass) * this.age * this.velocity.mag()) / 100;

	// die
	/*
	if (this.energy < 0)
	{
	this.dead = true;
	}

	// grow older
	this.age *= 1.00005;
	this.mature = this.age > this.fertility;
	*/
	// reset acceleration
	//m_acceleration.mult(0);
	m_acceleration = Vec2();
}
void PlaneEnemy::boundaries(){
	printf("boundaries location[%f, %f]\n", m_location.x, m_location.y);
	//printf("[%d, %d, %d, %d]\n", 50, kWIDTH - 50, 50, kHEIGHT - 50);
	if (m_location.x < 50){
		printf("<----\n");
		applyForce(Vec2((0.1 * 3), 0));
	}

	if (m_location.x > kCOL_WIDTH - 50){
		printf("---->\n");
		applyForce(Vec2(-0.1 * 3, 0));
	}

	if (m_location.y < 50){
		printf("--^--\n");
		applyForce(Vec2(0, 0.1 * 3));
	}

	if (m_location.y > kCOL_HEIGHT - 50){
		printf("--V--\n");
		applyForce(Vec2(0, -0.1 * 3));
	}
}
void PlaneEnemy::eat(){
	printf("eat \n");
}
void PlaneEnemy::shoal(){
	printf("shoal \n");
}

void PlaneEnemy::wander(){
	std::random_device rd;
	std::default_random_engine e(rd());
	std::uniform_real_distribution<double> u(0.0, 1.0); //������ֲ�����

	float suiji = u(e);
	if (suiji < .05) {
		//m_wandering.rotate()
		m_wandering.rotate(Vec2(0, 0), 3.1415926 * 2 * suiji);
	}
	m_velocity += m_wandering;
	printf("wander R[%f]-->vel=[%f, %f]:wander=[%f, %f]\n", suiji, m_velocity.x, m_velocity.y, m_wandering.x, m_wandering.y);
}

void PlaneEnemy::avoid(){
	printf("avoid \n");
}
void PlaneEnemy::mate(){
	printf("mate \n");
}
void PlaneEnemy::shoot(){
}