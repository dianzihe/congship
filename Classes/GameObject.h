#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "cocos2d.h"

#include <list>
#include <string>
#include <set>

#include "WorldState.h"
#include "behaviac/agent/agent.h"
#include "behaviac/agent/registermacros.h"

using namespace cocos2d;

const unsigned int kIdMask_Wolrd = 0x0001;
const unsigned int kIdMask_Player = 0x0002;
const unsigned int kIdMask_Opponent = 0x0004;
const unsigned int kIdMask_Projectile = 0x0008;
const unsigned int kIdMask_Fish = 0x000F;

//    class WorldState;

//class GameObject;
//int GameObject::IDCount = 0;
/// Base class for any item in the game
class GameObject : public behaviac::Agent
{
public:
	//static int IDCount ;
public:
	/// Default constructor
	GameObject();
	/// Cleans up resources in use by the object when it is deleted
	~GameObject();

	//DECLARE_BEHAVIAC_OBJECT(framework::GameObject, behaviac::Agent);
	BEHAVIAC_DECLARE_AGENTTYPE(GameObject, behaviac::Agent)

	/// Called every frame to update the object
	virtual bool doActions(float dt);
	/// Notify the object of a collision with another object. Only called if usesPhysics is true
	virtual bool registerCollision(GameObject* collidedObject);
	/// Notify the object it has hit the edge of the level. Responding improperly to this can cause out of bounds errors
	virtual bool registerWallCollision();
	/// Set the GameObject's sprite, and load the collision outline if it exists. If it doesn't, regenerate and save it.
	//* The resource is a relative filename to an image (without the extension). e.g. "Ammo\\test"
	//void setSprite(char* resource, bool bBG = false);


	/// If Newtonian physics is enabled for the world, this imparts a force on the object
	void applyForceRect(float x, float y);
	/// If Newtonian physics is enabled for the world, this imparts a force on the object
	void applyForcePolar(float heading, float magnitude);

	float getXPosition() const
	{
		return location.x;
	}
	float getYPosition() const
	{
		return location.y;
	}

	void setBrain(const char* bt)
	{
		log("------>setBrain:%s\n", bt);
		bool bRet = this->btload(bt);
		if (!bRet)
			log("error in btload %s\n", bt);
		else
			log("success in btload %s\n", bt);
		this->btsetcurrent(bt);
		this->btexec();
	}

	int getHealth() const;
	void setHealth(unsigned int hp);
	Sprite * setSprite(const std::string& filename);
	bool collideWith(GameObject* other) const;

	/// True if this object is the player. Undefined behavior if more than one object has this flag set to true.
	bool isPlayer;
	/// Determines whether the object collides with others
	bool usesPhysics;

	/// Number of milliseconds the object has been in existence. Updated every tick based on the timeElapsed
	//long age;
	long age;

	/// The way the object's sprite is "turned"
	float displayHeading;
	/// Absolute coordinates of the object in the world.
	Vec2 location;

	GameObject* owner; //Generally the object that created this object, if any

	/// The scalar component of the object's acceleration
	float accelMagnitude;

	/// The human friendly name of the object
	std::string displayName;
	/// Used to divide objects into different categories to customize interactions between them
	int faction;

public:
	/// Unique for each object instance
	int ID;
	/// Generate a unique ID for an object
	/*
	static int getID()
	{
		IDCount++;
		return IDCount;
	}
	*/

	/// The number of "hit points" the object has.
	unsigned int HP;

	/// The directional component of the object's velocity
	float movementHeading;

	/// The directional component of the object's acceleration
	float accelHeading;

	/// Am I facing the player
	bool alignedWithPlayer() const;
	/// Is the player facing me
	bool playerIsAligned() const;
	bool projectileNearby(float radius) const;
	float distanceToPlayer() const;

	void GoStraight(int speed);
	int TurnTowardsTarget(float turnSpeed);


};

#endif
