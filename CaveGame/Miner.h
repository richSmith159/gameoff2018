#pragma once

#include "CaveMap.h"
#include "Character.h"

#include <string>

class Miner : public Character
{
public:
	Miner();
	~Miner();

	void init(
		std::string name,
		int initialHealth,
		float speed,
		glm::vec2 initialPosition,
		glm::vec2 direction,
		Tempest::glTexture texture
	);
	void setTarget(Cell* newTarget) { m_target = newTarget; }
	void update(float deltaTime);

private:
	Cell * m_target;
};

