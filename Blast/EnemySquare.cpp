#include "EnemySquare.h"

#include <Tempest\ResourceManager.h>



EnemySquare::EnemySquare() {
	// empty
}


EnemySquare::~EnemySquare() {
	// empty
}

void EnemySquare::init(glm::vec2 position, int health, int speed, Player * player) {
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
	// empty
}
