#pragma once

#include "Bullet.h"
#include "EnemySquare.h"

#include <Tempest\Camera2D.h>
#include <Tempest\GLObjects.h>
#include <Tempest\GLSLProgram.h>
#include <Tempest\GLShader.h>

#include <Box2D\Box2D.h>
#include <vector>
#include <glm\glm\glm.hpp>

const float PI = 3.1415926f;

struct DebugVertex {
	glm::vec2 position;
	Tempest::ColorRGBA8 color;
};

class PhysicsRenderer
{
public:
	PhysicsRenderer();
	~PhysicsRenderer();

	void init();
	void begin(Tempest::Camera2D* activeCamera);
	void drawEnemySquare(EnemySquare* square, Tempest::ColorRGBA8 color);
	void drawCircle(const glm::vec2& center, const Tempest::ColorRGBA8& color, float radius);
	void drawBulletCapsule(Bullet* bullet, Tempest::ColorRGBA8 color);
	void render();
	void end();
	void dispose();

private:

	void drawSquareFromFixture(b2Fixture* fixture, b2Body* body, Tempest::ColorRGBA8 color);
	void drawCapsule(b2Body* body, Tempest::ColorRGBA8 color, float rectHeight, float radius, glm::vec2 centerPosition);

	Tempest::GLShader m_vertexShader;
	Tempest::GLShader m_fragmentShader;
	Tempest::GLSLProgram m_program;
	std::vector<DebugVertex> m_verts;
	std::vector<GLuint> m_indices;
	GLuint m_vbo = 0, m_vao = 0, m_ibo = 0;
	int m_numElements = 0;
	float m_lineWidth = 0.1f;
};
