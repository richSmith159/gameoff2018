#include "PhysicsSystem.h"



PhysicsSystem::PhysicsSystem() {
	// empty
}


PhysicsSystem::~PhysicsSystem() {
	// empty
}

void PhysicsSystem::initSystem(float gravityX, float gravityY) {
	// init simple physics
	const b2Vec2 gravity(gravityX, gravityY);
	m_world = std::make_unique<b2World>(gravity);
}

void PhysicsSystem::run(float deltaTime) {
	m_world->Step(1.0f / 60.0f, 6, 2);
}

PhysicsComponent* PhysicsSystem::addComponent(b2BodyType bodyType, float xPos, float yPos, float angle) {
	PhysicsComponent* component = new PhysicsComponent(bodyType, xPos, yPos, angle, m_world.get());
	m_components.push_back(component);
	return component;
}
