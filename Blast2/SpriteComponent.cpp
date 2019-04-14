#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include <Box2D\Box2D.h>

#include <iostream>



SpriteComponent::SpriteComponent(Tempest::glTexture texture, Tempest::ColorRGBA8 color, float width, float height) {
	m_width = width;
	m_height = height;
	m_texture = texture;
	m_color = color;
}

SpriteComponent::~SpriteComponent() {
	// empty
}

void SpriteComponent::onInsert() {
	// TODO: implement
}

void SpriteComponent::onRemove() {
	// TODO: implement
}

glm::vec4 SpriteComponent::calculateDestRect() {
	if (m_entity != nullptr) {
		if (m_entity->m_physicsComponent != nullptr) {
			std::cout << m_entity->m_physicsComponent->lol << std::endl;
			b2Vec2 bodyPosition = m_entity->m_physicsComponent->m_body->GetPosition();
			return glm::vec4(
				bodyPosition.x - (m_width * 0.5),
				bodyPosition.y - (m_height * 0.5),
				m_width,
				m_height
			);
		}
	}
	return glm::vec4(0.0f);
}
