#pragma once

#include <Tempest\Camera2D.h>
#include <Tempest\GLSLProgram.h>
#include <Tempest\GLShader.h>
#include <Tempest\SpriteBatch.h>


class SimpleRenderer
{
public:
	SimpleRenderer();
	~SimpleRenderer();

	void init();
	void begin(Tempest::Camera2D* camera);
	void render(glm::vec4 destRect, glm::vec4 uvRect, int textureID, float depth, Tempest::ColorRGBA8 color, float angle);
	void end();

private:
	Tempest::SpriteBatch m_spriteBatch;
	Tempest::GLShader m_vertexShader;
	Tempest::GLShader m_fragmentShader;
	Tempest::GLSLProgram m_program;
};

