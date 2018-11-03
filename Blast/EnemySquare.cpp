#include "EnemySquare.h"

#include <iostream>

#include <Tempest\ResourceManager.h>



EnemySquare::EnemySquare() {
	// empty
}


EnemySquare::~EnemySquare() {
	// empty
}

void EnemySquare::init(glm::vec2 position, float health, float speed, Player * player) {
	m_position = position;
	m_health = health;
	m_speed = speed;
	m_playerTarget = player;
	m_texture = Tempest::ResourceManager::getTexture("Assets/Textures/Entities/square.png");
	m_width = 16;
	m_height = 16;
	m_color = Tempest::ColorRGBA8(255, 255, 255, 255);
}

void EnemySquare::update(float deltaTime) {
	m_direction = glm::normalize(m_playerTarget->getCenterPosition() - getCenterPosition());
	m_position += m_direction * m_speed * deltaTime;
	std::cout << m_speed << std::endl;
}
