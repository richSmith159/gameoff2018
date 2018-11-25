#pragma once

#include <Tempest\GLObjects.h>

#include <Box2D\Box2D.h>
#include <glm\glm\glm.hpp>


enum class COLLISION_OBJECT_TYPE {BULLET = 1, ENEMY = 2, PLAYER = 3};

class Entity
{
public:
	Entity();
	virtual ~Entity();

	// getters
	float getWidth() { return m_width; }
	float getHeight() { return m_height; }
	glm::vec4 getUVRect() { return m_uvRect; }
	int getTextureId() { return m_texture.id; }
	glm::vec2 getPosition() { return m_position; }
	glm::vec2 getDirection() { return m_direction; }
	Tempest::ColorRGBA8 getColor() { return m_color; }
	b2Body* getBody() { return m_body; }
	b2Fixture* getFixture(const int& index) { return m_fixtures[index]; }
	COLLISION_OBJECT_TYPE getCollisionObjectType() { return m_collisionObjectType; }

	// setters
	void setPosition(const glm::vec2& newPosition) { m_position = newPosition; }
	void setDirection(const glm::vec2& newDirection) { m_direction = newDirection; }
	void setTexture(Tempest::glTexture newTexture) { m_texture = newTexture; }

	// calculations
	glm::vec2 getCenterPosition();
	glm::vec4 calculateDestRect();

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
	COLLISION_OBJECT_TYPE m_collisionObjectType;

};
