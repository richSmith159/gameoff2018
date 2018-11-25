#include "Bullet.h"

#include <iostream>


Bullet::Bullet(
	b2World* world,
	glm::vec2 startPosition,
	glm::vec2 direction,
	Tempest::glTexture texture,
	float width,
	float height,
	float damage,
	float speed,
	float range
) {
	m_speed = speed;
	m_range = range;
	m_width = width;
	m_height = height;
	m_damage = damage;
	m_collided = false;
	m_texture = texture;
	m_direction = direction;
	m_position = startPosition;
	m_startPosition = startPosition;
	m_color = Tempest::ColorRGBA8(255, 255, 255, 255);
	m_collisionObjectType = COLLISION_OBJECT_TYPE::BULLET;

	// Make the body
	b2BodyDef bodyDef;
	bodyDef.angle = 0;
	bodyDef.userData = (Entity*)this;
	bodyDef.fixedRotation = false;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(m_position.x, m_position.y);
	
	m_body = world->CreateBody(&bodyDef);

	// Create the box
	b2PolygonShape boxShape;
	boxShape.SetAsBox(m_height * 0.4f, m_width * 0.5f);

	// Create the fixture
	b2FixtureDef boxDef;
	boxDef.shape = &boxShape;
	m_fixtures[0] = m_body->CreateFixture(&boxDef);
	
	// Set velocity and angle (these properties should not change)
	glm::vec2 initialVelocity = glm::vec2(m_speed) * m_direction;
	m_body->SetLinearVelocity(b2Vec2(initialVelocity.x, initialVelocity.y));
	m_body->SetTransform(m_body->GetPosition(), atan2f(-m_direction.x, m_direction.y));
}

Bullet::~Bullet() {
	// empty
}

void Bullet::update(float deltaTime) {
	// empty
}

bool Bullet::outOfRange() {
	b2Vec2 bodyPosition = m_body->GetPosition();
	return glm::length(glm::distance(glm::vec2(bodyPosition.x, bodyPosition.y), m_startPosition)) > m_range;
}