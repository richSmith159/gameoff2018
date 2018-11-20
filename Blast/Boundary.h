#pragma once
#include "Entity.h"

#include <Tempest\GLObjects.h>
#include <glm\glm\glm.hpp>


class Boundary : public Entity
{
public:
	Boundary();
	~Boundary();

	// init the circular boundary
	void init(glm::vec2 position, float size, float decreaseRate, Tempest::glTexture texture);

	// calculations
	bool isWithinBoundary(const glm::vec2& position);
	void update(float deltaTime);

private:

	float m_decreaseRate;
	
};
