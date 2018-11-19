#pragma once
#include "Entity.h"

#include <Tempest\GLObjects.h>

#include <glm\glm\glm.hpp>


class Bullet : public Entity
{
public:
	Bullet(
		b2World* world,
		glm::vec2 startPosition,
		glm::vec2 direction,
		Tempest::glTexture texture,
		float width,
		float height,
		float damage,
		float speed,
		float range
	);
	~Bullet();

	void update(float deltaTime);
	
	// getters
	float getSpeed() { return m_speed; }
	float getDamage() { return m_damage; }
	bool getCollided() { return m_collided; }

	// setters
	void setCollided(const bool& collided) { m_collided = collided; }

	// calculations
	bool outOfRange();

private:
	float m_speed;
	float m_range;
	float m_damage;
	bool m_collided = false;
	glm::vec2 m_startPosition;

};
