#pragma once

#include <Tempest\GLObjects.h>

#include <glm\glm\glm.hpp>

class Entity
{
public:
	Entity();
	~Entity();

	// getters
	glm::vec2 getPosition() { return m_position; }
	glm::vec2 getDirection() { return m_direction; }

	// setters
	void setPosition(const glm::vec2& newPosition) { m_position = newPosition; }
	void setDirection(const glm::vec2& newDirection) { m_direction = newDirection; }

protected:
	
	glm::vec2 m_position;
	glm::vec2 m_direction;
	Tempest::ColorRGBA8 m_color;
	Tempest::glTexture m_texture; /* TODO: animated sprites */
	glm::vec4 m_uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

};

