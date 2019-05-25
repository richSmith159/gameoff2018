#include "Character.h"



Character::Character() {
	// empty
}


Character::~Character() {
	// empty
}

void Character::applyDamage(int damage) {
	m_health -= damage;
	if (m_health <= 0) {
		m_dead = true;
	}
}

void Character::applyHealth(int health) {
	m_health += health;
	if (m_health < MAX_CHARACTER_HEALTH) {
		m_health = MAX_CHARACTER_HEALTH;
	}
}

glm::vec4 Character::calculateDestRect()
{
	return glm::vec4(
		m_position.x,
		m_position.y,
		CHARACTER_WIDTH,
		CHARACTER_WIDTH
	);
}
