#include "Bullet.h"


Bullet::Bullet(
	glm::vec2 startPosition,
	glm::vec2 direction,
	Tempest::glTexture texture,
	float damage,
	float speed,
	float range) {
	m_position = startPosition;
	m_startPosition = startPosition;
	m_texture = texture;
	m_damage = damage;
	m_speed = speed;
	m_range = range;
}


Bullet::~Bullet() {
	// empty
}

void Bullet::update(float deltaTime) {
	m_position += m_direction * m_speed * deltaTime;
}

bool Bullet::outOfRange() {
	return glm::length(glm::distance(m_position, m_startPosition)) > m_range;
}
