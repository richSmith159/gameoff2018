#include "SpriteSystem.h"

#include <iostream>


SpriteSystem::SpriteSystem() {
	// empty
}


SpriteSystem::~SpriteSystem() {
	// empty
}

void SpriteSystem::run(float deltaTime) {
	m_renderer->begin(m_cameraHandle);
	std::cout << m_components.size() << std::endl;
	for (unsigned int i = 0; i < m_components.size(); i++) {
		m_renderer->render(&m_components[i]);
	}
	m_renderer->end();
}

void SpriteSystem::initSystem(Tempest::Camera2D* camera) {
	m_renderer->init();
	m_cameraHandle = camera;
}

SpriteComponent* SpriteSystem::addComponent(Tempest::glTexture texture, Tempest::ColorRGBA8 color, float width, float height) {
	m_components.emplace_back(texture, color, width, height);
	return &m_components.back();
}

void SpriteSystem::removeComponent() {
	// empty
}
