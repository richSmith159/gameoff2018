#include "SpriteSystem.h"
#include "PhysicsComponent.h"
#include <Tempest\Camera2D.h>
#include <iostream>


SpriteSystem::SpriteSystem() {
	// empty
}


SpriteSystem::~SpriteSystem() {
	// empty
}

void SpriteSystem::run(float deltaTime) {
	m_renderer->begin(m_cameraHandle);
	for (unsigned int i = 0; i < m_components.size(); i++) {
		m_renderer->render(m_components[i]);
	}
	m_renderer->end();
}

void SpriteSystem::initSystem(Tempest::Camera2D* camera) {
	m_renderer->init();
	m_cameraHandle = camera;
}

SpriteComponent* SpriteSystem::addComponent(Tempest::glTexture texture, Tempest::ColorRGBA8 color, float width, float height) {
	SpriteComponent* component = new SpriteComponent(texture, color, width, height);
	m_components.push_back(component);
	return component;
}

void SpriteSystem::removeComponent() {
	// empty
}