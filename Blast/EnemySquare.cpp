#include "EnemySquare.h"
#include <iostream>
#include <Tempest\ResourceManager.h>
#include <glm\glm\gtx\vector_angle.hpp>
#include <Box2D\Box2D.h>



EnemySquare::EnemySquare(glm::vec2 position, float health, float speed, Player * player, b2World* physicsWorld) {

	// set member variables
	m_position = position;
	m_health = health;
	m_speed = speed;
	m_playerTarget = player;
	m_texture = Tempest::ResourceManager::getTexture("Assets/Textures/Entities/square.png");
	m_width = 16;
	m_height = 16;
	m_color = Tempest::ColorRGBA8(255, 255, 255, 255);
	m_collisionObjectType = COLLISION_OBJECT_TYPE::ENEMY;
	std::cout << "initial: " << static_cast<std::underlying_type<COLLISION_OBJECT_TYPE>::type>(m_collisionObjectType) << std::endl;
	
	// init physics body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(m_position.x, m_position.y);
	bodyDef.angle = 0;
	// bodyDef.userData = (Entity*)this;
	bodyDef.userData = static_cast<Entity*>(this);
	bodyDef.fixedRotation = false;
	m_body = physicsWorld->CreateBody(&bodyDef);

	// init physics fixtures
	b2PolygonShape squareShape;
	b2FixtureDef fixtureDef;
	squareShape.SetAsBox(m_width * 0.5f, m_height * 0.5f);
	fixtureDef.shape = &squareShape;
	m_fixtures[0] = m_body->CreateFixture(&fixtureDef);

}


EnemySquare::~EnemySquare() {
	// empty
}
/*
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
	m_collisionObjectType = COLLISION_OBJECT_TYPE::ENEMY;
	std::cout << "initial: " << static_cast<std::underlying_type<COLLISION_OBJECT_TYPE>::type>(m_collisionObjectType) << std::endl;
	// init physics body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(m_position.x, m_position.y);
	bodyDef.angle = 0;
	// bodyDef.userData = (Entity*)this;
	bodyDef.userData = static_cast<Entity*>(this);
	bodyDef.fixedRotation = false;
	m_body = physicsWorld->CreateBody(&bodyDef);

	// init physics fixtures
	b2PolygonShape squareShape;
	b2FixtureDef fixtureDef;
	squareShape.SetAsBox(m_width * 0.5f, m_height * 0.5f);
	fixtureDef.shape = &squareShape;
	m_fixtures[0] = m_body->CreateFixture(&fixtureDef);
	
}
*/
void EnemySquare::update(float deltaTime) {
	b2Vec2 bodyPosition = m_body->GetPosition();
	m_direction = glm::normalize(m_playerTarget->getCenterPosition() - glm::vec2(bodyPosition.x, bodyPosition.y));
	float angle = atan2f(-m_direction.x, m_direction.y);
	glm::vec2 velocity = glm::vec2(m_speed, m_speed) * m_direction;
	
	m_body->SetTransform(bodyPosition, angle);
	m_body->ApplyForceToCenter(b2Vec2(velocity.x, velocity.y), true);
}
