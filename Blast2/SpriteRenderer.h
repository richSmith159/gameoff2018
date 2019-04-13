#pragma once

#include <Tempest\Camera2D.h>
#include <Tempest\GLSLProgram.h>
#include <Tempest\GLShader.h>
#include <Tempest\SpriteBatch.h>

#include "SpriteComponent.h"

class SpriteRenderer
{
public:
	SpriteRenderer();
	~SpriteRenderer();

	void init();
	void begin(Tempest::Camera2D* activeCamera);
	void render(SpriteComponent* component);
	void end();

private:

	Tempest::SpriteBatch m_spriteBatch;
	Tempest::GLShader m_vertexShader;
	Tempest::GLShader m_fragmentShader;
	Tempest::GLSLProgram m_program;

};
