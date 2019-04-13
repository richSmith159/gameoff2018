#include "EnemyCircle.h"
#include <Tempest\ResourceManager.h>

#include <glm\glm\gtx\perpendicular.hpp>


EnemyCircle::EnemyCircle(glm::vec2 position, float health, float speed, Player* player, b2World* physicsWorld) {
	
	// set member variables
	m_position = position;
	m_health = health;
	m_speed = speed;
	m_playerTarget = player;
	m_texture = Tempest::ResourceManager::getTexture("Assets/Textures/Entities/circle.png");
	m_width = 16;
	m_height = 16;
	m_color = Tempest::ColorRGBA8(255, 255, 255, 255);
	m_collisionObjectType = COLLISION_OBJECT_TYPE::ENEMY;

	// init physics body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(m_position.x, m_position.y);
	bodyDef.angle = 0;
	// bodyDef.userData = (Entity*)this;
	bodyDef.userData = static_cast<Entity*>(this);
	bodyDef.fixedRotation = false;
	m_body = physicsWorld->CreateBody(&bodyDef);
	
	// Create the circles
	b2CircleShape circleShape;
	circleShape.m_radius = m_width / 2.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;

	m_fixtures[0] = m_body->CreateFixture(&fixtureDef);

}


EnemyCircle::~EnemyCircle() {
	// empty
}

void EnemyCircle::update(float deltaTime) {
	b2Vec2 bodyPosition = m_body->GetPosition();
	m_direction = glm::normalize(m_playerTarget->getCenterPosition() - glm::vec2(bodyPosition.x, bodyPosition.y));
	float angle = atan2f(-m_direction.x, m_direction.y);
	glm::vec2 velocity = glm::vec2(m_speed, m_speed) * m_direction;
	glm::vec2 tangentVelocity = glm::perp(velocity, m_direction);

	m_body->SetTransform(bodyPosition, angle);
	m_body->ApplyLinearImpulseToCenter(b2Vec2(velocity.x, velocity.y), true);
	m_body->ApplyLinearImpulseToCenter(b2Vec2(tangentVelocity.x, tangentVelocity.y), true);
	
}
