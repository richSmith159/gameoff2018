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
		glm::vec2 direction
	);

	
	void update(float deltaTime);
	
	Cell* getTarget() { return m_target; }
	int getMaxCarryingCapacity() { return m_maxCarryingCapacity; }
	int getCurrentlyCarrying() { return m_currentlyCarrying; }
	
	void setTarget(Cell* newTarget) { m_target = newTarget; }
	void setMaxCarryingCapacity(int newCapacity) { m_maxCarryingCapacity = newCapacity; }
	void setCurrentlyCarrying(int amount) { m_currentlyCarrying = amount; }

	void offsetCurrentlyCarrying(int offset) { m_currentlyCarrying += offset; }
	bool isAtCapacity() { return m_currentlyCarrying >= m_maxCarryingCapacity; }
	
private:
	Cell * m_target;
	int m_maxCarryingCapacity = 100;
	int m_currentlyCarrying = 0;
};

