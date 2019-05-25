#include "Miner.h"



Miner::Miner()
{
}


Miner::~Miner()
{
}

void Miner::init(std::string name, int initialHealth, float speed, glm::vec2 initialPosition, glm::vec2 direction, Tempest::glTexture texture) {
	m_name = name;
	m_health = initialHealth;
	m_speed = speed;
	m_position = initialPosition;
	m_direction = direction;
	m_texture = texture;
}

void Miner::update(float deltaTime) {

}
