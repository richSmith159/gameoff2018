#pragma once
#include "Entity.h"

#include <Tempest\GLObjects.h>

#include <glm\glm\glm.hpp>

class Bullet : public Entity
{
public:
	Bullet(
		glm::vec2 startPosition,
		glm::vec2 direction,
		Tempest::glTexture texture,
		float damage,
		float speed,
		float range
	);
	~Bullet();

	void update(float deltaTime);
	bool outOfRange();


	// gettters
	float getSpeed() { return m_speed; }
	float getDamage() { return m_damage; }

private:
	float m_speed;
	float m_damage;
	glm::vec2 m_startPosition;
	float m_range;

};
