#pragma once
#include "Bullet.h"
#include "Entity.h"
#include "EnemySquare.h"
#include "Player.h"
#include "Boundary.h"

#include <Tempest\Camera2D.h>
#include <Tempest\GLSLProgram.h>
#include <Tempest\GLShader.h>
#include <Tempest\SpriteBatch.h>


class EntityRenderer
{
public:
	EntityRenderer();
	~EntityRenderer();

	void init();
	void begin(Tempest::Camera2D* activeCamera);
	void render(Entity* entity);
	void render(Player* player);
	void render(EnemySquare* enemy);
	void render(Bullet* bullet);
	void render(Boundary* boundary);
	void end();

private:

	Tempest::SpriteBatch m_spriteBatch;
	Tempest::GLShader m_vertexShader;
	Tempest::GLShader m_fragmentShader;
	Tempest::GLSLProgram m_program;

};

