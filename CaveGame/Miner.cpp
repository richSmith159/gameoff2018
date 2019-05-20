#include "Miner.h"



Miner::Miner()
{
}


Miner::~Miner()
{
}

void Miner::init(std::string name, glm::vec2 initialPosition) {
	m_name = name;
	m_position = initialPosition;
}

void Miner::update(float deltaTime) {

}
