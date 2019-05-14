#include "PhysicsComponent.h"



PhysicsComponent::PhysicsComponent(b2BodyType bodyType, glm::vec2 boundingDims, float xPos, float yPos, float angle, b2World* physicsWorldHandle) {
	b2BodyDef def;
	def.type = bodyType;
	def.position.Set(xPos, yPos);
	def.angle = angle;
	m_physicsWorldHandle = physicsWorldHandle;
	m_body = m_physicsWorldHandle->CreateBody(&def);
	
	// init physics fixtures
	b2PolygonShape squareShape;
	b2FixtureDef fixtureDef;
	squareShape.SetAsBox(boundingDims.x, boundingDims.y);
	fixtureDef.shape = &squareShape;
	m_fixtures[0] = m_body->CreateFixture(&fixtureDef);
}


PhysicsComponent::~PhysicsComponent() {
	// empty
}


void PhysicsComponent::onInsert() {
	// TODO: implement
}

void PhysicsComponent::onRemove() {
	// TODO: implement
}