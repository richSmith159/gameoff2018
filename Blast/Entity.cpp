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
