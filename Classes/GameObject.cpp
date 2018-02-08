#include "GameObject.h"
#include "WorldState.h"
//#include "globals.h"
//#include "util.h"
//#include "Projectile.h"

Sprite * GameObject::setSprite(const std::string& filename)
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


GameObject::GameObject()
{
	HP = 100;
	displayName = "default";
	displayHeading = 0;
	faction = 0;
	//ID = getID();
	movementHeading = 0;
	accelMagnitude = 0;
	accelHeading = 0;
	isPlayer = false;
	usesPhysics = true;
	age = 0;
	owner = NULL;
	//textureResource = NULL;
};

GameObject::~GameObject()
{
	printf("%s destructor\n", displayName.c_str());
}

bool GameObject::doActions(float dt)
{
	this->btexec();
	return true;
}

bool GameObject::registerCollision(GameObject* collidedObject)
{
	printf("%s Collided with %s", displayName, collidedObject->displayName);

	return true;
}

bool GameObject::registerWallCollision()
{
	//move a little away from the wall if too close
	accelMagnitude = 0;

	if (GameObject::location.x < 0)
	{
		GameObject::location.x = 0;
	}

	if (GameObject::location.y < 0)
	{
		GameObject::location.y = 0;
	}

	//for some reason it works fine without this code
	//if (GameObject::location.x > (WorldState.CoordinateSizeX - 1))
	//	GameObject::location.x = WorldState.CoordinateSizeX - 1;
	//if (GameObject::location.y > (WorldState.CoordinateSizeY - 1))
	//	GameObject::location.y = WorldState.CoordinateSizeY - 1;
	return true;
}

bool GameObject::collideWith(GameObject* other) const
{
	return false;
}

void GameObject::applyForceRect(float x, float y)
{
	float oldX = accelMagnitude * cos(accelHeading * 3.1415 / 180);
	float oldY = accelMagnitude * sin(accelHeading * 3.1415 / 180);
	//should probably be using vectors everywhere
	float newX = oldX + x;
	float newY = oldY + y;
	accelMagnitude = sqrt(newX * newX + newY * newY);
	accelHeading = (180.0f * atan2(newY, newX)) / 3.1415;
}

void GameObject::applyForcePolar(float heading, float magnitude)
{	}

bool GameObject::alignedWithPlayer() const
{
	return true;
}

int GameObject::getHealth() const
{
	return HP;
}

void GameObject::setHealth(unsigned int hp)
{
	HP = hp;
}

bool GameObject::projectileNearby(float radius) const
{

	/*
	const GameObjectList* objects = ws->getAllGameObjects();
	ConstGameObjectIter iter;

	for (iter = objects->begin(); iter != objects->end(); iter++)
	{
	if ((*iter)->faction != PROJECTILE_FACTION)
	{
	continue;
	}

	float distance = ws->distanceBetween(this, *iter);

	if (distance < radius)
	{
	return true;
	}
	}
	*/
	return false;
}

void GameObject::GoStraight(int speed)
{
	printf("go straight\n");
	//ws->moveObject(this, this->location.offsetPolar(this->displayHeading, (float)speed));
}

int GameObject::TurnTowardsTarget(float turnSpeed)
{
	/*
	GameObject* target = ws->getPlayer();
	float angleBetween = ws->angleBetween(this, target);

	turnSpeed /= 20.0f;

	if (angleBetween < -(turnSpeed + 1))
	{
	ws->rotateObject(this, -turnSpeed); //clockwise
	return behaviac::BT_RUNNING;
	}
	else if (angleBetween > turnSpeed + 1)
	{
	ws->rotateObject(this, turnSpeed);
	return behaviac::BT_RUNNING;
	}
	*/
	return behaviac::BT_RUNNING;
}

