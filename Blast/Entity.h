#pragma once

#include <Tempest\GLObjects.h>

#include <Box2D\Box2D.h>
#include <glm\glm\glm.hpp>

class Entity
{
public:
	Entity();
	~Entity();

	// getters
	glm::vec2 getPosition() { return m_position; }
	glm::vec2 getDirection() { return m_direction; }
	int getTextureId() { return m_texture.id; }
	glm::vec4 getUVRect() { return m_uvRect; }
	Tempest::ColorRGBA8 getColor() { return m_color; }
	glm::vec2 getCenterPosition();
	b2Body* getBody() { return m_body; }

	// setters
	void setPosition(const glm::vec2& newPosition) { m_position = newPosition; }
	void setDirection(const glm::vec2& newDirection) { m_direction = newDirection; }
	void setTexture(Tempest::glTexture newTexture) { m_texture = newTexture; }

	// calculations
	glm::vec4 calculateDestRect() { return glm::vec4(m_position.x, m_position.y, m_width, m_height); }


protected:

	void orientPhysicsBodyToDirection(glm::vec2 centerPosition);
	
	glm::vec2 m_position;
	glm::vec2 m_direction;
	Tempest::ColorRGBA8 m_color;
	Tempest::glTexture m_texture; /* TODO: animated sprites */
	glm::vec4 m_uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	float m_width;
	float m_height;

	b2Body* m_body = nullptr;
	b2Fixture* m_fixtures[3];

};

