#include "EnemySquare.h"

#include <iostream>

#include <Tempest\ResourceManager.h>

#include <glm\glm\gtx\vector_angle.hpp>



EnemySquare::EnemySquare() {
	// empty
}


EnemySquare::~EnemySquare() {
	// empty
}

void EnemySquare::init(glm::vec2 position, float health, float speed, Player * player, b2World* physicsWorld) {

	// set member variables
	m_position = position;
	m_health = health;
	m_speed = speed;
	m_playerTarget = player;
	m_texture = Tempest::ResourceManager::getTexture("Assets/Textures/Entities/square.png");
	m_width = 16;
	m_height = 16;
	m_color = Tempest::ColorRGBA8(255, 255, 255, 255);

	// init physics body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(m_position.x, m_position.y);
	bodyDef.fixedRotation = false;
	bodyDef.angle = 0;
	m_body = physicsWorld->CreateBody(&bodyDef);

	// init physics fixtures
	b2PolygonShape squareShape;
	squareShape.SetAsBox(m_width * 0.5f, m_height * 0.5f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &squareShape;
	m_fixtures[0] = m_body->CreateFixture(&fixtureDef);

	m_collisionObjectType = COLLISION_OBJECT_TYPE::ENEMY;


}

void EnemySquare::update(float deltaTime) {
	glm::vec2 centerPosition = getCenterPosition();
	m_direction = glm::normalize(m_playerTarget->getCenterPosition() - centerPosition);
	m_position += m_direction * m_speed * deltaTime;
	orientPhysicsBodyToDirection(centerPosition);
}
