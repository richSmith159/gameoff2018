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
	m_position = startPosition;
	m_startPosition = startPosition;
	m_direction = direction;
	m_texture = texture;
	m_damage = damage;
	m_speed = speed;
	m_range = range;
	m_width = width;
	m_height = height;
	m_color = Tempest::ColorRGBA8(255, 255, 255, 255);

	// Make the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(m_position.x, m_position.y);
	bodyDef.fixedRotation = true;
	bodyDef.angle = 0;
	bodyDef.userData = this;
	m_body = world->CreateBody(&bodyDef);

	// Create the box
	b2PolygonShape boxShape;
	boxShape.SetAsBox(m_height * 0.4f, m_width * 0.5f);

	b2FixtureDef boxDef;
	boxDef.shape = &boxShape;
	m_fixtures[0] = m_body->CreateFixture(&boxDef);

	m_collided = false;

	m_collisionObjectType = COLLISION_OBJECT_TYPE::BULLET;

}


Bullet::~Bullet() {
	// empty
}

void Bullet::update(float deltaTime) {
	glm::vec2 centerPosition = getCenterPosition();
	m_position += m_direction * m_speed * deltaTime;
	orientPhysicsBodyToDirection(centerPosition);
	// m_color.a *= 0.99999f;
}

bool Bullet::outOfRange() {
	return glm::length(glm::distance(m_position, m_startPosition)) > m_range;
}