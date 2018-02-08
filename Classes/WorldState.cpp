#include "WorldState.h"
#include "GameObject.h"
#include "PlaneEnemy.h"
#include "GameScene.h"
#include "enemy.h"
//#include "behaviac.h"
//#include "Projectile.h"
//#include "util.h"
//#include "Ship.h"

WorldState::WorldState() : m_player(NULL), m_ai(NULL), SyncSignal(false)
{
	description = "";
	CoordinateSizeX = kCOL_WIDTH;
	CoordinateSizeY = kCOL_HEIGHT;

	CellSizeX = (int)CoordinateSizeX / coarseGraining;
	CellSizeY = (int)CoordinateSizeY / coarseGraining;

	//textureResources = BEHAVIAC_NEW TextureResourceMap();
	activeObjectList = BEHAVIAC_NEW GameObjectList();
	deleteList = BEHAVIAC_NEW GameObjectList();
	backgroundObjectList = BEHAVIAC_NEW GameObjectList();
	worldMatrix = (GameObjectList***)BEHAVIAC_MALLOC(sizeof(GameObjectList**) * CellSizeX);

	for (int i = 0; i < CellSizeX; ++i)
	{
		worldMatrix[i] = (GameObjectList**)BEHAVIAC_MALLOC(sizeof(GameObjectList*) * CellSizeY);
	}

	for (int i = 0; i < CellSizeX; i++)
	{
		for (int j = 0; j < CellSizeY; j++)
		{
			worldMatrix[i][j] = BEHAVIAC_NEW GameObjectList();
		}
	}

	HealthHP = 50;
	//time = SDL_GetTicks();
	//time = 0;
}

WorldState::~WorldState()
{
	/*
	if (textureResources)
	{
		for (TextureResourceMap::iterator it = textureResources->begin(); it != textureResources->end(); ++it)
		{
			if (it->second && it->second->texture)
				SDL_DestroyTexture(it->second->texture);
		}
		textureResources->clear();

		BEHAVIAC_DELETE textureResources;
	}
	*/
}

/*
TextureResource* WorldState::GetTextureResource(const char* filename)
{
	TextureResource* textureRes = NULL;
	TextureResourceMap::iterator it = textureResources->find(filename);
	if (it != textureResources->end())
	{
		textureRes = it->second;
	}
	else
	{
		SDL_Texture* texture = IMG_LoadTexture(framework::renderer->sdlrenderer, filename);
		if (texture)
		{
			textureRes = BEHAVIAC_NEW TextureResource;
			textureRes->texture = texture;
			SDL_QueryTexture(texture, NULL, NULL, &textureRes->width, &textureRes->height);
			(*textureResources)[filename] = textureRes;
		}
	}

	return textureRes;
}
*/

GameObject* WorldState::getPlayer() const
{
	GameObjectIter itr;

	for (itr = activeObjectList->begin(); itr != activeObjectList->end(); itr++)
	{
		if ((*itr)->isPlayer)
		{
			return *itr;
		}
	}

	return NULL;
}

bool WorldState::insertObject(GameObject* gameObject, Vec2 p)
{
	if (pointOutofBounds(p))
	{
		return false;
	}

	GameObjectList* currentList = getListFromPoint(p);
	currentList->push_front(gameObject);
	gameObject->location = p;
	activeObjectList->push_front(gameObject);

	return true;
}

bool WorldState::deleteObject(GameObject* gameObject)
{
	registerForDeletion(gameObject);
	return true;
}

void WorldState::clearAIs()
{
	this->deleteQueued();

	for (GameObjectIter itr = activeObjectList->begin(); itr != activeObjectList->end();)
	{
		GameObjectIter t = itr++;
		GameObject* p = *t;

		if (!p->isPlayer)
		{
			GameObjectList* currentList = getListFromPoint(p->location);
			currentList->remove(p);

			BEHAVIAC_DELETE(p);

			activeObjectList->erase(t);
		}
	}
}

bool WorldState::moveObject(GameObject* gameObject, Vec2 p)
{
	if (pointOutofBounds(p))
	{
		gameObject->registerWallCollision();
		return false;
	}

	//test for and report potential collisions
	//currently tests against all objects (does not scale well)
	//update with more sophisticated filtering in the future

	GameObjectIter itr;

	if (gameObject->usesPhysics)
	{
		for (itr = activeObjectList->begin(); itr != activeObjectList->end(); itr++)
		{
			if ((*itr) == gameObject)
				continue;

			if ((*itr)->faction == PROJECTILE_FACTION /*&& (*itr)->owner != ws->getPlayer()*/ && (gameObject->isPlayer == false))
				continue;

			if (gameObject->faction == PROJECTILE_FACTION /*&& gameObject->owner != ws->getPlayer()*/ && ((*itr)->isPlayer == false))
				continue;

			if (((*itr)->owner == gameObject) || (gameObject->owner == *itr))
				continue;

			if ((*itr)->usesPhysics && (*itr)->collideWith(gameObject))
			{
				(*itr)->registerCollision(gameObject);
				gameObject->registerCollision(*itr);

				return false; //TODO support colliding with multiple entities
			}
		}
	}

	GameObjectList* currentList = getListFromPoint(gameObject->location);
	GameObjectList* newList = getListFromPoint(p);
	gameObject->location = p;

	if (currentList != newList)
	{
		newList->push_front(gameObject);
		currentList->remove(gameObject);
	}

	return true;
}

bool WorldState::rotateObject(GameObject* gameObject, float angle)
{
	if (gameObject->usesPhysics)
	{
		GameObjectIter itr;

		for (itr = activeObjectList->begin(); itr != activeObjectList->end(); itr++)
		{
			if ((*itr) == gameObject)
				continue;

			if ((*itr)->faction == PROJECTILE_FACTION && (gameObject->faction == PROJECTILE_FACTION))
				continue;

			if (((*itr)->owner == gameObject) || (gameObject->owner == *itr))
				continue;

			if ((*itr)->usesPhysics && (*itr)->collideWith(gameObject))
			{
				//(*itr)->registerCollision(gameObject);
				//gameObject->registerCollision(*itr);

				return false; //TODO support colliding with multiple entities
			}
		}
	}

	gameObject->displayHeading += angle;
	gameObject->displayHeading = mod(gameObject->displayHeading, 360.0f);
	return true;
}

void WorldState::registerForDeletion(GameObject* obj)
{
	deleteList->push_front(obj);
}

void WorldState::deleteQueued()
{
	ConstGameObjectIter itr;
	deleteList->sort();
	deleteList->unique();

	for (itr = deleteList->begin(); itr != deleteList->end(); ++itr)
	{
		GameObject* p = *itr;
		GameObjectList* currentList = getListFromPoint(p->location);
		activeObjectList->remove(p);
		currentList->remove(p);
		BEHAVIAC_DELETE(p);
	}

	deleteList->clear();
}

void WorldState::addBackgroundObject(GameObject* background)
{
	backgroundObjectList->push_back(background);
}

const GameObjectList* WorldState::getBackgroundObjects()
{
	return backgroundObjectList;
}

GameObjectList* WorldState::getAtCell(Vec2 p)
{
	if (pointOutofBounds(p))
	{
		return NULL;
	}

	return getListFromPoint(p);
}

const GameObjectList* WorldState::getAllGameObjects() const
{
	return  activeObjectList;
}

bool WorldState::pointOutofBounds(Vec2 p)
{
	if (p.x >= CoordinateSizeX || p.y >= CoordinateSizeY || p.x < 0 || p.y < 0)
	{
		return true;
	}

	return false;
}

GameObjectList* WorldState::getListFromPoint(Vec2 p)
{
	return worldMatrix[(int)p.x / coarseGraining][(int)p.y / coarseGraining];
}

float WorldState::distanceBetween(const GameObject* obj1, const GameObject* obj2) const
{
	Vec2 resultantVector(obj1->location.x - obj2->location.x, obj1->location.y - obj2->location.y);
	return resultantVector.length();
}

float WorldState::angleBetween(const GameObject* obj1, const GameObject* obj2) const
{
	Vec2 resultantVector(obj1->location.x - obj2->location.x, obj1->location.y - obj2->location.y);
	resultantVector.normalize();

	float angleBetween = getAngle(atan2(resultantVector.y, resultantVector.x));
	angleBetween -= obj1->displayHeading + 90.f;
	angleBetween = mod(angleBetween, 360.0f);
	if (angleBetween > 180.0f)
	{
		angleBetween = 180.0f - angleBetween;
	}

	return angleBetween;
}
void WorldState::spawnEnemy(int level)
{
	printf("----------0000000000011");
	loadlevel(level);
}


void WorldState::spawnEnemy()
{
#if 0
	log("==============refresh an enemy");

	auto winSize = Director::getInstance()->getWinSize();

	int enemy_type = PlaneEnemy::Enemy1;

	//根据游戏Level选择性随机刷新不同种类的战机
	switch (m_level)
	{
	case GameScene::LEVEL1:
		break;
	case GameScene::LEVEL2:
		enemy_type = random(0, 1);
		break;
	case GameScene::LEVEL3:
		enemy_type = random(0, 2);
		if (m_canBossRefresh && enemy_type == 2) //如果刷新出boss战机，那么禁止其继续刷新，直到该禁止标志被重置
			m_canBossRefresh = false;
		else enemy_type = random(0, 1);
		break;
	case GameScene::LEVEL4:
		enemy_type = random(0, 3);
		if (m_canBossRefresh && enemy_type >= 2)
			m_canBossRefresh = false;
		else enemy_type = random(0, 1);
		break;
	case GameScene::LEVEL5:
		enemy_type = random(0, 3);
		if (m_canBossRefresh && enemy_type >= 2)
			m_canBossRefresh = false;
		else enemy_type = random(0, 1);
		break;
	}

	//    auto enemy = behaviac::Agent::Create<Enemy>();
	//    enemy->createAnEnemyWithType(enemy_type);
	////根据战机类型加入战机
	//PlaneEnemy* enemy_plane = enemy->getPlane();
	//PlaneEnemyPtr enemy_plane = PlaneEnemy::createWithEnemyType(enemy_type);

	PlaneEnemy* p = behaviac::Agent::Create<PlaneEnemy>();
	p->init(enemy_type);
	p->SetIdFlag(kIdMask_Projectile);

	p->setBrain("fish");

	((Node*)this->getParent())->addChild(p->root, 0, GameScene::ENEMY_TAG);

	//behaviac::Agent::Destroy(enemy);

	//enemy->SetActive(false);
	//enemy_plane1->setColor(Color3B(255, 0, 255));

	//auto enemy_plane = PlaneEnemy::createWithEnemyType(enemy_type);
	//((Node*)this->getParent())->addChild(enemy_plane, 0, GameScene::ENEMY_TAG);

	//设定战机初始位置的X轴的取值范围，根据这个范围随机设置战机初始X轴位置
	int min = p->root->getContentSize().width / 2;
	int max = winSize.width - p->root->getContentSize().width / 2;
	log("[%d, %d] x=%d y=%d", min, max, random(min, max), winSize.height + p->root->getContentSize().height / 2);
	log("winsize [%d, %d]  content size [%d, %d]", winSize.width, winSize.height, p->root->getContentSize().width, p->root->getContentSize().height);
	p->root->setPosition(Vec2(random(min, max), winSize.height + p->root->getContentSize().height / 2));
	//enemy_plane->root->setPosition(Vec2(300, 400));

	//给敌机一个body
	Vec2 vec[10]; //存放敌方战机的多边形点
	memset(vec, 0, sizeof(vec));
	int vec_count = 0;
	switch (enemy_type)
	{
	case PlaneEnemy::Enemy1:
		vec[0] = Vec2(0, -18);
		vec[1] = Vec2(-24, 6);
		vec[2] = Vec2(24, 6);
		vec_count = 3;
		break;
	case PlaneEnemy::Enemy2:
		vec[0] = Vec2(0, -40);
		vec[1] = Vec2(-40, 0);
		vec[2] = Vec2(0, 45);
		vec[3] = Vec2(40, 0);
		vec_count = 4;
		break;
	default:
		vec[0] = Vec2(35, -120);
		vec[1] = Vec2(-35, -120);
		vec[2] = Vec2(-80, -88);
		vec[3] = Vec2(-80, 130);
		vec[4] = Vec2(80, 130);
		vec[5] = Vec2(80, -88);
		vec_count = 6;
		break;
	}
	//auto enemybody = PhysicsBody::createBox(enemy_plane->getContentSize());
	auto enemybody = PhysicsBody::create();
	enemybody->addShape(PhysicsShapePolygon::create(vec, vec_count));
	enemybody->setCollisionBitmask(0x0); //不进行碰撞模拟，因为不需要
	enemybody->setContactTestBitmask(GameScene::ENEMY_CONTACTMASKBIT);
	p->root->setPhysicsBody(enemybody);
#endif
}

void* WorldState::getParent()
{
	return dq_parent;
}

// set NPC parent
void WorldState::setParent(void* parent)
{
	//this->m_parent = const_cast<void *>(parent);
	this->dq_parent = (void *)parent;
}


void WorldState::loadlevel(int level)
{
	printf("==============loadlevel");

	auto winSize = Director::getInstance()->getWinSize();
	int m_canBossRefresh = 0;
	int enemy_type = PlaneEnemy::Enemy1;

	//根据游戏Level选择性随机刷新不同种类的战机
	switch (m_level)
	{
	case GameScene::LEVEL1:
		break;
	case GameScene::LEVEL2:
		enemy_type = random(0, 1);
		break;
	case GameScene::LEVEL3:
		enemy_type = random(0, 2);
		if (m_canBossRefresh && enemy_type == 2) //如果刷新出boss战机，那么禁止其继续刷新，直到该禁止标志被重置
			m_canBossRefresh = false;
		else enemy_type = random(0, 1);
		break;
	case GameScene::LEVEL4:
		enemy_type = random(0, 3);
		if (m_canBossRefresh && enemy_type >= 2)
			m_canBossRefresh = false;
		else enemy_type = random(0, 1);
		break;
	case GameScene::LEVEL5:
		enemy_type = random(0, 3);
		if (m_canBossRefresh && enemy_type >= 2)
			m_canBossRefresh = false;
		else enemy_type = random(0, 1);
		break;
	}

	//    auto enemy = behaviac::Agent::Create<Enemy>();
	//    enemy->createAnEnemyWithType(enemy_type);
	////根据战机类型加入战机
	//PlaneEnemy* enemy_plane = enemy->getPlane();
	//PlaneEnemyPtr enemy_plane = PlaneEnemy::createWithEnemyType(enemy_type);
	auto enemy = behaviac::Agent::Create<Enemy>();
	enemy->createAnEnemyWithType(enemy_type);
	////根据战机类型加入战机
	PlaneEnemy* enemy_plane = enemy->getPlane();
	((Node*)this->getParent())->addChild(enemy_plane, 0, GameScene::ENEMY_TAG);

	//设定战机初始位置的X轴的取值范围，根据这个范围随机设置战机初始X轴位置
	enemy_plane->setPosition(300, 400);

	/* 0129 ok
	PlaneEnemy* p = behaviac::Agent::Create<PlaneEnemy>();
	p->init(enemy_type);
	p->SetIdFlag(kIdMask_Projectile);
	p->setBrain("fish");
	((Node*)this->getParent())->addChild(p->root, 0, GameScene::ENEMY_TAG);
	*/
	//behaviac::Agent::Destroy(enemy);

	//enemy->SetActive(false);
	//enemy_plane1->setColor(Color3B(255, 0, 255));

	//auto enemy_plane = PlaneEnemy::createWithEnemyType(enemy_type);
	//((Node*)this->getParent())->addChild(enemy_plane, 0, GameScene::ENEMY_TAG);

	//设定战机初始位置的X轴的取值范围，根据这个范围随机设置战机初始X轴位置
	//int min = p->root->getContentSize().width / 2;
	//int max = winSize.width - p->root->getContentSize().width / 2;
	//log("[%d, %d] x=%d y=%d", min, max, random(min, max), winSize.height + p->root->getContentSize().height / 2);
	//log("winsize [%d, %d]  content size [%d, %d]", winSize.width, winSize.height, p->root->getContentSize().width, p->root->getContentSize().height);
	//p->root->setPosition(Vec2(random(min, max), winSize.height + p->root->getContentSize().height / 2));
	enemy_plane->setPosition(Vec2(300, 400));

	//insertObject(p, Vec2(0, 0));

	//给敌机一个body
	Vec2 vec[10]; //存放敌方战机的多边形点
	memset(vec, 0, sizeof(vec));
	int vec_count = 0;
	switch (enemy_type)
	{
	case PlaneEnemy::Enemy1:
		vec[0] = Vec2(0, -18);
		vec[1] = Vec2(-24, 6);
		vec[2] = Vec2(24, 6);
		vec_count = 3;
		break;
	case PlaneEnemy::Enemy2:
		vec[0] = Vec2(0, -40);
		vec[1] = Vec2(-40, 0);
		vec[2] = Vec2(0, 45);
		vec[3] = Vec2(40, 0);
		vec_count = 4;
		break;
	default:
		vec[0] = Vec2(35, -120);
		vec[1] = Vec2(-35, -120);
		vec[2] = Vec2(-80, -88);
		vec[3] = Vec2(-80, 130);
		vec[4] = Vec2(80, 130);
		vec[5] = Vec2(80, -88);
		vec_count = 6;
		break;
	}
	//auto enemybody = PhysicsBody::createBox(enemy_plane->getContentSize());
	auto enemybody = PhysicsBody::create();
	enemybody->addShape(PhysicsShapePolygon::create(vec, vec_count));
	enemybody->setCollisionBitmask(0x0); //不进行碰撞模拟，因为不需要
	enemybody->setContactTestBitmask(GameScene::ENEMY_CONTACTMASKBIT);
	//p->root->setPhysicsBody(enemybody);
	enemy_plane->setPhysicsBody(enemybody);
#if 0
	WorldState* state = (WorldState*)behaviac::Agent::GetInstance<WorldState>();

	state->clearAIs();

	int levels = BEHAVIAC_ARRAY_NELEMENT(gs_levels);

	if (level >= 0 && level < levels)
	{
		ws->GetPlayer()->setHealth(100);

		level_t& levelSt = gs_levels[level];

		char levelPath[_MAX_PATH];
		string_sprintf(levelPath, "ships/%s", levelSt.name);

		char levelModule[_MAX_PATH];
		string_sprintf(levelModule, "Hulls/%s", levelSt.module);

		if (levelSt.mode == 0)
		{
			Ship* opponent = behaviac::Agent::Create<framework::Ship>();
			opponent->SetIdFlag(kIdMask_Opponent);
			opponent->displayHeading = 180;
			opponent->setSprite(levelModule);

			if (levelSt.projectile == 0)
			{
				opponent->projectileBrain = &makeBoringBrain;
			}
			else if (levelSt.projectile == 1)
			{
				opponent->projectileBrain = &makeHomingBrain;
			}
			else if (levelSt.projectile == 2)
			{
				opponent->projectileBrain = &makeSlowBoringBrain;
			}
			else if (levelSt.projectile == 3)
			{
				opponent->projectileBrain = &makeSyncBrain;
			}
			else if (levelSt.projectile == -1)
			{
				opponent->projectileBrain = 0;
			}
			else
			{
				BEHAVIAC_ASSERT(0);
			}

			opponent->btload(levelPath);
			opponent->btsetcurrent(levelPath);

			state->insertObject(opponent, levelSt.start);
			state->rotateObject(opponent, levelSt.startRot);

			ws->SetAI(opponent);
		}
		else if (levelSt.mode > 0)
		{
			for (int i = 0; i < levelSt.mode; i++)
			{
				for (int j = 0; j < levelSt.mode; j++)
				{
					Ship* opponent = behaviac::Agent::Create<Ship>();
					opponent->SetIdFlag(kIdMask_Opponent);

					opponent->displayHeading = 180;
					opponent->setSprite(levelModule);

					if (levelSt.projectile == 0)
					{
						opponent->projectileBrain = &makeBoringBrain;
					}
					else if (levelSt.projectile == 1)
					{
						opponent->projectileBrain = &makeHomingBrain;
					}
					else if (levelSt.projectile == 2)
					{
						opponent->projectileBrain = &makeSlowBoringBrain;
					}
					else
					{
						BEHAVIAC_ASSERT(0);
					}

					opponent->btload(levelPath);
					opponent->btsetcurrent(levelPath);

					state->insertObject(opponent, Vec2(levelSt.start.x + 50 * i, levelSt.start.y + 50 * j));
				}
			}

			ws->SetAI(NULL);
		}
		else
		{
			state->btload(levelPath);
			state->btsetcurrent(levelPath);
			ws->SetAI(NULL);
		}

		ws->ResetSyncSignal();
	}
#endif
}


bool WorldState::NextWave() const
{
	if (this->getAllGameObjects()->size() == 1) //the player and the spawner
	{
		/////BEHAVIAC_APPLOG("", "NextWave", 0);
		/////BEHAVIAC_APPLOG("RED", "NextWave", 0);
		/////BEHAVIAC_APPLOG("GREEN", "NextWave", 0);

		return true;
	}

	return false;
}

int WorldState::PlayerHP() const
{
	assert(m_player);
	return m_player->getHealth();
}


