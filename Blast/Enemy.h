#pragma once
#include "Entity.h"
#include "Player.h"

#include <Box2D\Box2D.h>


class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();
	virtual void init(glm::vec2 position, float health, float speed, Player* player, b2World* physicsWorld) = 0;
	virtual void update(float deltaTime) = 0;

	// getters
	float getSpeed() { return m_speed; }
	float getHealth() { return m_health; }

	// setters
	void setHealth(const float& newHealth) { m_health = newHealth; }
	void setSpeed(const float& newSpeed) { m_speed = newSpeed; }

	void applyDamage(float damage) { m_health -= damage; }
	bool isDestroyed() { return m_health <= 0; }

protected:

	float m_health;
	float m_speed;
	Player* m_playerTarget;

};

