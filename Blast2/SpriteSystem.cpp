#include "SpriteSystem.h"



SpriteSystem::SpriteSystem() {
	// empty
}


SpriteSystem::~SpriteSystem() {
	// empty
}

void SpriteSystem::run(float deltaTime) {
	m_renderer->begin(m_cameraHandle);
	for (unsigned int i = 0; i < m_components.size(); i++) {
		m_renderer->render(&m_components[i]);
	}
}

void SpriteSystem::initSystem(Tempest::Camera2D* camera) {
	m_renderer->init();
	m_cameraHandle = camera;
}

void SpriteSystem::addComponent(Tempest::glTexture texture, Tempest::ColorRGBA8 color, float width, float height) {
	m_components.emplace_back(texture, color, width, height);
}

void SpriteSystem::removeComponent() {
	// empty
}
