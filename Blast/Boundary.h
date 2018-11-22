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

	// setters
	void scale(const float& scale) { m_height *= scale; m_width *= scale; }
	void resize(const glm::vec2& offset) { m_width += offset.x; m_height += offset.y; }

	// calculations
	bool isWithinBoundary(const glm::vec2& position);
	void update(float deltaTime);

private:

	float m_decreaseRate;
	
};
