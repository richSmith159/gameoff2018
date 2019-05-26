#include "Miner.h"
#include <Tempest\ResourceManager.h>


Miner::Miner() {
	// empty
}


Miner::~Miner() {
	// empty
}

void Miner::init(std::string name, int initialHealth, float speed, glm::vec2 initialPosition, glm::vec2 direction) {
	m_name = name;
	m_health = initialHealth;
	m_speed = speed;
	m_position = initialPosition;
	m_direction = direction;
	m_texture = Tempest::ResourceManager::getTexture("Textures/test.png");
}

void Miner::update(float deltaTime) {

}
