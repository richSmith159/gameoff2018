#include "Entity.h"


Entity::Entity() {
	// empty
}

Entity::~Entity() {
	// empty
}

glm::vec2 Entity::getCenterPosition() {
	return m_position + glm::vec2(m_width * 0.5f, m_height * 0.5f);
}

void Entity::orientPhysicsBodyToDirection(glm::vec2 centerPosition) {
	float angle = atan2f(-m_direction.x, m_direction.y);
	m_body->SetTransform(b2Vec2(centerPosition.x, centerPosition.y), angle);
}
