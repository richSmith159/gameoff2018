#pragma once
#include "Entity.h"
#include "Player.h"

#include <Box2D\Box2D.h>


class Enemy : public Entity
{
public:
	Enemy();
	virtual ~Enemy();
	// virtual void init(glm::vec2 position, float health, float speed, Player* player, b2World* physicsWorld) = 0;
	virtual void update(float deltaTime) = 0;

	// getters
	float getSpeed() { return m_speed; }
	float getHealth() { return m_health; }

	// setters
	void setSpeed(const float& newSpeed) { m_speed = newSpeed; }
	void setHealth(const float& newHealth) { m_health = newHealth; }
	
	// calculations
	bool isDestroyed() { return m_health <= 0; }
	void applyDamage(float damage) { m_health -= damage; }
	
protected:

	float m_health;
	float m_speed;
	Player* m_playerTarget;
	COLLISION_OBJECT_TYPE m_collisionObjectType = COLLISION_OBJECT_TYPE::ENEMY;
	
};
